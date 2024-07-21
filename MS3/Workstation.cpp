// Name: Nathan Kong
// Seneca Student ID: 150950236
// Seneca email: nkong@myseneca.ca
// Date of completion: 2024-07-20
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Workstation.h"

namespace seneca {
    std::deque<CustomerOrder> g_pending{};
    std::deque<CustomerOrder> g_completed{};
    std::deque<CustomerOrder> g_incomplete{};

    Workstation::Workstation(const std::string& str) : Station(str) {};

    void Workstation::fill(std::ostream& os) {
        if (!m_orders.empty()) {
            m_orders.front().fillItem(*this, os);
        }
    }

    bool Workstation::attemptToMoveOrder() {
        if (!m_orders.empty()) {
            CustomerOrder& order = m_orders.front();

            // If order requires no more service at this station == item is filled
            // Not enough inventory == `getQuantity() == 0`
            if (order.isItemFilled(getItemName()) || getQuantity() == 0) {
                if (m_pNextStation) {
                    *m_pNextStation += std::move(order);
                } else if (order.isOrderFilled()) {
                    // No next station in the assembly line
                    g_completed.push_back(std::move(order));
                } else {
                    g_incomplete.push_back(std::move(order));
                }
                
                m_orders.pop_front();
                return true;
            }
        }
        return false;
    }

    void Workstation::setNextStation(Workstation* station) { m_pNextStation = station; }

    Workstation* Workstation::getNextStation() const { return m_pNextStation; }

    void Workstation::display(std::ostream& os) const {
        os << getItemName() << " --> ";
        if (m_pNextStation) {
            os << m_pNextStation->getItemName();
        } else {
            os << "End of Line";
        }
        os << std::endl;
    }

    Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
        m_orders.push_back(std::move(newOrder));
        return *this;
    }
}
