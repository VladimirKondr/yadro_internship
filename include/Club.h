#ifndef CLUB_H
#define CLUB_H

#include "Table.h"
#include "events/TimePoint.h"
#include "events/EventBase.h"
#include "Client.h"

#include <vector>
#include <queue>
#include <string>
#include <memory>
#include <unordered_map>

namespace computer_club {

class Club {
private:
    int table_count_;
    TimePoint open_time_;
    TimePoint close_time_;
    double hourly_rate_;
    
    std::vector<Table> tables_;
    std::unordered_map<std::string, Client> clients_;
    std::queue<std::string> waiting_clients_;
    std::vector<std::shared_ptr<Event>> all_events_;

    bool IsTableIdValid(int table_id) const;
    bool IsClientInClub(const std::string& client_name) const;
    bool HasFreeTable() const;
    Table* GetTable(int table_id);
    
    void HandleClientArrival(const std::shared_ptr<Event>& event);
    void HandleClientSeating(const std::shared_ptr<Event>& event);
    void HandleClientWaiting(const std::shared_ptr<Event>& event);
    void HandleClientLeaving(const std::shared_ptr<Event>& event);
    void SeatClientFromQueue(const TimePoint& time, int table_id);

public:
    Club(int table_count, TimePoint open_time, TimePoint close_time, double hourly_rate);
    
    void ProcessEvent(const std::shared_ptr<Event>& event);
    void ClosingTime();
    
    const std::vector<std::shared_ptr<Event>>& GetAllEvents() const;
    const std::vector<Table>& GetTables() const;
    TimePoint GetOpenTime() const;
    TimePoint GetCloseTime() const;
};

} // namespace computer_club

#endif // CLUB_H