[] (PointerVariable PointerType) s (*shopping_simple.ProductServiceImpl struct{product_db NoSQLDatabase, product_queue Queue, num_workers int})
[_] (StructVariable UserType) shopping_simple.ProductServiceImpl struct{product_db NoSQLDatabase, product_queue Queue, num_workers int}
[__] (FieldVariable FieldType) product_db NoSQLDatabase
[___] (BlueprintBackendVariable BlueprintBackendType) product_db NoSQLDatabase
[__] (FieldVariable FieldType) product_queue Queue
[___] (BlueprintBackendVariable BlueprintBackendType) product_queue Queue

[] (InterfaceVariable UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ Frontend
[_] (Reference UserType) ref <ctx context.Context> @ CartService
[__] (Reference UserType) ref <ctx context.Context> @ Frontend

    --> r-tainted: read(product_db.Product.ProductID) {1}
[] (BasicVariable BasicType) productID string
     --> r-tainted: read(product_db.Product.ProductID) {1}
[_] (Reference BasicType) ref <productID string> @ Frontend
     --> w-tainted: write(cart_db.Cart.LastProductID, cart_db.Cart.Products) {2}         --> w-tainted: write(cart_db.Cart.LastProductID, cart_db.Cart.Products) {2} --> r-tainted: read(product_db.Product.ProductID) {1}
[_] (Reference BasicType) ref <productID string> @ CartService
      --> w-tainted: write(cart_db.Cart.LastProductID) {1}           --> w-tainted: write(cart_db.Cart.LastProductID) {1} --> r-tainted: read(product_db.Product.ProductID) {1}
[__] (Reference BasicType) ref <productID string> @ Frontend

    --> r-tainted: read(product_db.Product) {1}
[] (StructVariable UserType) product shopping_simple.Product struct{ProductID string, Description string, PricePerUnit int, Category string}

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = product_database, collection = product_collection}

[] (InterfaceVariable UserType) _ .error

[] (SliceVariable UserType) query primitive.D
[_] (StructVariable StructType) struct{Key "productid" string, Value string}
[__] (FieldVariable FieldType) Key "productid" string
[___] (BasicVariable BasicType) "productid" string
[__] (FieldVariable FieldType) Value string
       --> r-tainted: read(product_db.Product.ProductID) {1}
[___] (BasicVariable BasicType) productID string
        --> r-tainted: read(product_db.Product.ProductID) {1}
[____] (Reference BasicType) ref <productID string> @ Frontend
        --> w-tainted: write(cart_db.Cart.LastProductID, cart_db.Cart.Products) {2}               --> w-tainted: write(cart_db.Cart.LastProductID, cart_db.Cart.Products) {2} --> r-tainted: read(product_db.Product.ProductID) {1}
[____] (Reference BasicType) ref <productID string> @ CartService
         --> w-tainted: write(cart_db.Cart.LastProductID) {1}                 --> w-tainted: write(cart_db.Cart.LastProductID) {1} --> r-tainted: read(product_db.Product.ProductID) {1}
[_____] (Reference BasicType) ref <productID string> @ Frontend

    --> r-tainted: read(product_db.Product) {1}
[] (BlueprintBackendVariable BlueprintBackendType) result NoSQLCursor {database = product_database, collection = product_collection}
     --> r-tainted: read(product_db.Product) {1}
[_] (StructVariable UserType) product shopping_simple.Product struct{ProductID string, Description string, PricePerUnit int, Category string}

[] (InterfaceVariable UserType) err .error

[] (BasicVariable BasicType) exists bool

[] (InterfaceVariable UserType) err .error

