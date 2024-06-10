package frameworks

import (
	"analyzer/pkg/datastores"
	"analyzer/pkg/logger"
	"analyzer/pkg/types"
	"analyzer/pkg/utils"
	"strings"

	"github.com/blueprint-uservices/blueprint/blueprint/pkg/ir"
	"github.com/blueprint-uservices/blueprint/plugins/cmdbuilder"
	"github.com/blueprint-uservices/blueprint/plugins/golang"
	"github.com/blueprint-uservices/blueprint/plugins/golang/gocode"
	"github.com/blueprint-uservices/blueprint/plugins/rabbitmq"
	"github.com/blueprint-uservices/blueprint/plugins/redis"
	"github.com/blueprint-uservices/blueprint/plugins/workflow"
	"github.com/blueprint-uservices/blueprint/plugins/workflow/workflowspec"

	fb_specs "github.com/blueprint-uservices/blueprint/examples/foobar/wiring/specs"
	pn_specs "github.com/blueprint-uservices/blueprint/examples/postnotification/wiring/specs"
)

func BuildBlueprintAppInfo(appName string) ([]*types.ServiceInfo, []datastores.DatabaseInstance, []string) {
	var spec cmdbuilder.SpecOption
	if appName == "postnotification" {
		spec = pn_specs.Docker
	} else if appName == "foobar" {
		spec = fb_specs.Docker
	} else {
		logger.Logger.Fatalf("unknown application %s", appName)
	}

	servicesSpec, databasesNodes, frontends := BuildAndInspectIR(appName, spec)
	servicesInfo := buildBlueprintServicesInfo(servicesSpec)
	databasesInfo := buildDatabasesInstances(databasesNodes)
	return servicesInfo, databasesInfo, frontends
}

func findConstructorFromSpec(spec *workflowspec.Service) *gocode.Func {
	for _, pkg := range spec.Iface.File.Package.Module.Packages {
		for _, f := range pkg.Funcs {
			if workflowspec.IsConstructorOfIface(f, spec.Iface) {
				return &f.Func
			}
		}
	}
	logger.Logger.Fatalf("could not find constructor name from spec")
	return nil
}

func getUniqueName(name string) string {
	// remove .client suffix (e.g. notification_queue.client)
	splits := strings.Split(name, ".")[0]
	if len(splits) > 0 {
		return strings.Split(name, ".")[0]
	}
	return ""
}

func buildBlueprintServicesInfo(appSpecs map[*workflowspec.Service][]golang.Service) []*types.ServiceInfo {
	var services []*types.ServiceInfo
	for spec, serviceArgs := range appSpecs {
		constructorMethod := findConstructorFromSpec(spec)
		serviceInfo := &types.ServiceInfo{
			Name:            spec.Iface.Name,
			Filepath:        spec.Iface.File.Name,
			ConstructorName: constructorMethod.GetName(),
			ConstructorDBs:  make(map[string]string),
		}
		for _, method := range spec.Iface.Ast.Methods.List {
			serviceInfo.Methods = append(serviceInfo.Methods, method.Names[0].Name)
		}
		constructorArgs := constructorMethod.GetArguments()
		for idx, serviceArg := range serviceArgs {
			constructorMethod.GetArguments()
			if _, isServiceIR := serviceArg.(*workflow.WorkflowClient); !isServiceIR {
				// service spec args does not count with context at index 0
				constructorArg := constructorArgs[idx+1]
				serviceInfo.ConstructorDBs[constructorArg.GetName()] = getUniqueName(serviceArg.Name())
			}
		}
		for _, arg := range serviceArgs {
			if workflowClient, ok := arg.(*workflow.WorkflowClient); ok {
				serviceInfo.Edges = append(serviceInfo.Edges, getUniqueName(workflowClient.ServiceType))
			}
		}
		services = append(services, serviceInfo)
	}
	return services
}

func buildDatabasesInstances(databases map[string]ir.IRNode) []datastores.DatabaseInstance {
	var dbInstances []datastores.DatabaseInstance
	for name, node := range databases {
		name = getUniqueName(name)
		switch node.(type) {
		case *redis.RedisGoClient:
			dbInstances = append(dbInstances, &CacheInstance{
				BlueprintDatabaseInstance: BlueprintDatabaseInstance{
					Name: name,
					//FIXME, we can have many replicas
					Datastore: &datastores.Datastore{
						Type: datastores.Cache,
						Kind: datastores.Redis,
						Name: name,
						Schema: &datastores.Schema{},
					},
				},
			})
		case *rabbitmq.RabbitmqGoClient:
			dbInstances = append(dbInstances, &QueueInstance{
				BlueprintDatabaseInstance: BlueprintDatabaseInstance{
					Name: name,
					//FIXME, we can have many replicas
					Datastore: &datastores.Datastore{
						Type: datastores.Queue,
						Kind: datastores.RabbitMQ,
						Name: name,
						Schema: &datastores.Schema{},
					},
				},
			})
		default:
			logger.Logger.Warnf("unknown type for database instance: %s (type = %s)", name, utils.GetType(node))
			continue
		}
	}
	return dbInstances
}
