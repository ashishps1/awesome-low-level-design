class MenuItem:
    def __init__(self, item_id: str, name: str, price: float):
        self.id = item_id
        self.name = name
        self.price = price
        self.available = True

    def get_id(self) -> str:
        return self.id

    def set_available(self, available: bool):
        self.available = available

    def get_name(self) -> str:
        return self.name

    def get_price(self) -> float:
        return self.price

    def get_menu_item(self) -> str:
        return f"Name: {self.name}, Price: {self.price}"