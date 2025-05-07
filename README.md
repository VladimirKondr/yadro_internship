# yadro_internship
Completing a test assignment for an internship at YADRO in C++

# YADRO Internship Application

This project implements a prototype system for monitoring a computer club's operations, processing events, and calculating daily revenue and table usage times.

## Task Description

Develop a prototype system that monitors the operations of a computer club, processes events, and calculates the daily revenue and table usage times.

## Requirements

### Programming Language
- C++ (up to C++20 standard)
- Solution must compile with gcc or clang on Linux, or mingw/cygwin on Windows
- Only the Standard Template Library (STL) is permitted; no third-party libraries
- Build systems allowed: make, automake, cmake, gradle (optional)
- Proprietary build tools (e.g., MS Visual Studio project files) are not permitted

### Optional
- Unit tests using available libraries (e.g., Google Test, CppUTest)

## Input Format

```
<number of tables in the computer club>
<opening time> <closing time>
<cost per hour>
<event 1 time> <event 1 ID> <event 1 body>
<event 2 time> <event 2 ID> <event 2 body>
...
<event N time> <event N ID> <event N body>
```

- First line: number of tables (positive integer)
- Second line: opening and closing times (space-separated)
- Third line: cost per hour (positive integer)
- Remaining lines: list of events

Notes:
- Client names consist of characters from a-z, 0-9, _, and -
- Time is in 24-hour format (XX:XX), with leading zeros required (e.g., 15:03, 08:09)
- Tables are numbered from 1 to N
- Events are listed in chronological order

## Output Format

If the input format is incorrect, the program outputs the first line with the format error and terminates.

For valid input, the program should output:
1. The opening time on the first line
2. All events (both input and generated) that occurred during the day, each on a separate line
3. The closing time on a separate line
4. For each table on separate lines: table number, revenue for the day, and time of occupancy

## Revenue Calculation

Clients pay the specified hourly rate, with time rounded up to the nearest hour. The revenue is the sum of all payments from all clients.

## Events

### Input Events:
- **ID 1**: Client arrives - `<time> 1 <client_name>`
  - Client arrives at the club (create new client)
  - Error "YouShallNotPass" if client is already in the club
  - Error "NotOpenYet" if client arrives outside working hours

- **ID 2**: Client sits at a table - `<time> 2 <client_name> <table_number>`
  - Client is seated at the specified table
  - Client can change tables if already seated
  - Error "PlaceIsBusy" if the table is occupied
  - Error "ClientUnknown" if client is not in the club

- **ID 3**: Client waits - `<time> 3 <client_name>`
  - Add client to the waiting queue
  - Error "ICanWaitNoLonger!" if there are free tables
  - Client leaves (triggers ID 11) if waiting queue exceeds table count

- **ID 4**: Client leaves - `<time> 4 <client_name>`
  - Client leaves the club
  - Error "ClientUnknown" if client is not in the club
  - When a client leaves, their table becomes available for the first waiting client (ID 12)

### Output Events:
- **ID 11**: Client leaves - `<time> 11 <client_name>`
  - Generated at closing time for all remaining clients (in alphabetical order)
  - Generated when a client joins a full waiting queue

- **ID 12**: Client sits at table - `<time> 12 <client_name> <table_number>`
  - Generated for the first waiting client when any table becomes available

- **ID 13**: Error - `<time> 13 <error_message>`
  - Generated after any event that causes an error
  - The error-causing event has no effect on client status

## Example

### Input File:
```
3
09:00 19:00
10
08:48 1 client1
09:41 1 client1
09:48 1 client2
09:52 3 client1
09:54 2 client1 1
10:25 2 client2 2
10:58 1 client3
10:59 2 client3 3
11:30 1 client4
11:35 2 client4 2
11:45 3 client4
12:33 4 client1
12:43 4 client2
15:52 4 client4
```

### Console Output:
```
09:00
08:48 1 client1
08:48 13 NotOpenYet
09:41 1 client1
09:48 1 client2 
09:52 3 client1
09:52 13 ICanWaitNoLonger!
09:54 2 client1 1
10:25 2 client2 2
10:58 1 client3 
10:59 2 client3 3
11:30 1 client4
11:35 2 client4 2
11:35 13 PlaceIsBusy
11:45 3 client4
12:33 4 client1
12:33 12 client4 1
12:43 4 client2
15:52 4 client4
19:00 11 client3
19:00
1 70 05:58 
2 30 02:18
3 90 08:01
```

## Usage
```bash
$ ./task ../example.txt
```
