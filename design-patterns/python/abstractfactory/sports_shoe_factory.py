from .shoe_factory import ShoeFactory
from .bumpy_sole import BumpySole
from .round_shoe_lace import RoundShoeLace
from .sole import Sole
from .shoe_lace import ShoeLace


class SportsShoeFactory(ShoeFactory):
    """Concrete Factory for sports shoes"""
    
    def create_sole(self) -> Sole:
        return BumpySole()
    
    def create_shoe_lace(self) -> ShoeLace:
        return RoundShoeLace()