#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

int main() {
    ifstream file("testing.csv");

    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    vector<string> names;
    vector<vector<vector<string>>> times;
    vector<vector<string>> seriesNames;

    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> data;
        string str;

        while (getline(ss, str, ',')) {
            if (!str.empty() && str.front() == '"' && str.back() == '"') {
                str = str.substr(1, str.size() - 2);
            }
            data.push_back(str);
        }

        if (data.size() < 9) { // Assuming we need at least 9 values in each line
            cerr << "Invalid line: " << line << endl;
            continue;
        }

        names.push_back(data[0]);
        
        vector<vector<string>> day_time;
        vector<string> slots;
        string s;
        for (int i = 1; i <= 7; ++i) {
            stringstream timeSS(data[i]);
            while (getline(timeSS, s, ' ')) {
                slots.push_back(s);
            }
            day_time.push_back(slots);
            slots.clear();
        }
        times.push_back(day_time);

        vector<string> series;
        for (int i = 8; i < data.size(); ++i) {
            series.push_back(data[i]);
        }
        seriesNames.push_back(series);
    }

    file.close();

    for (int i = 0; i < names.size(); ++i) {
        for (int j = i + 1; j < names.size(); ++j) {
            if (times[i][0][0] > times[j][0][0]) {
                swap(times[i], times[j]);
                swap(names[i], names[j]);
                swap(seriesNames[i], seriesNames[j]);
            }
        }
    }

    cout << "Names:\n";
    for (int i=0;i<names.size();i++) {
        cout << names[i] << endl;
    }

    cout << "\nTimes:\n";
    //cout<<times[0][1][0]<<endl;
    for (int i=0;i<times.size();i++) {
        for (int j=0;j<times[i].size();j++) {
            for (int k=0;k<times[i][j].size();k++) {
                cout <<times[i][j][k]<< " ";
            }
            cout << endl;
        }
        cout<<endl;
    }

    cout << "\nSeries Names:\n";
    //cout<<seriesNames[2][0]<<endl;
    for (int i=0;i<seriesNames.size();i++) {
        for (int j=0;j<seriesNames[i].size();j++) {
            cout << seriesNames[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
