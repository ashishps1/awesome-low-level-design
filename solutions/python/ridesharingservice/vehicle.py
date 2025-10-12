from enums import RideType

class Vehicle:
    def __init__(self, license_number: str, model: str, vehicle_type: RideType):
        self._license_number = license_number
        self._model = model
        self._type = vehicle_type
    
    def get_license_number(self) -> str:
        return self._license_number
    
    def get_model(self) -> str:
        return self._model
    
    def get_type(self) -> RideType:
        return self._type