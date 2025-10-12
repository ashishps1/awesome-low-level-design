from typing import Dict
from member import Member
from connection import Connection
from notification_service import NotificationService
from enums import ConnectionStatus, NotificationType
import uuid
import threading
from notification import Notification

class ConnectionService:
    def __init__(self, notification_service: NotificationService):
        self.notification_service = notification_service
        self.connection_requests: Dict[str, Connection] = {}
        self.lock = threading.Lock()

    def send_request(self, from_member: Member, to_member: Member) -> str:
        connection = Connection(from_member, to_member)
        request_id = str(uuid.uuid4())
        
        with self.lock:
            self.connection_requests[request_id] = connection

        print(f"{from_member.get_name()} sent a connection request to {to_member.get_name()}.")

        notification = Notification(
            to_member.get_id(),
            NotificationType.CONNECTION_REQUEST,
            f"{from_member.get_name()} wants to connect with you. Request ID: {request_id}"
        )
        self.notification_service.send_notification(to_member, notification)

        return request_id

    def accept_request(self, request_id: str) -> None:
        with self.lock:
            request = self.connection_requests.get(request_id)
            
            if request and request.get_status() == ConnectionStatus.PENDING:
                request.set_status(ConnectionStatus.ACCEPTED)

                from_member = request.get_from_member()
                to_member = request.get_to_member()

                from_member.add_connection(to_member)
                to_member.add_connection(from_member)

                print(f"{to_member.get_name()} accepted the connection request from {from_member.get_name()}.")
                del self.connection_requests[request_id]
            else:
                print("Invalid or already handled request ID.")