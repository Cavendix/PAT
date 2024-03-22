#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

int k;

struct Word {
    string word;
    int frequency;
};

int compareStrings(const string& str1, const string& str2) {
    for (size_t i = 0; i < str1.length() && i < str2.length(); ++i) {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
    }  
    return str1.length() - str2.length();
}

// 比较函数，用于按照频率从大到小排序
bool compareFrequency(const Word& a, const Word& b) {
    if(a.frequency != b.frequency){
        return a.frequency > b.frequency;
    }
    else{
        int signal=compareStrings(a.word,b.word);
        if(signal<0)return true;
        else return false;
    }
    
}

class TrieNode {
public:
    TrieNode *children[36];
    bool isEndOfWord;
    string word;
    vector<Word> wordsWithPrefix;
    
    TrieNode() {
        isEndOfWord = false;
        word = "";
        wordsWithPrefix={};
        for (int i = 0; i < 36; ++i)
            children[i] = nullptr;
    }
};

class Trie {
public:
    TrieNode *root;

    Trie() {
        root = new TrieNode();
    }
    
    int getIndex(char ch) {
        if (isdigit(ch))
            return ch - '0' + 26;
        else
            return ch - 'a';
    }
    
    void insert(string word,int frequency) {
        TrieNode *current = root;
        int length = word.length();
        for (int i = 0; i < length; ++i) {


            auto found = false;
for (int i = 0; i < current->wordsWithPrefix.size(); ++i) {
    if (current->wordsWithPrefix[i].word == word) {
        // 如果找到相同的值
        current->wordsWithPrefix[i].frequency = frequency;
        found = true;
        break;
    }
}

if (!found) {
    // 如果未找到相同的值
    current->wordsWithPrefix.push_back({word, frequency});
}


            
            
            sort(current->wordsWithPrefix.begin(), current->wordsWithPrefix.end(), compareFrequency);
            if(current->wordsWithPrefix.size()>k){
                current->wordsWithPrefix.resize(k);
            }

            char ch = word[i];

            int index = getIndex(ch);
            if (!current->children[index])
                current->children[index] = new TrieNode();
            current = current->children[index];
        }
        current->isEndOfWord = true;
        current->word = word;
    }
    
    vector<Word> findWordsWithPrefix(string prefix) {
        vector<Word> suggestions;
        TrieNode *current = root;
        for (char ch : prefix) {
            int index = getIndex(ch);
            if (!current->children[index])
                return suggestions;
            current = current->children[index];
        }

        return current->wordsWithPrefix;
    }
};

int main() {
    int n, m;
    cin >> n >> m >> k;

    Trie trie;

    unordered_map<string, int> wordFreq;
    vector<Word> dictionary;

    for (int i = 0; i < n; ++i) {
        int frequency;
        string word;
        cin >> frequency >> word;
        trie.insert(word,frequency);
    }


    for (int i = 0; i < m; ++i) {
        string prefix;
        cin >> prefix;
        vector<Word> suggestions = trie.findWordsWithPrefix(prefix);
        if (suggestions.empty()) {
            cout << "no suggestion" << endl;
        } 
        else {
            for (int j = 0; j < min(k, (int)suggestions.size()); ++j){
                    cout << suggestions[j].word << endl; 
            }
            
        }

        if(i!=m-1){
            cout<<endl;
        }
    }

    return 0;
}
