module postnotification/workflow

go 1.20

require (
	github.com/blueprint-uservices/blueprint/runtime v0.0.0-20240120085724-a66c24cd32b1
	go.mongodb.org/mongo-driver v1.13.0
)

require (
	go.opentelemetry.io/otel v1.21.0 // indirect
	go.opentelemetry.io/otel/metric v1.21.0 // indirect
	go.opentelemetry.io/otel/trace v1.21.0 // indirect
	golang.org/x/exp v0.0.0-20231110203233-9a3e6036ecaa // indirect
)

replace github.com/blueprint-uservices/blueprint/blueprint => ../../../blueprint

replace github.com/blueprint-uservices/blueprint/plugins => ../../../plugins

//replace github.com/blueprint-uservices/blueprint/runtime => ../../../runtime
