package blueprint

import (
	"strings"

	"github.com/blueprint-uservices/blueprint/blueprint/pkg/ir"
	"github.com/blueprint-uservices/blueprint/plugins/golang"
	"github.com/blueprint-uservices/blueprint/plugins/memcached"
	"github.com/blueprint-uservices/blueprint/plugins/mongodb"
	"github.com/blueprint-uservices/blueprint/plugins/rabbitmq"
	"github.com/blueprint-uservices/blueprint/plugins/redis"
	"github.com/blueprint-uservices/blueprint/plugins/workflow"
	"github.com/blueprint-uservices/blueprint/plugins/workflow/workflowspec"

	"analyzer/pkg/app/datastores"
	"analyzer/pkg/frameworks"
	"analyzer/pkg/logger"
	"analyzer/pkg/utils"
)

func LoadWiring(appName string) (map[string]*frameworks.ServiceInfo, []*datastores.Datastore, []string) {
	spec := utils.LoadAppSpec(appName)
	servicesSpec, databasesNodes, frontends := BuildAndInspectIR(appName, spec)
	servicesInfo := buildBlueprintServicesInfo(servicesSpec)
	datastoresInfo := buildDatastores(databasesNodes)
	return servicesInfo, datastoresInfo, frontends
}

func getUniqueName(name string) string {
	// remove .client suffix (e.g. notification_queue.client)
	splits := strings.Split(name, ".")[0]
	if len(splits) > 0 {
		return strings.Split(name, ".")[0]
	}
	return ""
}

func buildBlueprintServicesInfo(appSpecs map[*workflowspec.Service][]golang.Service) map[string]*frameworks.ServiceInfo {
	services := make(map[string]*frameworks.ServiceInfo)
	for spec, serviceArgs := range appSpecs {
		serviceInfo := &frameworks.ServiceInfo{
			Name:            spec.Iface.Name,
			PackageName:     spec.Iface.File.Package.ShortName,
			PackagePath:     spec.Iface.File.Package.Name,
			Filepath:        spec.Iface.File.Name,
			ConstructorName: spec.Constructor.Name,
			AstInterface:    spec.Iface.Ast,
			AstConstructor:  spec.Constructor.Ast,
			ServiceArgs:     []string{"context"}, // args in spec do not count with the context at index 0 so we insert a dummy value now
		}
		for _, method := range spec.Iface.Ast.Methods.List {
			serviceInfo.Methods = append(serviceInfo.Methods, method.Names[0].Name)
		}
		for _, arg := range serviceArgs {
			if workflowClient, ok := arg.(*workflow.WorkflowClient); ok {
				serviceInfo.Edges = append(serviceInfo.Edges, getUniqueName(workflowClient.ServiceType))
			}
			serviceInfo.ServiceArgs = append(serviceInfo.ServiceArgs, getUniqueName(arg.Name()))
		}
		services[serviceInfo.Name] = serviceInfo
	}
	return services
}

func buildDatastores(databases map[string]ir.IRNode) []*datastores.Datastore {
	var datastoresLst []*datastores.Datastore
	for name, node := range databases {
		name = getUniqueName(name)
		var datastore *datastores.Datastore
		switch node.(type) {
		case *redis.RedisGoClient:
			datastore = &datastores.Datastore{
				Name: name,
				Type: datastores.Cache,
				Kind: datastores.Redis,
			}
		case *memcached.MemcachedGoClient:
			datastore = &datastores.Datastore{
				Name: name,
				Type: datastores.Cache,
				Kind: datastores.Memcached,
			}
		case *rabbitmq.RabbitmqGoClient:
			datastore = &datastores.Datastore{
				Name: name,
				Type: datastores.Queue,
				Kind: datastores.RabbitMQ,
			}
		case *mongodb.MongoDBGoClient:
			datastore = &datastores.Datastore{
				Name: name,
				Type: datastores.NoSQL,
				Kind: datastores.MongoDB,
			}
		default:
			logger.Logger.Warnf("unknown type for database instance: %s (type = %s)", name, utils.GetType(node))
			continue
		}
		datastoresLst = append(datastoresLst, datastore)
	}
	return datastoresLst
}
