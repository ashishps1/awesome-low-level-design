class City:
    def __init__(self, city_id: str, name: str):
        self.id = city_id
        self.name = name

    def get_id(self) -> str:
        return self.id

    def get_name(self) -> str:
        return self.name