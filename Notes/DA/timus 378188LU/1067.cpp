#include <iostream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

vector<string> splitPath(const string& path) {
    stringstream stream(path);
    vector<string> result;
    string segment;
    while (getline(stream, segment, '\\')) {
        result.push_back(segment);
    }
    return result;
}

class DirectoryMap {
    map<string, DirectoryMap> subDirectories;

public:
    void add(const vector<string>& path) {
        if (path.empty()) return;
        const string& parent = path[0];
        vector<string> child(path.begin() + 1, path.end());
        subDirectories[parent].add(child);
    }

    void list(int depth = 0) const {
        for (const auto& directory : subDirectories) {
            cout << string(depth, ' ') << directory.first << endl;
            directory.second.list(depth + 1);
        }
    }
};

int main() {
    int numPaths;
    DirectoryMap directoryMap;
    cin >> numPaths;
    cin.ignore(); // Ignore newline character
    string path;
    for (int i = 0; i < numPaths; ++i) {
        getline(cin, path);
        vector<string> splitResult = splitPath(path);
        directoryMap.add(splitResult);
    }
    directoryMap.list();
    return 0;
}
