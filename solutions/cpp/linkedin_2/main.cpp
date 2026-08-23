// Single-file build (no header files) — merged from the multi-file project.
// Build & run:  g++ -std=c++17 main.cpp -o app && ./app
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ----- forward declarations -----
class Experience;
class Education;
class Profile;
class User;
class Post;
class LinkedInManager;

// ===== Profile.hpp =====
struct Experience {
    string company;
    string position;
    string startDate;
    string endDate;
    string description;
};

struct Education {
    string school;
    string degree;
    string field;
    string startDate;
    string endDate;
};

class Profile {
private:
    string name;
    string headline;
    string about;
    string location;
    vector<string> skills;
    vector<Experience> experiences;
    vector<Education> educations;

public:
    Profile(string name, string headline);

    string getName() const;
    
    void setAbout(const string& about);
    void setLocation(const string& location);
    void addSkill(const string& skill);
    void addExperience(const Experience& exp);
    void addEducation(const Education& edu);
    void displayInfo() const;
};

// ===== User.hpp =====
class User {
private:
    string userId;
    string email;
    string password;
    Profile* profile;
    vector<User*> connections;
    vector<Post*> posts;
    bool active;

public:
    User(string userId, string email, string password);
    ~User();
    
    string getUserId() const;
    string getEmail() const;
    Profile* getProfile() const;
    bool isActive() const;
    const vector<User*>& getConnections() const;
    const vector<Post*>& getPosts() const;
    
    void setProfile(Profile* profile);
    void addConnection(User* user);
    void removeConnection(User* user);
    void addPost(Post* post);
    void setActive(bool status);
    void displayInfo() const;
};

// ===== Post.hpp =====
enum class PostType {
    TEXT,
    IMAGE,
    VIDEO,
    ARTICLE
};

class Post {
private:
    string postId;
    User* author;
    string content;
    PostType type;
    string timestamp;
    vector<User*> likes;
    vector<string> comments;

public:
    Post(string postId, User* author, string content, 
         PostType type, string timestamp);
    
    string getPostId() const;
    User* getAuthor() const;
    string getContent() const;
    PostType getType() const;
    string getTimestamp() const;
    const vector<User*>& getLikes() const;
    const vector<string>& getComments() const;
    
    void addLike(User* user);
    void removeLike(User* user);
    void addComment(const string& comment);
    void displayInfo() const;
};

// ===== LinkedInManager.hpp =====
class LinkedInManager {
private:
    vector<User*> users;
    vector<Post*> posts;
    int postIdCounter;

public:
    LinkedInManager();
    ~LinkedInManager();
    
    void addUser(User* user);
    Post* createPost(string userId, string content,
                    PostType type, string timestamp);
    
    bool addConnection(string userId1, string userId2);
    bool removeConnection(string userId1, string userId2);
    
    bool likePost(string userId, string postId);
    bool unlikePost(string userId, string postId);
    bool commentOnPost(string userId, string postId,
                      const string& comment);
    
    void displayUserProfile(string userId) const;
    void displayUserConnections(string userId) const;
    void displayUserPosts(string userId) const;
    void displayAllUsers() const;
    
private:
    User* findUser(const string& userId) const;
    Post* findPost(const string& postId) const;
    string generatePostId();
};

// ===== LinkedInManager.cpp =====
LinkedInManager::LinkedInManager() : postIdCounter(1) {}

LinkedInManager::~LinkedInManager() {
    for (auto user : users) delete user;
    for (auto post : posts) delete post;
}

void LinkedInManager::addUser(User* user) {
    users.push_back(user);
}

Post* LinkedInManager::createPost(string userId, string content,
                                PostType type, string timestamp) {
    User* user = findUser(userId);
    if (!user || !user->isActive()) return nullptr;
    
    Post* post = new Post(generatePostId(), user, content, type, timestamp);
    posts.push_back(post);
    user->addPost(post);
    return post;
}

bool LinkedInManager::addConnection(string userId1, string userId2) {
    User* user1 = findUser(userId1);
    User* user2 = findUser(userId2);
    
    if (!user1 || !user2 || !user1->isActive() || !user2->isActive()) {
        return false;
    }
    
    user1->addConnection(user2);
    return true;
}

bool LinkedInManager::removeConnection(string userId1, string userId2) {
    User* user1 = findUser(userId1);
    User* user2 = findUser(userId2);
    
    if (!user1 || !user2) return false;
    
    user1->removeConnection(user2);
    return true;
}

