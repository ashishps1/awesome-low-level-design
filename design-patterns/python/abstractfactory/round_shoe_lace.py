from .shoe_lace import ShoeLace


class RoundShoeLace(ShoeLace):
    """Concrete Product - Round shoe lace for casual and sports shoes"""
    
    def get_lace_type(self) -> str:
        return "Round Shoe Lace"