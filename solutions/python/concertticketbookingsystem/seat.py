from enums import SeatType, SeatStatus
import threading

class SeatNotAvailableException(Exception):
    pass

class Seat:
    def __init__(self, id: str, seatNumber: str, seatType: SeatType, price: float):
        self.id = id
        self.seatNumber = seatNumber
        self.seatType = seatType
        self.price = price
        self.seatStatus = SeatStatus.AVAILABLE
        self._lock = threading.Lock()
    
    # We will use a state machine to ensure correctness
    # This way, cant book if seat is already reserved,
    # Cant release is seat is not booked etc.
    # The lock ensures thread safety, state machine ensures correctness
    def book(self):
        with self._lock:
            if self.seatStatus != SeatStatus.AVAILABLE:
                raise Exception("Seat not available")
            self.seatStatus = SeatStatus.RESERVED

    def confirm_booking(self):
        # This function is called after payment is confirmed so the seat status
        # gets updated from reserved to booked.
        with self._lock:
            if self.seatStatus != SeatStatus.RESERVED:
                raise Exception("Invalid state")
            self.seatStatus = SeatStatus.BOOKED

    def release(self):
        with self._lock:
            # If not really required by added for sake of correctness in transitions
            if self.seatStatus == SeatStatus.AVAILABLE:
                print("Seat was already in available state.")
                return
            self.seatStatus = SeatStatus.AVAILABLE

    def getPrice(self) -> float:
        return self.price
    
    def getId(self) -> str:
        return self.id
    
    def getSeatType(self) -> "SeatType":
        return self.seatType
    
    def getSeatNumber(self) -> str:
        return self.seatNumber
    
    def getSeatStatus(self) -> "SeatStatus":
        return self.seatStatus
        
    def __str__(self):
        return f"Seat: {self.id}, Status: {self.seatStatus}"
    
    def __repr__(self):
        return f"Seat(id={self.id})"