bool LinkedInManager::likePost(string userId, string postId) {
    User* user = findUser(userId);
    Post* post = findPost(postId);
    
    if (!user || !post || !user->isActive()) return false;
    
    post->addLike(user);
    return true;
}

bool LinkedInManager::unlikePost(string userId, string postId) {
    User* user = findUser(userId);
    Post* post = findPost(postId);
    
    if (!user || !post) return false;
    
    post->removeLike(user);
    return true;
}

bool LinkedInManager::commentOnPost(string userId, string postId,
                                  const string& comment) {
    User* user = findUser(userId);
    Post* post = findPost(postId);
    
    if (!user || !post || !user->isActive()) return false;
    
    post->addComment(comment);
    return true;
}

void LinkedInManager::displayUserProfile(string userId) const {
    User* user = findUser(userId);
    if (user) {
        user->displayInfo();
    }
}

void LinkedInManager::displayUserConnections(string userId) const {
    User* user = findUser(userId);
    if (!user) return;
    
    cout << "\nConnections for " << user->getEmail() << ":" << endl;
    for (const auto& connection : user->getConnections()) {
        connection->displayInfo();
        cout << "------------------------" << endl;
    }
}

void LinkedInManager::displayUserPosts(string userId) const {
    User* user = findUser(userId);
    if (!user) return;
    
    cout << "\nPosts by " << user->getEmail() << ":" << endl;
    for (const auto& post : user->getPosts()) {
        post->displayInfo();
        cout << "------------------------" << endl;
    }
}

void LinkedInManager::displayAllUsers() const {
    cout << "\nAll Users:" << endl;
    for (const auto& user : users) {
        user->displayInfo();
        cout << "------------------------" << endl;
    }
}

User* LinkedInManager::findUser(const string& userId) const {
    for (auto user : users) {
        if (user->getUserId() == userId) return user;
    }
    return nullptr;
}

Post* LinkedInManager::findPost(const string& postId) const {
    for (auto post : posts) {
        if (post->getPostId() == postId) return post;
    }
    return nullptr;
}

string LinkedInManager::generatePostId() {
    return "P" + to_string(postIdCounter++);
} 

// ===== Post.cpp =====
Post::Post(string postId, User* author, string content,
           PostType type, string timestamp)
    : postId(postId), author(author), content(content),
      type(type), timestamp(timestamp) {}

string Post::getPostId() const { return postId; }
User* Post::getAuthor() const { return author; }
string Post::getContent() const { return content; }
PostType Post::getType() const { return type; }
string Post::getTimestamp() const { return timestamp; }
const vector<User*>& Post::getLikes() const { return likes; }
const vector<string>& Post::getComments() const { return comments; }

void Post::addLike(User* user) {
    if (user && find(likes.begin(), likes.end(), user) == likes.end()) {
        likes.push_back(user);
    }
}

void Post::removeLike(User* user) {
    auto it = find(likes.begin(), likes.end(), user);
    if (it != likes.end()) {
        likes.erase(it);
    }
}

void Post::addComment(const string& comment) {
    comments.push_back(comment);
}

void Post::displayInfo() const {
    cout << "\nPost Details:" << endl;
    cout << "ID: " << postId << endl;
    cout << "Author: " << author->getProfile()->getName() << endl;
    cout << "Type: ";
    switch (type) {
        case PostType::TEXT: cout << "Text"; break;
        case PostType::IMAGE: cout << "Image"; break;
        case PostType::VIDEO: cout << "Video"; break;
        case PostType::ARTICLE: cout << "Article"; break;
    }
    cout << endl;
    cout << "Content: " << content << endl;
    cout << "Timestamp: " << timestamp << endl;
    cout << "Likes: " << likes.size() << endl;
    cout << "Comments: " << comments.size() << endl;
    
    if (!comments.empty()) {
        cout << "\nComments:" << endl;
        for (const auto& comment : comments) {
            cout << "- " << comment << endl;
        }
    }
} 

// ===== Profile.cpp =====
Profile::Profile(string name, string headline)
    : name(name), headline(headline) {}


string Profile::getName() const{
    return name;
}

void Profile::setAbout(const string& about) {
    this->about = about;
}

void Profile::setLocation(const string& location) {
    this->location = location;
}

void Profile::addSkill(const string& skill) {
    skills.push_back(skill);
}

void Profile::addExperience(const Experience& exp) {
    experiences.push_back(exp);
}

void Profile::addEducation(const Education& edu) {
    educations.push_back(edu);
}

