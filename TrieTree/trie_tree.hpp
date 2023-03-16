#ifndef TRIE_TREE_HPP
#define TRIE_TREE_HPP
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <queue>

struct TrieNode
{
    TrieNode(char chr, size_t freqs)
        : char_(chr)
        , char_freqs_(freqs)
    {}

    char char_;
    size_t char_freqs_;
    std::map<char, TrieNode*> child_map_;
};

class TrieTree
{
public:
    TrieTree()
    {
        root_ = new TrieNode('\0', 0);
    }

    ~TrieTree()
    {
        std::queue<TrieNode*> q;
        q.push(root_);

        while(!q.empty())
        {
            TrieNode* front = q.front();
            q.pop();

            for (auto& pair : front->child_map_)
            {
                q.push(pair.second);
            }

            delete front;
        }
    }

    void Add(const std::string& word)
    {
        if (word.size() == 0)
            return;

        TrieNode* curr = root_;

        for (size_t i = 0; i < word.size(); i++)
        {
           auto child_iter = curr->child_map_.find(word[i]);
           if (child_iter == curr->child_map_.end())
           {
                TrieNode* new_node = new TrieNode(word[i], 0);
                curr->child_map_.emplace(word[i], new_node);
                curr = new_node;
                continue;
           }

            curr = child_iter->second;
        }

        curr->char_freqs_++;
    }

    size_t Query(const std::string& word) const
    {
        if (word.size() == 0)
            return 0;

        TrieNode* curr = root_;
        for (size_t i = 0; i < word.size(); i++)
        {
            auto child_iter = curr->child_map_.find(word[i]);
            if (child_iter == curr->child_map_.end())
                return 0;

            curr = child_iter->second;
        }

        return curr->char_freqs_;
    }

    void Remove(const std::string& word)
    {
        if (word.size() == 0)
            return;

        TrieNode* curr = root_;
        char del_char = root_->char_;
        TrieNode* del_char_parent_node = root_;

        for (size_t i = 0; i < word.size(); i++)
        {
            auto child_iter = curr->child_map_.find(word[i]);
            if (child_iter == curr->child_map_.end())
                return;

            if (curr->char_freqs_ > 0 || curr->child_map_.size() > 0)
            {
                del_char_parent_node = curr;
                del_char = curr->char_;
            }

            curr = child_iter->second;
        }

        if (curr->child_map_.size() > 0)
        {
            curr->char_freqs_ = 0;
            return;
        }

        TrieNode* del_node = del_char_parent_node->child_map_[del_char];
        del_char_parent_node->child_map_.erase(del_char);

        std::queue<TrieNode *> q;
        q.push(del_node);

        while (!q.empty())
        {
            TrieNode* front = q.front();
            q.pop();

            for (auto& pair : front->child_map_)
            {
                q.push(pair.second);
            }

            delete front;
        }
    }

    void PreOrder(std::vector<std::string> word_list) const 
	{
		std::string word;
		PreOrder(root_, word, word_list);
	}

	void QueryPrefix(const std::string& prefix, std::vector<std::string>& word_list) const
	{
        if (prefix.size() == 0)
            return;

		TrieNode* cur = root_;
		for (size_t i = 0; i < prefix.size(); i++)
		{
			auto child_iter = cur->child_map_.find(prefix[i]);
			if (child_iter == cur->child_map_.end())
                return;

			cur = child_iter->second;
		}

        std::string word = prefix.substr(0, prefix.size()-1);

		PreOrder(cur, word, word_list);
	}

private:
    void PreOrder(TrieNode* curr, std::string& word, std::vector<std::string>& word_list) const
    {
        if (curr != root_)
        {
            word.push_back(curr->char_);
            if (curr->char_freqs_ > 0)
            {
                word_list.emplace_back(word);
            }
        }

        for (const auto& pair : curr->child_map_)
        {
            PreOrder(pair.second, word, word_list);
        }
    }

private:
    TrieNode* root_;
};


#endif