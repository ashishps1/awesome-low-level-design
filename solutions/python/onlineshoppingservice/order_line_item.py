class OrderLineItem:
    def __init__(self, product_id: str, product_name: str, quantity: int, price_at_purchase: float):
        self.product_id = product_id
        self.product_name = product_name
        self.quantity = quantity
        self.price_at_purchase = price_at_purchase

    def get_product_id(self) -> str:
        return self.product_id

    def get_quantity(self) -> int:
        return self.quantity