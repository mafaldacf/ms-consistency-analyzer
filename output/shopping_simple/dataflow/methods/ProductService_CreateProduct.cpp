[] (PointerVariable PointerType) s (*shopping_simple.ProductServiceImpl struct{product_db NoSQLDatabase, product_queue Queue, num_workers int})
[_] (StructVariable UserType) shopping_simple.ProductServiceImpl struct{product_db NoSQLDatabase, product_queue Queue, num_workers int}
[__] (FieldVariable FieldType) product_db NoSQLDatabase
[___] (BlueprintBackendVariable BlueprintBackendType) product_db NoSQLDatabase
[__] (FieldVariable FieldType) product_queue Queue
[___] (BlueprintBackendVariable BlueprintBackendType) product_queue Queue

[] (InterfaceVariable UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ Frontend

    --> w-tainted: write(product_db.Product.ProductID) {1}
[] (BasicVariable BasicType) productID string
     --> w-tainted: write(product_db.Product.ProductID) {1}
[_] (Reference BasicType) ref <productID string> @ Frontend

    --> w-tainted: write(product_db.Product.Description) {1}
[] (BasicVariable BasicType) description string
     --> w-tainted: write(product_db.Product.Description) {1}
[_] (Reference BasicType) ref <description string> @ Frontend

    --> w-tainted: write(product_db.Product.PricePerUnit) {1}
[] (BasicVariable BasicType) pricePerUnit int
     --> w-tainted: write(product_db.Product.PricePerUnit) {1}
[_] (Reference BasicType) ref <pricePerUnit int> @ Frontend

    --> w-tainted: write(product_db.Product.Category) {1}
[] (BasicVariable BasicType) category string
     --> w-tainted: write(product_db.Product.Category) {1}
[_] (Reference BasicType) ref <category string> @ Frontend

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = product_database, collection = product_collection}

[] (InterfaceVariable UserType) _ .error

    --> w-tainted: write(product_db.Product) {1}
[] (StructVariable UserType) product shopping_simple.Product struct{ProductID string, Description string, PricePerUnit int, Category string}
     --> w-tainted: write(product_db.Product.Category) {1}
[_] (FieldVariable FieldType) Category string
      --> w-tainted: write(product_db.Product.Category) {1}
[__] (BasicVariable BasicType) category string
       --> w-tainted: write(product_db.Product.Category) {1}
[___] (Reference BasicType) ref <category string> @ Frontend
     --> w-tainted: write(product_db.Product.Description) {1}
[_] (FieldVariable FieldType) Description string
      --> w-tainted: write(product_db.Product.Description) {1}
[__] (BasicVariable BasicType) description string
       --> w-tainted: write(product_db.Product.Description) {1}
[___] (Reference BasicType) ref <description string> @ Frontend
     --> w-tainted: write(product_db.Product.PricePerUnit) {1}
[_] (FieldVariable FieldType) PricePerUnit int
      --> w-tainted: write(product_db.Product.PricePerUnit) {1}
[__] (BasicVariable BasicType) pricePerUnit int
       --> w-tainted: write(product_db.Product.PricePerUnit) {1}
[___] (Reference BasicType) ref <pricePerUnit int> @ Frontend
     --> w-tainted: write(product_db.Product.ProductID) {1}
[_] (FieldVariable FieldType) ProductID string
      --> w-tainted: write(product_db.Product.ProductID) {1}
[__] (BasicVariable BasicType) productID string
       --> w-tainted: write(product_db.Product.ProductID) {1}
[___] (Reference BasicType) ref <productID string> @ Frontend

[] (InterfaceVariable UserType) err .error

