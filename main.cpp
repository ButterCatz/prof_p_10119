#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_SEARCH 10

struct entry {
    int frequency;
    vector<string> sentence;
};

vector<entry> read_entries() {
    int n;
    cin >> n;
    vector<entry> entries;
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        entry e;
        cin >> e.frequency;
        for (int j = 0; j < k; j++) {
            string s;
            cin >> s;
            e.sentence.push_back(s);
        }
        entries.push_back(e);
    }
    return entries;
}

vector<string> read_query() {
    int w;
    cin >> w;
    vector<string> query(w);
    for (int i = 0; i < w; i++) {
        cin >> query[i];
    }
    return query;
}

bool is_preposition(string s) {
    string PREPOSITION[20] = {"of",   "to",      "in",    "for",   "with",    "on",    "at",
                              "by",   "from",    "up",    "about", "than",    "after", "before",
                              "down", "between", "under", "since", "without", "near"};

    return find(PREPOSITION, PREPOSITION + 20, s) != PREPOSITION + 20;
}

bool is_match(vector<string> candidate, vector<string> query) {
    int tolerance = 2;
    int s1, s2;
    s1 = s2 = 0;
    while (tolerance && s2 < candidate.size()) {
        if (query[s1] == candidate[s2]) {
            s1++;
            s2++;
        } else {
            if (is_preposition(query[s1]) && is_preposition(candidate[s2])) {
                s1++;
                s2++;
                tolerance--;
            } else if (is_preposition(query[s1])) {
                s1++;
                tolerance--;
            } else if (is_preposition(candidate[s2])) {
                s2++;
                tolerance--;
            } else {
                break;
            }
        }
        if (s1 == query.size()) {
            return true;
        }
    }

    while (tolerance) {
        if (is_preposition(query[s1])) {
            s1++;
            tolerance--;
        } else {
            break;
        }
        if (s1 == query.size()) {
            return true;
        }
    }

    return false;
}

vector<entry> get_matched(vector<entry> entries, vector<string> query) {
    vector<entry> matched;
    for (int i = 0; i < entries.size(); i++) {
        vector<string> candidate = entries[i].sentence;
        if (is_match(candidate, query)) {
            matched.push_back(entries[i]);
        }
    }
    return matched;
}

void print_matched(vector<entry> matched) {
    if (matched.size() == 0) {
        cout << "NO MATCH" << endl;
        return;
    }
    int match_count = 0;
    for (int j = 0; j < matched.size(); j++) {
        if (match_count == MAX_SEARCH &&
            (j + 1 < matched.size() && matched[j].frequency != matched[j + 1].frequency)) {
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

int main(int argc, char const *argv[]) {
    vector<entry> entries{read_entries()};

    stable_sort(entries.begin(), entries.end(), [](entry a, entry b) { return a.frequency > b.frequency; });

    int Q;
    cin >> Q;
    for (int i = 0; i < Q; i++) {
        vector<string> query{read_query()};
        vector<entry> matched{get_matched(entries, query)};

        cout << "Case #" << i + 1 << ":" << endl;
        print_matched(matched);
    }
    return 0;
}