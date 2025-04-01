class Coffee:
    def __init__(self, name, price, recipe):
        self.name = name
        self.price = price
        self.recipe = recipe

    def get_name(self):
        return self.name

    def get_price(self):
        return self.price

    def get_recipe(self):
        return self.recipe