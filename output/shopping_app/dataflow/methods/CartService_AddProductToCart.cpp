[] (PointerObject PointerType) c (*shopping_app.CartServiceImpl struct{order_service shopping_app.OrderService, product_service shopping_app.ProductService, cart_db NoSQLDatabase})
[_] (StructObject UserType) shopping_app.CartServiceImpl struct{order_service shopping_app.OrderService, product_service shopping_app.ProductService, cart_db NoSQLDatabase}
[__] (FieldObject FieldType) cart_db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) cart_db NoSQLDatabase
[__] (FieldObject FieldType) order_service shopping_app.OrderService
[___] (ServiceObject ServiceType) order_service shopping_app.OrderService
[__] (FieldObject FieldType) product_service shopping_app.ProductService
[___] (ServiceObject ServiceType) product_service shopping_app.ProductService

[] (InterfaceObject UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ Frontend

    --> r-tainted: read(cart_db._.cartID) {1}
[] (BasicObject BasicType) cartID string
     --> r-tainted: read(cart_db._.cartID) {1}
[_] (Reference BasicType) ref <cartID string> @ Frontend

    --> r-tainted: read(product_db._.productID) {1}
[] (BasicObject BasicType) productID string
     --> r-tainted: read(product_db._.productID) {1}
[_] (Reference BasicType) ref <productID string> @ Frontend

[] (StructObject UserType) product shopping_app.Product struct{ProductID string, Description string, PricePerUnit int, Category string}

[] (StructObject UserType) product shopping_app.Product struct{ProductID string, Description string, PricePerUnit int, Category string}
     --> r-tainted: read(product_db.Product) {1}
[_] (Reference UserType) ref <product shopping_app.Product struct{ProductID string, Description string, PricePerUnit int, Category string}> @ ProductService
[_] (FieldObject FieldType) PricePerUnit int
      --> w-tainted: write(cart_db.Cart.PricePerUnit) {1}           --> w-tainted: write(cart_db.Cart.PricePerUnit) {1} --> r-tainted: read(cart_db.int) {1}
[__] (BasicObject BasicType) PricePerUnit int
[_] (FieldObject FieldType) ProductID string
      --> w-tainted: write(cart_db.Cart.ProductID) {1}           --> w-tainted: write(cart_db.Cart.ProductID) {1} --> r-tainted: read(cart_db.string) {1}
[__] (BasicObject BasicType) ProductID string

[] (InterfaceObject UserType) _ .error
[_] (Reference UserType) ref <err .error> @ ProductService

    --> w-tainted: write(cart_db.Cart) {1}       --> w-tainted: write(cart_db.Cart) {1} --> r-tainted: read(cart_db.Cart, cart_db.PricePerUnit, cart_db.int, cart_db.ProductID, cart_db.string, cart_db.Quantity) {6}
[] (StructObject UserType) cart shopping_app.Cart struct{CartID string, UserID string, ProductID string, Quantity int, PricePerUnit int, Status string}
     --> w-tainted: write(cart_db.Cart.PricePerUnit) {1}         --> w-tainted: write(cart_db.Cart.PricePerUnit) {1} --> r-tainted: read(cart_db.PricePerUnit) {1}
[_] (FieldObject FieldType) PricePerUnit int
      --> w-tainted: write(cart_db.Cart.PricePerUnit) {1}           --> w-tainted: write(cart_db.Cart.PricePerUnit) {1} --> r-tainted: read(cart_db.int) {1}
[__] (BasicObject BasicType) PricePerUnit int
     --> w-tainted: write(cart_db.Cart.ProductID) {1}         --> w-tainted: write(cart_db.Cart.ProductID) {1} --> r-tainted: read(cart_db.ProductID) {1}
[_] (FieldObject FieldType) ProductID string
      --> w-tainted: write(cart_db.Cart.ProductID) {1}           --> w-tainted: write(cart_db.Cart.ProductID) {1} --> r-tainted: read(cart_db.string) {1}
[__] (BasicObject BasicType) ProductID string
     --> w-tainted: write(cart_db.Cart.Quantity) {1}         --> w-tainted: write(cart_db.Cart.Quantity) {1} --> r-tainted: read(cart_db.Quantity) {1}
[_] (FieldObject FieldType) Quantity int
      --> w-tainted: write(cart_db.Cart.Quantity) {1}           --> w-tainted: write(cart_db.Cart.Quantity) {1} --> r-tainted: read(cart_db.int) {1}
[__] (BasicObject BasicType) 1 int

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = cart_database, collection = cart_collection}

[] (InterfaceObject UserType) _ .error

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{Key "cartID" string, Value string}
[__] (FieldObject FieldType) Key "cartID" string
[___] (BasicObject BasicType) "cartID" string
[__] (FieldObject FieldType) Value string
       --> r-tainted: read(cart_db._.cartID) {1}
