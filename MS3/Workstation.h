// Name: Nathan Kong
// Seneca Student ID: 150950236
// Seneca email: nkong@myseneca.ca
// Date of completion: 2024-07-20
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H

#include <deque>
#include "CustomerOrder.h"
#include "Station.h"

namespace seneca {
    extern std::deque<CustomerOrder> g_pending;
    extern std::deque<CustomerOrder> g_completed;
    extern std::deque<CustomerOrder> g_incomplete;

    class Workstation : public Station {
        std::deque<CustomerOrder> m_orders{};
        Workstation* m_pNextStation{nullptr};
    public:
        Workstation(const std::string& str);
        void fill(std::ostream& os);
        bool attemptToMoveOrder();
        void setNextStation(Workstation* station = nullptr);
        Workstation* getNextStation() const;
        void display(std::ostream& os) const;
        Workstation& operator+=(CustomerOrder&& newOrder);

        // Workstation cannot be copied or moved
        Workstation(const Workstation&) = delete;
        Workstation& operator=(const Workstation&) = delete;
        Workstation(Workstation&&) = delete;
        Workstation& operator=(Workstation&&) = delete;
    };
}

#endif
