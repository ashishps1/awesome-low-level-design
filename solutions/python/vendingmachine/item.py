class Item:
    def __init__(self, code: str, name: str, price: int):
        self.code = code
        self.name = name
        self.price = price

    def get_name(self) -> str:
        return self.name

    def get_price(self) -> int:
        return self.price