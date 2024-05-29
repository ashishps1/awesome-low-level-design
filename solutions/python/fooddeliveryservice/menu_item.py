class MenuItem:
    def __init__(self, item_id: str, name: str, description: str, price: float):
        self._id = item_id
        self._name = name
        self._description = description
        self._price = price
        self._available = True

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
    def available(self) -> bool:
        return self._available

    @available.setter
    def available(self, available: bool):
        self._available = available
