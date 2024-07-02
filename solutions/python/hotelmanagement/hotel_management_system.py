from datetime import datetime, timedelta
from typing import Dict
from collections import defaultdict
from guest import Guest
from room import Room, RoomStatus
from reservation import Reservation, ReservationStatus
from payment import Payment
import uuid

class HotelManagementSystem:
    _instance = None

    def __new__(cls):
        if cls._instance is None:
            cls._instance = super().__new__(cls)
            cls._instance.guests = {}
            cls._instance.rooms = {}
            cls._instance.reservations = {}
        return cls._instance

    @staticmethod
    def get_instance():
        if HotelManagementSystem._instance is None:
            HotelManagementSystem()
        return HotelManagementSystem._instance

    def add_guest(self, guest: Guest):
        self.guests[guest.id] = guest

    def get_guest(self, guest_id: str) -> Guest:
        return self.guests.get(guest_id)

    def add_room(self, room: Room):
        self.rooms[room.id] = room

    def get_room(self, room_id: str) -> Room:
        return self.rooms.get(room_id)

    def book_room(self, guest: Guest, room: Room, check_in_date: datetime, check_out_date: datetime) -> Reservation:
        if room.status == RoomStatus.AVAILABLE:
            room.book()
            reservation_id = self.generate_reservation_id()
            reservation = Reservation(reservation_id, guest, room, check_in_date, check_out_date)
            self.reservations[reservation_id] = reservation
            return reservation
        return None

    def cancel_reservation(self, reservation_id: str):
        reservation = self.reservations.get(reservation_id)
        if reservation:
            reservation.cancel()
            self.reservations.pop(reservation_id, None)

    def check_in(self, reservation_id: str):
        reservation = self.reservations.get(reservation_id)
        if reservation and reservation.status == ReservationStatus.CONFIRMED:
            reservation.room.check_in()
        else:
            raise Exception("Invalid reservation or reservation not confirmed.")

    def check_out(self, reservation_id: str, payment: Payment):
        reservation = self.reservations.get(reservation_id)
        if reservation and reservation.status == ReservationStatus.CONFIRMED:
            room = reservation.room
            amount = room.price * (reservation.check_out_date - reservation.check_in_date).days
            if payment.process_payment(amount):
                room.check_out()
                self.reservations.pop(reservation_id, None)
            else:
                raise Exception("Payment failed.")
        else:
            raise Exception("Invalid reservation or reservation not confirmed.")

    def generate_reservation_id(self) -> str:
        return "RES" + uuid.uuid4().hex[:8].upper()
