class DeliveryAgent:
    def __init__(self, agent_id: str, name: str, phone: str):
        self._id = agent_id
        self._name = name
        self._phone = phone
        self._available = True

    @property
    def id(self) -> str:
        return self._id

    @property
    def name(self) -> str:
        return self._name

    @property
    def phone(self) -> str:
        return self._phone

    @property
    def available(self) -> bool:
        return self._available

    @available.setter
    def available(self, available: bool):
        self._available = available
