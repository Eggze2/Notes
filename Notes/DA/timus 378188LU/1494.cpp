#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    int stackTop = 0;
    int proofIndex = 0;

    vector<int> requiredOrder(n);
    vector<int> stack(n);

    for (int i = 0; i < n; ++i) {
        cin >> requiredOrder[i];
    }

    for (int i = 1; i <= n; ++i) {
        stack[++stackTop] = i;
        while (stackTop && stack[stackTop] == requiredOrder[proofIndex]) {
            --stackTop;
            ++proofIndex;
        }
    }

    if (stackTop == 0) {
        cout << "Not a proof" << endl;
    } else {
        cout << "Cheater" << endl;
    }

    return 0;
}
