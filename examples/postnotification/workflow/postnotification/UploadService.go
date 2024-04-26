package postnotification

import (
	"context"
	"math/rand"

	"github.com/blueprint-uservices/blueprint/runtime/core/backend"
	"postnotification/workflow/postnotification/common"
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
	post := Post{
		ReqID:     rand.Int63(),
		PostID:    rand.Int63(),
		Text:      text,
	}
	u.storageService.StorePost(ctx, post.ReqID, post)

	message := Message{
		ReqID:     common.Int64ToString(post.ReqID),
		PostID:    common.Int64ToString(post.PostID),
	}
	u.notifyService.Notify(ctx, message)

	return post.PostID, nil
}
