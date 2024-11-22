[] (PointerObject PointerType) s (*shopping_app.StockServiceImpl struct{stock_db NoSQLDatabase})
[_] (StructObject UserType) shopping_app.StockServiceImpl struct{stock_db NoSQLDatabase}
[__] (FieldObject FieldType) stock_db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) stock_db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ OrderService
[__] (Reference UserType) ref <ctx context.Context> @ Frontend

    --> w-tainted: write(stock_db.Stock.ProductID) {1}
[] (BasicObject BasicType) productID string
     --> w-tainted: write(order_db.Order.ProductID, stock_db.Stock.ProductID, billing_db.Bill.ProductID) {3}         --> w-tainted: write(order_db.Order.ProductID, stock_db.Stock.ProductID, billing_db.Bill.ProductID) {3} --> r-tainted: read(product_db._.productID) {1}
[_] (Reference BasicType) ref <productID string> @ OrderService
      --> w-tainted: write(order_db.Order.ProductID, stock_db.Stock.ProductID, billing_db.Bill.ProductID) {3}           --> w-tainted: write(order_db.Order.ProductID, stock_db.Stock.ProductID, billing_db.Bill.ProductID) {3} --> r-tainted: read(product_db._.productID) {1}
[__] (Reference BasicType) ref <productID string> @ Frontend

    --> w-tainted: write(stock_db.Stock.Quantity) {1}
[] (BasicObject BasicType) quantity int
     --> w-tainted: write(order_db.Order.Quantity, stock_db.Stock.Quantity, billing_db.Bill.TotalCost) {3}
[_] (Reference BasicType) ref <quantity int> @ OrderService
      --> w-tainted: write(order_db.Order.Quantity, stock_db.Stock.Quantity, billing_db.Bill.TotalCost) {3}
[__] (Reference BasicType) ref <quantity int> @ Frontend

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = stock_database, collection = stock_collection}

[] (InterfaceObject UserType) _ .error

    --> w-tainted: write(stock_db.Stock) {1}
[] (StructObject UserType) stock shopping_app.Stock struct{ProductID string, Quantity int}
     --> w-tainted: write(stock_db.Stock.ProductID) {1}
[_] (FieldObject FieldType) ProductID string
      --> w-tainted: write(stock_db.Stock.ProductID) {1}
[__] (BasicObject BasicType) productID string
       --> w-tainted: write(order_db.Order.ProductID, stock_db.Stock.ProductID, billing_db.Bill.ProductID) {3}             --> w-tainted: write(order_db.Order.ProductID, stock_db.Stock.ProductID, billing_db.Bill.ProductID) {3} --> r-tainted: read(product_db._.productID) {1}
[___] (Reference BasicType) ref <productID string> @ OrderService
        --> w-tainted: write(order_db.Order.ProductID, stock_db.Stock.ProductID, billing_db.Bill.ProductID) {3}               --> w-tainted: write(order_db.Order.ProductID, stock_db.Stock.ProductID, billing_db.Bill.ProductID) {3} --> r-tainted: read(product_db._.productID) {1}
[____] (Reference BasicType) ref <productID string> @ Frontend
     --> w-tainted: write(stock_db.Stock.Quantity) {1}
[_] (FieldObject FieldType) Quantity int
      --> w-tainted: write(stock_db.Stock.Quantity) {1}
[__] (BasicObject BasicType) quantity int
       --> w-tainted: write(order_db.Order.Quantity, stock_db.Stock.Quantity, billing_db.Bill.TotalCost) {3}
[___] (Reference BasicType) ref <quantity int> @ OrderService
        --> w-tainted: write(order_db.Order.Quantity, stock_db.Stock.Quantity, billing_db.Bill.TotalCost) {3}
[____] (Reference BasicType) ref <quantity int> @ Frontend

