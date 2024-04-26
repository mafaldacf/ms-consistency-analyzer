module postnotification/workload

go 1.20

replace github.com/blueprint-uservices/blueprint/runtime => ../../../runtime

replace postnotification/workflow => ../workflow

require postnotification/workflow v0.0.0-00010101000000-000000000000

require (
	github.com/blueprint-uservices/blueprint/runtime v0.0.0 // indirect
	go.mongodb.org/mongo-driver v1.13.0 // indirect
	go.opentelemetry.io/otel v1.21.0 // indirect
	go.opentelemetry.io/otel/metric v1.21.0 // indirect
	go.opentelemetry.io/otel/trace v1.21.0 // indirect
	golang.org/x/exp v0.0.0-20231110203233-9a3e6036ecaa // indirect
)
