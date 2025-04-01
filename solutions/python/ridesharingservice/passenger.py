class Passenger:
    def __init__(self, id, name, contact, location):
        self.id = id
        self.name = name
        self.contact = contact
        self.location = location

    def get_id(self):
        return self.id

    def get_name(self):
        return self.name

    def get_contact(self):
        return self.contact

    def get_location(self):
        return self.location