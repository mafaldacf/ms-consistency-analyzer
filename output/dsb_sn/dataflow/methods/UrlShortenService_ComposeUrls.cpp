[0] (PointerObject PointerType) u (*socialnetwork.UrlShortenServiceImpl struct{urlShortenDB NoSQLDatabase, hostname string})
[_1] (StructObject UserType) socialnetwork.UrlShortenServiceImpl struct{urlShortenDB NoSQLDatabase, hostname "http://short-url/" string}
[__2] (FieldObject FieldType) hostname "http://short-url/" string
[___3] (BasicObject BasicType) "http://short-url/" string
[__2] (FieldObject FieldType) urlShortenDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) urlShortenDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ TextService
[__2] (Reference UserType) ref <ctx context.Context> @ ComposePostService
[___3] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.ReqID) {1}
[0] (BasicObject BasicType) reqID int64
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (Reference BasicType) ref <reqID int64> @ TextService
      --> w-tainted: write(post_db.Post.ReqID) {1}
[__2] (Reference BasicType) ref <reqID int64> @ ComposePostService
       --> w-tainted: write(post_db.Post.ReqID) {1}
[___3] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

[0] (ArrayObject ArrayType) urls []string
[_1] (Reference SliceType) ref <url_strings []string> @ TextService
[__2] (BasicObject BasicType) text string
[___3] (Reference BasicType) ref <text string> @ ComposePostService
[____4] (Reference BasicType) ref <text string> @ Wrk2APIService
[__2] (BasicObject BasicType) int
[__2] (BasicObject BasicType) text string
[___3] (Reference BasicType) ref <text string> @ ComposePostService
[____4] (Reference BasicType) ref <text string> @ Wrk2APIService
[__2] (BasicObject BasicType) int

[0] (ArrayObject ArrayType) target_urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}
     --> w-tainted: write(urlshorten_db.[]interface{}.*) {1}
[_1] (StructObject UserType) target_url socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}
      --> w-tainted: write(urlshorten_db.[]interface{}.*) {1}
[__2] (FieldObject FieldType) ExpandedUrl string
       --> w-tainted: write(urlshorten_db.[]interface{}.*) {1}
[___3] (BasicObject BasicType) url string
      --> w-tainted: write(urlshorten_db.[]interface{}.*) {1}
[__2] (FieldObject FieldType) ShortenedUrl string
       --> w-tainted: write(urlshorten_db.[]interface{}.*) {1}
[___3] (BasicObject BasicType) shortened_url string

    --> w-tainted: write(urlshorten_db.[]interface{}) {1}
[0] (ArrayObject ArrayType) target_url_docs []interface{}
     --> w-tainted: write(urlshorten_db.[]interface{}.*) {1}
[_1] (StructObject UserType) target_url socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}
      --> w-tainted: write(urlshorten_db.[]interface{}.*) {1}
[__2] (FieldObject FieldType) ExpandedUrl string
       --> w-tainted: write(urlshorten_db.[]interface{}.*) {1}
[___3] (BasicObject BasicType) url string
      --> w-tainted: write(urlshorten_db.[]interface{}.*) {1}
[__2] (FieldObject FieldType) ShortenedUrl string
       --> w-tainted: write(urlshorten_db.[]interface{}.*) {1}
[___3] (BasicObject BasicType) shortened_url string

    --> w-tainted: write(urlshorten_db.[]interface{}.*) {1}
[0] (BasicObject BasicType) url string

    --> w-tainted: write(urlshorten_db.[]interface{}.*) {1}
[0] (BasicObject BasicType) shortened_url string

    --> w-tainted: write(urlshorten_db.[]interface{}.*) {1}
[0] (StructObject UserType) target_url socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}
     --> w-tainted: write(urlshorten_db.[]interface{}.*) {1}
[_1] (FieldObject FieldType) ExpandedUrl string
      --> w-tainted: write(urlshorten_db.[]interface{}.*) {1}
[__2] (BasicObject BasicType) url string
     --> w-tainted: write(urlshorten_db.[]interface{}.*) {1}
[_1] (FieldObject FieldType) ShortenedUrl string
      --> w-tainted: write(urlshorten_db.[]interface{}.*) {1}
[__2] (BasicObject BasicType) shortened_url string

[0] (ArrayObject ArrayType) target_urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}
[_1] (StructObject UserType) target_url socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}
[__2] (FieldObject FieldType) ExpandedUrl string
[___3] (BasicObject BasicType) url string
[__2] (FieldObject FieldType) ShortenedUrl string
[___3] (BasicObject BasicType) shortened_url string

