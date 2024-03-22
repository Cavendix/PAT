#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>

using namespace std;

struct Word {
    int frequency;
    string word;
};

int compareStrings(const string& str1, const string& str2) {
    for (size_t i = 0; i < str1.length() && i < str2.length(); ++i) {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
    }  
    return str1.length() - str2.length();
}

bool compareWords(const Word &a, const Word &b) {
    if (a.frequency != b.frequency)
        return a.frequency > b.frequency;
    else{
        int signal=compareStrings(a.word,b.word);
        if(signal<0)return true;
        else return false;
    }
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    unordered_map<string, int> wordFreq;
    vector<Word> dictionary;

    for (int i = 0; i < n; ++i) {
        int frequency;
        string word;
        cin >> frequency >> word;
        if (wordFreq.find(word) == wordFreq.end()) {
            wordFreq[word] = frequency;
            dictionary.push_back({frequency, word});
        } else {
            if (wordFreq[word] < frequency) {
                wordFreq[word] = frequency;
                for (auto &entry : dictionary) {
                    if (entry.word == word) {
                        entry.frequency = frequency;
                        break;
                    }
                }
            }
        }
    }

    sort(dictionary.begin(), dictionary.end(), compareWords);

    for (int i = 0; i < m; ++i) {
        string query;
        cin >> query;
        vector<string> suggestions;
        for (auto &entry : dictionary) {
            if (entry.word.substr(0, query.length()) == query&&entry.word!=query) {
                suggestions.push_back(entry.word);
                if (suggestions.size() == k)
                    break;
            }
        }

        if (suggestions.empty()) {
            cout << "no suggestion" << endl;
        } 
        else {
            for (const auto &word : suggestions) {
                cout << word << endl;
            }
        }

        if(i!=m-1){
            cout<<endl;
        }
    }

    return 0;
}
