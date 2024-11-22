[] (PointerObject PointerType) s (*shopping_simple.ProductServiceImpl struct{product_db NoSQLDatabase, product_queue Queue, num_workers int})
[_] (StructObject UserType) shopping_simple.ProductServiceImpl struct{product_db NoSQLDatabase, product_queue Queue, num_workers int}
[__] (FieldObject FieldType) product_db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) product_db NoSQLDatabase
[__] (FieldObject FieldType) product_queue Queue
[___] (BlueprintBackendObject BlueprintBackendType) product_queue Queue

[] (InterfaceObject UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ Frontend
[_] (Reference UserType) ref <ctx context.Context> @ CartService
[__] (Reference UserType) ref <ctx context.Context> @ Frontend

    --> r-tainted: read(product_db.Product.ProductID) {1}
[] (BasicObject BasicType) productID string
     --> r-tainted: read(product_db.Product.ProductID) {1}
[_] (Reference BasicType) ref <productID string> @ Frontend
     --> w-tainted: write(cart_db.Cart.LastProductID, cart_db.Cart.Products) {2}         --> w-tainted: write(cart_db.Cart.LastProductID, cart_db.Cart.Products) {2} --> r-tainted: read(product_db.Product.ProductID) {1}
[_] (Reference BasicType) ref <productID string> @ CartService
      --> w-tainted: write(cart_db.Cart.Products) {1}           --> w-tainted: write(cart_db.Cart.Products) {1} --> r-tainted: read(product_db.Product.ProductID) {1}
[__] (Reference BasicType) ref <productID string> @ Frontend

    --> r-tainted: read(product_db.Product) {1}
[] (StructObject UserType) product shopping_simple.Product struct{ProductID string, Description string, PricePerUnit int, Category string}

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = product_database, collection = product_collection}

[] (InterfaceObject UserType) _ .error

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{Key "productid" string, Value string}
[__] (FieldObject FieldType) Key "productid" string
[___] (BasicObject BasicType) "productid" string
[__] (FieldObject FieldType) Value string
       --> r-tainted: read(product_db.Product.ProductID) {1}
[___] (BasicObject BasicType) productID string
        --> r-tainted: read(product_db.Product.ProductID) {1}
[____] (Reference BasicType) ref <productID string> @ Frontend
        --> w-tainted: write(cart_db.Cart.LastProductID, cart_db.Cart.Products) {2}               --> w-tainted: write(cart_db.Cart.LastProductID, cart_db.Cart.Products) {2} --> r-tainted: read(product_db.Product.ProductID) {1}
[____] (Reference BasicType) ref <productID string> @ CartService
         --> w-tainted: write(cart_db.Cart.Products) {1}                 --> w-tainted: write(cart_db.Cart.Products) {1} --> r-tainted: read(product_db.Product.ProductID) {1}
[_____] (Reference BasicType) ref <productID string> @ Frontend

    --> r-tainted: read(product_db.Product) {1}
[] (BlueprintBackendObject BlueprintBackendType) result NoSQLCursor {database = product_database, collection = product_collection}
     --> r-tainted: read(product_db.Product) {1}
[_] (StructObject UserType) product shopping_simple.Product struct{ProductID string, Description string, PricePerUnit int, Category string}

[] (InterfaceObject UserType) err .error

[] (BasicObject BasicType) exists bool

[] (InterfaceObject UserType) err .error

