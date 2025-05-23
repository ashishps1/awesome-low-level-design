import copy
from .enemy_prototype import EnemyPrototype


class Enemy(EnemyPrototype):
    """Concrete Prototype - Enemy with cloning capability"""
    
    def __init__(self, enemy_type: str, health: int, speed: int, armored: bool, weapon: str):
        self._enemy_type = enemy_type
        self._health = health
        self._speed = speed
        self._armored = armored
        self._weapon = weapon
    
    def clone(self) -> 'Enemy':
        """Create a deep copy of this enemy"""
        return copy.deepcopy(self)
    
    # Getters
    @property
    def enemy_type(self) -> str:
        return self._enemy_type
    
    @property
    def health(self) -> int:
        return self._health
    
    @property
    def speed(self) -> int:
        return self._speed
    
    @property
    def armored(self) -> bool:
        return self._armored
    
    @property
    def weapon(self) -> str:
        return self._weapon
    
    # Setters for customization after cloning
    @health.setter
    def health(self, health: int):
        self._health = health
    
    @speed.setter
    def speed(self, speed: int):
        self._speed = speed
    
    @armored.setter
    def armored(self, armored: bool):
        self._armored = armored
    
    @weapon.setter
    def weapon(self, weapon: str):
        self._weapon = weapon
    
    def __str__(self) -> str:
        return (f"Enemy(type={self._enemy_type}, health={self._health}, "
                f"speed={self._speed}, armored={self._armored}, weapon={self._weapon})")