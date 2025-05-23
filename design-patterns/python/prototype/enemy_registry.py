from typing import Dict
from .enemy import Enemy


class EnemyRegistry:
    """Registry for managing enemy prototypes"""
    
    def __init__(self):
        self._prototypes: Dict[str, Enemy] = {}
    
    def register_enemy(self, key: str, enemy: Enemy) -> None:
        """Register an enemy prototype"""
        self._prototypes[key] = enemy
    
    def get_enemy(self, key: str) -> Enemy:
        """Get a cloned enemy from the registry"""
        if key not in self._prototypes:
            raise KeyError(f"Enemy type '{key}' not found in registry")
        return self._prototypes[key].clone()
    
    def get_available_types(self) -> list:
        """Get list of available enemy types"""
        return list(self._prototypes.keys())