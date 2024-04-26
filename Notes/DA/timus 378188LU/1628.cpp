#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int weeks, days, unluckyEntries;
    cin >> weeks >> days >> unluckyEntries;

    vector<pair<int, int>> unluckyDays;
    for(int entry = 0; entry < unluckyEntries; ++entry) {
        int week, day;
        cin >> week >> day;
        unluckyDays.emplace_back(week, day);
    }

    // Add perimeter days as unlucky days to simplify edge cases
    for(int day = 1; day <= days; ++day) {
        unluckyDays.emplace_back(0, day); // Before the start of calendar
        unluckyDays.emplace_back(weeks + 1, day); // After the end of calendar
    }
    for(int week = 1; week <= weeks; ++week) {
        unluckyDays.emplace_back(week, 0); // Before the start of a week
        unluckyDays.emplace_back(week, days + 1); // After the end of a week
    }

    int whiteStreaksCount = 0;
    vector<pair<int, int>> trackSingleUnluckyDay;

    // Sort unlucky days by weeks, then by days
    sort(unluckyDays.begin(), unluckyDays.end(),
        [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.first < b.first || (a.first == b.first && a.second < b.second);
        }
    );

    // Find vertical white streaks (days without bad luck) between unlucky days
    for(size_t index = 0; index + 1 < unluckyDays.size(); ++index) {
        int verticalDistance = unluckyDays[index + 1].second - unluckyDays[index].second;
        if(unluckyDays[index].first == unluckyDays[index + 1].first && verticalDistance >= 2) {
            if(verticalDistance == 2)
                trackSingleUnluckyDay.emplace_back(unluckyDays[index].first, unluckyDays[index].second + 1);
            else
                ++whiteStreaksCount;
        }
    }

    // Sort unlucky days by days, then by weeks
    sort(unluckyDays.begin(), unluckyDays.end(),
        [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.second < b.second || (a.second == b.second && a.first < b.first);
        }
    );

    // Find horizontal white streaks (weeks without bad luck) between unlucky days
    for(size_t index = 0; index + 1 < unluckyDays.size(); ++index) {
        int horizontalDistance = unluckyDays[index + 1].first - unluckyDays[index].first;
        if(unluckyDays[index].second == unluckyDays[index + 1].second && horizontalDistance >= 2) {
            if(horizontalDistance == 2) {
                if(find(trackSingleUnluckyDay.begin(), trackSingleUnluckyDay.end(),
                        make_pair(unluckyDays[index].first + 1, unluckyDays[index].second))
                   != trackSingleUnluckyDay.end()) {
                    ++whiteStreaksCount;
                }
            } else {
                ++whiteStreaksCount;
            }
        }
    }

    cout << whiteStreaksCount << endl;

    return 0;
}