#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

using ll = long long;
using CityFinance = pair<ll, string>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    map<string, ll> bankirs;
    map<string, string> bankirsCity;
    map<string, ll> moneys;

    // Faster input reading and directly inserting into maps
    for(int i = 0; i < n; ++i) {
        string name, city;
        ll money;
        cin >> name >> city >> money;
        bankirs[name] = money;
        bankirsCity[name] = city;
        moneys[city] += money;
    }

    set<CityFinance> cities;
    for(const auto& [city, money] : moneys) {
        cities.emplace(money, city);
    }

    int m, q;
    cin >> m >> q;

    vector<tuple<int, string, string>> events;
    for (int i = 0; i < q; ++i) {
        int day;
        string name, city;
        cin >> day >> name >> city;
        events.emplace_back(day, name, city);
    }

    // No need for a custom comparator since tuple naturally orders by its elements sequence
    sort(events.begin(), events.end());

    map<string, int> ans;
    int currentEvent = 0;

    for (int day = 0; day < m; ++day) {
        while (currentEvent < events.size() && get<0>(events[currentEvent]) == day) {
            auto& [_, name, newCity] = events[currentEvent];
            auto& oldCity = bankirsCity[name];
            auto sum = bankirs[name];

            cities.erase({moneys[oldCity], oldCity});
            cities.erase({moneys[newCity], newCity});
            moneys[oldCity] -= sum;
            moneys[newCity] += sum;
            cities.insert({moneys[oldCity], oldCity});
            cities.insert({moneys[newCity], newCity});
            bankirsCity[name] = newCity;

            currentEvent++;
        }

        if (cities.size() > 1) {
            auto a = *prev(cities.end());
            auto b = *prev(cities.end(), 2);
            if(a.first > b.first) ans[a.second]++;
        } else if (!cities.empty()) {
            ans[begin(cities)->second]++;
        }
    }

    for (const auto& [city, count] : ans) {
        if(count > 0) {
            cout << city << " " << count << "\n";
        }
    }
}