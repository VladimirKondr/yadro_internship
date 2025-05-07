#ifndef CLUB_H
#define CLUB_H

#include "Client.h"
#include "Table.h"
#include "events/EventBase.h"
#include "events/TimePoint.h"

#include <memory>
#include <queue>
#include <vector>

namespace computer_club {

class Club {
   private:
    TimePoint open_time_;
    TimePoint close_time_;
    double hourly_rate_;

    std::queue<std::shared_ptr<Client>> waiting_clients_;
    std::vector<std::shared_ptr<Event>> all_events_;

    Club(TimePoint open_time, TimePoint close_time, double hourly_rate);
    static std::unique_ptr<Club> instance;

    void HandleClientArrival(const std::shared_ptr<Event>& event);
    void HandleClientSeating(const std::shared_ptr<Event>& event);
    void HandleClientWaiting(const std::shared_ptr<Event>& event);
    void HandleClientLeaving(const std::shared_ptr<Event>& event);
    void SeatClientFromQueue(const TimePoint& time, const std::shared_ptr<Table>& table);

   public:
    Club(const Club&) = delete;
    Club& operator=(const Club&) = delete;
    Club(Club&&) = default;
    Club& operator=(Club&&) = default;
    ~Club() = default;

    static Club& GetInstance(
        TimePoint open_time = {}, TimePoint close_time = {}, double hourly_rate = 0.0);

    void ProcessEvent(const std::shared_ptr<Event>& event);
    void ClosingTime();

    [[nodiscard]] const std::vector<std::shared_ptr<Event>>& GetAllEvents() const;
    [[nodiscard]] const std::vector<std::shared_ptr<Table>>& GetTables() const;
    [[nodiscard]] TimePoint GetOpenTime() const;
    [[nodiscard]] TimePoint GetCloseTime() const;
    [[nodiscard]] double GetHourlyRate() const;
};

}  // namespace computer_club

#endif  // CLUB_H