package workloadgen

import (
	"context"
	"fmt"
	"time"

	"flag"

	"github.com/blueprint-uservices/blueprint/examples/post_notification/workflow/postnotification"
)

// The WorkloadGen interface, which the Blueprint compiler will treat as a
// Workflow service
type SimpleWorkload interface {
	ImplementsSimpleWorkload(context.Context) error
}

// workloadGen implementation
type workloadGen struct {
	SimpleWorkload

	postnotification postnotification.Frontend
}

var myarg = flag.Int("myarg", 12345, "help message for myarg")

func NewSimpleWorkload(ctx context.Context, postnotification postnotification.Frontend) (SimpleWorkload, error) {
	return &workloadGen{postnotification: postnotification}, nil
}

func (s *workloadGen) Run(ctx context.Context) error {
	fmt.Printf("myarg is %v\n", *myarg)
	ticker := time.NewTicker(1 * time.Second)
	for {
		select {
		case <-ctx.Done():
			return nil
		case t := <-ticker.C:
			fmt.Println("Tick at", t)
		}
	}
}

func (s *workloadGen) ImplementsSimpleWorkload(context.Context) error {
	return nil
}
