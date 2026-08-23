// Single-file build (no header files) — merged from the multi-file project.
// Build & run:  g++ -std=c++17 main.cpp -o app && ./app
#include <algorithm>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ----- forward declarations -----
class Comment;
class Post;
class User;
class StackOverflow;

// ===== Comment.hpp =====
class Comment {
private:
    string commentId;
    string userId;
    string content;
    time_t timestamp;

public:
    Comment(string commentId, string userId, string content);
    
    string getCommentId() const;
    string getUserId() const;
    string getContent() const;
    time_t getTimestamp() const;
    
    void displayInfo() const;
};

// ===== Post.hpp =====
enum class PostType {
    QUESTION,
    ANSWER
};

class Post {
private:
    string postId;
    string userId;
    string content;
    vector<string> tags;
    vector<Comment*> comments;
    vector<string> votes;  // userIds who voted
    int score;
    bool accepted;
    PostType type;
    time_t timestamp;

public:
    Post(string postId, string userId, string content,
         const vector<string>& tags, PostType type);
    ~Post();
    
    string getPostId() const;
    string getUserId() const;
    string getContent() const;
    const vector<string>& getTags() const;
    const vector<Comment*>& getComments() const;
    int getScore() const;
    bool isAccepted() const;
    PostType getType() const;
    time_t getTimestamp() const;
    
    void addComment(Comment* comment);
    bool addVote(const string& userId);
    bool removeVote(const string& userId);
    void setAccepted(bool status);
    void displayInfo() const;
};

// ===== User.hpp =====
class User {
private:
    string userId;
    string username;
    string email;
    int reputation;
    vector<string> badges;
    bool active;

public:
    User(string userId, string username, string email);
    
    string getUserId() const;
    string getUsername() const;
    string getEmail() const;
    int getReputation() const;
    const vector<string>& getBadges() const;
    bool isActive() const;
    
    void updateReputation(int points);
    void addBadge(const string& badge);
    void setActive(bool status);
    void displayInfo() const;
};

// ===== StackOverflow.hpp =====
class StackOverflow {
private:
    vector<User*> users;
    vector<Post*> posts;
    int userIdCounter;
    int postIdCounter;
    int commentIdCounter;

public:
    StackOverflow();
    ~StackOverflow();
    
    // User management
    User* registerUser(const string& username, const string& email);
    void removeUser(const string& userId);
    
    // Post management
    Post* addQuestion(const string& userId, const string& content,
                     const vector<string>& tags);
    Post* addAnswer(const string& userId, const string& questionId,
                   const string& content);
    Comment* addComment(const string& userId, const string& postId,
                       const string& content);
    
    // Voting and acceptance
    bool votePost(const string& userId, const string& postId);
    bool unvotePost(const string& userId, const string& postId);
    bool acceptAnswer(const string& userId, const string& answerId);
    
    // Search and display
    vector<Post*> searchQuestions(const string& tag) const;
    void displayUserProfile(const string& userId) const;
    void displayQuestion(const string& questionId) const;
    void displayAllQuestions() const;

private:
    User* findUser(const string& userId) const;
    Post* findPost(const string& postId) const;
    void updateUserReputation(const string& userId, int points);
    string generateUserId();
    string generatePostId();
    string generateCommentId();
};

// ===== Comment.cpp =====
Comment::Comment(string commentId, string userId, string content)
    : commentId(commentId), userId(userId), content(content) {
    timestamp = time(nullptr);
}

string Comment::getCommentId() const { return commentId; }
string Comment::getUserId() const { return userId; }
string Comment::getContent() const { return content; }
time_t Comment::getTimestamp() const { return timestamp; }

void Comment::displayInfo() const {
    cout << "- " << content << " (by User " << userId << ")" << endl;
} 

// ===== Post.cpp =====
Post::Post(string postId, string userId, string content,
           const vector<string>& tags, PostType type)
    : postId(postId), userId(userId), content(content), tags(tags),
      score(0), accepted(false), type(type) {
    timestamp = time(nullptr);
}

Post::~Post() {
    for (auto comment : comments) {
        delete comment;
    }
}

string Post::getPostId() const { return postId; }
string Post::getUserId() const { return userId; }
string Post::getContent() const { return content; }
const vector<string>& Post::getTags() const { return tags; }
const vector<Comment*>& Post::getComments() const { return comments; }
int Post::getScore() const { return score; }
bool Post::isAccepted() const { return accepted; }
PostType Post::getType() const { return type; }
time_t Post::getTimestamp() const { return timestamp; }

void Post::addComment(Comment* comment) {
    comments.push_back(comment);
}