[___] (BasicObject BasicType) cartID string
        --> r-tainted: read(cart_db._.cartID) {1}
[____] (Reference BasicType) ref <cartID string> @ Frontend

    --> r-tainted: read(cart_db._) {1}
[] (BlueprintBackendObject BlueprintBackendType) result NoSQLCursor {database = cart_database, collection = cart_collection}
     --> w-tainted: write(cart_db.Cart) {1}         --> w-tainted: write(cart_db.Cart) {1} --> r-tainted: read(cart_db.Cart, cart_db.PricePerUnit, cart_db.int, cart_db.ProductID, cart_db.string, cart_db.Quantity) {6}
[_] (StructObject UserType) cart shopping_app.Cart struct{CartID string, UserID string, ProductID string, Quantity int, PricePerUnit int, Status string}
      --> w-tainted: write(cart_db.Cart.PricePerUnit) {1}           --> w-tainted: write(cart_db.Cart.PricePerUnit) {1} --> r-tainted: read(cart_db.PricePerUnit) {1}
[__] (FieldObject FieldType) PricePerUnit int
       --> w-tainted: write(cart_db.Cart.PricePerUnit) {1}             --> w-tainted: write(cart_db.Cart.PricePerUnit) {1} --> r-tainted: read(cart_db.int) {1}
[___] (BasicObject BasicType) PricePerUnit int
      --> w-tainted: write(cart_db.Cart.ProductID) {1}           --> w-tainted: write(cart_db.Cart.ProductID) {1} --> r-tainted: read(cart_db.ProductID) {1}
[__] (FieldObject FieldType) ProductID string
       --> w-tainted: write(cart_db.Cart.ProductID) {1}             --> w-tainted: write(cart_db.Cart.ProductID) {1} --> r-tainted: read(cart_db.string) {1}
[___] (BasicObject BasicType) ProductID string
      --> w-tainted: write(cart_db.Cart.Quantity) {1}           --> w-tainted: write(cart_db.Cart.Quantity) {1} --> r-tainted: read(cart_db.Quantity) {1}
[__] (FieldObject FieldType) Quantity int
       --> w-tainted: write(cart_db.Cart.Quantity) {1}             --> w-tainted: write(cart_db.Cart.Quantity) {1} --> r-tainted: read(cart_db.int) {1}
[___] (BasicObject BasicType) 1 int

[] (InterfaceObject UserType) _ .error

[] (PointerObject PointerType) c (*shopping_app.CartServiceImpl struct{order_service shopping_app.OrderService, product_service shopping_app.ProductService, cart_db NoSQLDatabase})
[_] (StructObject UserType) shopping_app.CartServiceImpl struct{order_service shopping_app.OrderService, product_service shopping_app.ProductService, cart_db NoSQLDatabase}
[__] (FieldObject FieldType) cart_db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) cart_db NoSQLDatabase
[__] (FieldObject FieldType) order_service shopping_app.OrderService
[___] (ServiceObject ServiceType) order_service shopping_app.OrderService
[__] (FieldObject FieldType) product_service shopping_app.ProductService
[___] (ServiceObject ServiceType) product_service shopping_app.ProductService

