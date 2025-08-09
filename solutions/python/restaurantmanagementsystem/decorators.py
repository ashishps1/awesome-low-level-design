from bill import BillComponent
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from bill import BillComponent

class BillDecorator(BillComponent):
    def __init__(self, component: BillComponent):
        self._wrapped = component
    
    def calculate_total(self) -> float:
        return self._wrapped.calculate_total()
    
    def get_description(self) -> str:
        return self._wrapped.get_description()


class TaxDecorator(BillDecorator):
    def __init__(self, component: BillComponent, tax_rate: float):
        super().__init__(component)
        self._tax_rate = tax_rate
    
    def calculate_total(self) -> float:
        return super().calculate_total() * (1 + self._tax_rate)
    
    def get_description(self) -> str:
        return super().get_description() + f", Tax @{self._tax_rate * 100}%"


class ServiceChargeDecorator(BillDecorator):
    def __init__(self, component: BillComponent, charge: float):
        super().__init__(component)
        self._service_charge = charge
    
    def calculate_total(self) -> float:
        return super().calculate_total() + self._service_charge
    
    def get_description(self) -> str:
        return super().get_description() + ", Service Charge"