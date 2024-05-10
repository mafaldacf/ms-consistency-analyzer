package frameworks

import (
	"analyzer/pkg/logger"
	"reflect"

	"github.com/blueprint-uservices/blueprint/blueprint/pkg/blueprint/logging"
	"github.com/blueprint-uservices/blueprint/blueprint/pkg/coreplugins/namespaceutil"
	"github.com/blueprint-uservices/blueprint/blueprint/pkg/ir"
	"github.com/blueprint-uservices/blueprint/blueprint/pkg/wiring"
	"github.com/blueprint-uservices/blueprint/plugins/cmdbuilder"
	"github.com/blueprint-uservices/blueprint/plugins/golang"
	"github.com/blueprint-uservices/blueprint/plugins/goproc"
	"github.com/blueprint-uservices/blueprint/plugins/linuxcontainer"
	"github.com/blueprint-uservices/blueprint/plugins/rabbitmq"
	"github.com/blueprint-uservices/blueprint/plugins/redis"
	"github.com/blueprint-uservices/blueprint/plugins/workflow"
	"github.com/blueprint-uservices/blueprint/plugins/workflow/workflowspec"
)

func BuildAndInspectIR(name string, spec cmdbuilder.SpecOption) (map[*workflowspec.Service][]golang.Service, map[string]ir.IRNode) {
	builder := buildIR(name, spec)
	return inspectIR(builder)
}

func buildIR(name string, spec cmdbuilder.SpecOption) *cmdbuilder.CmdBuilder {
	builder := &cmdbuilder.CmdBuilder{
		Name: name,
		Registry: map[string]cmdbuilder.SpecOption{},
		Spec: spec,
	}
	logging.DisableCompilerLogging()
	builder.Registry[spec.Name] = spec
	builder.Wiring = wiring.NewWiringSpec(builder.Name)
	if builder.Wiring == nil {
		logger.Logger.Fatal("error creating new wiring spec")
		return nil
	}
	nodesToBuild, err := builder.Spec.Build(builder.Wiring)
	if err != nil {
		logger.Logger.Fatal("error building wiring spec")
		return nil
	}

	builder.IR, err = builder.Wiring.BuildIR(nodesToBuild...)
	if err != nil {
		logger.Logger.Fatal("error building IR")
		return nil
	}
	return builder
}

func inspectIR(builder *cmdbuilder.CmdBuilder) (map[*workflowspec.Service][]golang.Service, map[string]ir.IRNode) {
	services := make(map[*workflowspec.Service][]golang.Service)
	databases := make(map[string]ir.IRNode)
	//logger.Logger.Debugf("IR: %v", builder.IR)
	logger.Logger.Debug("")
	for _, node := range builder.IR.Children {
		if n, ok := node.(namespaceutil.IRNamespace); ok {
			if nn, ok := n.(ir.IRNode); ok {
				if nnn, ok := nn.(*linuxcontainer.Container); ok {
					logger.Logger.Debug("--------------------------------------------")
					logger.Logger.Debug("")
					logger.Logger.Debug(nnn.String())
					logger.Logger.Debug("")
					for _, child := range nnn.Nodes {
						if nnnn, ok := child.(*goproc.Process); ok {
							for _, child := range nnnn.Edges {
								t := reflect.TypeOf(child).Elem().Name()
								logger.Logger.Debugf("[EDGE] got edge %s with type %s", child.Name(), t)
							}
							for _, child := range nnnn.Nodes {
								if redisClient, ok := child.(*redis.RedisGoClient); ok {
									logger.Logger.Debugf("[NODE] [redis.RedisGoClient] got node %s", redisClient.Name())
								} else if rabbitClient, ok := child.(*rabbitmq.RabbitmqGoClient); ok {
									logger.Logger.Debugf("[NODE] [rabbitmq.RabbitmqGoClient] got node %s", rabbitClient.Name())
								} else if workflowHandler, ok := child.(*workflow.WorkflowHandler); ok {
									logger.Logger.Debugf("[NODE] [workflow.WorkflowHandler] got node %s (service_type = %v)", workflowHandler.Name(), workflowHandler.ServiceType)

									// make sure that services that do not have any other dependencies are also included
									services[workflowHandler.ServiceInfo] = nil
									for _, arg := range workflowHandler.Args {
										if redisClient, ok := arg.(*redis.RedisGoClient); ok {
											services[workflowHandler.ServiceInfo] = append(services[workflowHandler.ServiceInfo], redisClient)
											databases[redisClient.Name()] = redisClient
											logger.Logger.Debugf("[HANDLER ARG] [redis.RedisGoClient] got node %s", redisClient.Name())
										} else if rabbitClient, ok := arg.(*rabbitmq.RabbitmqGoClient); ok {
											services[workflowHandler.ServiceInfo] = append(services[workflowHandler.ServiceInfo], rabbitClient)
											databases[rabbitClient.Name()] = rabbitClient
											logger.Logger.Debugf("[HANDLER ARG] [rabbitmq.RabbitmqGoClient] got node %s", rabbitClient.Name())
										} else if workflowClient, ok := arg.(*workflow.WorkflowClient); ok {
											services[workflowHandler.ServiceInfo] = append(services[workflowHandler.ServiceInfo], workflowClient)
											logger.Logger.Debugf("[HANDLER ARG] [workflow.WorkflowClient] got node %s (service_type = %v)", workflowClient.Name(), workflowClient.ServiceType)
										}
									}
								}
							}

						}
					}
					logger.Logger.Debug("")
				}
			}
		} else if redisContainer, ok := node.(*redis.RedisContainer); ok {
			logger.Logger.Debugf("ignoring redis.RedisContainer for node %s, interface %s", redisContainer.Name(), redisContainer.Iface)
		} else if rabbitContainer, ok := node.(*rabbitmq.RabbitmqContainer); ok {
			logger.Logger.Debugf("ignoring rabbitmq.RabbitmqContainer for node %s, interface %s", rabbitContainer.Name(), rabbitContainer.Iface)
		}
	}

	logger.Logger.Debug()
	for key, value := range services {
		logger.Logger.Debugf("Inspecting service %s", key.Iface.Name)
		for _, arg := range value {
			if workflowClient, ok := arg.(*workflow.WorkflowClient); ok {
				logger.Logger.Debugf("\t\t[workflow] %s", workflowClient.ServiceType)
			} else if rabbitClient, ok := arg.(*rabbitmq.RabbitmqGoClient); ok {
				logger.Logger.Debugf("\t\t[rabbitmq] %s", rabbitClient.Name())
			} else if redisClient, ok := arg.(*redis.RedisGoClient); ok {
				logger.Logger.Debugf("\t\t[redis] %s", redisClient.Name())
			}
		}
	}
	logger.Logger.Debug()
	logger.Logger.Debugf("Inspecting databases")
	for _, value := range databases {
		if rabbitClient, ok := value.(*rabbitmq.RabbitmqGoClient); ok {
			logger.Logger.Debugf("\t\t[rabbitmq] %s", rabbitClient.Name())
		} else if redisClient, ok := value.(*redis.RedisGoClient); ok {
			logger.Logger.Debugf("\t\t[redis] %s", redisClient.Name())
		}
	}
	return services, databases
}
