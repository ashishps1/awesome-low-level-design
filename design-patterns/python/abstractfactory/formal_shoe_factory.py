from .shoe_factory import ShoeFactory
from .thin_sole import ThinSole
from .tape_shoe_lace import TapeShoeLace
from .sole import Sole
from .shoe_lace import ShoeLace


class FormalShoeFactory(ShoeFactory):
    """Concrete Factory for formal shoes"""
    
    def create_sole(self) -> Sole:
        return ThinSole()
    
    def create_shoe_lace(self) -> ShoeLace:
        return TapeShoeLace()