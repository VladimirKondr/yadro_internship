#ifndef TABLEPOOL_H
#define TABLEPOOL_H

#include "Table.h"
#include "events/TimePoint.h"

#include <memory>
#include <string>
#include <unordered_set>

namespace computer_club {

class TablePool {
   private:
    static int table_count;
    static double hourly_rate;
    static std::vector<std::shared_ptr<Table>> tables;
    static std::unique_ptr<TablePool> instance;

    TablePool() = default;

    TablePool(int table_count, double hourly_rate);

   public:
    TablePool(const TablePool&) = delete;
    TablePool& operator=(const TablePool&) = delete;
    TablePool(TablePool&&) = default;
    TablePool& operator=(TablePool&&) = default;
    ~TablePool() = default;

    static void Initialize(int table_count, double hourly_rate);

    static TablePool& GetInstance();

    [[nodiscard]] static int TableCount();

    [[nodiscard]] static double HourlyRate();

    [[nodiscard]] static std::vector<std::shared_ptr<Table>> Tables();

    [[nodiscard]] static bool Contains(int table_id);

    [[nodiscard]] static std::shared_ptr<Table> GetTable(int table_id);

    [[nodiscard]] static std::vector<std::shared_ptr<Table>> GetFreeTables();

    [[nodiscard]] static std::string ToString();

    static void Reset();
};

}  // namespace computer_club

#endif  // TABLEPOOL_H