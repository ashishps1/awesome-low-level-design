class MenuItem:
    def __init__(self, item_id: str, name: str, price: float):
        self._id = item_id
        self._name = name
        self._price = price
    
    def get_id(self) -> str:
        return self._id
    
    def get_name(self) -> str:
        return self._name
    
    def get_price(self) -> float:
        return self._price
    
    def __str__(self) -> str:
        return f"MenuItem(id={self._id}, name={self._name}, price=${self._price:.2f})"
