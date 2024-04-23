// storage_service_proc runs the storage_service_proc Golang process.
//
// storage_service_proc is auto-generated by Blueprint's goproc plugin (goproc/goprocgen/main.go.go)
//
// Usage:
//
//   go run main.go --post_db.dial_addr=value --storage_service_service.thrift.bind_addr=value 
//
// storage_service_proc requires the following arguments are passed:
//
//   --post_db.dial_addr
//       Auto-generated by Blueprint IR node:
//       post_db.dial_addr = AddressConfig()
//
//   --storage_service_service.thrift.bind_addr
//       Auto-generated by Blueprint IR node:
//       storage_service_service.thrift.bind_addr = AddressConfig()
//
// storage_service_proc will instantiate the following IR nodes:
//   storage_service_proc.stdoutmetriccollector
//   storage_service_proc.logger
//   post_db.client
//   storage_service_service
//   storage_service_service.thrift_server
package main

import (
	"context"
	"os"

	"golang.org/x/exp/slog"
)

func main() {
	slog.Info("Running storage_service_proc")
	n, err := New_storage_service_proc("storage_service_proc").Build(context.Background())
	if err != nil {
		slog.Error(err.Error())
		os.Exit(1)
	}
	n.Await()
	slog.Info("storage_service_proc exiting")
}