from concurrent.futures import ThreadPoolExecutor

class Restaurant:
    _instance = None
    _lock = ThreadPoolExecutor(max_workers=1)

    def __new__(cls):
        if not cls._instance:
            with cls._lock:
                if not cls._instance:
                    cls._instance = super().__new__(cls)
                    cls._instance._initialize()
        return cls._instance

    def _initialize(self):
        self.menu = []
        self.orders = {}
        self.reservations = []
        self.payments = {}
        self.staff = []

    def add_menu_item(self, item):
        self.menu.append(item)

    def remove_menu_item(self, item):
        self.menu.remove(item)

    def get_menu(self):
        return self.menu[:]

    def place_order(self, order):
        self.orders[order.get_id()] = order
        self._notify_kitchen(order)

    def update_order_status(self, order_id, status):
        order = self.orders.get(order_id)
        if order:
            order.set_status(status)
            self._notify_staff(order)

    def make_reservation(self, reservation):
        self.reservations.append(reservation)

    def cancel_reservation(self, reservation):
        self.reservations.remove(reservation)

    def process_payment(self, payment):
        self.payments[payment.get_id()] = payment

    def add_staff(self, staff):
        self.staff.append(staff)

    def remove_staff(self, staff):
        self.staff.remove(staff)

    def _notify_kitchen(self, order):
        pass

    def _notify_staff(self, order):
        pass