// Atlassian R1 - 12/08/2022
/* Given a list of fileMetadata objects (has size and collection name it belongs to)
 * 1. Given 'k', return total size of all files combined and a list of top k collections by size.
 * 2. (Extension), A file can belong to multiple collections, how do you handle?
 * 3. (Extension), Collections can have parent -> child relationships and a parents size should also include child's size, how do you handle.
 *
 * Solution: Was able to fully code upto 2nd extension
 * 3rd was orally discussed (tree rep for relationships and traversal to update sizes) (had about 2-3 mins left)
 * I offered to code the 3rd extension given another 10 mins but interviewer was satisfied with the answer. Ended discussion with some Q's on atlassian work culture.
 *
 * Overall good experience, specific instructions to code on a local IDE and make use of IDE suggested optimizations if any.
 */

#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <queue>

#define pis pair<int, string>
using namespace std;

struct FileMetadata {
    int size;
    vector<string> collectionNames;

    FileMetadata (int size, vector<string> collectionName) {
        this->size = size;
        this->collectionNames = std::move(collectionName);
    }

    explicit FileMetadata (int size) {
        this->size = size;
    }
};

// FileMetadata* getMetadata(string &fileName) //
FileMetadata* getMetadata (string &fileName) {
    map<string, FileMetadata*> metaDataMap = {
            {"file1", new FileMetadata(100)},
            {"file2", new FileMetadata(200, vector<string>{"C1"})},
            {"file3", new FileMetadata(200, vector<string>{"C1"})},
            {"file4", new FileMetadata(300, vector<string>{"C2", "C3"})},
            {"file5", new FileMetadata(10)}
    };

    return metaDataMap[fileName];
}

pair<int, vector<string>> processFiles(vector<string> &fileNames, int k) {
    int totalSize = 0;
    FileMetadata *currentMetadata;
    map<string, int> collectionToSize;

    for (string& curFile: fileNames) {
        currentMetadata = getMetadata(curFile);
        totalSize += currentMetadata->size;

        if (!currentMetadata->collectionNames.empty()) {
            for (string &collectionName: currentMetadata->collectionNames) {
                if (collectionToSize.find(collectionName) == collectionToSize.end())
                    collectionToSize[collectionName] = 0;
                collectionToSize[collectionName] += currentMetadata->size;
            }
        }
    }

    k = min(k, (int) collectionToSize.size());
    priority_queue<pis, vector<pis>, greater<>> pq;

    int temp = 0;
    if (k > 0) {
        for (const auto& entry: collectionToSize) {
            temp += 1;
            if (temp > k) {
                if (pq.top().first < entry.second) {
                    pq.pop();
                    pq.push({entry.second, entry.first});
                }
            }
            else
                pq.push({entry.second, entry.first});
        }
    }

    vector<string> topCollections;
    while (!pq.empty()) {
        topCollections.push_back(pq.top().second);
        pq.pop();
    }

    return {totalSize, topCollections};
}

int main() {
    vector<string> fileNames{"file1", "file2", "file3", "file4", "file5"};
    int k = 3;
    pair<int, vector<string>> result = processFiles(fileNames, k);

    cout << "Total Size: " << result.first << "\n";
    cout << "Top " << k << " Collections: " << "\n";
    for (string &collectionName: result.second) {
        cout << collectionName << "\n";
    }

    return 0;
}
