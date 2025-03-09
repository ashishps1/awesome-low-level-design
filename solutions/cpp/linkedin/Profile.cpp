#include "Profile.hpp"
#include <iostream>

Profile::Profile(std::string name, std::string headline)
    : name(name), headline(headline) {}


std::string Profile::getName() const{
    return name;
}

void Profile::setAbout(const std::string& about) {
    this->about = about;
}

void Profile::setLocation(const std::string& location) {
    this->location = location;
}

void Profile::addSkill(const std::string& skill) {
    skills.push_back(skill);
}

void Profile::addExperience(const Experience& exp) {
    experiences.push_back(exp);
}

void Profile::addEducation(const Education& edu) {
    educations.push_back(edu);
}

void Profile::displayInfo() const {
    std::cout << "\nProfile Information:" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Headline: " << headline << std::endl;
    if (!about.empty()) {
        std::cout << "About: " << about << std::endl;
    }
    if (!location.empty()) {
        std::cout << "Location: " << location << std::endl;
    }
    
    if (!skills.empty()) {
        std::cout << "\nSkills:" << std::endl;
        for (const auto& skill : skills) {
            std::cout << "- " << skill << std::endl;
        }
    }
    
    if (!experiences.empty()) {
        std::cout << "\nExperience:" << std::endl;
        for (const auto& exp : experiences) {
            std::cout << exp.position << " at " << exp.company << std::endl;
            std::cout << exp.startDate << " - " << exp.endDate << std::endl;
            std::cout << exp.description << std::endl;
            std::cout << "------------------------" << std::endl;
        }
    }
    
    if (!educations.empty()) {
        std::cout << "\nEducation:" << std::endl;
        for (const auto& edu : educations) {
            std::cout << edu.degree << " in " << edu.field << std::endl;
            std::cout << edu.school << std::endl;
            std::cout << edu.startDate << " - " << edu.endDate << std::endl;
            std::cout << "------------------------" << std::endl;
        }
    }
} 