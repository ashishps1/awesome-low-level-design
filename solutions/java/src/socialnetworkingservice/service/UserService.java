package socialnetworkingservice.service;

import socialnetworkingservice.model.User;
import socialnetworkingservice.repository.UserRepository;

public class UserService {
    private final UserRepository userRepository = UserRepository.getInstance();

    public User createUser(String name, String email) {
        User user = new User(name, email);
        userRepository.save(user);
        return user;
    }

    public void addFriend(String userId1, String userId2) {
        User user1 = userRepository.findById(userId1);
        User user2 = userRepository.findById(userId2);

        user1.addFriend(user2);
        user2.addFriend(user1);
    }

    public User getUserById(String userId) {
        return userRepository.findById(userId);
    }
}
