// Name: Nathan Kong
// Seneca Student ID: 150950236
// Seneca email: nkong@myseneca.ca
// Date of completion: 2024-07-04
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SENECA_STATION_H
#define SENECA_STATION_H

#include <string>
#include <iostream>

namespace seneca {
    class Station {
        int m_id{};
        std::string m_name{};
        std::string m_desc{};
        size_t m_nextSerial{};
        size_t m_quantity{};

        static size_t m_widthField;
        static size_t id_generator;
    
    public:
        Station(const std::string& str);
        const std::string& getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(std::ostream& os, bool full) const;
    };
}

#endif
