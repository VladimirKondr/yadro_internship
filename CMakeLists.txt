cmake_minimum_required(VERSION 3.20)
project(ComputerClub)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_COMPILER "clang++")

include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

add_library(club_lib STATIC
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
target_include_directories(club_lib PUBLIC include)

add_executable(task
    src/main.cpp
)
target_link_libraries(task club_lib)

find_package(GTest QUIET)
if(GTEST_FOUND)
    enable_testing()
    
    add_executable(timepoint_test tests/unit/TimePointTest.cpp)
    add_executable(table_test tests/unit/TableTest.cpp)
    add_executable(client_test tests/unit/ClientTest.cpp)
    add_executable(client_pool_test tests/unit/ClientPoolTest.cpp)
    add_executable(table_pool_test tests/unit/TablePoolTest.cpp)
    add_executable(event_base_test tests/unit/EventBaseTest.cpp)
    add_executable(concrete_events_test tests/unit/ConcreteEventsTest.cpp)
    add_executable(parser_test tests/unit/ParserTest.cpp)
    
    set(TEST_LIST 
        timepoint_test table_test client_test client_pool_test table_pool_test
        event_base_test concrete_events_test parser_test
    )
    
    foreach(TEST_NAME ${TEST_LIST})
        target_link_libraries(${TEST_NAME} club_lib GTest::GTest GTest::Main)
        add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
        
        add_custom_target(run_${TEST_NAME}
            COMMAND ${CMAKE_BINARY_DIR}/${TEST_NAME}
            DEPENDS ${TEST_NAME}
        )
    endforeach()
    
    add_custom_target(unit_tests
        COMMAND ${CMAKE_CTEST_COMMAND} -V
        DEPENDS ${TEST_LIST}
    )
endif()