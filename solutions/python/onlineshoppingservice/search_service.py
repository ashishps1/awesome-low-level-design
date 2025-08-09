from typing import Collection, List
from product import Product
from enums import ProductCategory

class SearchService:
    def __init__(self, product_catalog: Collection[Product]):
        self.product_catalog = product_catalog

    def search_by_name(self, name: str) -> List[Product]:
        return [p for p in self.product_catalog if name.lower() in p.get_name().lower()]

    def search_by_category(self, category: ProductCategory) -> List[Product]:
        return [p for p in self.product_catalog if p.get_category() == category]