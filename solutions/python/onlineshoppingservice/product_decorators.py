from product import Product
from enums import ProductCategory

class ProductDecorator(Product):
    def __init__(self, decorated_product: Product):
        super().__init__()
        self.decorated_product = decorated_product

    def get_id(self) -> str:
        return self.decorated_product.get_id()

    def get_name(self) -> str:
        return self.decorated_product.get_name()

    def get_price(self) -> float:
        return self.decorated_product.get_price()

    def get_description(self) -> str:
        return self.decorated_product.get_description()

    def get_category(self) -> ProductCategory:
        return self.decorated_product.get_category()

class GiftWrapDecorator(ProductDecorator):
    GIFT_WRAP_COST = 5.00

    def __init__(self, product: Product):
        super().__init__(product)

    def get_price(self) -> float:
        return super().get_price() + self.GIFT_WRAP_COST

    def get_description(self) -> str:
        return super().get_description() + " (Gift Wrapped)"