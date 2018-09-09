#ifndef COUNTRY_HPP
#define COUNTRY_HPP

#include <string>

using namespace std;

class Country {
public:
    enum Language {
        CHINESE,
        SPANISH,
        ENGLISH,
        HINDI,
        ARABIC
    };
    Country(const std::string &name, Language language);
    Language getLanguage() const;
    std::string getName() const;
    ~Country();
private:
    string name;
    Language language;
    Country(const Country &other);
    Country& operator=(const Country &other);
};

#endif
