from staff import Chef, Waiter
from table import Table
from menu_item import MenuItem
from typing import Dict, List, Optional
import threading
from menu import Menu

class Restaurant:
    _instance = None
    _lock = threading.Lock()
    
    def __new__(cls):
        if cls._instance is None:
            with cls._lock:
                if cls._instance is None:
                    cls._instance = super().__new__(cls)
                    cls._instance._initialized = False
        return cls._instance
    
    def __init__(self):
        if not self._initialized:
            self._waiters: Dict[str, Waiter] = {}
            self._chefs: Dict[str, Chef] = {}
            self._tables: Dict[int, Table] = {}
            self._menu = Menu()
            self._initialized = True
    
    @classmethod
    def get_instance(cls):
        return cls()
    
    def add_waiter(self, waiter: Waiter):
        self._waiters[waiter.id] = waiter
    
    def get_waiter(self, waiter_id: str) -> Optional[Waiter]:
        return self._waiters.get(waiter_id)
    
    def add_chef(self, chef: Chef):
        self._chefs[chef.id] = chef
    
    def get_chef(self, chef_id: str) -> Optional[Chef]:
        return self._chefs.get(chef_id)
    
    def get_chefs(self) -> List[Chef]:
        return list(self._chefs.values())
    
    def get_waiters(self) -> List[Waiter]:
        return list(self._waiters.values())
    
    def add_table(self, table: Table):
        self._tables[table.id] = table
    
    @property
    def menu(self) -> Menu:
        return self._menu