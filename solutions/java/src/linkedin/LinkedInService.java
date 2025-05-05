package linkedin;

import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

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

    public User registerUser(String name, String email, String password) {
        User user = new User(name, email, password);
        users.put(user.getId(), user);
        return user;
    }

    public User loginUser(String email, String password) {
        for (User user : users.values()) {
            if (user.getEmail().equals(email) && user.getPassword().equals(password)) {
                return user;
            }
        }
        return null;
    }

    public void sendConnectionRequest(User sender, User receiver) {
        Connection connection = new Connection(sender, new Timestamp(System.currentTimeMillis()));
        receiver.getConnections().add(connection);
        sendNotification(receiver, NotificationType.CONNECTION_REQUEST, "New connection request from " + sender.getName());
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

    public JobPosting postJobListing(String title, String company, String description, String location) {
        JobPosting jobPosting = new JobPosting(title, company, description, location);
        jobPostings.put(jobPosting.getId(), jobPosting);
        return jobPosting;
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
        Message message = new Message(sender, receiver, content);
        receiver.addToInbox(message);
        sender.addToSentMessages(message);
        sendNotification(receiver, NotificationType.MESSAGE, "New message from " + sender.getName());
    }

    private void sendNotification(User receiver, NotificationType type, String message) {
        Notification notification = new Notification(receiver, type, message);
        receiver.addNotification(notification);
    }

    public List<Notification> getNotifications(String userId) {
        User user = users.get(userId);
        return user.getNotifications();
    }
}
