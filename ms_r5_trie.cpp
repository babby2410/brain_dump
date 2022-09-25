#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

struct TrieNode {
    TrieNode () {
        this->isWord = false;
        this->wordCount = 0;
    }

    bool isWord;
    int wordCount;
    unordered_map<char, TrieNode*> children;
};

TrieNode *root = new TrieNode();

void addToTrie (string &str) {
    TrieNode *localRoot = root;
    for (char c: str) {
        if (localRoot->children.find(c) == localRoot->children.end())
            localRoot->children[c] = new TrieNode();
        localRoot = localRoot->children[c];
    }
    localRoot->isWord = true;
    localRoot->wordCount += 1;
}

pair<bool, int> searchTrie (string &str) {
    TrieNode *localRoot = root;
    for (char c: str) {
        if (localRoot->children.find(c) == localRoot->children.end())
            return {false, 0};
        localRoot = localRoot->children[c];
    }

    return {localRoot->isWord, localRoot->wordCount};
}

int main() {
    vector<string> trieInput{"cat", "cats", "cattle", "cat"};
    for (string &ipt: trieInput) {
        addToTrie(ipt);
    }

    string searchStr = "cattle";
    pair<bool, int> result = searchTrie(searchStr);
    cout << "Search Result for -> " << searchStr << " : " << result.first << ", " << result.second << "\n";

    return 0;
}
