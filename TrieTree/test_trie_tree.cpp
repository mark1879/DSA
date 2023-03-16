#include "trie_tree.hpp"
#include <gtest/gtest.h>

void TestAddWord(TrieTree* trie_tree, std::vector<std::string> word_list)
{
    for (const auto& word : word_list)
    {
        EXPECT_EQ(trie_tree->Query(word) == 0, true);
        trie_tree->Add(word);
        EXPECT_EQ(trie_tree->Query(word) > 0, true);
    }
}

void TestQueryPrefix(TrieTree* trie_tree, std::string prefix, std::vector<std::string> ans)
{
    std::vector<std::string> prefix_words;
    trie_tree->QueryPrefix(prefix, prefix_words);

    EXPECT_EQ(ans.size(), prefix_words.size());

    for (size_t i = 0, size = ans.size(); i < size; i++)
    {
        EXPECT_EQ(ans[i].compare(prefix_words[i]) == 0, true);
    }
}

void TestRemoveWord(TrieTree* trie_tree, std::vector<std::string> word_list)
{
    for (const auto& word : word_list)
    {
        EXPECT_EQ(trie_tree->Query(word) > 0, true);
        trie_tree->Remove(word);
        EXPECT_EQ(trie_tree->Query(word) == 0, true);
    }
}

int main()
{
    std::cout << "test_trie_tree..." << std::endl;

    TrieTree trie_tree;

    TestAddWord(&trie_tree, {"hello", "he", "helloo", "china", "chi", "ch"});

    TestQueryPrefix(&trie_tree, "he", {"he", "hello", "helloo"});
    TestQueryPrefix(&trie_tree, "ch", {"ch", "chi", "china"});

    // TestRemoveWord(&trie_tree, {"hello", "he", "chi", "ch"});

    std::cout << "test done!" << std::endl << std::endl;

    return 0;
}