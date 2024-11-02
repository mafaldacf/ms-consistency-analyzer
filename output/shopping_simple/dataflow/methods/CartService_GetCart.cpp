[] (PointerVariable PointerType) s (*shopping_simple.CartServiceImpl struct{product_service shopping_simple.ProductService, cart_db NoSQLDatabase, product_queue Queue, num_workers 4 int})
[_] (StructVariable UserType) shopping_simple.CartServiceImpl struct{product_service shopping_simple.ProductService, cart_db NoSQLDatabase, product_queue Queue, num_workers 4 int}
[__] (FieldVariable FieldType) cart_db NoSQLDatabase
[___] (BlueprintBackendVariable BlueprintBackendType) cart_db NoSQLDatabase
[__] (FieldVariable FieldType) num_workers 4 int
[___] (BasicVariable BasicType) 4 int
[__] (FieldVariable FieldType) product_queue Queue
[___] (BlueprintBackendVariable BlueprintBackendType) product_queue Queue
[__] (FieldVariable FieldType) product_service shopping_simple.ProductService
[___] (ServiceVariable ServiceType) product_service shopping_simple.ProductService

[] (InterfaceVariable UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ Frontend

    --> r-tainted: read(cart_db.Cart.CartID) {1}
[] (BasicVariable BasicType) cartID string
     --> r-tainted: read(cart_db.Cart.CartID) {1}
[_] (Reference BasicType) ref <cartID string> @ Frontend

    --> r-tainted: read(cart_db.Cart) {1}
[] (StructVariable UserType) cart shopping_simple.Cart struct{CartID string, TotalQuantity 1 int, LastProductID string, Products []string}

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = cart_database, collection = cart_database}

[] (InterfaceVariable UserType) _ .error

[] (SliceVariable UserType) filter primitive.D
[_] (StructVariable StructType) struct{Key "cartid" string, Value string}
[__] (FieldVariable FieldType) Key "cartid" string
[___] (BasicVariable BasicType) "cartid" string
[__] (FieldVariable FieldType) Value string
       --> r-tainted: read(cart_db.Cart.CartID) {1}
[___] (BasicVariable BasicType) cartID string
        --> r-tainted: read(cart_db.Cart.CartID) {1}
[____] (Reference BasicType) ref <cartID string> @ Frontend

    --> r-tainted: read(cart_db.Cart) {1}
[] (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = cart_database, collection = cart_database}
     --> r-tainted: read(cart_db.Cart) {1}
[_] (StructVariable UserType) cart shopping_simple.Cart struct{CartID string, TotalQuantity 1 int, LastProductID string, Products []string}

[] (InterfaceVariable UserType) err .error

[] (BasicVariable BasicType) exists bool

[] (InterfaceVariable UserType) err .error

