from board_entity import BoardEntity
from typing import List

class Board:
    def __init__(self, size: int, entities: List[BoardEntity]):
        self.size = size
        self.snakes_and_ladders = {}
        
        for entity in entities:
            self.snakes_and_ladders[entity.get_start()] = entity.get_end()
    
    def get_size(self) -> int:
        return self.size
    
    def get_final_position(self, position: int) -> int:
        return self.snakes_and_ladders.get(position, position)