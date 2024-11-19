[] (PointerObject PointerType) s (*shopping_simple.CartServiceImpl struct{product_service shopping_simple.ProductService, cart_db NoSQLDatabase, product_queue Queue, num_workers 4 int})
[_] (StructObject UserType) shopping_simple.CartServiceImpl struct{product_service shopping_simple.ProductService, cart_db NoSQLDatabase, product_queue Queue, num_workers 4 int}
[__] (FieldObject FieldType) cart_db NoSQLDatabase
[___] (BlueprintBackendObject BlueprintBackendType) cart_db NoSQLDatabase
[__] (FieldObject FieldType) num_workers 4 int
[___] (BasicObject BasicType) 4 int
[__] (FieldObject FieldType) product_queue Queue
[___] (BlueprintBackendObject BlueprintBackendType) product_queue Queue
[__] (FieldObject FieldType) product_service shopping_simple.ProductService
[___] (ServiceObject ServiceType) product_service shopping_simple.ProductService

[] (InterfaceObject UserType) ctx context.Context
[_] (Reference UserType) ref <ctx context.Context> @ Frontend

    --> w-tainted: write(cart_db.Cart.CartID) {1}       --> w-tainted: write(cart_db.Cart.CartID) {1} --> r-tainted: read(cart_db.Cart.CartID) {1}
[] (BasicObject BasicType) cartID string
     --> w-tainted: write(cart_db.Cart.CartID) {1}         --> w-tainted: write(cart_db.Cart.CartID) {1} --> r-tainted: read(cart_db.Cart.CartID) {1}
[_] (Reference BasicType) ref <cartID string> @ Frontend

    --> w-tainted: write(cart_db.Cart.LastProductID, cart_db.Cart.Products) {2}       --> w-tainted: write(cart_db.Cart.LastProductID, cart_db.Cart.Products) {2} --> r-tainted: read(product_db.Product.ProductID) {1}
[] (BasicObject BasicType) productID string
     --> w-tainted: write(cart_db.Cart.Products) {1}         --> w-tainted: write(cart_db.Cart.Products) {1} --> r-tainted: read(product_db.Product.ProductID) {1}
[_] (Reference BasicType) ref <productID string> @ Frontend

[] (StructObject UserType) product shopping_simple.Product struct{ProductID string, Description string, PricePerUnit int, Category string}

[] (StructObject UserType) product shopping_simple.Product struct{ProductID string, Description string, PricePerUnit int, Category string}
[_] (Reference UserType) ref <product shopping_simple.Product struct{ProductID string, Description string, PricePerUnit int, Category string}> @ ProductService
[_] (FieldObject FieldType) PricePerUnit int
[__] (BasicObject BasicType) PricePerUnit int

[] (InterfaceObject UserType) _ .error
[_] (Reference UserType) ref <err .error> @ ProductService

[] (StructObject UserType) cart shopping_simple.Cart struct{CartID string, TotalQuantity 1 int, LastProductID string, Products []string}

[] (StructObject UserType) cartProduct shopping_simple.CartProduct struct{CartID string, ProductID string, PricePerUnit int, Quantity 1 int}

[] (BlueprintBackendObject BlueprintBackendType) collection NoSQLCollection {database = cart_database, collection = cart_collection}

[] (InterfaceObject UserType) _ .error

[] (SliceObject UserType) filter primitive.D
[_] (StructObject StructType) struct{Key "cartid" string, Value string}
[__] (FieldObject FieldType) Key "cartid" string
[___] (BasicObject BasicType) "cartid" string
[__] (FieldObject FieldType) Value string
       --> w-tainted: write(cart_db.Cart.CartID) {1}             --> w-tainted: write(cart_db.Cart.CartID) {1} --> r-tainted: read(cart_db.Cart.CartID) {1}
[___] (BasicObject BasicType) cartID string
        --> w-tainted: write(cart_db.Cart.CartID) {1}               --> w-tainted: write(cart_db.Cart.CartID) {1} --> r-tainted: read(cart_db.Cart.CartID) {1}
[____] (Reference BasicType) ref <cartID string> @ Frontend

[] (BlueprintBackendObject BlueprintBackendType) result NoSQLCursor {database = cart_database, collection = cart_collection}
[_] (StructObject UserType) cart shopping_simple.Cart struct{CartID string, TotalQuantity 1 int, LastProductID string, Products []string}

[] (InterfaceObject UserType) err .error

[] (StructObject UserType) cartProduct shopping_simple.CartProduct struct{CartID string, ProductID string, PricePerUnit int, Quantity 1 int}
[_] (FieldObject FieldType) CartID string
      --> w-tainted: write(cart_db.Cart.CartID) {1}           --> w-tainted: write(cart_db.Cart.CartID) {1} --> r-tainted: read(cart_db.Cart.CartID) {1}
[__] (BasicObject BasicType) cartID string
       --> w-tainted: write(cart_db.Cart.CartID) {1}             --> w-tainted: write(cart_db.Cart.CartID) {1} --> r-tainted: read(cart_db.Cart.CartID) {1}
[___] (Reference BasicType) ref <cartID string> @ Frontend
[_] (FieldObject FieldType) PricePerUnit int
[__] (BasicObject BasicType) PricePerUnit int
[_] (FieldObject FieldType) ProductID string
      --> w-tainted: write(cart_db.Cart.LastProductID, cart_db.Cart.Products) {2}           --> w-tainted: write(cart_db.Cart.LastProductID, cart_db.Cart.Products) {2} --> r-tainted: read(product_db.Product.ProductID) {1}
[__] (BasicObject BasicType) productID string
       --> w-tainted: write(cart_db.Cart.Products) {1}             --> w-tainted: write(cart_db.Cart.Products) {1} --> r-tainted: read(product_db.Product.ProductID) {1}
[___] (Reference BasicType) ref <productID string> @ Frontend
[_] (FieldObject FieldType) Quantity 1 int
[__] (BasicObject BasicType) 1 int

[] (BasicObject BasicType) exists bool

[] (InterfaceObject UserType) _ .error

