from datetime import datetime

class Message:
    def __init__(self, payload: str):
        self.payload = payload
        self.timestamp = datetime.now()

    def get_payload(self) -> str:
        return self.payload

    def __str__(self) -> str:
        return f"Message{{payload='{self.payload}'}}"