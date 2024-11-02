[] (PointerVariable PointerType) f (*shopping_simple.FrontendImpl struct{product_service shopping_simple.ProductService, cart_service shopping_simple.CartService})
[_] (StructVariable UserType) shopping_simple.FrontendImpl struct{product_service shopping_simple.ProductService, cart_service shopping_simple.CartService}
[__] (FieldVariable FieldType) cart_service shopping_simple.CartService
[___] (ServiceVariable ServiceType) cart_service shopping_simple.CartService
[__] (FieldVariable FieldType) product_service shopping_simple.ProductService
[___] (ServiceVariable ServiceType) product_service shopping_simple.ProductService

[] (InterfaceVariable UserType) ctx context.Context

    --> w-tainted: write(product_db.Product.ProductID) {1}
[] (BasicVariable BasicType) productID string

    --> w-tainted: write(product_db.Product.Description) {1}
[] (BasicVariable BasicType) description string

    --> w-tainted: write(product_db.Product.PricePerUnit) {1}
[] (BasicVariable BasicType) pricePerUnit int

    --> w-tainted: write(product_db.Product.Category) {1}
[] (BasicVariable BasicType) category string

