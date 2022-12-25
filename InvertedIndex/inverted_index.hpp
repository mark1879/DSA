#ifndef INVERTED_INDEX_HPP
#define INVERTED_INDEX_HPP
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <unordered_set>
#include "Utils.hpp"
#include "Logger.hpp"

using namespace std;

struct InvertedItem {
    InvertedItem(string doc_id, int frequency, int location) 
        : doc_id_(doc_id)
        , word_frequency_(frequency) {

        word_locations_.emplace_back(location);
    }

    bool operator==(const InvertedItem& item) const {
        return doc_id_ == item.doc_id_;
    }

    bool operator<(const InvertedItem& item) const {
        return doc_id_ < item.doc_id_;
    }

    string doc_id_;
    unsigned int word_frequency_;
    list<unsigned int> word_locations_;
};

class InvertedList {
public:
    InvertedList(const string& doc_id, unsigned int location) {
        item_list_.emplace_back(doc_id, 1, location);
    }

    void AddItem(const string& doc_id, unsigned int location) {
        for (auto& item : item_list_) {
            if (item.doc_id_ == doc_id) {
                item.word_frequency_++;
                item.word_locations_.emplace_back(location);
                return;
            }
        }

        item_list_.emplace_back(doc_id, 1, location);
    }

    const list<InvertedItem>& get_item_list() const {
        return item_list_;
    }

private:
    list<InvertedItem> item_list_;
};

class InvertedIndex {
public:
    bool AddFile(const string& file_path) {
        ifstream ifs;

        ifs.open(file_path);
        if(!ifs.is_open()) {
            LOG_ERROR("Open file failed: %s", file_path.c_str());
            return false;
        }  
    
        vector<string> word_list;
        char buf[1024] = { 0 };

        while (ifs.getline(buf, 1023)) {
            string line(buf);

            vector<string> words = Utils::StrTok(line);
            word_list.insert(word_list.end(), words.begin(), words.end());

            memset(buf, 0, 1024);
        }
    
        ifs.close();

        unsigned int location = 0;

        for (string& word : word_list) {
            auto it = inverted_map_.find(word);
            if (it == inverted_map_.end()) {
                InvertedList inverted_list(file_path, location);
                inverted_map_.emplace(word, inverted_list);
            } else {
                it->second.AddItem(file_path, location);
            }

            ++location;
        }

        return true;
    }


    bool Query(const string& phrases, unordered_map<string, vector<InvertedItem>>& results) {
        vector<string> words = Utils::StrTok(phrases);

        if (words.empty()) {
            LOG_ERROR("Illegal phrases: %s", phrases.c_str());
            return false;
        }

        // 多个单词查询，合并处理
        vector<InvertedList> invertd_list;
        for (const auto& word : words) {
            auto it = inverted_map_.find(word);
            if (it != inverted_map_.end()) 
                invertd_list.push_back(it->second);
        }

        // 多个list求交集
        vector<InvertedItem> temp;
        vector<InvertedItem> v1(invertd_list[0].get_item_list().begin(),
            invertd_list[0].get_item_list().end());

        for (auto item = invertd_list.begin() + 1; item != invertd_list.end(); item++) {
            vector<InvertedItem> v2(item->get_item_list().begin(),
                item->get_item_list().end());

            sort(v1.begin(), v1.end());
            sort(v2.begin(), v2.end());

            set_intersection(v1.begin(), v1.end(),
                v2.begin(), v2.end(),
                back_inserter(temp));

            v1.swap(temp);
            temp.clear();
        }

        unordered_set<string> docs;
        for (const auto& item : v1)
            docs.insert(item.doc_id_);

        for (const auto& word : words) {
            auto it = inverted_map_.find(word);
            if (it == inverted_map_.end())
                continue;

            for (auto item : it->second.get_item_list()) {
                if (docs.count(item.doc_id_) > 0)
                    results[word].push_back(item);
            }
        }

        return true;
    }
private:
    list<string> file_list_;
    unordered_map<string, InvertedList> inverted_map_;
};

#endif