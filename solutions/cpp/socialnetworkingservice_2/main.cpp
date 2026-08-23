// Single-file build (no header files) — merged from the multi-file project.
// Build & run:  g++ -std=c++17 main.cpp -o app && ./app
#include <algorithm>
#include <chrono>
#include <ctime>
#include <iostream>
#include <set>
#include <string>
#include <thread>
#include <vector>

using namespace std;

// ----- forward declarations -----
class Post;
class User;
class SocialNetwork;

// ===== Post.hpp =====
class Post {
private:
    string postId;
    string userId;
    string content;
    time_t timestamp;
    vector<string> likes;  // Vector of userIds who liked
    vector<string> comments;

public:
    Post(string postId, string userId, string content);
    
    string getPostId() const;
    string getUserId() const;
    string getContent() const;
    time_t getTimestamp() const;
    const vector<string>& getLikes() const;
    const vector<string>& getComments() const;
    
    void addLike(const string& userId);
    void removeLike(const string& userId);
    void addComment(const string& comment);
    void displayInfo() const;
};

// ===== User.hpp =====
class User {
private:
    string userId;
    string username;
    string email;
    set<string> friends;  // Set of friend userIds
    bool active;

public:
    User(string userId, string username, string email);
    
    string getUserId() const;
    string getUsername() const;
    string getEmail() const;
    const set<string>& getFriends() const;
    bool isActive() const;
    
    void addFriend(const string& friendId);
    void removeFriend(const string& friendId);
    void setActive(bool status);
    void displayInfo() const;
};

// ===== SocialNetwork.hpp =====
class SocialNetwork {
private:
    vector<User*> users;
    vector<Post*> posts;
    int userIdCounter;
    int postIdCounter;

public:
    SocialNetwork();
    ~SocialNetwork();
    
    // User management
    User* registerUser(const string& username, const string& email);
    void removeUser(const string& userId);
    bool addFriend(const string& userId1, const string& userId2);
    bool removeFriend(const string& userId1, const string& userId2);
    
    // Post management
    Post* createPost(const string& userId, const string& content);
    bool likePost(const string& userId, const string& postId);
    bool unlikePost(const string& userId, const string& postId);
    bool addComment(const string& postId, const string& comment);
    
    // Display functions
    void displayUserProfile(const string& userId) const;
    void displayUserFriends(const string& userId) const;
    void displayUserPosts(const string& userId) const;
    void displayAllUsers() const;
    void displayAllPosts() const;

private:
    User* findUser(const string& userId) const;
    Post* findPost(const string& postId) const;
    string generateUserId();
    string generatePostId();
};

// ===== Post.cpp =====
Post::Post(string postId, string userId, string content)
    : postId(postId), userId(userId), content(content) {
    timestamp = time(nullptr);
}

string Post::getPostId() const { return postId; }
string Post::getUserId() const { return userId; }
string Post::getContent() const { return content; }
time_t Post::getTimestamp() const { return timestamp; }
const vector<string>& Post::getLikes() const { return likes; }
const vector<string>& Post::getComments() const { return comments; }

void Post::addLike(const string& userId) {
    if (find(likes.begin(), likes.end(), userId) == likes.end()) {
        likes.push_back(userId);
    }
}

void Post::removeLike(const string& userId) {
    auto it = find(likes.begin(), likes.end(), userId);
    if (it != likes.end()) {
        likes.erase(it);
    }
}

void Post::addComment(const string& comment) {
    comments.push_back(comment);
}

void Post::displayInfo() const {
    cout << "\nPost ID: " << postId << endl;
    cout << "Content: " << content << endl;
    cout << "Time: " << ctime(&timestamp);
    cout << "Likes: " << likes.size() << endl;
    
    if (!comments.empty()) {
        cout << "Comments:" << endl;
        for (const auto& comment : comments) {
            cout << "- " << comment << endl;
        }
    }
} 

// ===== SocialNetwork.cpp =====
SocialNetwork::SocialNetwork() : userIdCounter(1), postIdCounter(1) {}

SocialNetwork::~SocialNetwork() {
    for (auto user : users) delete user;
    for (auto post : posts) delete post;
}

User* SocialNetwork::registerUser(const string& username, const string& email) {
    string userId = generateUserId();
    User* user = new User(userId, username, email);
    users.push_back(user);
    return user;
}

void SocialNetwork::removeUser(const string& userId) {
    auto it = find_if(users.begin(), users.end(),
        [userId](User* user) { return user->getUserId() == userId; });
    
    if (it != users.end()) {
        // Remove user from friends lists
        for (auto user : users) {
            user->removeFriend(userId);
        }
        
        // Remove user's posts
        posts.erase(
            remove_if(posts.begin(), posts.end(),
                [userId](Post* post) { return post->getUserId() == userId; }),
            posts.end()
        );
        
        delete *it;
        users.erase(it);
    }
}

bool SocialNetwork::addFriend(const string& userId1, const string& userId2) {
    User* user1 = findUser(userId1);
    User* user2 = findUser(userId2);
    
    if (!user1 || !user2 || userId1 == userId2) return false;
    
    user1->addFriend(userId2);
    user2->addFriend(userId1);
    return true;
}

bool SocialNetwork::removeFriend(const string& userId1, const string& userId2) {
    User* user1 = findUser(userId1);
    User* user2 = findUser(userId2);
    
    if (!user1 || !user2) return false;
    
    user1->removeFriend(userId2);
    user2->removeFriend(userId1);
    return true;
}

