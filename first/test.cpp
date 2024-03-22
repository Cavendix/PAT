#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEnd;
    int frequency;

    TrieNode() {
        isEnd = false;
        frequency = 0;
    }
};

class Trie {
public:
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        TrieNode* node = root;
        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->isEnd = true;
        node->frequency++;
    }

    vector<pair<string, int>> search(string prefix) {
        vector<pair<string, int>> suggestions;
        TrieNode* node = root;
        for (char c : prefix) {
            if (node->children.find(c) == node->children.end()) {
                return suggestions;
            }
            node = node->children[c];
        }
        traverse(node, prefix, suggestions);
        sort(suggestions.begin(), suggestions.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second > b.second;
        });
        return suggestions;
    }

    void traverse(TrieNode* node, string prefix, vector<pair<string, int>>& suggestions) {
        if (node->isEnd) {
            suggestions.push_back({prefix, node->frequency});
        }
        for (auto it = node->children.begin(); it != node->children.end(); ++it) {
            traverse(it->second, prefix + it->first, suggestions);
        }
    }
};

int main() {
    Trie trie;
    // 将字典数据插入到 Trie 中
    vector<string> dictionary = {
        "the", "to", "that", "this", "they", "their", "them", "these", "than", "time",
        "then", "two", "there", "those", "through", "the", "think", "2", "tx356", "though"
    };
    for (const string& word : dictionary) {
        trie.insert(word);
    }

    // 用户输入
    string prefix;
    cout << "请输入前缀：";
    cin >> prefix;

    // 查找匹配提示
    vector<pair<string, int>> suggestions = trie.search(prefix);
    cout << "完整提示：" << endl;
    for (const auto& suggestion : suggestions) {
        cout << suggestion.first << " (" << suggestion.second << " occurrences)" << endl;
    }

    return 0;
}
