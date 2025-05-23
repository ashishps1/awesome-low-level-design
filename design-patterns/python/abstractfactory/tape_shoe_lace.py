from .shoe_lace import ShoeLace


class TapeShoeLace(ShoeLace):
    """Concrete Product - Tape shoe lace for formal shoes"""
    
    def get_lace_type(self) -> str:
        return "Tape Shoe Lace"