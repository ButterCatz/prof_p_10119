#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string PREPOSITION[20] = {"of", "to", "in", "for", "with", "on", "at", "by", "from", "up", "about", "than", "after", "before", "down", "between", "under", "since", "without", "near"};

int MAX_SEARCH = 10;

struct entry {
    int frequency;
    vector<string> sentence;
};

int main(int argc, char const *argv[]) {
    // std::cout << "hello!";
    int N;
    cin >> N;
    entry entries[N];

    for (int i = 0; i < N; i++) {
        int k;
        cin >> k >> entries[i].frequency;
        for (int j = 0; j < k; j++) {
            string s;
            cin >> s;
            entries[i].sentence.push_back(s);
        }
    }

    stable_sort(entries, entries + N, [](entry a, entry b) { return a.frequency > b.frequency; });

    int Q;
    cin >> Q;
    for (int i = 0; i < Q; i++) {
        int w;
        cin >> w;
        vector<string> query(w);
        for (int j = 0; j < w; j++) {
            cin >> query[j];
        }

        vector<entry> matched;
        for (int j = 0; j < N; j++) {
            auto candidate = entries[j].sentence;
            int tolerance = 2;
            bool match = false;
            int s1, s2;
            s1 = s2 = 0;
            while (tolerance && s2 < candidate.size()) {
                if (query[s1] == candidate[s2]) {
                    s1++;
                    s2++;
                } else {
                    if (find(PREPOSITION, PREPOSITION + 20, query[s1]) != PREPOSITION + 20 &&
                        find(PREPOSITION, PREPOSITION + 20, candidate[s2]) != PREPOSITION + 20) {
                        s1++;
                        s2++;
                        tolerance--;
                    } else if (find(PREPOSITION, PREPOSITION + 20, query[s1]) != PREPOSITION + 20) {
                        s1++;
                        tolerance--;
                    } else if (find(PREPOSITION, PREPOSITION + 20, candidate[s2]) != PREPOSITION + 20) {
                        s2++;
                        tolerance--;
                    } else {
                        break;
                    }
                }
                if (s1 == query.size()) {
                    match = true;
                    break;
                }
            }

            while (tolerance) {
                if (find(PREPOSITION, PREPOSITION + 20, query[s1]) != PREPOSITION + 20) {
                    s1++;
                    tolerance--;
                } else {
                    break;
                }
                if (s1 == query.size()) {
                    match = true;
                    break;
                }
            }
            
            if (match) {
                matched.push_back(entries[j]);
            }
        }

        cout << "Case #" << i + 1 << ":" << endl;

        int match_count = 0;
        for (int j = 0; j < matched.size(); j++) {
            if (match_count == MAX_SEARCH && (j + 1 < matched.size() && matched[j].frequency != matched[j + 1].frequency)) {
                break;
            }
            cout << matched[j].frequency << " ";
            for (int k = 0; k < matched[j].sentence.size(); k++) {
                cout << matched[j].sentence[k] << " ";
            }
            cout << endl;
            match_count++;
        }
    }
    return 0;
}