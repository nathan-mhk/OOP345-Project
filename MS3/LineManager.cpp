// Name: Nathan Kong
// Seneca Student ID: 150950236
// Seneca email: nkong@myseneca.ca
// Date of completion: 2024-07-20
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "LineManager.h"
#include <algorithm>
#include <fstream>
#include "Utilities.h"

namespace seneca {
    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
        std::ifstream ifs(file, std::ios::in);

        if (!ifs.good()) {
            throw std::string("Unable to open [") + file + "] file.";
        }

        std::vector<std::string> data{};
        std::string line{};

        // The only place where we are allowed to use loops
        do {
            std::getline(ifs, line);
            data.push_back(line);
        } while (ifs.good());

        ifs.close();

        Utilities utils{};
        bool found{false};
        Workstation* prevStation{nullptr};
        std::for_each(data.begin(), data.end(), [&](const std::string& str) {
            size_t pos{};
            bool more{true};
            std::string stationName{};

            stationName = utils.extractToken(str, pos, more);

            std::vector<Workstation*>::const_iterator currStation = std::find_if(stations.begin(), stations.end(), [&](Workstation* station) {
                return station->getItemName() == stationName;
            });

            if (currStation == stations.end()) {
                throw std::string("Unable to find current station [") + stationName + "] in the assembly line.";
            }

            if (more) {
                // Not last station
                stationName = utils.extractToken(str, pos, more);

                std::vector<Workstation*>::const_iterator nextStation = std::find_if(stations.begin(), stations.end(), [&](Workstation* station) {
                    return station->getItemName() == stationName;
                });

                if (nextStation == stations.end()) {
                    throw std::string("Unable to find next station [") + stationName + "] in the assembly line.";
                }

                if (*nextStation == *currStation) {
                    throw std::string("Station [") + (*nextStation)->getItemName() + "] cannot be its own next station.";
                }

                (*currStation)->setNextStation(*nextStation);
            } else {
                // Last station
                if (found) {
                    throw std::string("More than one last-station found.");
                }
                prevStation = *currStation;
                found = true;
                (*currStation)->setNextStation(nullptr);
            }
            m_activeLine.push_back(*currStation);
        });
        
        // Find first station
        size_t count{};
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* s) {
            found = false;
            std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* station) {
                // Added `!found` to prevent finding prevStation more than once in a single iteration
                if (!found && station->getNextStation() == prevStation) {
                    found = true;
                    prevStation = station;
                }
            });
            ++count;
            if (!found) {
                // No station is pointing at the current station
                if (count != m_activeLine.size()) {
                    /**
                     * If there's only one first-station, it should took exactly `.size()` iterations to find the first-station.
                     * Otherwise, `count` will be < `.size()`
                     */
                    throw std::string("More than one first-station found.");
                }
                m_firstStation = prevStation;
            }
        });

        // Total number of orders in the `g_pending` queue initially.
        m_cntCustomerOrder = g_pending.size();
    }

    void LineManager::reorderStations() {
        std::vector<Workstation*> orderedLines{};
        Workstation* currStation = m_firstStation;

        while (currStation) {
            orderedLines.push_back(currStation);
            currStation = currStation->getNextStation();
        }

        m_activeLine = orderedLines;
    }

    bool LineManager::run(std::ostream& os) {
        static size_t itrNum{0};

        os << "Line Manager Iteration: " << ++itrNum << std::endl;

        if (!g_pending.empty()) {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }

        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* station) {
            station->fill(os);
        });

        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* station) {
            station->attemptToMoveOrder();
        });

        return (g_completed.size() + g_incomplete.size()) == m_cntCustomerOrder;
    }

    void LineManager::display(std::ostream& os) const {
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* station) {
            station->display(os);
        });
    }
}