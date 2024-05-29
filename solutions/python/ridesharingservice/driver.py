from enum import Enum

class DriverStatus(Enum):
    AVAILABLE = 1
    BUSY = 2

class Driver:
    def __init__(self, id, name, contact, license_plate, location, status):
        self.id = id
        self.name = name
        self.contact = contact
        self.license_plate = license_plate
        self.location = location
        self.status = status

    def set_id(self, id):
        self.id = id

    def set_name(self, name):
        self.name = name

    def set_contact(self, contact):
        self.contact = contact

    def set_license_plate(self, license_plate):
        self.license_plate = license_plate

    def set_location(self, location):
        self.location = location

    def set_status(self, status):
        self.status = status

    def get_id(self):
        return self.id

    def get_name(self):
        return self.name

    def get_contact(self):
        return self.contact

    def get_license_plate(self):
        return self.license_plate

    def get_location(self):
        return self.location

    def get_status(self):
        return self.status