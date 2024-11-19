[] (PointerObject PointerType) s (*shopping_simple.CartServiceImpl struct{product_service shopping_simple.ProductService, cart_db NoSQLDatabase, product_queue Queue, num_workers 4 int})
[_] (StructObject UserType) shopping_simple.CartServiceImpl struct{product_service shopping_simple.ProductService, cart_db NoSQLDatabase, product_queue Queue, num_workers 4 int}
[__] (FieldObject FieldType) cart_db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) cart_db NoSQLDatabase
[__] (FieldObject FieldType) num_workers 4 int
[___] (BasicObject BasicType) 4 int
[__] (FieldObject FieldType) product_queue Queue
[___] (BlueprintBackendObject BlueprintBackendType) product_queue Queue
[__] (FieldObject FieldType) product_service shopping_simple.ProductService
[___] (ServiceObject ServiceType) product_service shopping_simple.ProductService

[] (InterfaceObject UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ Frontend

    --> r-tainted: read(cart_db.Cart.CartID) {1}
[] (BasicObject BasicType) cartID string
     --> r-tainted: read(cart_db.Cart.CartID) {1}
[_] (Reference BasicType) ref <cartID string> @ Frontend

    --> r-tainted: read(cart_db.Cart) {1}
[] (StructObject UserType) cart shopping_simple.Cart struct{CartID string, TotalQuantity 1 int, LastProductID string, Products []string}

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = cart_database, collection = cart_database}

[] (InterfaceObject UserType) _ .error

[] (SliceObject UserType) filter primitive.D
[_] (StructObject StructType) struct{Key "cartid" string, Value string}
[__] (FieldObject FieldType) Key "cartid" string
[___] (BasicObject BasicType) "cartid" string
[__] (FieldObject FieldType) Value string
       --> r-tainted: read(cart_db.Cart.CartID) {1}
[___] (BasicObject BasicType) cartID string
        --> r-tainted: read(cart_db.Cart.CartID) {1}
[____] (Reference BasicType) ref <cartID string> @ Frontend

    --> r-tainted: read(cart_db.Cart) {1}
[] (BlueprintBackendObject BlueprintBackendType) result NoSQLCursor {database = cart_database, collection = cart_database}
     --> r-tainted: read(cart_db.Cart) {1}
[_] (StructObject UserType) cart shopping_simple.Cart struct{CartID string, TotalQuantity 1 int, LastProductID string, Products []string}

[] (InterfaceObject UserType) err .error

[] (BasicObject BasicType) exists bool

[] (InterfaceObject UserType) err .error

