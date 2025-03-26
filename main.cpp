#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_SEARCH 10

class entry {
private:
    int frequency;
    vector<string> sentence;
public:
    vector<string> get_sentence() const {
        return sentence;
    }

    bool operator>(const entry &e) const {
        return frequency > e.frequency;
    }

    bool operator!=(const entry &e) const {
        return frequency != e.frequency;
    }

    friend istream &operator>>(istream &is, entry &e) {
        int k;
        is >> k >> e.frequency;
        e.sentence.clear();
        for (int j = 0; j < k; j++) {
            string s;
            is >> s;
            e.sentence.push_back(s);
        }
        return is;
    }

    friend ostream &operator<<(ostream &os, const entry &e) {
        os << e.frequency << " ";
        for (int i = 0; i < e.sentence.size(); i++) {
            os << e.sentence[i] << " ";
        }
        return os;
    }
};

vector<entry> read_entries() {
    int n;
    cin >> n;
    vector<entry> entries;
    for (int i = 0; i < n; i++) {
        entry e;
        cin >> e;
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
        vector<string> candidate {entries[i].get_sentence()};
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
            (j + 1 < matched.size() && matched[j] != matched[j + 1])) {
            break;
        }
        cout << matched[j] << endl;
        match_count++;
    }
}

int main(int argc, char const *argv[]) {
    vector<entry> entries{read_entries()};

    stable_sort(entries.begin(), entries.end(), greater<entry>());

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