#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

class HashTable {
public:
    HashTable() {}
    virtual ~HashTable() { }

    virtual bool Insert(size_t key) = 0;
    virtual void Erase(size_t key) = 0;
    virtual bool Find(size_t key) const = 0;
};


#endif