bool Post::addVote(const string& userId) {
    if (find(votes.begin(), votes.end(), userId) == votes.end()) {
        votes.push_back(userId);
        score++;
        return true;
    }
    return false;
}

bool Post::removeVote(const string& userId) {
    auto it = find(votes.begin(), votes.end(), userId);
    if (it != votes.end()) {
        votes.erase(it);
        score--;
        return true;
    }
    return false;
}

void Post::setAccepted(bool status) {
    accepted = status;
}

void Post::displayInfo() const {
    cout << "\nPost ID: " << postId << endl;
    cout << "Type: " << (type == PostType::QUESTION ? "Question" : "Answer") << endl;
    cout << "Content: " << content << endl;
    cout << "Score: " << score << endl;
    cout << "Status: " << (accepted ? "Accepted" : "Not Accepted") << endl;
    
    if (!tags.empty()) {
        cout << "Tags: ";
        for (const auto& tag : tags) {
            cout << tag << " ";
        }
        cout << endl;
    }
    
    if (!comments.empty()) {
        cout << "Comments:" << endl;
        for (const auto& comment : comments) {
            comment->displayInfo();
        }
    }
    
    cout << "Time: " << ctime(&timestamp);
} 

// ===== StackOverflow.cpp =====
StackOverflow::StackOverflow() : userIdCounter(1), postIdCounter(1), commentIdCounter(1) {}

StackOverflow::~StackOverflow() {
    for (auto user : users) delete user;
    for (auto post : posts) delete post;
}

User* StackOverflow::registerUser(const string& username, const string& email) {
    string userId = generateUserId();
    User* user = new User(userId, username, email);
    users.push_back(user);
    return user;
}

void StackOverflow::removeUser(const string& userId) {
    auto it = find_if(users.begin(), users.end(),
        [userId](User* user) { return user->getUserId() == userId; });
    
    if (it != users.end()) {
        delete *it;
        users.erase(it);
    }
}

Post* StackOverflow::addQuestion(const string& userId, const string& content,
                                const vector<string>& tags) {
    if (!findUser(userId)) return nullptr;
    
    string postId = generatePostId();
    Post* question = new Post(postId, userId, content, tags, PostType::QUESTION);
    posts.push_back(question);
    return question;
}

Post* StackOverflow::addAnswer(const string& userId, const string& questionId,
                              const string& content) {
    if (!findUser(userId)) return nullptr;
    
    Post* question = findPost(questionId);
    if (!question || question->getType() != PostType::QUESTION) return nullptr;
    
    string postId = generatePostId();
    Post* answer = new Post(postId, userId, content, vector<string>(), PostType::ANSWER);
    posts.push_back(answer);
    return answer;
}

Comment* StackOverflow::addComment(const string& userId, const string& postId,
                                 const string& content) {
    if (!findUser(userId)) return nullptr;
    
    Post* post = findPost(postId);
    if (!post) return nullptr;
    
    string commentId = generateCommentId();
    Comment* comment = new Comment(commentId, userId, content);
    post->addComment(comment);
    return comment;
}

bool StackOverflow::votePost(const string& userId, const string& postId) {
    User* user = findUser(userId);
    Post* post = findPost(postId);
    
    if (!user || !post || userId == post->getUserId()) return false;
    
    if (post->addVote(userId)) {
        updateUserReputation(post->getUserId(), 10);  // +10 for upvote
        return true;
    }
    return false;
}

bool StackOverflow::unvotePost(const string& userId, const string& postId) {
    Post* post = findPost(postId);
    if (!post) return false;
    
    if (post->removeVote(userId)) {
        updateUserReputation(post->getUserId(), -10);  // -10 for removed upvote
        return true;
    }
    return false;
}

bool StackOverflow::acceptAnswer(const string& userId, const string& answerId) {
    Post* answer = findPost(answerId);
    if (!answer || answer->getType() != PostType::ANSWER) return false;
    
    answer->setAccepted(true);
    updateUserReputation(answer->getUserId(), 15);  // +15 for accepted answer
    return true;
}

vector<Post*> StackOverflow::searchQuestions(const string& tag) const {
    vector<Post*> results;
    for (const auto& post : posts) {
        if (post->getType() == PostType::QUESTION) {
            const auto& tags = post->getTags();
            if (find(tags.begin(), tags.end(), tag) != tags.end()) {
                results.push_back(post);
            }
        }
    }
    return results;
}

void StackOverflow::displayUserProfile(const string& userId) const {
    User* user = findUser(userId);
    if (!user) return;
    
    user->displayInfo();
    
    cout << "\nPosts by " << user->getUsername() << ":" << endl;
    for (const auto& post : posts) {
        if (post->getUserId() == userId) {
            post->displayInfo();
        }
    }
}

