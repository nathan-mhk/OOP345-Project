// Name: Nathan Kong
// Seneca Student ID: 150950236
// Seneca email: nkong@myseneca.ca
// Date of completion: 2024-07-20
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SENECA_LINEMANAGER_H
#define SENECA_LINEMANAGER_H

#include "Workstation.h"
#include <vector>

namespace seneca {
    extern std::deque<CustomerOrder> g_pending;
    extern std::deque<CustomerOrder> g_completed;
    extern std::deque<CustomerOrder> g_incomplete;

    class LineManager {
        std::vector<Workstation*> m_activeLine{};
        size_t m_cntCustomerOrder{};
        Workstation* m_firstStation{nullptr};
    
    public:
        LineManager(const std::string& file, const std::vector<Workstation*>& stations);
        void reorderStations();
        bool run(std::ostream& os);
        void display(std::ostream& os) const;
    };
}

#endif
