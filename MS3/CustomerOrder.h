// Name: Nathan Kong
// Seneca Student ID: 150950236
// Seneca email: nkong@myseneca.ca
// Date of completion: 2024-07-04
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H

#include <string>
#include <iostream>
#include "Station.h"

namespace seneca {
    class CustomerOrder {
        struct Item {
            std::string m_itemName{""};
            size_t m_serialNumber{0};
            bool m_isFilled{false};

            Item(const std::string& src) : m_itemName(src) {};
        };

        std::string m_name{""};
        std::string m_product{""};
        size_t m_cntItem{0};
        Item** m_lstItem{};

        static size_t m_widthField;

    public:
        CustomerOrder() = default;
        CustomerOrder(const std::string& str);
        
        // Copy
        CustomerOrder(const CustomerOrder&);
        CustomerOrder& operator=(const CustomerOrder&) = delete;
        
        // Move
        CustomerOrder(CustomerOrder&& other) noexcept;
        CustomerOrder& operator=(CustomerOrder&& other) noexcept;

        ~CustomerOrder();

        bool isOrderFilled() const;
        bool isItemFilled(const std::string& itemName) const;
        void fillItem(Station& station, std::ostream& os);
        void display(std::ostream& os) const;
    };
}

#endif
