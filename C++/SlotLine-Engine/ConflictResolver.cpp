/*
 * Problem (The Commons): Users constantly double-book meeting rooms or overlap schedules.
 * Logic: The Interval Merge algorithm. We take a chaotic list of start and end times, sort them 
 * chronologically, and merge any overlapping blocks to create a clean, unified timeline of 
 * when a resource is actually busy.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

#define BOLD "\033[1m"
#define GRAY "\033[90m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

struct TimeSlot {
    int start;
    int end;
};

// Sort by start time
bool compareSlots(const TimeSlot& a, const TimeSlot& b) {
    return a.start < b.start;
}

class ConflictResolver {
public:
    vector<TimeSlot> mergeSchedules(vector<TimeSlot>& intervals) {
        if (intervals.empty()) return {};

        sort(intervals.begin(), intervals.end(), compareSlots);
        vector<TimeSlot> merged;
        merged.push_back(intervals[0]);

        for (size_t i = 1; i < intervals.size(); i++) {
            TimeSlot& lastMerged = merged.back();
            
            // If current slot overlaps with previous, merge them
            if (intervals[i].start <= lastMerged.end) {
                lastMerged.end = max(lastMerged.end, intervals[i].end);
            } else {
                merged.push_back(intervals[i]);
            }
        }
        return merged;
    }
};

string formatTime(int hours) {
    string suffix = (hours >= 12 && hours < 24) ? " PM" : " AM";
    int displayHour = (hours > 12) ? hours - 12 : hours;
    if (displayHour == 0) displayHour = 12;
    return to_string(displayHour) + ":00" + suffix;
}

int main() {
    cout << BOLD << "\n--- SlotLine Engine: Schedule Resolver ---" << RESET << "\n";
    cout << GRAY << "Raw User Bookings (24h format): [9-11], [10-12], [14-16], [15-18]" << RESET << "\n\n";

    vector<TimeSlot> rawBookings = {{9, 11}, {10, 12}, {14, 16}, {15, 18}};
    ConflictResolver resolver;
    
    vector<TimeSlot> cleanSchedule = resolver.mergeSchedules(rawBookings);

    cout << "  " << GREEN << "[✓] Conflicts Resolved. Actual Resource Usage:" << RESET << "\n";
    for (const auto& slot : cleanSchedule) {
        cout << "      • " << formatTime(slot.start) << " to " << formatTime(slot.end) << "\n";
    }
    cout << "\n";

    return 0;
}