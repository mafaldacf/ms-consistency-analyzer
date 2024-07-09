module analyzer

go 1.22

toolchain go1.22.2

require golang.org/x/tools v0.21.0

require github.com/blueprint-uservices/blueprint/plugins v0.0.0

require github.com/blueprint-uservices/blueprint/blueprint v0.0.0

require github.com/blueprint-uservices/blueprint/runtime v0.0.0 // indirect

require github.com/blueprint-uservices/blueprint/examples/postnotification/workflow v0.0.0 // indirect

require github.com/blueprint-uservices/blueprint/examples/postnotification/wiring v0.0.0

require github.com/blueprint-uservices/blueprint/examples/sockshop/workflow v0.0.0 // indirect

require github.com/blueprint-uservices/blueprint/examples/sockshop/wiring v0.0.0

require github.com/blueprint-uservices/blueprint/examples/train_ticket/workflow v0.0.0 // indirect

require github.com/blueprint-uservices/blueprint/examples/train_ticket/wiring v0.0.0

require github.com/blueprint-uservices/blueprint/examples/foobar/workflow v0.0.0 // indirect

require (
	github.com/blueprint-uservices/blueprint/examples/foobar/wiring v0.0.0
	gopkg.in/yaml.v2 v2.4.0
)

require (
	filippo.io/edwards25519 v1.1.0 // indirect
	github.com/blueprint-uservices/blueprint/examples/sockshop/workload v0.0.0-20240405152959-f078915d2306 // indirect
	github.com/cespare/xxhash/v2 v2.3.0 // indirect
	github.com/dgryski/go-rendezvous v0.0.0-20200823014737-9f7001d12a5f // indirect
	github.com/go-logr/logr v1.4.1 // indirect
	github.com/go-logr/stdr v1.2.2 // indirect
	github.com/go-redis/redis/v8 v8.11.5 // indirect
	github.com/go-sql-driver/mysql v1.8.1 // indirect
	github.com/golang/snappy v0.0.4 // indirect
	github.com/google/uuid v1.6.0 // indirect
	github.com/jmoiron/sqlx v1.4.0 // indirect
	github.com/klauspost/compress v1.17.8 // indirect
	github.com/mattn/go-sqlite3 v1.14.22 // indirect
	github.com/montanaflynn/stats v0.7.1 // indirect
	github.com/openzipkin/zipkin-go v0.4.3 // indirect
	github.com/otiai10/copy v1.14.0 // indirect
	github.com/pkg/errors v0.9.1 // indirect
	github.com/rabbitmq/amqp091-go v1.9.0 // indirect
	github.com/xdg-go/pbkdf2 v1.0.0 // indirect
	github.com/xdg-go/scram v1.1.2 // indirect
	github.com/xdg-go/stringprep v1.0.4 // indirect
	github.com/youmark/pkcs8 v0.0.0-20240424034433-3c2c7870ae76 // indirect
	go.mongodb.org/mongo-driver v1.15.0 // indirect
	go.opentelemetry.io/otel v1.26.0 // indirect
	go.opentelemetry.io/otel/exporters/stdout/stdoutmetric v1.26.0 // indirect
	go.opentelemetry.io/otel/exporters/stdout/stdouttrace v1.26.0 // indirect
	go.opentelemetry.io/otel/exporters/zipkin v1.26.0 // indirect
	go.opentelemetry.io/otel/metric v1.26.0 // indirect
	go.opentelemetry.io/otel/sdk v1.26.0 // indirect
	go.opentelemetry.io/otel/sdk/metric v1.26.0 // indirect
	go.opentelemetry.io/otel/trace v1.26.0 // indirect
	golang.org/x/crypto v0.22.0 // indirect
	golang.org/x/exp v0.0.0-20240525044651-4c93da0ed11d // indirect
	golang.org/x/sys v0.20.0 // indirect
	golang.org/x/text v0.14.0 // indirect
)

require (
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

replace github.com/blueprint-uservices/blueprint/examples/sockshop => ./blueprint/examples/sockshop

replace github.com/blueprint-uservices/blueprint/examples/sockshop/workflow => ./blueprint/examples/sockshop/workflow

replace github.com/blueprint-uservices/blueprint/examples/sockshop/wiring => ./blueprint/examples/sockshop/wiring

replace github.com/blueprint-uservices/blueprint/examples/train_ticket => ./blueprint/examples/train_ticket

replace github.com/blueprint-uservices/blueprint/examples/train_ticket/workflow => ./blueprint/examples/train_ticket/workflow

replace github.com/blueprint-uservices/blueprint/examples/train_ticket/wiring => ./blueprint/examples/train_ticket/wiring

replace github.com/blueprint-uservices/blueprint/examples/foobar => ./blueprint/examples/foobar

replace github.com/blueprint-uservices/blueprint/examples/foobar/workflow => ./blueprint/examples/foobar/workflow

replace github.com/blueprint-uservices/blueprint/examples/foobar/wiring => ./blueprint/examples/foobar/wiring