void Profile::displayInfo() const {
    cout << "\nProfile Information:" << endl;
    cout << "Name: " << name << endl;
    cout << "Headline: " << headline << endl;
    if (!about.empty()) {
        cout << "About: " << about << endl;
    }
    if (!location.empty()) {
        cout << "Location: " << location << endl;
    }
    
    if (!skills.empty()) {
        cout << "\nSkills:" << endl;
        for (const auto& skill : skills) {
            cout << "- " << skill << endl;
        }
    }
    
    if (!experiences.empty()) {
        cout << "\nExperience:" << endl;
        for (const auto& exp : experiences) {
            cout << exp.position << " at " << exp.company << endl;
            cout << exp.startDate << " - " << exp.endDate << endl;
            cout << exp.description << endl;
            cout << "------------------------" << endl;
        }
    }
    
    if (!educations.empty()) {
        cout << "\nEducation:" << endl;
        for (const auto& edu : educations) {
            cout << edu.degree << " in " << edu.field << endl;
            cout << edu.school << endl;
            cout << edu.startDate << " - " << edu.endDate << endl;
            cout << "------------------------" << endl;
        }
    }
} 

// ===== User.cpp =====
User::User(string userId, string email, string password)
    : userId(userId), email(email), password(password), profile(nullptr), active(true) {}

User::~User() {
    delete profile;
    for (auto post : posts) {
        delete post;
    }
}

string User::getUserId() const { return userId; }
string User::getEmail() const { return email; }
Profile* User::getProfile() const { return profile; }
bool User::isActive() const { return active; }
const vector<User*>& User::getConnections() const { return connections; }
const vector<Post*>& User::getPosts() const { return posts; }

void User::setProfile(Profile* profile) {
    delete this->profile;
    this->profile = profile;
}

void User::addConnection(User* user) {
    if (user && find(connections.begin(), connections.end(), user) == connections.end()) {
        connections.push_back(user);
        user->connections.push_back(this);
    }
}

void User::removeConnection(User* user) {
    auto it = find(connections.begin(), connections.end(), user);
    if (it != connections.end()) {
        connections.erase(it);
        auto it2 = find(user->connections.begin(), user->connections.end(), this);
        if (it2 != user->connections.end()) {
            user->connections.erase(it2);
        }
    }
}

void User::addPost(Post* post) {
    posts.push_back(post);
}

void User::setActive(bool status) {
    active = status;
}

void User::displayInfo() const {
    cout << "User ID: " << userId << endl;
    cout << "Email: " << email << endl;
    cout << "Status: " << (active ? "Active" : "Inactive") << endl;
    cout << "Connections: " << connections.size() << endl;
    cout << "Posts: " << posts.size() << endl;
    if (profile) {
        profile->displayInfo();
    }
} 

// ===== LinkedInDemo.cpp =====
int main() {
    LinkedInManager linkedin;
    
    // Create users
    User* user1 = new User("U001", "john@example.com", "password123");
    User* user2 = new User("U002", "jane@example.com", "password456");
    
    // Create profiles
    Profile* profile1 = new Profile("John Doe", "Software Engineer");
    Profile* profile2 = new Profile("Jane Smith", "Product Manager");
    
    user1->setProfile(profile1);
    user2->setProfile(profile2);
    
    // Add skills
    profile1->addSkill("C++");
    profile1->addSkill("Python");
    profile2->addSkill("Product Management");
    profile2->addSkill("Agile");
    
    // Add experience
    Experience exp1{"Tech Corp", "Software Engineer", "2020", "Present",
                   "Developing enterprise applications"};
    profile1->addExperience(exp1);
    
    // Add education
    Education edu1{"University of Tech", "BS", "Computer Science",
                  "2016", "2020"};
    profile1->addEducation(edu1);
    
    linkedin.addUser(user1);
    linkedin.addUser(user2);
    
    // Create connection
    linkedin.addConnection("U001", "U002");
    
    // Create posts
    Post* post = linkedin.createPost("U001", "Hello LinkedIn!",
                                   PostType::TEXT, "2024-01-01");
    if (post) {
        linkedin.likePost("U002", post->getPostId());
        linkedin.commentOnPost("U002", post->getPostId(),
                             "Great to see you here!");
    }
    
    // Display information
    cout << "User Profiles:" << endl;
    linkedin.displayUserProfile("U001");
    linkedin.displayUserProfile("U002");
    
    cout << "\nUser Connections:" << endl;
    linkedin.displayUserConnections("U001");
    
    cout << "\nUser Posts:" << endl;
    linkedin.displayUserPosts("U001");
    
    return 0;
} 

