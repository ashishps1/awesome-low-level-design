from shopping_cart import ShoppingCart

class Account:
    def __init__(self, username: str, password: str):
        self.username = username
        self.password = password
        self.cart = ShoppingCart()

    def get_cart(self) -> ShoppingCart:
        return self.cart