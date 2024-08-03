package utils

import (
	"strings"

	"analyzer/pkg/logger"
)

const (
	PATH_BLUEPRINT_EXAMPLES     string = "github.com/blueprint-uservices/blueprint/examples/"
	PATH_BLUEPRINT_CORE_BACKEND string = "github.com/blueprint-uservices/blueprint/runtime/core/backend"
)

var APP_TO_PACKAGE = map[string]string{
	"postnotification":        PATH_BLUEPRINT_EXAMPLES + "postnotification/workflow/postnotification",
	"postnotification_simple": PATH_BLUEPRINT_EXAMPLES + "postnotification_simple/workflow/postnotification_simple",
	"foobar":                  PATH_BLUEPRINT_EXAMPLES + "foobar/workflow/foobar",
	"sockshop2":               PATH_BLUEPRINT_EXAMPLES + "sockshop2/workflow",
	"trainticket":             PATH_BLUEPRINT_EXAMPLES + "train_ticket/workflow",
	"shopping_app":            PATH_BLUEPRINT_EXAMPLES + "shopping_app/workflow",
	"dsb_hotel":               PATH_BLUEPRINT_EXAMPLES + "dsb_hotel/workflow/hotelreservation",
	"dsb_sn":                  PATH_BLUEPRINT_EXAMPLES + "dsb_sn/workflow/socialnetwork",
}

func LoadAppPath(app string) string {
	if path, ok := APP_TO_PACKAGE[app]; ok {
		return path
	}
	logger.Logger.Fatalf("unknown application name %s", app)
	return ""
}

func IsAppPackage(appPath string, packagePath string) bool {
	return strings.HasPrefix(packagePath, appPath)
}

func IsBlueprintBackendPath(path string) bool {
	return path == PATH_BLUEPRINT_CORE_BACKEND
}