Post* SocialNetwork::createPost(const string& userId, const string& content) {
    if (!findUser(userId)) return nullptr;
    
    string postId = generatePostId();
    Post* post = new Post(postId, userId, content);
    posts.push_back(post);
    return post;
}

bool SocialNetwork::likePost(const string& userId, const string& postId) {
    User* user = findUser(userId);
    Post* post = findPost(postId);
    
    if (!user || !post) return false;
    
    post->addLike(userId);
    return true;
}

bool SocialNetwork::unlikePost(const string& userId, const string& postId) {
    User* user = findUser(userId);
    Post* post = findPost(postId);
    
    if (!user || !post) return false;
    
    post->removeLike(userId);
    return true;
}

bool SocialNetwork::addComment(const string& postId, const string& comment) {
    Post* post = findPost(postId);
    if (!post) return false;
    
    post->addComment(comment);
    return true;
}

void SocialNetwork::displayUserProfile(const string& userId) const {
    User* user = findUser(userId);
    if (user) {
        cout << "\nUser Profile:" << endl;
        user->displayInfo();
    }
}

void SocialNetwork::displayUserFriends(const string& userId) const {
    User* user = findUser(userId);
    if (!user) return;
    
    cout << "\nFriends of " << user->getUsername() << ":" << endl;
    for (const auto& friendId : user->getFriends()) {
        if (User* friend_ = findUser(friendId)) {
            cout << "- " << friend_->getUsername() << endl;
        }
    }
}

void SocialNetwork::displayUserPosts(const string& userId) const {
    User* user = findUser(userId);
    if (!user) return;
    
    cout << "\nPosts by " << user->getUsername() << ":" << endl;
    for (const auto& post : posts) {
        if (post->getUserId() == userId) {
            post->displayInfo();
        }
    }
}

void SocialNetwork::displayAllUsers() const {
    cout << "\nAll Users:" << endl;
    for (const auto& user : users) {
        user->displayInfo();
        cout << "------------------------" << endl;
    }
}

void SocialNetwork::displayAllPosts() const {
    cout << "\nAll Posts:" << endl;
    for (const auto& post : posts) {
        post->displayInfo();
        cout << "------------------------" << endl;
    }
}

User* SocialNetwork::findUser(const string& userId) const {
    auto it = find_if(users.begin(), users.end(),
        [userId](User* user) { return user->getUserId() == userId; });
    return it != users.end() ? *it : nullptr;
}

Post* SocialNetwork::findPost(const string& postId) const {
    auto it = find_if(posts.begin(), posts.end(),
        [postId](Post* post) { return post->getPostId() == postId; });
    return it != posts.end() ? *it : nullptr;
}

string SocialNetwork::generateUserId() {
    return "U" + to_string(userIdCounter++);
}

string SocialNetwork::generatePostId() {
    return "P" + to_string(postIdCounter++);
} 

// ===== User.cpp =====
User::User(string userId, string username, string email)
    : userId(userId), username(username), email(email), active(true) {}

string User::getUserId() const { return userId; }
string User::getUsername() const { return username; }
string User::getEmail() const { return email; }
const set<string>& User::getFriends() const { return friends; }
bool User::isActive() const { return active; }

void User::addFriend(const string& friendId) {
    friends.insert(friendId);
}

void User::removeFriend(const string& friendId) {
    friends.erase(friendId);
}

void User::setActive(bool status) {
    active = status;
}

void User::displayInfo() const {
    cout << "User: " << username << " (ID: " << userId << ")" << endl;
    cout << "Email: " << email << endl;
    cout << "Status: " << (active ? "Active" : "Inactive") << endl;
    cout << "Friends: " << friends.size() << endl;
} 

// ===== SocialNetworkDemo.cpp =====
int main() {
    SocialNetwork network;
    
    // Register users
    User* user1 = network.registerUser("john_doe", "john@email.com");
    User* user2 = network.registerUser("jane_smith", "jane@email.com");
    User* user3 = network.registerUser("bob_wilson", "bob@email.com");
    
    cout << "Initial users:" << endl;
    network.displayAllUsers();
    
    // Add friends
    network.addFriend(user1->getUserId(), user2->getUserId());
    network.addFriend(user2->getUserId(), user3->getUserId());
    
    // Create posts
    Post* post1 = network.createPost(user1->getUserId(), "Hello, world!");
    Post* post2 = network.createPost(user2->getUserId(), "Having a great day!");
    
    // Like and comment on posts
    network.likePost(user2->getUserId(), post1->getPostId());
    network.likePost(user3->getUserId(), post1->getPostId());
    network.addComment(post1->getPostId(), "Great post!");
    
    network.likePost(user1->getUserId(), post2->getPostId());
    network.addComment(post2->getPostId(), "Glad to hear that!");
    
    // Display user profiles and posts
    cout << "\nUser Profiles and Posts:" << endl;
    network.displayUserProfile(user1->getUserId());
    network.displayUserFriends(user1->getUserId());
    network.displayUserPosts(user1->getUserId());
    
    network.displayUserProfile(user2->getUserId());
    network.displayUserFriends(user2->getUserId());
    network.displayUserPosts(user2->getUserId());
    
    // Remove a friend and display updated info
    network.removeFriend(user1->getUserId(), user2->getUserId());
    cout << "\nAfter removing friendship:" << endl;
    network.displayUserFriends(user1->getUserId());
    
    return 0;
} 

