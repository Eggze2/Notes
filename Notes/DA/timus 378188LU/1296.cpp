#include <iostream>
#include <climits>

using namespace std;

int main() {
    int N;
    cin >> N;

    int* sequence = new int[N];

    for (int i = 0; i < N; ++i) {
        cin >> sequence[i];
    }

    int max_ending_here = 0;
    int max_so_far = 0;

    for (int i = 0; i < N; ++i) {
        max_ending_here = max(0, max_ending_here + sequence[i]);
        max_so_far = max(max_so_far, max_ending_here);
    }

    cout << max_so_far << endl;

    delete[] sequence;

    return 0;
}
