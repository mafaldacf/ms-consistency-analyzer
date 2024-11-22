[] (PointerObject PointerType) s (*shopping_app.ProductServiceImpl struct{product_db NoSQLDatabase})
[_] (StructObject UserType) shopping_app.ProductServiceImpl struct{product_db NoSQLDatabase}
[__] (FieldObject FieldType) product_db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) product_db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ CartService
[__] (Reference UserType) ref <ctx context.Context> @ Frontend
[_] (Reference UserType) ref <ctx context.Context> @ OrderService
[__] (Reference UserType) ref <ctx context.Context> @ Frontend

    --> r-tainted: read(product_db._.productID) {1}
[] (BasicObject BasicType) productID string
     --> r-tainted: read(product_db._.productID) {1}
[_] (Reference BasicType) ref <productID string> @ CartService
      --> r-tainted: read(product_db._.productID) {1}
[__] (Reference BasicType) ref <productID string> @ Frontend
     --> w-tainted: write(order_db.Order.ProductID, stock_db.Stock.ProductID, billing_db.Bill.ProductID) {3}         --> w-tainted: write(order_db.Order.ProductID, stock_db.Stock.ProductID, billing_db.Bill.ProductID) {3} --> r-tainted: read(product_db._.productID) {1}
[_] (Reference BasicType) ref <productID string> @ OrderService
      --> w-tainted: write(order_db.Order.ProductID, stock_db.Stock.ProductID, billing_db.Bill.ProductID) {3}           --> w-tainted: write(order_db.Order.ProductID, stock_db.Stock.ProductID, billing_db.Bill.ProductID) {3} --> r-tainted: read(product_db._.productID) {1}
[__] (Reference BasicType) ref <productID string> @ Frontend

    --> r-tainted: read(product_db.Product) {1}
[] (StructObject UserType) product shopping_app.Product struct{ProductID string, Description string, PricePerUnit int, Category string}

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = product_database, collection = product_collection}

[] (InterfaceObject UserType) _ .error

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{Key "productID" string, Value string}
[__] (FieldObject FieldType) Key "productID" string
[___] (BasicObject BasicType) "productID" string
[__] (FieldObject FieldType) Value string
       --> r-tainted: read(product_db._.productID) {1}
[___] (BasicObject BasicType) productID string
        --> r-tainted: read(product_db._.productID) {1}
[____] (Reference BasicType) ref <productID string> @ CartService
         --> r-tainted: read(product_db._.productID) {1}
[_____] (Reference BasicType) ref <productID string> @ Frontend
        --> w-tainted: write(order_db.Order.ProductID, stock_db.Stock.ProductID, billing_db.Bill.ProductID) {3}               --> w-tainted: write(order_db.Order.ProductID, stock_db.Stock.ProductID, billing_db.Bill.ProductID) {3} --> r-tainted: read(product_db._.productID) {1}
[____] (Reference BasicType) ref <productID string> @ OrderService
         --> w-tainted: write(order_db.Order.ProductID, stock_db.Stock.ProductID, billing_db.Bill.ProductID) {3}                 --> w-tainted: write(order_db.Order.ProductID, stock_db.Stock.ProductID, billing_db.Bill.ProductID) {3} --> r-tainted: read(product_db._.productID) {1}
[_____] (Reference BasicType) ref <productID string> @ Frontend

    --> r-tainted: read(product_db._) {1}
[] (BlueprintBackendObject BlueprintBackendType) result NoSQLCursor {database = product_database, collection = product_collection}
     --> r-tainted: read(product_db.Product) {1}
[_] (StructObject UserType) product shopping_app.Product struct{ProductID string, Description string, PricePerUnit int, Category string}

[] (InterfaceObject UserType) _ .error

[] (BasicObject BasicType) _ bool

[] (InterfaceObject UserType) err .error

