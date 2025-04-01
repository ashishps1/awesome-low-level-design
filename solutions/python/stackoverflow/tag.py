class Tag:
    def __init__(self, name: str):
        self.id = id(self)
        self.name = name