#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User
{
private:
    int id;
    string name;
    string email;

public:
    User(int userId, const string &userName, const string &userEmail);

    // Getters
    int getId() const;
    string getName() const;
    string getEmail() const;

    // Setters
    void setName(const string &newName);
    void setEmail(const string &newEmail);
};

#endif
