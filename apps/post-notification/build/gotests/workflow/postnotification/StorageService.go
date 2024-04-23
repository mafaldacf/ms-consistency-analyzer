package postnotification

import (
	"context"
	"fmt"

	"github.com/blueprint-uservices/blueprint/runtime/core/backend"
	"go.mongodb.org/mongo-driver/bson"
)

type StorageService interface {
	StorePost(ctx context.Context, reqID int64, post Post) error
	ReadPost(ctx context.Context, reqID int64, postID int64) (Post, error)
}

type StorageServiceImpl struct {
	database backend.NoSQLDatabase
}

func NewStorageServiceImpl(ctx context.Context, database backend.NoSQLDatabase) (StorageService, error) {
	u := &StorageServiceImpl{database: database}
	return u, nil
}

func (u *StorageServiceImpl) StorePost(ctx context.Context, reqID int64, post Post) error {
	backend.GetLogger().Info(ctx, "entering StorePost for reqid %d", reqID)
	collection, err := u.database.GetCollection(ctx, "post", "post")
	if err != nil {
		return err
	}
	err = collection.InsertOne(ctx, post)
	if err != nil {
		return err
	}
	return nil
}

func (u *StorageServiceImpl) ReadPost(ctx context.Context, reqID int64, postID int64) (Post, error) {
	backend.GetLogger().Info(ctx, "entering ReadPost for reqid %d", reqID)
	var post Post

	collection, err := u.database.GetCollection(ctx, "post", "post")
	if err != nil {
		return post, err
	}

	filter := bson.D{
		{Key: "postid", Value: postID},
	}
	result, err := collection.FindOne(ctx, filter)
	if err != nil {
		backend.GetLogger().Error(ctx, "error reading post: %s", err.Error())
		return post, err
	}

	res, err := result.One(ctx, &post)
	if !res || err != nil {
		backend.GetLogger().Error(ctx, "post %d not found", postID)
		return post, fmt.Errorf("post not found")
	}
	backend.GetLogger().Info(ctx, "post found! %w", post)
	return post, nil
}
