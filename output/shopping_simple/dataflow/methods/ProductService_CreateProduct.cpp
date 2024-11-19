[] (PointerObject PointerType) s (*shopping_simple.ProductServiceImpl struct{product_db NoSQLDatabase, product_queue Queue, num_workers int})
[_] (StructObject UserType) shopping_simple.ProductServiceImpl struct{product_db NoSQLDatabase, product_queue Queue, num_workers int}
[__] (FieldObject FieldType) product_db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) product_db NoSQLDatabase
[__] (FieldObject FieldType) product_queue Queue
[___] (BlueprintBackendObject BlueprintBackendType) product_queue Queue

[] (InterfaceObject UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ Frontend

    --> w-tainted: write(product_db.Product.ProductID) {1}
[] (BasicObject BasicType) productID string
     --> w-tainted: write(product_db.Product.ProductID) {1}
[_] (Reference BasicType) ref <productID string> @ Frontend

    --> w-tainted: write(product_db.Product.Description) {1}
[] (BasicObject BasicType) description string
     --> w-tainted: write(product_db.Product.Description) {1}
[_] (Reference BasicType) ref <description string> @ Frontend

    --> w-tainted: write(product_db.Product.PricePerUnit) {1}
[] (BasicObject BasicType) pricePerUnit int
     --> w-tainted: write(product_db.Product.PricePerUnit) {1}
[_] (Reference BasicType) ref <pricePerUnit int> @ Frontend

    --> w-tainted: write(product_db.Product.Category) {1}
[] (BasicObject BasicType) category string
     --> w-tainted: write(product_db.Product.Category) {1}
[_] (Reference BasicType) ref <category string> @ Frontend

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = product_database, collection = product_collection}

[] (InterfaceObject UserType) _ .error

    --> w-tainted: write(product_db.Product) {1}
[] (StructObject UserType) product shopping_simple.Product struct{ProductID string, Description string, PricePerUnit int, Category string}
     --> w-tainted: write(product_db.Product.Category) {1}
[_] (FieldObject FieldType) Category string
      --> w-tainted: write(product_db.Product.Category) {1}
[__] (BasicObject BasicType) category string
       --> w-tainted: write(product_db.Product.Category) {1}
[___] (Reference BasicType) ref <category string> @ Frontend
     --> w-tainted: write(product_db.Product.Description) {1}
[_] (FieldObject FieldType) Description string
      --> w-tainted: write(product_db.Product.Description) {1}
[__] (BasicObject BasicType) description string
       --> w-tainted: write(product_db.Product.Description) {1}
[___] (Reference BasicType) ref <description string> @ Frontend
     --> w-tainted: write(product_db.Product.PricePerUnit) {1}
[_] (FieldObject FieldType) PricePerUnit int
      --> w-tainted: write(product_db.Product.PricePerUnit) {1}
[__] (BasicObject BasicType) pricePerUnit int
       --> w-tainted: write(product_db.Product.PricePerUnit) {1}
[___] (Reference BasicType) ref <pricePerUnit int> @ Frontend
     --> w-tainted: write(product_db.Product.ProductID) {1}
[_] (FieldObject FieldType) ProductID string
      --> w-tainted: write(product_db.Product.ProductID) {1}
[__] (BasicObject BasicType) productID string
       --> w-tainted: write(product_db.Product.ProductID) {1}
[___] (Reference BasicType) ref <productID string> @ Frontend

[] (InterfaceObject UserType) err .error

