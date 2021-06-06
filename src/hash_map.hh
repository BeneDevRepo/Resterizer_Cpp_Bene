#pragma once

#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <iostream>

template <typename _Item>
struct bucket {
    std::string     key;
    _Item           item;
    bool            occupied;
};

template <typename _Item>
class hash_map {
    using _Bucket = bucket<_Item>;

    private:
        _Bucket* data;
        unsigned int size = 10;

        unsigned int hash(const std::string& key) {
            unsigned int ret = 0;
            for (char c : key)
                ret += c;
            ret ^= 7521453792 * key[0];
            return ret;
        }

    public:
        hash_map() {
            this->size = 10;
            this->data = new _Bucket[size]();
        }

        ~hash_map() {
            delete[] this->data;
        }

        void insert(std::string key, _Item item) {
            size_t index = hash(key) % this->size;
            _Bucket *bucket = &this->data[index];

            if (!bucket->occupied) {
                bucket->key = key;
                bucket->item = item;
                bucket->occupied = true;
                return;
            }

            std::cout << bucket->key << "\n";

            if (!key.compare(bucket->key)) {//WTF
                bucket->item = item;
                return;
            }

            while (this->data[index].occupied) {
                unsigned int new_size = this->size * 2;
                _Bucket *new_data = new _Bucket[new_size]();
                for (unsigned int i = 0; i < this->size; ((int&)i)++) {
                    if(this->data[i].occupied) {
                        _Bucket new_bucket = { this->data[i].key, this->data[i].item, true };
                        new_data[hash(this->data[i].key) % new_size] = new_bucket;
                    }
                }
                
                delete[] this->data;
                this->data = new_data;
                this->size = new_size;
                index = hash(key) % new_size;
                bucket = &this->data[index];
            }

            bucket->key = key;
            bucket->item = item;
            bucket->occupied = true;
        }

        _Item& get(const std::string& key) {
            size_t index = hash(key) % this->size;
            _Bucket *bucket = &this->data[index];

            if (!bucket->occupied) throw std::logic_error("Item not found.");
            return bucket->item;
        }
};

// hash_map::hash_map(/* args */) {
// }

// hash_map::~hash_map() {
// }


// typedef struct hash_map hash_map_t;


// hash_map_t *hash_map_init();

// void hash_map_insert(hash_map_t *hm, const char *key, void *ptr);

// void *hash_map_get(hash_map_t *hm, const char *key);

// void hash_map_terminate(hash_map_t *hm);
