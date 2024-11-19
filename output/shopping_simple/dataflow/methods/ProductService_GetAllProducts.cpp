[] (PointerObject PointerType) s (*shopping_simple.ProductServiceImpl struct{product_db NoSQLDatabase, product_queue Queue, num_workers int})
[_] (StructObject UserType) shopping_simple.ProductServiceImpl struct{product_db NoSQLDatabase, product_queue Queue, num_workers int}
[__] (FieldObject FieldType) product_db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) product_db NoSQLDatabase
[__] (FieldObject FieldType) product_queue Queue
[___] (BlueprintBackendObject BlueprintBackendType) product_queue Queue

[] (InterfaceObject UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ Frontend

    --> r-tainted: read(product_db.[]shopping_simple.Product struct{ProductID string, Description string, PricePerUnit int, Category string}) {1}
[] (ArrayObject ArrayType) products []shopping_simple.Product struct{ProductID string, Description string, PricePerUnit int, Category string}

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = product_database, collection = product_collection}

[] (InterfaceObject UserType) _ .error

[] (SliceObject UserType) filter primitive.D

    --> r-tainted: read(product_db.Product) {1}
[] (BlueprintBackendObject BlueprintBackendType) cursor NoSQLCursor {database = product_database, collection = product_collection}
     --> r-tainted: read(product_db.[]shopping_simple.Product struct{ProductID string, Description string, PricePerUnit int, Category string}) {1}
[_] (ArrayObject ArrayType) products []shopping_simple.Product struct{ProductID string, Description string, PricePerUnit int, Category string}

[] (InterfaceObject UserType) _ .error

[] (InterfaceObject UserType) err .error

