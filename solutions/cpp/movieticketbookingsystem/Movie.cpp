#include "Movie.hpp"
#include <iostream>

Movie::Movie(std::string movieId, std::string title, std::string description,
             MovieGenre genre, int durationMinutes, std::string language)
    : movieId(movieId), title(title), description(description),
      genre(genre), durationMinutes(durationMinutes), language(language),
      active(true) {}

std::string Movie::getMovieId() const { return movieId; }
std::string Movie::getTitle() const { return title; }
std::string Movie::getDescription() const { return description; }
MovieGenre Movie::getGenre() const { return genre; }
int Movie::getDurationMinutes() const { return durationMinutes; }
std::string Movie::getLanguage() const { return language; }
bool Movie::isActive() const { return active; }
const std::vector<std::string>& Movie::getCast() const { return cast; }

void Movie::addCastMember(const std::string& actor) {
    cast.push_back(actor);
}

void Movie::setActive(bool status) {
    active = status;
}

void Movie::displayInfo() const {
    std::cout << "Movie: " << title << " (ID: " << movieId << ")" << std::endl;
    std::cout << "Description: " << description << std::endl;
    std::cout << "Genre: ";
    switch (genre) {
        case MovieGenre::ACTION: std::cout << "Action"; break;
        case MovieGenre::COMEDY: std::cout << "Comedy"; break;
        case MovieGenre::DRAMA: std::cout << "Drama"; break;
        case MovieGenre::HORROR: std::cout << "Horror"; break;
        case MovieGenre::SCIFI: std::cout << "Sci-Fi"; break;
        case MovieGenre::THRILLER: std::cout << "Thriller"; break;
    }
    std::cout << std::endl;
    std::cout << "Duration: " << durationMinutes << " minutes" << std::endl;
    std::cout << "Language: " << language << std::endl;
    std::cout << "Status: " << (active ? "Active" : "Inactive") << std::endl;
    
    if (!cast.empty()) {
        std::cout << "Cast:" << std::endl;
        for (const auto& actor : cast) {
            std::cout << "- " << actor << std::endl;
        }
    }
} 