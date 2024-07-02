class MenuItem:
    def __init__(self, id, name, description, price, available):
        self.id = id
        self.name = name
        self.description = description
        self.price = price
        self.available = available

    def get_id(self):
        return self.id

    def get_name(self):
        return self.name

    def get_description(self):
        return self.description

    def get_price(self):
        return self.price

    def is_available(self):
        return self.available