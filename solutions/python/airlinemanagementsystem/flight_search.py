from datetime import date

class FlightSearch:
    def __init__(self, flights):
        self.flights = flights

    def search_flights(self, source, destination, date):
        return [flight for flight in self.flights
                if flight.get_source().lower() == source.lower()
                and flight.get_destination().lower() == destination.lower()
                and flight.get_departure_time().date() == date]