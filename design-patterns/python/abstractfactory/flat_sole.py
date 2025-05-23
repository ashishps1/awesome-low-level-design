from .sole import Sole


class FlatSole(Sole):
    """Concrete Product - Flat Sole for casual shoes"""
    
    def get_sole_type(self) -> str:
        return "Flat Sole"