module analyzer

go 1.21

require golang.org/x/tools v0.20.0

require postnotification/workflow v0.0.0 // indirect

require (
	github.com/blueprint-uservices/blueprint/plugins v0.0.0
	postnotification/wiring v0.0.0-00010101000000-000000000000
)

require github.com/blueprint-uservices/blueprint/blueprint v0.0.0

require github.com/blueprint-uservices/blueprint/runtime v0.0.0 // indirect

require (
	github.com/cespare/xxhash/v2 v2.1.2 // indirect
	github.com/dgryski/go-rendezvous v0.0.0-20200823014737-9f7001d12a5f // indirect
	github.com/go-logr/logr v1.4.1 // indirect
	github.com/go-logr/stdr v1.2.2 // indirect
	github.com/go-redis/redis/v8 v8.11.5 // indirect
	github.com/otiai10/copy v1.14.0 // indirect
	github.com/rabbitmq/amqp091-go v1.8.1 // indirect
	go.mongodb.org/mongo-driver v1.14.0 // indirect
	go.opentelemetry.io/otel v1.25.0 // indirect
	go.opentelemetry.io/otel/exporters/stdout/stdoutmetric v1.25.0 // indirect
	go.opentelemetry.io/otel/exporters/stdout/stdouttrace v1.25.0 // indirect
	go.opentelemetry.io/otel/metric v1.25.0 // indirect
	go.opentelemetry.io/otel/sdk v1.25.0 // indirect
	go.opentelemetry.io/otel/sdk/metric v1.25.0 // indirect
	go.opentelemetry.io/otel/trace v1.25.0 // indirect
	golang.org/x/exp v0.0.0-20240409090435-93d18d7e34b8 // indirect
	golang.org/x/sys v0.19.0 // indirect
)

require (
	github.com/sirupsen/logrus v1.9.3
	golang.org/x/mod v0.17.0 // indirect
	golang.org/x/sync v0.7.0 // indirect
)

replace postnotification => ./examples/postnotification

replace postnotification/workflow => ./examples/postnotification/workflow

replace postnotification/wiring => ./examples/postnotification/wiring

replace github.com/blueprint-uservices/blueprint/plugins => ../blueprint/plugins

replace github.com/blueprint-uservices/blueprint/blueprint => ../blueprint/blueprint

replace github.com/blueprint-uservices/blueprint/runtime => ../blueprint/runtime
