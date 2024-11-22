[] (PointerObject PointerType) s (*shopping_app.ProductServiceImpl struct{product_db NoSQLDatabase})
[_] (StructObject UserType) shopping_app.ProductServiceImpl struct{product_db NoSQLDatabase}
[__] (FieldObject FieldType) product_db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) product_db NoSQLDatabase

[] (InterfaceObject UserType) ctx context.Context

[] (BasicObject BasicType) productID string

[] (BasicObject BasicType) description string

[] (BasicObject BasicType) pricePerUnit int

[] (BasicObject BasicType) category string

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = product_database, collection = product_collection}

[] (InterfaceObject UserType) _ .error

[] (StructObject UserType) product shopping_app.Product struct{ProductID string, Description string, PricePerUnit int, Category string}
[_] (FieldObject FieldType) Category string
[__] (BasicObject BasicType) category string
[_] (FieldObject FieldType) Description string
[__] (BasicObject BasicType) description string
[_] (FieldObject FieldType) PricePerUnit int
[__] (BasicObject BasicType) pricePerUnit int
[_] (FieldObject FieldType) ProductID string
[__] (BasicObject BasicType) productID string

[] (InterfaceObject UserType) err .error

