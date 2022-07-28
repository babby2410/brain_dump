//
// Created by Anil Bhargav Paindla on 28/07/22.
//

#include <utility>
#include <set>
#include <vector>
#include <iostream>

#define pi pair<int, int>
using namespace std;

// Build an API a system that can schedule meetings in a predefined set of conference rooms.
// It should have a method like scheduleMeeting(startTime, endTime) which returns any available room at that time and reserves it or an error if no rooms are available.

class MeetingScheduler {
private:
    vector<set<pi>> meetingRooms;

    static bool findSlot(int startTime, int endTime, set <pair<int, int>> &meetingRoom) {
        pi currentReservation = {startTime, endTime};
        if (meetingRoom.empty()) {
            meetingRoom.insert(currentReservation);
            return true;
        }
        // If slot can be placed at the end of current list of slots, place it
        pi floorReservation, ceilReservation;
        if (meetingRoom.lower_bound(currentReservation) == meetingRoom.end()) {
            floorReservation = *meetingRoom.rbegin();
            if (floorReservation.second > currentReservation.first)
                return false;
            meetingRoom.insert(currentReservation);
            return true;
        }
        // check for any overlap with ceiling reservation, slot with start time >= currentReservation
        ceilReservation = *meetingRoom.lower_bound(currentReservation);
        if (ceilReservation.first < currentReservation.second)
            return false;
        // If slot can be placed at the beginning of current list of slots, place it
        auto floorPos = meetingRoom.upper_bound({currentReservation.first - 1, currentReservation.second});
        if (floorPos == meetingRoom.begin()) {
            meetingRoom.insert(currentReservation);
            return true;
        }
        // check for any overlap with floor reservation, slot with start time < current reservation
        floorPos--;
        floorReservation = *floorPos;
        if (floorReservation.second > currentReservation.first)
            return false;
        // No overlaps observed
        meetingRoom.insert(currentReservation);
        return true;
    }

public:
    explicit MeetingScheduler(int n) {
        this->meetingRooms.resize(n);
    }

    pair<bool, int> scheduleMeeting(int startTime, int endTime) {
        for (int i = 0; i < this->meetingRooms.size(); i++) {
            if (MeetingScheduler::findSlot(startTime, endTime, meetingRooms[i]))
                return {true, i};
        }
        return {false, -1};
    }
};

int main() {
    auto *scheduler = new MeetingScheduler(2);

    pi tryReservation = scheduler->scheduleMeeting(10, 20);
    if (tryReservation.first) {
        cout << "Reservation Success! at: " << tryReservation.second << "\n";
    } else {
        cout << "Reservation Failed! \n";
    }

    tryReservation = scheduler->scheduleMeeting(25, 30);
    if (tryReservation.first) {
        cout << "Reservation Success! at: " << tryReservation.second << "\n";
    } else {
        cout << "Reservation Failed! \n";
    }

    tryReservation = scheduler->scheduleMeeting(15, 20);
    if (tryReservation.first) {
        cout << "Reservation Success! at: " << tryReservation.second << "\n";
    } else {
        cout << "Reservation Failed! \n";
    }

    tryReservation = scheduler->scheduleMeeting(35, 40);
    if (tryReservation.first) {
        cout << "Reservation Success! at: " << tryReservation.second << "\n";
    } else {
        cout << "Reservation Failed! \n";
    }

    tryReservation = scheduler->scheduleMeeting(18, 25);
    if (tryReservation.first) {
        cout << "Reservation Success! at: " << tryReservation.second << "\n";
    } else {
        cout << "Reservation Failed! \n";
    }

    tryReservation = scheduler->scheduleMeeting(10, 15);
    if (tryReservation.first) {
        cout << "Reservation Success! at: " << tryReservation.second << "\n";
    } else {
        cout << "Reservation Failed! \n";
    }

    return 0;
}

