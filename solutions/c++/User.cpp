#include "User.h"

User::User(int userId, const string &userName, const string &userEmail)
    : id(userId), name(userName), email(userEmail) {}

int User::getId() const { return id; }
string User::getName() const { return name; }
string User::getEmail() const { return email; }


void User::setName(const string &newName) { name = newName; }
void User::setEmail(const string &newEmail) { email = newEmail; }
