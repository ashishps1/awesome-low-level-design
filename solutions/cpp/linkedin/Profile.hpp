#ifndef PROFILE_HPP
#define PROFILE_HPP

#include <string>
#include <vector>

struct Experience {
    std::string company;
    std::string position;
    std::string startDate;
    std::string endDate;
    std::string description;
};

struct Education {
    std::string school;
    std::string degree;
    std::string field;
    std::string startDate;
    std::string endDate;
};

class Profile {
private:
    std::string name;
    std::string headline;
    std::string about;
    std::string location;
    std::vector<std::string> skills;
    std::vector<Experience> experiences;
    std::vector<Education> educations;

public:
    Profile(std::string name, std::string headline);

    std::string getName() const;
    
    void setAbout(const std::string& about);
    void setLocation(const std::string& location);
    void addSkill(const std::string& skill);
    void addExperience(const Experience& exp);
    void addEducation(const Education& edu);
    void displayInfo() const;
};

#endif 