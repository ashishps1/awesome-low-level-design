from abc import ABC, abstractmethod
from typing import List, Optional, TYPE_CHECKING
from split import Split
from user import User

class SplitStrategy(ABC):
    @abstractmethod
    def calculate_splits(self, total_amount: float, paid_by: 'User', participants: List['User'], split_values: Optional[List[float]]) -> List['Split']:
        pass

class EqualSplitStrategy(SplitStrategy):
    def calculate_splits(self, total_amount: float, paid_by: 'User', participants: List['User'], split_values: Optional[List[float]]) -> List['Split']:
        splits = []
        amount_per_person = total_amount / len(participants)
        for participant in participants:
            splits.append(Split(participant, amount_per_person))
        return splits

class ExactSplitStrategy(SplitStrategy):
    def calculate_splits(self, total_amount: float, paid_by: 'User', participants: List['User'], split_values: Optional[List[float]]) -> List['Split']:
        if len(participants) != len(split_values):
            raise ValueError("Number of participants and split values must match.")
        if abs(sum(split_values) - total_amount) > 0.01:
            raise ValueError("Sum of exact amounts must equal the total expense amount.")
        
        splits = []
        for i in range(len(participants)):
            splits.append(Split(participants[i], split_values[i]))
        return splits

class PercentageSplitStrategy(SplitStrategy):
    def calculate_splits(self, total_amount: float, paid_by: 'User', participants: List['User'], split_values: Optional[List[float]]) -> List['Split']:
        if len(participants) != len(split_values):
            raise ValueError("Number of participants and split values must match.")
        if abs(sum(split_values) - 100.0) > 0.01:
            raise ValueError("Sum of percentages must be 100.")
        
        splits = []
        for i in range(len(participants)):
            amount = (total_amount * split_values[i]) / 100.0
            splits.append(Split(participants[i], amount))
        return splits