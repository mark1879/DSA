#ifndef UTILS_HPP
#define UTILS_HPP
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class Utils {
public: 
    static std::vector<std::string> StrTok(const std::string& s) {
        std::vector<std::string> words;

        char* word = strtok(const_cast<char*>(s.c_str()), " ");
        while(word != nullptr) {
            std::string trim_word = Trim(word);
            if (trim_word.size() > 0)
	            words.push_back(trim_word);

	        word = strtok(nullptr, " ");
        }

        return words;
    }

private:
    static std::string Trim(const std::string& s) {
        return Rtrim(Ltrim(s));
    }

    static std::string Ltrim(const std::string& s)
    {
        size_t start = s.find_first_not_of(kWhiteSpace);
        return (start == std::string::npos) ? "" : s.substr(start);
    }

    static std::string Rtrim(const std::string& s)
    {
        size_t end = s.find_last_not_of(kWhiteSpace);
        return (end == std::string::npos) ? "" : s.substr(0, end + 1);
    }

private:
    static const std::string kWhiteSpace;
};

const std::string Utils::kWhiteSpace = " \t\f\v\n\r *.,?!\"";

#endif