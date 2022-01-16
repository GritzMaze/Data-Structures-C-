#pragma once

#include <iostream>
#include <set>

const int DEFAULT_TABLE_SIZE = 128;

template <class Key, class Value>
class HashNode
{
public:
    Key key;
    Value value;
    HashNode<Key, Value> *next;

    HashNode(Key key, Value value)
    {
        this->key = key;
        this->value = value;
        this->next = nullptr;
    }

    Key &getKey()
    {
        return this->key;
    }

    Value &getValue()
    {
        return this->value;
    }

    void setValue(Value value)
    {
        this->value = value;
    }

    HashNode<Key, Value> *getNext()
    {
        return this->next;
    }

    void setNext(HashNode<Key, Value> *next)
    {
        this->next = next;
    }
};

template <class Key, class Value, class Hash = std::hash<Key> >
class HashMap
{
    public:
                                HashMap(size_t size = DEFAULT_TABLE_SIZE);
                                ~HashMap();
        HashNode<Key, Value>*    insert(Key key, Value value);
        Value&                  operator[](Key key);
        HashMap&                operator=( const HashMap& )     = default;
        bool                    contains(Key key)               const;
        size_t                  countOf(Key key)                const;
        std::multiset<Key>      keys()                          const;
        std::multiset<Key>      uniqueKeys()                    const;
        std::multiset<Value>    values()                        const;
        size_t                  size()                          const;
        size_t                  capacity()                      const;
        void                    clear();
        void                    resize(size_t newSize);
        void                    print()                         const;
        void                    remove(Key key);

    private:
        HashNode<Key, Value>**  table;
        size_t                  size_;
        size_t                  capacity_;
        Hash                    hash_;
        size_t                  maxSize;

        void                    resizeTable(size_t newSize);
        size_t                  hash(Key key)                   const;
        size_t                  getIndex(Key key)               const;
        void                    printTable()                    const;
        HashNode<Key, Value>*   find(Key key)                   const;
};

template <class Key, class Value, class Hash>
HashMap<Key, Value, Hash>::HashMap(size_t size)
{
    this->size_ = 0;
    this->capacity_ = size;
    this->maxSize = 96;
    this->table = new HashNode<Key, Value> *[size];
    for (size_t i = 0; i < size; i++)
    {
        this->table[i] = nullptr;
    }
}

template <class Key, class Value, class Hash>
HashMap<Key, Value, Hash>::~HashMap()
{
    this->clear();
    delete[] this->table;
}

template <class Key, class Value, class Hash>
HashNode<Key, Value> *HashMap<Key, Value, Hash>::insert(Key key, Value value)
{

    if (this->size_ >= this->maxSize)
    {
        this->resizeTable(this->capacity_ * 2);
    }

    unsigned long hashValue = this->hash(key);
    HashNode<Key, Value> *prev = nullptr;
    HashNode<Key, Value> *curr = this->table[hashValue];

    while (curr != nullptr && curr->getKey() != key)
    {
        prev = curr;
        curr = curr->getNext();
    }

    if (curr == nullptr)
    {
        curr = new HashNode<Key, Value>(key, value);
        if (prev == nullptr)
        {
            this->table[hashValue] = curr;
        }
        else
        {
            prev->setNext(curr);
        }
        this->size_++;
    }
    else
    {
        curr->setValue(value);
    }
    return curr;
}


template <class Key, class Value, class Hash>
void HashMap<Key, Value, Hash>::remove(Key key)
{
    unsigned long hashValue = this->hash(key);
    HashNode<Key, Value> *prev = nullptr;
    HashNode<Key, Value> *curr = this->table[hashValue];

    while (curr != nullptr && curr->getKey() != key)
    {
        prev = curr;
        curr = curr->getNext();
    }

    if (curr != nullptr)
    {
        if (prev == nullptr)
        {
            this->table[hashValue] = curr->getNext();
        }
        else
        {
            prev->setNext(curr->getNext());
        }
        delete curr;
        this->size_--;
    }
}

template <class Key, class Value, class Hash>
Value &HashMap<Key, Value, Hash>::operator[](Key key)
{
    if (HashNode<Key, Value>* data = this->find(key))
    {
        return data->getValue();
    }
    else
    {
        return insert(key, Value())->getValue();
    }
}

