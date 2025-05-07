#include "TablePool.h"

#include "Table.h"
#include "events/TimePoint.h"

#include <memory>
#include <string>

namespace computer_club {

int TablePool::table_count = 0;
double TablePool::hourly_rate = 0.0;
std::vector<std::shared_ptr<Table>> TablePool::tables;
std::unique_ptr<TablePool> TablePool::instance = nullptr;

TablePool::TablePool(int table_count, double hourly_rate) {
    computer_club::TablePool::table_count = table_count;
    computer_club::TablePool::hourly_rate = hourly_rate;
    for (int i = 0; i <= table_count; ++i) {
        tables.push_back(std::make_shared<Table>(i));
    }
}

void TablePool::Initialize(int table_count, double hourly_rate) {
    if (!instance) {
        instance = std::unique_ptr<TablePool>(new TablePool(table_count, hourly_rate));
        return;
    }
    throw std::runtime_error(
        "Instance already initialized. Use GetInstance() to access the existing instance.");
}

TablePool& TablePool::GetInstance() {
    if (!instance) {
        throw std::runtime_error(
            "Instance not initialized. Call Initiallize(int, double, const TimePoint&, const "
            "TimePoint&) first.");
    }
    return *instance;
}

int TablePool::TableCount() {
    return table_count;
}

double TablePool::HourlyRate() {
    return hourly_rate;
}

std::vector<std::shared_ptr<Table>> TablePool::Tables() {
    return tables;
}

bool TablePool::Contains(int table_id) {
    return table_id >= 0 && table_id < table_count;
}

std::shared_ptr<Table> TablePool::GetTable(int table_id) {
    if (table_id < 1 || table_id > table_count) {
        throw std::out_of_range("Invalid table ID");
    }
    return tables[table_id];
}

std::vector<std::shared_ptr<Table>> TablePool::GetFreeTables() {
    std::vector<std::shared_ptr<Table>> free_tables;

    for (const auto& table : tables) {
        if (!table->IsOccupied() && table->Id() != 0) {
            free_tables.push_back(table);
        }
    }

    return free_tables;
}

std::string TablePool::ToString() {
    return "TablePool: " + std::to_string(table_count) + " tables, " + std::to_string(hourly_rate) +
           " hourly rate";
}

}  // namespace computer_club