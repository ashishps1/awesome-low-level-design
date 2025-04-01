package linkedin;

import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.UUID;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.CopyOnWriteArrayList;

public class LinkedInService {
    private static LinkedInService instance;
    private final Map<String, User> users;
    private final Map<String, JobPosting> jobPostings;
    private final Map<String, List<Notification>> notifications;

    private LinkedInService() {
        users = new ConcurrentHashMap<>();
        jobPostings = new ConcurrentHashMap<>();
        notifications = new ConcurrentHashMap<>();
    }

    public static synchronized LinkedInService getInstance() {
        if (instance == null) {
            instance = new LinkedInService();
        }
        return instance;
    }

    public void registerUser(User user) {
        users.put(user.getId(), user);
    }

    public User loginUser(String email, String password) {
        for (User user : users.values()) {
            if (user.getEmail().equals(email) && user.getPassword().equals(password)) {
                return user;
            }
        }
        return null;
    }

    public void updateUserProfile(User user) {
        users.put(user.getId(), user);
    }

    public void sendConnectionRequest(User sender, User receiver) {
        Connection connection = new Connection(sender, new Timestamp(System.currentTimeMillis()));
        receiver.getConnections().add(connection);
        Notification notification = new Notification(generateNotificationId(), receiver,
                NotificationType.CONNECTION_REQUEST, "New connection request from " + sender.getName(),
                new Timestamp(System.currentTimeMillis()));
        addNotification(receiver.getId(), notification);
    }

    public void acceptConnectionRequest(User user, User connectionUser) {
        for (Connection connection : user.getConnections()) {
            if (connection.getUser().equals(connectionUser)) {
                user.getConnections().add(new Connection(connectionUser, new Timestamp(System.currentTimeMillis())));
                break;
            }
        }
    }

    public List<User> searchUsers(String keyword) {
        List<User> results = new ArrayList<>();
        for (User user : users.values()) {
            if (user.getName().contains(keyword)) {
                results.add(user);
            }
        }
        return results;
    }

    public void postJobListing(JobPosting jobPosting) {
        jobPostings.put(jobPosting.getId(), jobPosting);
        for (User user : users.values()) {
            Notification notification = new Notification(generateNotificationId(), user,
                    NotificationType.JOB_POSTING, "New job posting: " + jobPosting.getTitle(),
                    new Timestamp(System.currentTimeMillis()));
            addNotification(user.getId(), notification);
        }
    }

    public List<JobPosting> searchJobPostings(String keyword) {
        List<JobPosting> results = new ArrayList<>();
        for (JobPosting jobPosting : jobPostings.values()) {
            if (jobPosting.getTitle().contains(keyword) || jobPosting.getDescription().contains(keyword)) {
                results.add(jobPosting);
            }
        }
        return results;
    }

    public void sendMessage(User sender, User receiver, String content) {
        Message message = new Message(generateMessageId(), sender, receiver, content,
                new Timestamp(System.currentTimeMillis()));
        receiver.getInbox().add(message);
        sender.getSentMessages().add(message);
        Notification notification = new Notification(generateNotificationId(), receiver,
                NotificationType.MESSAGE, "New message from " + sender.getName(),
                new Timestamp(System.currentTimeMillis()));
        addNotification(receiver.getId(), notification);
    }

    private void addNotification(String userId, Notification notification) {
        notifications.computeIfAbsent(userId, k -> new CopyOnWriteArrayList<>()).add(notification);
    }

    public List<Notification> getNotifications(String userId) {
        return notifications.getOrDefault(userId, new ArrayList<>());
    }

    private String generateNotificationId() {
        return UUID.randomUUID().toString();
    }

    private String generateMessageId() {
        return UUID.randomUUID().toString();
    }
}
