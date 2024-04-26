package specs

import (
	"postnotification/workflow/postnotification"

	"github.com/blueprint-uservices/blueprint/blueprint/pkg/wiring"
	"github.com/blueprint-uservices/blueprint/plugins/cmdbuilder"
	"github.com/blueprint-uservices/blueprint/plugins/gotests"
	"github.com/blueprint-uservices/blueprint/plugins/mongodb"
	"github.com/blueprint-uservices/blueprint/plugins/rabbitmq"
	"github.com/blueprint-uservices/blueprint/plugins/workflow"
)

var Repl = cmdbuilder.SpecOption{
	Name:        "docker",
	Description: "Deploys each service in a separate container with thrift, and uses mongodb as NoSQL database backends.",
	Build:       makeRplSpec,
}

//userTimelineDatabase : NoSQLDatabase = MongoDB(replica_set="dbrs", is_primary=True).WithServer(default_deployer)
//userTimelineDatabase2 : NoSQLDatabase = MongoDB(replica_set="dbrs", is_primary=False).WithServer(default_deployer)

// Create a basic social network wiring spec.
// Returns the names of the nodes to instantiate or an error.
func makeRplSpec(spec wiring.WiringSpec) ([]string, error) {
	var containers []string
	var allServices []string

	post_db := mongodb.Container(spec, "post_db")
	post_db_2 := mongodb.Container(spec, "post_db")
	notification_queue := rabbitmq.Container(spec, "notification_queue", "notification")

	allServices = append(allServices, post_db)
	allServices = append(allServices, post_db_2)
	allServices = append(allServices, notification_queue)

	storage_service := workflow.Service[postnotification.StorageService](spec, "storage_service_service", post_db)
	storage_service_ctr := applyDockerDefaults(spec, storage_service, "storage_service_proc", "storage_service_container")
	containers = append(containers, storage_service_ctr)
	allServices = append(allServices, "storage_service_service")

	storage_service_2 := workflow.Service[postnotification.StorageService](spec, "storage_service_service", post_db_2)
	storage_service_ctr_2 := applyDockerDefaults(spec, storage_service_2, "storage_service_proc", "storage_service_container")
	containers = append(containers, storage_service_ctr_2)
	allServices = append(allServices, "storage_service_service")

	notify_service := workflow.Service[postnotification.NotifyService](spec, "notify_service_service", storage_service, notification_queue)
	notify_service_ctr := applyDockerQueueDefaults(spec, notify_service, "notify_service_proc", "notify_service_container")
	containers = append(containers, notify_service_ctr)

	frontend := workflow.Service[postnotification.Frontend](spec, "frontend", storage_service, notification_queue)
	frontend_ctr := applyHTTPDefaults(spec, frontend, "frontend_proc", "frontend_container")
	containers = append(containers, frontend_ctr)
	allServices = append(allServices, "frontend")

	tests := gotests.Test(spec, allServices...)
	containers = append(containers, tests)

	return containers, nil
}
