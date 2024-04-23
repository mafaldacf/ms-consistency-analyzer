module blueprint/testclients

go 1.21

replace github.com/blueprint-uservices/blueprint/examples/post_notification/workflow => ../workflow

replace github.com/blueprint-uservices/blueprint/runtime => ../runtime

require (
	github.com/apache/thrift v0.20.0
	github.com/blueprint-uservices/blueprint/examples/post_notification/workflow v0.0.0-00010101000000-000000000000
	github.com/blueprint-uservices/blueprint/runtime v0.0.0-20240120085724-a66c24cd32b1
)

require (
	github.com/golang/snappy v0.0.4 // indirect
	github.com/klauspost/compress v1.16.6 // indirect
	github.com/montanaflynn/stats v0.0.0-20171201202039-1bf9dbcd8cbe // indirect
	github.com/rabbitmq/amqp091-go v1.8.1 // indirect
	github.com/xdg-go/pbkdf2 v1.0.0 // indirect
	github.com/xdg-go/scram v1.1.2 // indirect
	github.com/xdg-go/stringprep v1.0.4 // indirect
	github.com/youmark/pkcs8 v0.0.0-20181117223130-1be2e3e5546d // indirect
	go.mongodb.org/mongo-driver v1.13.0 // indirect
	go.opentelemetry.io/otel v1.21.0 // indirect
	go.opentelemetry.io/otel/metric v1.21.0 // indirect
	go.opentelemetry.io/otel/trace v1.21.0 // indirect
	golang.org/x/crypto v0.11.0 // indirect
	golang.org/x/exp v0.0.0-20231110203233-9a3e6036ecaa // indirect
	golang.org/x/sync v0.0.0-20220722155255-886fb9371eb4 // indirect
	golang.org/x/text v0.11.0 // indirect
)
