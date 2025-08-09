class Address:
    def __init__(self, street: str, city: str, state: str, zip_code: str):
        self.street = street
        self.city = city
        self.state = state
        self.zip_code = zip_code

    def __str__(self) -> str:
        return f"{self.street}, {self.city}, {self.state} {self.zip_code}"