void StackOverflow::displayQuestion(const string& questionId) const {
    Post* question = findPost(questionId);
    if (!question || question->getType() != PostType::QUESTION) return;
    
    question->displayInfo();
    
    cout << "\nAnswers:" << endl;
    for (const auto& post : posts) {
        if (post->getType() == PostType::ANSWER) {
            post->displayInfo();
        }
    }
}

void StackOverflow::displayAllQuestions() const {
    cout << "\nAll Questions:" << endl;
    for (const auto& post : posts) {
        if (post->getType() == PostType::QUESTION) {
            post->displayInfo();
            cout << "------------------------" << endl;
        }
    }
}

User* StackOverflow::findUser(const string& userId) const {
    auto it = find_if(users.begin(), users.end(),
        [userId](User* user) { return user->getUserId() == userId; });
    return it != users.end() ? *it : nullptr;
}

Post* StackOverflow::findPost(const string& postId) const {
    auto it = find_if(posts.begin(), posts.end(),
        [postId](Post* post) { return post->getPostId() == postId; });
    return it != posts.end() ? *it : nullptr;
}

void StackOverflow::updateUserReputation(const string& userId, int points) {
    if (User* user = findUser(userId)) {
        user->updateReputation(points);
    }
}

string StackOverflow::generateUserId() {
    return "U" + to_string(userIdCounter++);
}

string StackOverflow::generatePostId() {
    return "P" + to_string(postIdCounter++);
}

string StackOverflow::generateCommentId() {
    return "C" + to_string(commentIdCounter++);
} 

// ===== User.cpp =====
User::User(string userId, string username, string email)
    : userId(userId), username(username), email(email), reputation(1), active(true) {}

string User::getUserId() const { return userId; }
string User::getUsername() const { return username; }
string User::getEmail() const { return email; }
int User::getReputation() const { return reputation; }
const vector<string>& User::getBadges() const { return badges; }
bool User::isActive() const { return active; }

void User::updateReputation(int points) {
    reputation += points;
}

void User::addBadge(const string& badge) {
    badges.push_back(badge);
}

void User::setActive(bool status) {
    active = status;
}

void User::displayInfo() const {
    cout << "User: " << username << " (ID: " << userId << ")" << endl;
    cout << "Email: " << email << endl;
    cout << "Reputation: " << reputation << endl;
    cout << "Status: " << (active ? "Active" : "Inactive") << endl;
    
    if (!badges.empty()) {
        cout << "Badges:" << endl;
        for (const auto& badge : badges) {
            cout << "- " << badge << endl;
        }
    }
} 

// ===== StackOverflowDemo.cpp =====
int main() {
    StackOverflow stackoverflow;
    
    // Register users
    User* user1 = stackoverflow.registerUser("john_doe", "john@email.com");
    User* user2 = stackoverflow.registerUser("alice_smith", "alice@email.com");
    User* user3 = stackoverflow.registerUser("bob_wilson", "bob@email.com");
    
    cout << "Initial users:" << endl;
    stackoverflow.displayUserProfile(user1->getUserId());
    
    // Add questions
    vector<string> tags = {"c++", "programming"};
    Post* question1 = stackoverflow.addQuestion(
        user1->getUserId(),
        "How do I use smart pointers in C++?",
        tags
    );
    
    // Add answers
    Post* answer1 = stackoverflow.addAnswer(
        user2->getUserId(),
        question1->getPostId(),
        "Smart pointers automatically manage memory for you..."
    );
    
    Post* answer2 = stackoverflow.addAnswer(
        user3->getUserId(),
        question1->getPostId(),
        "There are three main types of smart pointers..."
    );
    
    // Add comments
    stackoverflow.addComment(
        user1->getUserId(),
        answer1->getPostId(),
        "Thanks, that's helpful!"
    );
    
    // Vote on posts
    stackoverflow.votePost(user2->getUserId(), question1->getPostId());
    stackoverflow.votePost(user3->getUserId(), answer1->getPostId());
    stackoverflow.votePost(user1->getUserId(), answer2->getPostId());
    
    // Accept answer
    stackoverflow.acceptAnswer(user1->getUserId(), answer1->getPostId());
    
    // Display results
    cout << "\nQuestion with answers:" << endl;
    stackoverflow.displayQuestion(question1->getPostId());
    
    cout << "\nUser profiles after activity:" << endl;
    stackoverflow.displayUserProfile(user1->getUserId());
    stackoverflow.displayUserProfile(user2->getUserId());
    
    // Search questions
    cout << "\nSearching for C++ questions:" << endl;
    auto results = stackoverflow.searchQuestions("c++");
    for (const auto& question : results) {
        question->displayInfo();
    }
    
    return 0;
} 

