from .sole import Sole


class ThinSole(Sole):
    """Concrete Product - Thin Sole for formal shoes"""
    
    def get_sole_type(self) -> str:
        return "Thin Sole"