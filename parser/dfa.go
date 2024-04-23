package parser

import (
	"fmt"
	"go/ast"

	"github.com/godoctor/godoctor/analysis/cfg"
	"github.com/godoctor/godoctor/analysis/dataflow"
	"github.com/godoctor/godoctor/analysis/loader"
	"golang.org/x/tools/go/packages"
)

func DataFlowAnalysis(targetMethod string) {
	var config packages.Config
	config.Dir = "./apps/post-notification/workflow/postnotification"
	config.Overlay = map[string][]byte{"StorageService.go": []byte("StorageService.go")}

	var laterError error

	prog, err := loader.Load(&config, func(err error) { laterError = err })
	if err != nil {
		fmt.Printf("error loading %s", err.Error())
		return
	}
	if laterError != nil {
		fmt.Printf("error loading, later error not nil %s", laterError)
	}
	var info *packages.Package
	for _, info = range prog.AllPackages {
		if info.Name == targetMethod {
			break
		}
	}

	funcOne := info.Syntax[0].Decls[1].(*ast.FuncDecl)
	cfg := cfg.FromFunc(funcOne)
	in, out := dataflow.LiveVars(cfg, info)

	ast.Inspect(info.Syntax[0], func(n ast.Node) bool {
		switch stmt := n.(type) {
		case ast.Stmt:
			a, b := in[stmt], out[stmt]
			fmt.Printf("a: %w, b:%w\n", a, b)
		}
		return true
	})
}
