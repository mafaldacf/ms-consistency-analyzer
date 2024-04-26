package dummy

import (
	"context"
)

type DummyService interface {
	Dummy(ctx context.Context) error
}

type DummyServiceImpl struct {
	
}

func NewDummyServiceImpl(ctx context.Context) (DummyService, error) {
	d := &DummyServiceImpl{}
	return d, nil
}

func (d *DummyServiceImpl) Dummy(ctx context.Context) error {
	return nil
}
