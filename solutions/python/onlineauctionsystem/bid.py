import datetime

class Bid:
    def __init__(self, bid_id, bidder, amount):
        self.id = bid_id
        self.bidder = bidder
        self.amount = amount
        self.timestamp = datetime.datetime.now()

    def get_amount(self):
        return self.amount

    def get_bidder(self):
        return self.bidder