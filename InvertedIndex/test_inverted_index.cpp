#include "inverted_index.hpp"
#include <dirent.h>
#include <stdlib.h>

void AddFiles(const string& dir_path, InvertedIndex& inverted_index) {
    struct dirent *dirp;

    DIR* dir = opendir(dir_path.c_str());

    while ((dirp = readdir(dir)) != nullptr) {
        if (dirp->d_type == DT_REG) {
            string file_path = dir_path + "/" + dirp->d_name;
            inverted_index.AddFile(file_path);
        }
    }

    closedir(dir);
}

int main() {
    cout << "<<<<<< test_inverted_index..." << endl;

    // convert into absolute path
    string dir_path = realpath("../InvertedIndex/poems", nullptr);
    InvertedIndex inverted_index;
    
    AddFiles(dir_path, inverted_index);

    unordered_map<string, vector<InvertedItem>> results;
    inverted_index.Query("was But", results);

    for (auto it : results) {
        cout << it.first << endl;
        for (auto item : it.second)
            cout << item.doc_id_ << endl;

        cout << endl;
    }

    cout << "test done!" << endl << endl;

    return 0;
}