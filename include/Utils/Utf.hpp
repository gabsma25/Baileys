#ifndef UTf_HELPER_HPP
#define UTf_HELPER_HPP

#include <SFML/Graphics.hpp>
#include <string>

namespace Utf {
    // Converte std::string (UTF-8) para sf::String (internamente UTF-32)
    inline sf::String toSf(const std::string& s) {
        return sf::String::fromUtf8(s.begin(), s.end());
    }

    inline sf::String toSf(const char* s) {
        const std::string tmp(s);
        return sf::String::fromUtf8(tmp.begin(), tmp.end());
    }
}

#endif // UTf_HELPER_HPP
