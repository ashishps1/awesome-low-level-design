from .shoe_factory import ShoeFactory
from .casual_shoe_factory import CasualShoeFactory
from .formal_shoe_factory import FormalShoeFactory
from .sports_shoe_factory import SportsShoeFactory
from .shoe import Shoe


class ShoeManufacture:
    """Client that uses Abstract Factory to produce shoes"""
    
    @staticmethod
    def produce_shoe(shoe_type: str) -> Shoe:
        """Produce a shoe using the appropriate factory"""
        factory = ShoeManufacture._get_factory(shoe_type)
        sole = factory.create_sole()
        shoe_lace = factory.create_shoe_lace()
        return Shoe(sole, shoe_lace)
    
    @staticmethod
    def _get_factory(shoe_type: str) -> ShoeFactory:
        """Get the appropriate factory based on shoe type"""
        shoe_type = shoe_type.upper()
        
        if shoe_type == "CASUAL":
            return CasualShoeFactory()
        elif shoe_type == "FORMAL":
            return FormalShoeFactory()
        elif shoe_type == "SPORTS":
            return SportsShoeFactory()
        else:
            raise ValueError(f"Unknown shoe type: {shoe_type}")


def abstract_factory_demo():
    """Demonstrate Abstract Factory pattern"""
    print("=== Abstract Factory Pattern Demo ===")
    
    # Produce different types of shoes
    casual_shoe = ShoeManufacture.produce_shoe("CASUAL")
    formal_shoe = ShoeManufacture.produce_shoe("FORMAL")
    sports_shoe = ShoeManufacture.produce_shoe("SPORTS")
    
    print(f"Casual Shoe: {casual_shoe.describe()}")
    print(f"Formal Shoe: {formal_shoe.describe()}")
    print(f"Sports Shoe: {sports_shoe.describe()}")


if __name__ == "__main__":
    abstract_factory_demo()