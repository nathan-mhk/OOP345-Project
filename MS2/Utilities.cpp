// Name: Nathan Kong
// Seneca Student ID: 150950236
// Seneca email: nkong@myseneca.ca
// Date of completion: 2024-07-04
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Utilities.h"

namespace seneca {
    // Helper Functions
    std::string trim(const std::string& str) {
        size_t start = str.find_first_not_of(" \r\n\t");
        size_t last = str.find_last_not_of(" \r\n\t");

        if (start == std::string::npos) start = 0;
        if (last == std::string::npos) last = str.length() - 1;

        // [start, last - start + 1) == [start, last - start]
        return str.substr(start, last - start + 1);
    }

    char Utilities::m_delimiter{};

    void Utilities::setFieldWidth(size_t newWidth) { m_widthField = newWidth; }

    size_t Utilities::getFieldWidth() const { return m_widthField; }

    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
        more = false;

        if (str[next_pos] == m_delimiter) {
            throw std::to_string(m_delimiter) + " found at " + std::to_string(next_pos);
        }

        std::string token{""};

        size_t pos = str.find(m_delimiter, next_pos);
        if (pos != std::string::npos) {
            // `token` will not contain any delimiters ~~~~v
            token = trim(str.substr(next_pos, pos - next_pos));

            more = true;
            next_pos = pos + 1;

        } else {
            token = trim(str.substr(next_pos));
        }

        if (token.length() > m_widthField) m_widthField = token.length();
        return token;
    }

    void Utilities::setDelimiter(char newDelimiter) { m_delimiter = newDelimiter; }

    char Utilities::getDelimiter() { return m_delimiter; }
}