[0] (ArrayObject ArrayType) target_url_docs []interface{}
[_1] (StructObject UserType) target_url socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}
[__2] (FieldObject FieldType) ExpandedUrl string
[___3] (BasicObject BasicType) url string
[__2] (FieldObject FieldType) ShortenedUrl string
[___3] (BasicObject BasicType) shortened_url string

[0] (PointerObject PointerType) u (*socialnetwork.UrlShortenServiceImpl struct{urlShortenDB NoSQLDatabase, hostname string})
[_1] (StructObject UserType) socialnetwork.UrlShortenServiceImpl struct{urlShortenDB NoSQLDatabase, hostname "http://short-url/" string}
[__2] (FieldObject FieldType) hostname "http://short-url/" string
[___3] (BasicObject BasicType) "http://short-url/" string
[__2] (FieldObject FieldType) urlShortenDB NoSQLDatabase
[___3] (BlueprintBackendObject BlueprintBackendType) urlShortenDB NoSQLDatabase

[0] (InterfaceObject UserType) ctx context.Context
[_1] (Reference UserType) ref <ctx context.Context> @ TextService
[__2] (Reference UserType) ref <ctx context.Context> @ ComposePostService
[___3] (Reference UserType) ref <ctx context.Context> @ Wrk2APIService

    --> w-tainted: write(post_db.Post.ReqID) {1}
[0] (BasicObject BasicType) reqID int64
     --> w-tainted: write(post_db.Post.ReqID) {1}
[_1] (Reference BasicType) ref <reqID int64> @ TextService
      --> w-tainted: write(post_db.Post.ReqID) {1}
[__2] (Reference BasicType) ref <reqID int64> @ ComposePostService
       --> w-tainted: write(post_db.Post.ReqID) {1}
[___3] (Reference BasicType) ref <reqID int64> @ Wrk2APIService

[0] (ArrayObject ArrayType) urls []string
[_1] (Reference SliceType) ref <url_strings []string> @ TextService
[__2] (BasicObject BasicType) text string
[___3] (Reference BasicType) ref <text string> @ ComposePostService
[____4] (Reference BasicType) ref <text string> @ Wrk2APIService
[__2] (BasicObject BasicType) int
[__2] (BasicObject BasicType) text string
[___3] (Reference BasicType) ref <text string> @ ComposePostService
[____4] (Reference BasicType) ref <text string> @ Wrk2APIService
[__2] (BasicObject BasicType) int

[0] (ArrayObject ArrayType) target_urls []socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}
     --> w-tainted: write(urlshorten_db.[]interface{}.*) {1}
[_1] (StructObject UserType) target_url socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}
      --> w-tainted: write(urlshorten_db.[]interface{}.*) {1}
[__2] (FieldObject FieldType) ExpandedUrl string
       --> w-tainted: write(urlshorten_db.[]interface{}.*) {1}
[___3] (BasicObject BasicType) url string
      --> w-tainted: write(urlshorten_db.[]interface{}.*) {1}
[__2] (FieldObject FieldType) ShortenedUrl string
       --> w-tainted: write(urlshorten_db.[]interface{}.*) {1}
[___3] (BasicObject BasicType) shortened_url string

    --> w-tainted: write(urlshorten_db.[]interface{}) {1}
[0] (ArrayObject ArrayType) target_url_docs []interface{}
     --> w-tainted: write(urlshorten_db.[]interface{}.*) {1}
[_1] (StructObject UserType) target_url socialnetwork.URL struct{ShortenedUrl string, ExpandedUrl string}
      --> w-tainted: write(urlshorten_db.[]interface{}.*) {1}
[__2] (FieldObject FieldType) ExpandedUrl string
       --> w-tainted: write(urlshorten_db.[]interface{}.*) {1}
[___3] (BasicObject BasicType) url string
      --> w-tainted: write(urlshorten_db.[]interface{}.*) {1}
[__2] (FieldObject FieldType) ShortenedUrl string
       --> w-tainted: write(urlshorten_db.[]interface{}.*) {1}
[___3] (BasicObject BasicType) shortened_url string

    --> w-tainted: write(urlshorten_db.[]interface{}.*) {1}
[0] (BasicObject BasicType) url string

[0] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = url-shorten, collection = url-shorten}

[0] (InterfaceObject UserType) err .error

[0] (InterfaceObject UserType) err .error

