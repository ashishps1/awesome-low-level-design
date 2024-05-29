class Product:
    def __init__(self, product_id: str, name: str, description: str, price: float, quantity: int):
        self._id = product_id
        self._name = name
        self._description = description
        self._price = price
        self._quantity = quantity

    def update_quantity(self, quantity: int):
        self._quantity += quantity

    def is_available(self, quantity: int) -> bool:
        return self._quantity >= quantity

    @property
    def id(self) -> str:
        return self._id

    @property
    def name(self) -> str:
        return self._name

    @property
    def description(self) -> str:
        return self._description

    @property
    def price(self) -> float:
        return self._price

    @property
    def quantity(self) -> int:
        return self._quantity
