#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> weights(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> weights[i];
    }

    int totalWeight = 0;
    for (int i = 0; i < n; ++i) {
        totalWeight += weights[i];
    }

    std::vector<bool> possibleWeightDifferences(totalWeight + 1, false);
    possibleWeightDifferences[0] = true;

    // 看通过组合，哪些特定重量可以达到
    for (int i = 0; i < n; ++i) {
        for (int j = totalWeight; j >= weights[i]; --j) {
            possibleWeightDifferences[j] = possibleWeightDifferences[j] || possibleWeightDifferences[j - weights[i]];
        }
    }
    // 看在能达到的特定重量中，哪种情况与一半的总重与剩下的更接近，因为只关心重量差
    int minWeightDifference = totalWeight;
    for (int i = 0; i <= totalWeight / 2; ++i) {
        if (possibleWeightDifferences[i]) {
            minWeightDifference = std::min(minWeightDifference, totalWeight - 2 * i);
        }
    }

    std::cout << minWeightDifference << std::endl;

    return 0;
}
