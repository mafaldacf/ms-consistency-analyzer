[] (PointerVariable PointerType) f (*shopping_simple.FrontendImpl struct{product_service shopping_simple.ProductService, cart_service shopping_simple.CartService})
[_] (StructVariable UserType) shopping_simple.FrontendImpl struct{product_service shopping_simple.ProductService, cart_service shopping_simple.CartService}
[__] (FieldVariable FieldType) cart_service shopping_simple.CartService
[___] (ServiceVariable ServiceType) cart_service shopping_simple.CartService
[__] (FieldVariable FieldType) product_service shopping_simple.ProductService
[___] (ServiceVariable ServiceType) product_service shopping_simple.ProductService

[] (InterfaceVariable UserType) ctx context.Context

    --> w-tainted: write(cart_db.Cart.CartID) {1}       --> w-tainted: write(cart_db.Cart.CartID) {1} --> r-tainted: read(cart_db.Cart.CartID) {1}
[] (BasicVariable BasicType) cartID string

    --> w-tainted: write(cart_db.Cart.LastProductID) {1}       --> w-tainted: write(cart_db.Cart.LastProductID) {1} --> r-tainted: read(product_db.Product.ProductID) {1}
[] (BasicVariable BasicType) productID string

