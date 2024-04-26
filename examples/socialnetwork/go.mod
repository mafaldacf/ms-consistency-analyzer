module detection-tool

go 1.21

toolchain go1.21.5

replace github.com/blueprint-uservices/blueprint/blueprint => ../../blueprint

replace github.com/blueprint-uservices/blueprint/plugins => ../../plugins

replace github.com/blueprint-uservices/blueprint/runtime => ../../runtime

replace postnotification/workflow => ./workflow

replace postnotification/wiring/specs => ./wiring/specs

require (
	postnotification/wiring/specs v0.0.0-00010101000000-000000000000 // indirect
	postnotification/workflow v0.0.0 // indirect
	github.com/blueprint-uservices/blueprint/plugins v0.0.0 // indirect
	github.com/blueprint-uservices/blueprint/runtime v0.0.0-20240120085724-a66c24cd32b1 // indirect
)