template <class Key, class Value, class Hash>
bool HashMap<Key, Value, Hash>::contains(Key key) const
{
    if(this->find(key))
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <class Key, class Value, class Hash>
size_t HashMap<Key, Value, Hash>::countOf(Key key) const
{
    if (HashNode<Key, Value>* data = this->find(key))
    {
        return data->getValue();
    }
    else
    {
        return 0;
    }
}

template <class Key, class Value, class Hash>
std::multiset<Key> HashMap<Key, Value, Hash>::keys() const
{
    std::multiset<Key> keys;
    for (size_t i = 0; i < this->capacity_; i++)
    {
        HashNode<Key, Value> *node = this->table[i];
        while (node != nullptr)
        {
            Key key = node->getKey();
            int count = node->getValue();
            for(int i = 0; i < count; i++)
            {
                keys.insert(key);
            }
            node = node->getNext();
        }
    }
    return keys;
}

template <class Key, class Value, class Hash>
std::multiset<Key> HashMap<Key, Value, Hash>::uniqueKeys() const
{
    std::multiset<Key> keys;
    for (size_t i = 0; i < this->capacity_; i++)
    {
        HashNode<Key, Value> *node = this->table[i];
        while (node != nullptr)
        {
            keys.insert(node->getKey());
            node = node->getNext();
        }
    }
    return keys;
}

template <class Key, class Value, class Hash>
std::multiset<Value> HashMap<Key, Value, Hash>::values() const
{
    std::multiset<Value> values;
    for (size_t i = 0; i < this->capacity_; i++)
    {
        HashNode<Key, Value> *node = this->table[i];
        while (node != nullptr)
        {
            values.insert(node->getValue());
            node = node->getNext();
        }
    }
    return values;
}

template <class Key, class Value, class Hash>
size_t HashMap<Key, Value, Hash>::size() const
{
    return this->size_;
}

template <class Key, class Value, class Hash>
size_t HashMap<Key, Value, Hash>::capacity() const
{
    return this->capacity_;
}

template <class Key, class Value, class Hash>
void HashMap<Key, Value, Hash>::clear()
{
    for (size_t i = 0; i < this->capacity_; i++)
    {
        HashNode<Key, Value> *node = this->table[i];
        while (node != nullptr)
        {
            HashNode<Key, Value> *next = node->getNext();
            delete node;
            node = next;
        }
    }
    this->size_ = 0;
}

template <class Key, class Value, class Hash>
void HashMap<Key, Value, Hash>::resizeTable(size_t newSize)
{
    int oldTableSize = this->capacity_;
    this->capacity_ = newSize;
    this->maxSize = (int) (this->capacity_ * 0.75f);
    HashNode<Key, Value> **oldTable = this->table;
    this->table = new HashNode<Key, Value>* [newSize];
    for (size_t i = 0; i < newSize; i++)
    {
        table[i] = nullptr;
    }

    this->size_ = 0;

    for (size_t i = 0; i < oldTableSize; i++)
    {
        if(oldTable[i] != nullptr) {
            HashNode<Key, Value>* oldEntry;
            HashNode<Key, Value>* newEntry = oldTable[i];
            while(newEntry != nullptr)
            {
                this->insert(newEntry->getKey(), newEntry->getValue());
                oldEntry = newEntry;
                newEntry = newEntry->getNext();
                delete oldEntry;
            }
        }
    }

    delete[] oldTable;
}

template <class Key, class Value, class Hash>
size_t HashMap<Key, Value, Hash>::hash(Key key) const
{
    return this->hash_(key) % this->capacity_;
}

template <class Key, class Value, class Hash>
void HashMap<Key, Value, Hash>::print() const
{
    for (size_t i = 0; i < this->capacity_; i++)
    {
        HashNode<Key, Value> *node = this->table[i];
        while (node != nullptr)
        {
            std::cout << node->getKey() << " " << node->getValue() << std::endl;
            node = node->getNext();
        }
    }
}

template <class Key, class Value, class Hash>
HashNode<Key, Value>* HashMap<Key, Value, Hash>::find(Key key) const
{
    unsigned long hashValue = this->hash(key);
    HashNode<Key, Value> *curr = this->table[hashValue];

    while (curr != nullptr && curr->getKey() != key)
    {
        curr = curr->getNext();
    }

    return curr;
}