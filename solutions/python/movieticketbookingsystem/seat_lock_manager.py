from typing import Dict, List
from show import Show
from seat import Seat
from enums import SeatStatus
import threading
from concurrent.futures import ThreadPoolExecutor
import time

class SeatLockManager:
    def __init__(self):
        self.locked_seats: Dict[Show, Dict[Seat, str]] = {}
        self.executor = ThreadPoolExecutor(max_workers=5)
        self.LOCK_TIMEOUT_SECONDS = 0.5  # 0.5 seconds. In real world, timeout would be in minutes

    def lock_seats(self, show: Show, seats: List[Seat], user_id: str) -> None:
        # Use a lock per show to ensure atomicity for that specific show
        show_lock = getattr(show, '_lock', None)
        if show_lock is None:
            show._lock = threading.Lock()
            show_lock = show._lock

        with show_lock:
            # Check if any of the requested seats are already locked or booked
            for seat in seats:
                if seat.get_status() != SeatStatus.AVAILABLE:
                    print(f"Seat {seat.get_id()} is not available.")
                    return

            # Lock the seats
            for seat in seats:
                seat.set_status(SeatStatus.LOCKED)

            if show not in self.locked_seats:
                self.locked_seats[show] = {}
            
            for seat in seats:
                self.locked_seats[show][seat] = user_id

            # Schedule a task to unlock the seats after a timeout
            self.executor.submit(self._unlock_after_timeout, show, seats, user_id)
            print(f"Locked seats: {[seat.get_id() for seat in seats]} for user {user_id}")

    def _unlock_after_timeout(self, show: Show, seats: List[Seat], user_id: str) -> None:
        time.sleep(self.LOCK_TIMEOUT_SECONDS)
        self.unlock_seats(show, seats, user_id)

    def unlock_seats(self, show: Show, seats: List[Seat], user_id: str) -> None:
        show_lock = getattr(show, '_lock', None)
        if show_lock is None:
            return

        with show_lock:
            show_locks = self.locked_seats.get(show)
            if show_locks is not None:
                for seat in seats:
                    # Only unlock if it's still locked by the same user (prevents race conditions)
                    if seat in show_locks and show_locks[seat] == user_id:
                        del show_locks[seat]
                        if seat.get_status() == SeatStatus.LOCKED:
                            seat.set_status(SeatStatus.AVAILABLE)
                            print(f"Unlocked seat: {seat.get_id()} due to timeout.")
                        else:
                            print(f"Unlocked seat: {seat.get_id()} due to booking completion.")
                
                if not show_locks:
                    del self.locked_seats[show]

    def shutdown(self) -> None:
        print("Shutting down SeatLockProvider scheduler.")
        self.executor.shutdown(wait=True)