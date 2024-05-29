from datetime import date, timedelta

class Reservation:
    def __init__(self, reservation_id, customer, car, start_date, end_date):
        self.reservation_id = reservation_id
        self.customer = customer
        self.car = car
        self.start_date = start_date
        self.end_date = end_date
        self.total_price = self.calculate_total_price()

    def calculate_total_price(self):
        days_rented = (self.end_date - self.start_date).days + 1
        return self.car.rental_price_per_day * days_rented

    def get_start_date(self):
        return self.start_date

    def get_end_date(self):
        return self.end_date

    def get_car(self):
        return self.car

    def get_total_price(self):
        return self.total_price

    def get_reservation_id(self):
        return self.reservation_id