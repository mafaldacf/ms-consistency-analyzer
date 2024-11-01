package utils

import (
	"strings"

	"analyzer/pkg/logger"
)

func RemoveQuotesFromPathImport(path string) string {
	return strings.Trim(path, "\"")
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
