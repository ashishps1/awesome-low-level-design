from .sole import Sole


class BumpySole(Sole):
    """Concrete Product - Bumpy Sole for sports shoes"""
    
    def get_sole_type(self) -> str:
        return "Bumpy Sole"