[] (InterfaceObject UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ Frontend

    --> r-tainted: read(cart_db._.cartID) {1}
[] (BasicObject BasicType) cartID string
     --> r-tainted: read(cart_db._.cartID) {1}
[_] (Reference BasicType) ref <cartID string> @ Frontend

    --> r-tainted: read(product_db._.productID) {1}
[] (BasicObject BasicType) productID string
     --> r-tainted: read(product_db._.productID) {1}
[_] (Reference BasicType) ref <productID string> @ Frontend

[] (StructObject UserType) product shopping_app.Product struct{ProductID string, Description string, PricePerUnit int, Category string}

[] (StructObject UserType) product shopping_app.Product struct{ProductID string, Description string, PricePerUnit int, Category string}
     --> r-tainted: read(product_db.Product) {1}
[_] (Reference UserType) ref <product shopping_app.Product struct{ProductID string, Description string, PricePerUnit int, Category string}> @ ProductService
[_] (FieldObject FieldType) PricePerUnit int
      --> w-tainted: write(cart_db.Cart.PricePerUnit) {1}           --> w-tainted: write(cart_db.Cart.PricePerUnit) {1} --> r-tainted: read(cart_db.int) {1}
[__] (BasicObject BasicType) PricePerUnit int
[_] (FieldObject FieldType) ProductID string
      --> w-tainted: write(cart_db.Cart.ProductID) {1}           --> w-tainted: write(cart_db.Cart.ProductID) {1} --> r-tainted: read(cart_db.string) {1}
[__] (BasicObject BasicType) ProductID string

[] (InterfaceObject UserType) _ .error
[_] (Reference UserType) ref <err .error> @ ProductService

    --> w-tainted: write(cart_db.Cart) {1}       --> w-tainted: write(cart_db.Cart) {1} --> r-tainted: read(cart_db.Cart, cart_db.PricePerUnit, cart_db.int, cart_db.ProductID, cart_db.string, cart_db.Quantity) {6}
[] (StructObject UserType) cart shopping_app.Cart struct{CartID string, UserID string, ProductID string, Quantity int, PricePerUnit int, Status string}
     --> w-tainted: write(cart_db.Cart.PricePerUnit) {1}         --> w-tainted: write(cart_db.Cart.PricePerUnit) {1} --> r-tainted: read(cart_db.PricePerUnit) {1}
[_] (FieldObject FieldType) PricePerUnit int
      --> w-tainted: write(cart_db.Cart.PricePerUnit) {1}           --> w-tainted: write(cart_db.Cart.PricePerUnit) {1} --> r-tainted: read(cart_db.int) {1}
[__] (BasicObject BasicType) PricePerUnit int
     --> w-tainted: write(cart_db.Cart.ProductID) {1}         --> w-tainted: write(cart_db.Cart.ProductID) {1} --> r-tainted: read(cart_db.ProductID) {1}
[_] (FieldObject FieldType) ProductID string
      --> w-tainted: write(cart_db.Cart.ProductID) {1}           --> w-tainted: write(cart_db.Cart.ProductID) {1} --> r-tainted: read(cart_db.string) {1}
[__] (BasicObject BasicType) ProductID string
     --> w-tainted: write(cart_db.Cart.Quantity) {1}         --> w-tainted: write(cart_db.Cart.Quantity) {1} --> r-tainted: read(cart_db.Quantity) {1}
[_] (FieldObject FieldType) Quantity int
      --> w-tainted: write(cart_db.Cart.Quantity) {1}           --> w-tainted: write(cart_db.Cart.Quantity) {1} --> r-tainted: read(cart_db.int) {1}
[__] (BasicObject BasicType) 1 int

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = cart_database, collection = cart_collection}

[] (InterfaceObject UserType) _ .error

[] (SliceObject UserType) query primitive.D
[_] (StructObject StructType) struct{Key "cartID" string, Value string}
[__] (FieldObject FieldType) Key "cartID" string
[___] (BasicObject BasicType) "cartID" string
[__] (FieldObject FieldType) Value string
       --> r-tainted: read(cart_db._.cartID) {1}
[___] (BasicObject BasicType) cartID string
        --> r-tainted: read(cart_db._.cartID) {1}
[____] (Reference BasicType) ref <cartID string> @ Frontend

    --> r-tainted: read(cart_db._) {1}
[] (BlueprintBackendObject BlueprintBackendType) result NoSQLCursor {database = cart_database, collection = cart_collection}
     --> w-tainted: write(cart_db.Cart) {1}         --> w-tainted: write(cart_db.Cart) {1} --> r-tainted: read(cart_db.Cart, cart_db.PricePerUnit, cart_db.int, cart_db.ProductID, cart_db.string, cart_db.Quantity) {6}
[_] (StructObject UserType) cart shopping_app.Cart struct{CartID string, UserID string, ProductID string, Quantity int, PricePerUnit int, Status string}
      --> w-tainted: write(cart_db.Cart.PricePerUnit) {1}           --> w-tainted: write(cart_db.Cart.PricePerUnit) {1} --> r-tainted: read(cart_db.PricePerUnit) {1}
[__] (FieldObject FieldType) PricePerUnit int
       --> w-tainted: write(cart_db.Cart.PricePerUnit) {1}             --> w-tainted: write(cart_db.Cart.PricePerUnit) {1} --> r-tainted: read(cart_db.int) {1}
[___] (BasicObject BasicType) PricePerUnit int
      --> w-tainted: write(cart_db.Cart.ProductID) {1}           --> w-tainted: write(cart_db.Cart.ProductID) {1} --> r-tainted: read(cart_db.ProductID) {1}
[__] (FieldObject FieldType) ProductID string
       --> w-tainted: write(cart_db.Cart.ProductID) {1}             --> w-tainted: write(cart_db.Cart.ProductID) {1} --> r-tainted: read(cart_db.string) {1}
[___] (BasicObject BasicType) ProductID string
      --> w-tainted: write(cart_db.Cart.Quantity) {1}           --> w-tainted: write(cart_db.Cart.Quantity) {1} --> r-tainted: read(cart_db.Quantity) {1}
[__] (FieldObject FieldType) Quantity int
       --> w-tainted: write(cart_db.Cart.Quantity) {1}             --> w-tainted: write(cart_db.Cart.Quantity) {1} --> r-tainted: read(cart_db.int) {1}
[___] (BasicObject BasicType) 1 int

[] (InterfaceObject UserType) _ .error

