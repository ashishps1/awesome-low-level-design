from .enemy import Enemy
from .enemy_registry import EnemyRegistry


class Game:
    """Game class demonstrating prototype pattern usage"""
    
    def __init__(self):
        self._enemy_registry = EnemyRegistry()
        self._setup_prototypes()
    
    def _setup_prototypes(self) -> None:
        """Setup initial enemy prototypes"""
        # Create prototype enemies
        warrior = Enemy("Warrior", 100, 50, True, "Sword")
        mage = Enemy("Mage", 80, 70, False, "Staff")
        archer = Enemy("Archer", 90, 80, False, "Bow")
        
        # Register prototypes
        self._enemy_registry.register_enemy("WARRIOR", warrior)
        self._enemy_registry.register_enemy("MAGE", mage)
        self._enemy_registry.register_enemy("ARCHER", archer)
    
    def spawn_enemy(self, enemy_type: str) -> Enemy:
        """Spawn a new enemy using prototype pattern"""
        return self._enemy_registry.get_enemy(enemy_type.upper())
    
    def get_available_enemy_types(self) -> list:
        """Get available enemy types"""
        return self._enemy_registry.get_available_types()


def prototype_demo():
    """Demonstrate Prototype pattern"""
    print("=== Prototype Pattern Demo ===")
    
    game = Game()
    
    print("Available enemy types:", game.get_available_enemy_types())
    
    # Spawn enemies using prototypes
    print("\n--- Spawning Enemies ---")
    warrior1 = game.spawn_enemy("WARRIOR")
    warrior2 = game.spawn_enemy("WARRIOR")
    mage1 = game.spawn_enemy("MAGE")
    
    print(f"Warrior 1: {warrior1}")
    print(f"Warrior 2: {warrior2}")
    print(f"Mage 1: {mage1}")
    
    # Verify they are different instances
    print(f"\nWarrior1 is Warrior2: {warrior1 is warrior2}")
    print(f"Warriors have same attributes: {warrior1.health == warrior2.health}")
    
    # Customize cloned enemies
    print("\n--- Customizing Cloned Enemies ---")
    warrior2.health = 120  # Strengthen the second warrior
    warrior2.weapon = "Battle Axe"
    
    print(f"Original Warrior: {warrior1}")
    print(f"Modified Warrior: {warrior2}")


if __name__ == "__main__":
    prototype_demo()