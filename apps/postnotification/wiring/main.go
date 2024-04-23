// Package main provides an application for compiling different
// wiring specs for PostNotification application.
//
// To display options and usage, invoke:
//
//	go run main.go -h
package main

import (
	"github.com/blueprint-uservices/blueprint/examples/post_notification/wiring/specs"
	"github.com/blueprint-uservices/blueprint/plugins/cmdbuilder"
)

func main() {
	// Build a supported wiring spec
	name := "PostNotification"
	cmdbuilder.MakeAndExecute(
		name,
		specs.Docker,
	)
}
