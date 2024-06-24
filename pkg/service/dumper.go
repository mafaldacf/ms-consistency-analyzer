package service

func (node *Service) Yaml() map[string]interface{} {
	data := make(map[string]interface{})
	// exposed methods
	for _, method := range node.ExportedMethods {
		data[method.String()] = method.Yaml()
	}
	// queue handler methods
	for _, method := range node.QueueHandlerMethods {
		data[method.String()] = method.Yaml()
	}
	// internal methods (already contain handlers)
	for _, method := range node.InternalMethods {
		data[method.String()] = method.Yaml()
	}
	return data
}

func (node *Service) YamlCalls() map[string][]string {
	data := make(map[string][]string)
	// exposed methods
	for _, method := range node.ExportedMethods {
		data[method.String()] = method.YamlCalls()
	}
	// queue handler methods
	for _, method := range node.QueueHandlerMethods {
		data[method.String()] = method.YamlCalls()
	}
	// internal methods (already contain handlers)
	for _, method := range node.InternalMethods {
		data[method.String()] = method.YamlCalls()
	}
	return data
}
