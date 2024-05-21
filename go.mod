module analyzer

go 1.22

toolchain go1.22.2

require golang.org/x/tools v0.21.0

require github.com/blueprint-uservices/blueprint/plugins v0.0.0

require github.com/blueprint-uservices/blueprint/blueprint v0.0.0

require github.com/blueprint-uservices/blueprint/runtime v0.0.0 // indirect

require github.com/blueprint-uservices/blueprint/examples/postnotification/workflow v0.0.0 // indirect

require github.com/blueprint-uservices/blueprint/examples/postnotification/wiring v0.0.0

require github.com/blueprint-uservices/blueprint/examples/foobar/workflow v0.0.0 // indirect

require github.com/blueprint-uservices/blueprint/examples/foobar/wiring v0.0.0

require (
	github.com/cespare/xxhash/v2 v2.3.0 // indirect
	github.com/dgryski/go-rendezvous v0.0.0-20200823014737-9f7001d12a5f // indirect
	github.com/go-logr/logr v1.4.1 // indirect
	github.com/go-logr/stdr v1.2.2 // indirect
	github.com/go-redis/redis/v8 v8.11.5 // indirect
	github.com/otiai10/copy v1.14.0 // indirect
	github.com/rabbitmq/amqp091-go v1.9.0 // indirect
	go.mongodb.org/mongo-driver v1.15.0 // indirect
	go.opentelemetry.io/otel v1.26.0 // indirect
	go.opentelemetry.io/otel/exporters/stdout/stdoutmetric v1.26.0 // indirect
	go.opentelemetry.io/otel/exporters/stdout/stdouttrace v1.26.0 // indirect
	go.opentelemetry.io/otel/metric v1.26.0 // indirect
	go.opentelemetry.io/otel/sdk v1.26.0 // indirect
	go.opentelemetry.io/otel/sdk/metric v1.26.0 // indirect
	go.opentelemetry.io/otel/trace v1.26.0 // indirect
	golang.org/x/exp v0.0.0-20240506185415-9bf2ced13842 // indirect
	golang.org/x/sys v0.20.0 // indirect
)

require (
	github.com/golang-collections/collections v0.0.0-20130729185459-604e922904d3
	github.com/sirupsen/logrus v1.9.3
	golang.org/x/mod v0.17.0 // indirect
	golang.org/x/sync v0.7.0 // indirect
)

replace github.com/blueprint-uservices/blueprint/plugins => ./blueprint/plugins

replace github.com/blueprint-uservices/blueprint/blueprint => ./blueprint/blueprint

replace github.com/blueprint-uservices/blueprint/runtime => ./blueprint/runtime

replace github.com/blueprint-uservices/blueprint/examples/postnotification => ./blueprint/examples/postnotification

replace github.com/blueprint-uservices/blueprint/examples/postnotification/workflow => ./blueprint/examples/postnotification/workflow

replace github.com/blueprint-uservices/blueprint/examples/postnotification/wiring => ./blueprint/examples/postnotification/wiring

replace github.com/blueprint-uservices/blueprint/examples/foobar => ./blueprint/examples/foobar

replace github.com/blueprint-uservices/blueprint/examples/foobar/workflow => ./blueprint/examples/foobar/workflow

replace github.com/blueprint-uservices/blueprint/examples/foobar/wiring => ./blueprint/examples/foobar/wiring
