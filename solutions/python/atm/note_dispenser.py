import threading
from typing import Optional
from dispense_chain import DispenseChain

class NoteDispenser(DispenseChain):
    def __init__(self, note_value: int, num_notes: int):
        self._note_value = note_value
        self._num_notes = num_notes
        self._next_chain: Optional[DispenseChain] = None
        self._lock = threading.Lock()
    
    def set_next_chain(self, next_chain: DispenseChain):
        self._next_chain = next_chain
    
    def dispense(self, amount: int):
        with self._lock:
            if amount >= self._note_value:
                num_to_dispense = min(amount // self._note_value, self._num_notes)
                remaining_amount = amount - (num_to_dispense * self._note_value)
                
                if num_to_dispense > 0:
                    print(f"Dispensing {num_to_dispense} x ${self._note_value} note(s)")
                    self._num_notes -= num_to_dispense
                
                if remaining_amount > 0 and self._next_chain is not None:
                    self._next_chain.dispense(remaining_amount)
            elif self._next_chain is not None:
                self._next_chain.dispense(amount)
    
    def can_dispense(self, amount: int) -> bool:
        with self._lock:
            if amount < 0:
                return False
            if amount == 0:
                return True
            
            num_to_use = min(amount // self._note_value, self._num_notes)
            remaining_amount = amount - (num_to_use * self._note_value)
            
            if remaining_amount == 0:
                return True
            if self._next_chain is not None:
                return self._next_chain.can_dispense(remaining_amount)
            return False
        
class NoteDispenser20(NoteDispenser):
    def __init__(self, num_notes: int):
        super().__init__(20, num_notes)

class NoteDispenser50(NoteDispenser):
    def __init__(self, num_notes: int):
        super().__init__(50, num_notes)

class NoteDispenser100(NoteDispenser):
    def __init__(self, num_notes: int):
        super().__init__(100, num_notes)