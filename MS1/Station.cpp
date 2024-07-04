// Name: Nathan Kong
// Seneca Student ID: 150950236
// Seneca email: nkong@myseneca.ca
// Date of completion: 2024-07-
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Station.h"
#include "Utilities.h"

namespace seneca {
    size_t Station::m_widthField{0};
    size_t Station::id_generator{0};

    Station::Station(const std::string& str) {
        Utilities utils;
        size_t next_pos{0};
        bool more{true};

        // extractToken can throw exceptions
        // try {
            m_name = utils.extractToken(str, next_pos, more);
            m_nextSerial = std::stoul(utils.extractToken(str, next_pos, more));
            m_quantity = std::stoul(utils.extractToken(str, next_pos, more));

            size_t utilsWidth = utils.getFieldWidth();
            m_widthField = m_widthField > utilsWidth ? m_widthField : utilsWidth;

            m_desc = utils.extractToken(str, next_pos, more);

        // } catch (...) {
        //     std::cout << "Error: failed to extract token" << std::endl;
        // }

        /**
         * Every time a new instance is created, the current value of the id_generator
         * is stored in that instance, and id_generator is incremented.
         * 
         * ^ Should be id_generator++ but the output does not match
         */
        m_id = ++id_generator;
    }

    const std::string& Station::getItemName() const { return m_name; }

    size_t Station::getNextSerialNumber() { return m_nextSerial++; }

    size_t Station::getQuantity() const { return m_quantity; }

    void Station::updateQuantity() { m_quantity--; }

    void Station::display(std::ostream& os, bool full) const {
        os.width(3);
        os.fill('0');
        os << std::right << m_id << " | ";
        os.fill(' ');

        os.width(m_widthField);
        os << std::left << m_name << " | ";

        os.width(6);
        os.fill('0');
        os << std::right << m_nextSerial << " | ";
        os.fill(' ');
        
        if (full) {
            os.width(4);
            os << std::right << m_quantity << " | " << m_desc;
        }

        os << std::endl;
    }
}
