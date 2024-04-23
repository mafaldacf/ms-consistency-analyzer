

struct Post {
	1: i64 ReqID,
	2: i64 PostID,
	3: string Text,
	4: i64 Timestamp,
}

struct StorageService_ReadPost_Request {
	1: i64 reqID,
	2: i64 postID,
}

struct StorageService_ReadPost_Response {
	1: Post ret0,
}

struct StorageService_StorePost_Request {
	1: i64 reqID,
	2: Post post,
}

struct StorageService_StorePost_Response {
}



service StorageService {
	StorageService_ReadPost_Response ReadPost (1:StorageService_ReadPost_Request req),
	StorageService_StorePost_Response StorePost (1:StorageService_StorePost_Request req),
}

