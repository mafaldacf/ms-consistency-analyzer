module blueprint/goproc/storage_service_proc

go 1.21

replace github.com/blueprint-uservices/blueprint/runtime => ../runtime

replace github.com/blueprint-uservices/blueprint/examples/post_notification/workflow => ../workflow

require (
	github.com/apache/thrift v0.20.0
	github.com/blueprint-uservices/blueprint/examples/post_notification/workflow v0.0.0-00010101000000-000000000000
	github.com/blueprint-uservices/blueprint/runtime v0.0.0-20240120085724-a66c24cd32b1
	golang.org/x/exp v0.0.0-20240409090435-93d18d7e34b8
)

require (
	github.com/go-logr/logr v1.3.0 // indirect
	github.com/go-logr/stdr v1.2.2 // indirect
	github.com/golang/snappy v0.0.4 // indirect
	github.com/klauspost/compress v1.16.6 // indirect
	github.com/montanaflynn/stats v0.0.0-20171201202039-1bf9dbcd8cbe // indirect
	github.com/xdg-go/pbkdf2 v1.0.0 // indirect
	github.com/xdg-go/scram v1.1.2 // indirect
	github.com/xdg-go/stringprep v1.0.4 // indirect
	github.com/youmark/pkcs8 v0.0.0-20181117223130-1be2e3e5546d // indirect
	go.mongodb.org/mongo-driver v1.13.0 // indirect
	go.opentelemetry.io/otel v1.21.0 // indirect
	go.opentelemetry.io/otel/exporters/stdout/stdoutmetric v0.44.0 // indirect
	go.opentelemetry.io/otel/exporters/stdout/stdouttrace v1.20.0 // indirect
	go.opentelemetry.io/otel/metric v1.21.0 // indirect
	go.opentelemetry.io/otel/sdk v1.21.0 // indirect
	go.opentelemetry.io/otel/sdk/metric v1.21.0 // indirect
	go.opentelemetry.io/otel/trace v1.21.0 // indirect
	golang.org/x/crypto v0.11.0 // indirect
	golang.org/x/sync v0.7.0 // indirect
	golang.org/x/sys v0.14.0 // indirect
	golang.org/x/text v0.11.0 // indirect
)
