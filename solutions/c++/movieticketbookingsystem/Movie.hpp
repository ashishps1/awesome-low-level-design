#ifndef MOVIE_HPP
#define MOVIE_HPP

#include <string>
#include <vector>

enum class MovieGenre {
    ACTION,
    COMEDY,
    DRAMA,
    HORROR,
    SCIFI,
    THRILLER
};

class Movie {
private:
    std::string movieId;
    std::string title;
    std::string description;
    MovieGenre genre;
    int durationMinutes;
    std::string language;
    std::vector<std::string> cast;
    bool active;

public:
    Movie(std::string movieId, std::string title, std::string description,
          MovieGenre genre, int durationMinutes, std::string language);
    
    std::string getMovieId() const;
    std::string getTitle() const;
    std::string getDescription() const;
    MovieGenre getGenre() const;
    int getDurationMinutes() const;
    std::string getLanguage() const;
    bool isActive() const;
    const std::vector<std::string>& getCast() const;
    
    void addCastMember(const std::string& actor);
    void setActive(bool status);
    void displayInfo() const;
};

#endif 