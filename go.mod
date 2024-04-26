module analyzer

go 1.21

require golang.org/x/tools v0.20.0

require postnotification/workflow v0.0.0

require github.com/blueprint-uservices/blueprint/plugins v0.0.0

require github.com/blueprint-uservices/blueprint/blueprint v0.0.0 // indirect

require github.com/blueprint-uservices/blueprint/runtime v0.0.0 // indirect

require (
	go.mongodb.org/mongo-driver v1.14.0 // indirect
	go.opentelemetry.io/otel v1.25.0 // indirect
	go.opentelemetry.io/otel/metric v1.25.0 // indirect
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
