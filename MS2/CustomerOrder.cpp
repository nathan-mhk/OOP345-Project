// Name: Nathan Kong
// Seneca Student ID: 150950236
// Seneca email: nkong@myseneca.ca
// Date of completion: 2024-07-04
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "CustomerOrder.h"
#include "Utilities.h"

namespace seneca {
    size_t CustomerOrder::m_widthField{};

    CustomerOrder::CustomerOrder(const std::string& str) {
        Utilities utils{};
        size_t next_pos{};
        bool more{true};

        // try {
            m_name = utils.extractToken(str, next_pos, more);
            m_product = utils.extractToken(str, next_pos, more);

            // Count the number of items
            m_cntItem = 1;
            for (const char& c : str.substr(next_pos)) {
                if (c == utils.getDelimiter()) ++m_cntItem;
            }

            m_lstItem = new Item*[m_cntItem];

            for (size_t i = 0; more && i < m_cntItem; ++i) {
                std::string itemName = utils.extractToken(str, next_pos, more);
                m_lstItem[i] = new Item(itemName);
            }
        // } catch (...) {
        //     std::cout << "Error failed to extract token" << std::endl;
        // }

        size_t utilsWidth = utils.getFieldWidth();
        m_widthField = m_widthField > utilsWidth ? m_widthField : utilsWidth;
    }

    CustomerOrder::CustomerOrder(const CustomerOrder&) {
        throw "Copy constructor is not allowed";
    }

    CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept {
        *this = std::move(other);
    }

    void CustomerOrder::clear() {
        for (size_t i = 0; i < m_cntItem; ++i) {
            delete m_lstItem[i];
            m_lstItem[i] = nullptr;
        }
        delete[] m_lstItem;
        m_lstItem = nullptr;
    }

    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept {
        if (this != &other) {
            clear();
            m_name = other.m_name;
            m_product = other.m_product;
            m_cntItem = other.m_cntItem;
            m_lstItem = other.m_lstItem;

            other.m_name = "";
            other.m_product = "";
            other.m_cntItem = 0;
            other.m_lstItem = nullptr;
        }
        return *this;
    }

    CustomerOrder::~CustomerOrder() {
        clear();
    }

    bool CustomerOrder::isOrderFilled() const {
        for (size_t i = 0; i < m_cntItem; ++i) {
            if (!m_lstItem[i]->m_isFilled) return false;
        }
        return true;
    }

    bool CustomerOrder::isItemFilled(const std::string& itemName) const {
        for (size_t i = 0; i < m_cntItem; ++i) {
            if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled) return false;
        }
        return true;
    }

    void CustomerOrder::fillItem(Station& station, std::ostream& os) {
        const std::string& itemName = station.getItemName();

        for (size_t i = 0; i < m_cntItem; ++i) {
            Item& item = *m_lstItem[i];
            if (item.m_itemName == itemName) {
                if (station.getQuantity() > 0) {
                    station.updateQuantity();

                    item.m_serialNumber = station.getNextSerialNumber();
                    item.m_isFilled = true;

                    // There are indentations in the sample output
                    os << "    Filled " << m_name << ", " << m_product << " [" << item.m_itemName << "]" << std::endl;
                } else {
                    os << "    Unable to fill " << m_name << ", " << m_product << " [" << item.m_itemName << "]" << std::endl;
                }
                return;     // This modifier fills **one** item in the current order
            }
        }
    }

    void CustomerOrder::display(std::ostream& os) const {
        os << m_name << " - " << m_product << std::endl;

        for (size_t i = 0; i < m_cntItem; ++i) {
            Item& item = *m_lstItem[i];

            os << "[";
            os.width(6);
            os.fill('0');
            os << item.m_serialNumber << "] ";
            os.fill(' ');

            os.width(m_widthField);
            os << std::left << item.m_itemName << " - ";

            if (item.m_isFilled) os << "FILLED" << std::endl;
            else os << "TO BE FILLED" << std::endl;
        }
    }
}
