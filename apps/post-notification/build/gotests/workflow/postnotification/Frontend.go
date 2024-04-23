package postnotification

import (
	"context"
	"fmt"
	"math/rand"
	"time"

	"github.com/blueprint-uservices/blueprint/runtime/core/backend"
)

type Frontend interface {
	UploadPost(ctx context.Context, username string, text string) (int64, error)
	FetchPost(ctx context.Context, postID int64) (Post, error)
}

type FrontendImpl struct {
	storageService  StorageService
	queue    		backend.Queue
}

func NewFrontendImpl(ctx context.Context, storageService StorageService, queue backend.Queue) (Frontend, error) {
	return &FrontendImpl{storageService: storageService, queue: queue}, nil
}

func (f *FrontendImpl) UploadPost(ctx context.Context, username string, text string) (int64, error) {
	if text == "" {
		return -1, fmt.Errorf("text cannot be empty")
	}
	reqID := rand.Int63()
	postID := rand.Int63()

	// call for storage service
	post := Post{
		ReqID:     reqID,
		PostID:    postID,
		Text:      text,
		Timestamp: time.Now().UnixNano() / int64(time.Millisecond),
	}
	err := f.storageService.StorePost(ctx, reqID, post)
	if err != nil {
		return -1, err
	}

	// queue for notify service
	message := Message{
		ReqID:     Int64ToString(post.ReqID),
		PostID:    Int64ToString(post.PostID),
		Timestamp: Int64ToString(time.Now().UnixNano() / int64(time.Millisecond)),
	}
	result, err := f.queue.Push(ctx, message)
	if err != nil || !result {
		backend.GetLogger().Error(ctx, "error pushing message to queue %s", err.Error())
		return -1, fmt.Errorf("error pushing message to queue %s", err.Error())
	}

	return postID, nil
}

func (f *FrontendImpl) FetchPost(ctx context.Context, postID int64) (Post, error) {
	reqID := rand.Int63()
	return f.storageService.ReadPost(ctx, reqID, postID)
}
