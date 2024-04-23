package postnotification

import (
	"context"
	"math/rand"
	"time"

	"github.com/blueprint-uservices/blueprint/runtime/core/backend"
)

type UploadService interface {
	UploadPost(ctx context.Context, username string, text string) (int64, error)
}

type UploadServiceImpl struct {
	storageService  StorageService
	notifyService  	NotifyService
	queue    		backend.Queue
}

func NewUploadServiceImpl(ctx context.Context, storageService StorageService, notifyService NotifyService, queue backend.Queue) (UploadService, error) {
	return &UploadServiceImpl{storageService: storageService, notifyService: notifyService, queue: queue}, nil
}

func (u *UploadServiceImpl) UploadPost(ctx context.Context, username string, text string) (int64, error) {
	text = ""
	post := Post{
		ReqID:     rand.Int63(),
		PostID:    rand.Int63(),
		Text:      text,
	}
	u.storageService.StorePost(ctx, post.ReqID, post)

	message := Message{
		ReqID:     Int64ToString(post.ReqID),
		PostID:    Int64ToString(post.PostID),
	}
	u.notifyService.Notify(ctx, message)

	return post.PostID, nil
}
