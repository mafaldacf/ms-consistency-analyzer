[] (PointerObject PointerType) f (*shopping_simple.FrontendImpl struct{product_service shopping_simple.ProductService, cart_service shopping_simple.CartService})
[_] (StructObject UserType) shopping_simple.FrontendImpl struct{product_service shopping_simple.ProductService, cart_service shopping_simple.CartService}
[__] (FieldObject FieldType) cart_service shopping_simple.CartService
[___] (ServiceObject ServiceType) cart_service shopping_simple.CartService
[__] (FieldObject FieldType) product_service shopping_simple.ProductService
[___] (ServiceObject ServiceType) product_service shopping_simple.ProductService

[] (InterfaceObject UserType) ctx context.Context

    --> w-tainted: write(cart_db.Cart.CartID) {1}       --> w-tainted: write(cart_db.Cart.CartID) {1} --> r-tainted: read(cart_db.Cart.CartID) {1}
[] (BasicObject BasicType) cartID string

    --> w-tainted: write(cart_db.Cart.LastProductID) {1}       --> w-tainted: write(cart_db.Cart.LastProductID) {1} --> r-tainted: read(product_db.Product.ProductID) {1}
[] (BasicObject BasicType) productID string

