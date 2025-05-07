cmake_minimum_required(VERSION 3.20)
project(ComputerClub)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER "clang++")

include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

add_executable(task
    src/main.cpp
    src/Parser.cpp
    src/Logger.cpp
    src/Table.cpp
    src/Club.cpp
    src/Client.cpp
    src/events/EventBase.cpp
    src/events/IncomingEvent.cpp
    src/events/OutgoingEvent.cpp
    src/events/ClientArrivalEvent.cpp
    src/events/ClientChangedSeatingEvent.cpp
    src/events/ClientWaitingEvent.cpp
    src/events/ClientLeftVoluntarilyEvent.cpp
    src/events/ClientLeftInvoluntarilyEvent.cpp
    src/events/ClientSeatingEvent.cpp
    src/events/ErrorEvent.cpp
    src/events/TimePoint.cpp
    src/ClientPool.cpp
    src/TablePool.cpp
)

find_package(GTest QUIET)
if(GTEST_FOUND)
    enable_testing()
    add_executable(club_test
        tests/ClubTest.cpp
        src/Parser.cpp
        src/Logger.cpp
        src/Table.cpp
        src/Club.cpp
        src/Client.cpp
        src/events/EventBase.cpp
        src/events/IncomingEvent.cpp
        src/events/OutgoingEvent.cpp
        src/events/ClientArrivalEvent.cpp
        src/events/ClientChangedSeatingEvent.cpp
        src/events/ClientWaitingEvent.cpp
        src/events/ClientLeftVoluntarilyEvent.cpp
        src/events/ClientLeftInvoluntarilyEvent.cpp
        src/events/ClientSeatingEvent.cpp
        src/events/ErrorEvent.cpp
        src/events/TimePoint.cpp
        src/ClientPool.cpp
        src/TablePool.cpp
    )
    target_include_directories(club_test PRIVATE include)
    target_link_libraries(club_test GTest::GTest GTest::Main)
    add_test(NAME ClubTest COMMAND club_test)
endif()
