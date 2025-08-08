package linkedin.services;

import linkedin.enums.ConnectionStatus;
import linkedin.enums.NotificationType;
import linkedin.entities.Connection;
import linkedin.entities.Member;
import linkedin.entities.Notification;

import java.util.Map;
import java.util.UUID;
import java.util.concurrent.ConcurrentHashMap;

public class ConnectionService {
    private final NotificationService notificationService;
    // Simulates a DB table for connection requests
    private final Map<String, Connection> connectionRequests = new ConcurrentHashMap<>();

    public ConnectionService(NotificationService notificationService) {
        this.notificationService = notificationService;
    }

    public String sendRequest(Member from, Member to) {
        Connection connection = new Connection(from, to);
        String requestId = UUID.randomUUID().toString();
        connectionRequests.put(requestId, connection);

        System.out.printf("%s sent a connection request to %s.%n", from.getName(), to.getName());

        Notification notification = new Notification(
                to.getId(),
                NotificationType.CONNECTION_REQUEST,
                from.getName() + " wants to connect with you. Request ID: " + requestId
        );
        notificationService.sendNotification(to, notification);

        return requestId;
    }

    public void acceptRequest(String requestId) {
        Connection request = connectionRequests.get(requestId);
        if (request != null && request.getStatus() == ConnectionStatus.PENDING) {
            request.setStatus(ConnectionStatus.ACCEPTED);

            Member from = request.getFromMember();
            Member to = request.getToMember();

            from.addConnection(to);
            to.addConnection(from);

            System.out.printf("%s accepted the connection request from %s.%n", to.getName(), from.getName());
            connectionRequests.remove(requestId); // Clean up
        } else {
            System.out.println("Invalid or already handled request ID.");
        }
    }
}
