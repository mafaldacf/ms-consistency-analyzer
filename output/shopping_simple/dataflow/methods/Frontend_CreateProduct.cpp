[] (PointerObject PointerType) f (*shopping_simple.FrontendImpl struct{product_service shopping_simple.ProductService, cart_service shopping_simple.CartService})
[_] (StructObject UserType) shopping_simple.FrontendImpl struct{product_service shopping_simple.ProductService, cart_service shopping_simple.CartService}
[__] (FieldObject FieldType) cart_service shopping_simple.CartService
[___] (ServiceObject ServiceType) cart_service shopping_simple.CartService
[__] (FieldObject FieldType) product_service shopping_simple.ProductService
[___] (ServiceObject ServiceType) product_service shopping_simple.ProductService

[] (InterfaceObject UserType) ctx context.Context

    --> w-tainted: write(product_db.Product.ProductID) {1}
[] (BasicObject BasicType) productID string

    --> w-tainted: write(product_db.Product.Description) {1}
[] (BasicObject BasicType) description string

    --> w-tainted: write(product_db.Product.PricePerUnit) {1}
[] (BasicObject BasicType) pricePerUnit int

    --> w-tainted: write(product_db.Product.Category) {1}
[] (BasicObject BasicType) category string

