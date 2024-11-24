[] (PointerObject PointerType) s (*shopping_simple.CartServiceImpl struct{product_service shopping_simple.ProductService, cart_db NoSQLDatabase, product_queue Queue, num_workers int})
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

    --> w-tainted: write(cart_db.Cart.CartID) {1}
[] (BasicObject BasicType) cartID string
     --> w-tainted: write(cart_db.Cart.CartID) {1}
[_] (Reference BasicType) ref <cartID string> @ Frontend

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = cart_database, collection = cart_database}

[] (InterfaceObject UserType) _ .error

    --> w-tainted: write(cart_db.Cart) {1}
[] (StructObject UserType) cart shopping_simple.Cart struct{CartID string, LastProductID string, TotalQuantity int, Products []string}
     --> w-tainted: write(cart_db.Cart.CartID) {1}
[_] (FieldObject FieldType) CartID string
      --> w-tainted: write(cart_db.Cart.CartID) {1}
[__] (BasicObject BasicType) cartID string
       --> w-tainted: write(cart_db.Cart.CartID) {1}
[___] (Reference BasicType) ref <cartID string> @ Frontend

[] (InterfaceObject UserType) err .error

