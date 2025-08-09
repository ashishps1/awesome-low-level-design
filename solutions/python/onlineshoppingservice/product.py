from abc import ABC, abstractmethod
from enums import ProductCategory
import uuid

class Product(ABC):
    def __init__(self):
        self.id: str = ""
        self.name: str = ""
        self.description: str = ""
        self.price: float = 0.0
        self.category: ProductCategory = None

    @abstractmethod
    def get_id(self) -> str:
        pass

    @abstractmethod
    def get_name(self) -> str:
        pass

    @abstractmethod
    def get_description(self) -> str:
        pass

    @abstractmethod
    def get_price(self) -> float:
        pass

    @abstractmethod
    def get_category(self) -> ProductCategory:
        pass

    class BaseProduct:
        def __init__(self, product_id: str, name: str, description: str, price: float, category: ProductCategory):
            self.id = product_id
            self.name = name
            self.description = description
            self.price = price
            self.category = category

        def get_id(self) -> str:
            return self.id

        def get_name(self) -> str:
            return self.name

        def get_description(self) -> str:
            return self.description

        def get_price(self) -> float:
            return self.price

        def get_category(self) -> ProductCategory:
            return self.category

    class Builder:
        def __init__(self, name: str, price: float):
            self.name = name
            self.price = price
            self.description = ""
            self.category = None

        def with_description(self, description: str) -> 'Product.Builder':
            self.description = description
            return self

        def with_category(self, category: ProductCategory) -> 'Product.Builder':
            self.category = category
            return self

        def build(self) -> 'Product':
            return Product.BaseProduct(str(uuid.uuid4()), self.name, self.description, self.price, self.category)