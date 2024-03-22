#include <iostream>
using namespace std;

int main() {
    int t;  // the number of tests
    cin >> t;
    int* n = new int[t];  // total number of people
    int* k = new int[t];  // total number of teams for each test case

    for (int i = 0; i < t; i++) {
        cin >> n[i] >> k[i];
    }

    for (int i = 0; i < t; i++) {
        int c = 0;  // total fights, reset for each test case
        int peoplePerTeam = n[i] / k[i];
        int extraPeople = n[i] % k[i];

        for (int j = 0; j < k[i]; j++) {
            int currentTeamSize = peoplePerTeam + (j < extraPeople ? 1 : 0);
            for (int m = j + 1; m < k[i]; m++) {
                int opponentTeamSize = peoplePerTeam + (m < extraPeople ? 1 : 0);
                c += currentTeamSize * opponentTeamSize;
            }
        }

        cout << c << endl;
    }

    delete[] n;
    delete[] k;

    return 0;
}
