#include <iostream>
#include <vector>

const int N = 8;
const std::vector<int> Arr1 = {0, 2, 5, 7};
const std::vector<int> Arr2 = {1, 3, 4, 6};

std::vector<int> v(N, 0);

void Input() {
    for (int i = 0; i < N; i++)
        std::cin >> v[i];
}

void Generate(int x, int y) {
    v[x]++;
    v[y]++;
    std::cout << static_cast<char>('A' + x) << static_cast<char>('A' + y) << "+\n";
}

void Annihilate(int x, int y) {
    v[x]--;
    v[y]--;
    std::cout << static_cast<char>('A' + x) << static_cast<char>('A' + y) << "-\n";
}

void Move(int St, int Ed) {
    int Tmp = (!Ed && St < 4) ? 1 : (!Ed) ? 4 : (St > 3) ? 5 : 0;
    while (v[St]) {
        if (!v[Tmp])
            Generate(Tmp, Ed);
        Annihilate(Tmp, St);
    }
}

int main() {
    Input();
    int a = 0, b = 0;
    for (int i : Arr1)
        a += v[i];
    for (int i : Arr2)
        b += v[i];

    if (a != b)
        std::cout << "IMPOSSIBLE\n";
    else {
        for (int i : Arr1)
            if (i)
                Move(i, 0);
        for (int i : Arr2)
            if (i != 4)
                Move(i, 4);
        while (v[0])
            Annihilate(0, 4);
    }

    return 0;
}
