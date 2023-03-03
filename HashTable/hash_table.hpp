#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

class HashTable {
public:
    HashTable() {}
    virtual ~HashTable() { }

    virtual void Insert(int key) = 0;
    virtual void Erase(int key) = 0;
    virtual bool Find(int key) const = 0;
};


#endif