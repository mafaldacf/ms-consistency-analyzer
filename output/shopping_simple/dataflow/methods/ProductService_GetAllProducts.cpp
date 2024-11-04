[] (PointerVariable PointerType) s (*shopping_simple.ProductServiceImpl struct{product_db NoSQLDatabase, product_queue Queue, num_workers int})
[_] (StructVariable UserType) shopping_simple.ProductServiceImpl struct{product_db NoSQLDatabase, product_queue Queue, num_workers int}
[__] (FieldVariable FieldType) product_db NoSQLDatabase
[___] (BlueprintBackendVariable BlueprintBackendType) product_db NoSQLDatabase
[__] (FieldVariable FieldType) product_queue Queue
[___] (BlueprintBackendVariable BlueprintBackendType) product_queue Queue

[] (InterfaceVariable UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ Frontend

    --> r-tainted: read(product_db.[]shopping_simple.Product struct{ProductID string, Description string, PricePerUnit int, Category string}) {1}
[] (ArrayVariable ArrayType) products []shopping_simple.Product struct{ProductID string, Description string, PricePerUnit int, Category string}

[] (BlueprintBackendVariable BlueprintBackendType) collection NoSQLCollection {database = product_database, collection = product_collection}

[] (InterfaceVariable UserType) _ .error

[] (SliceVariable UserType) filter primitive.D

    --> r-tainted: read(product_db.Product) {1}
[] (BlueprintBackendVariable BlueprintBackendType) cursor NoSQLCursor {database = product_database, collection = product_collection}
     --> r-tainted: read(product_db.[]shopping_simple.Product struct{ProductID string, Description string, PricePerUnit int, Category string}) {1}
[_] (ArrayVariable ArrayType) products []shopping_simple.Product struct{ProductID string, Description string, PricePerUnit int, Category string}

[] (InterfaceVariable UserType) _ .error

[] (InterfaceVariable UserType) err .error

