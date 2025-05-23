from .shoe_factory import ShoeFactory
from .flat_sole import FlatSole
from .round_shoe_lace import RoundShoeLace
from .sole import Sole
from .shoe_lace import ShoeLace


class CasualShoeFactory(ShoeFactory):
    """Concrete Factory for casual shoes"""
    
    def create_sole(self) -> Sole:
        return FlatSole()
    
    def create_shoe_lace(self) -> ShoeLace:
        return RoundShoeLace()