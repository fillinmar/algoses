#include <iostream>
#include <string>
#include <utility>
#include <vector>

size_t hashFunc1(const std::string &str, size_t m) //Gorner
{
    const char *cstr = str.c_str();
    size_t hash = 0;
    for (; *cstr != 0; ++cstr)
        hash = (hash * 7 + *cstr) % m;
    return hash;
};

size_t hashFunc2(const std::string &str, size_t m) //return only odd numbers
{
    const char *cstr = str.c_str();
    size_t hash = 0;
    for (; *cstr != 0; ++cstr)
        hash = (hash * 7 + *cstr) % m;
    if (hash % 2)
        return hash;
    else
        return hash + 1;
};


class HashTable {
public:
    HashTable() : buckets(std::vector<Elem>(0, Elem("", true, false))), itemCount(0), bucketsCount(0) {
    }

    HashTable(const HashTable &) = delete;

    HashTable &operator=(const HashTable &) = delete;

    HashTable(HashTable &&) = delete;

    HashTable &operator=(HashTable &&) = delete;

    bool insert(const std::string &key) {
        if (find(key)) {
            return false;
        }
        if (buckets.empty() || itemCount >= bucketsCount * LIMIT) {
            grow();
        }
        int i = 0;
        size_t firstDeletedPos = -1;
        size_t firstHash = hashFunc1(key, bucketsCount);
        size_t secondHash = hashFunc2(key, bucketsCount);
        size_t bucketIdx = firstHash;

        while (!buckets[bucketIdx].empty && i < bucketsCount) {
            if (buckets[bucketIdx].key == key)
                return false;
            if (firstDeletedPos == -1 && buckets[bucketIdx].del)
                firstDeletedPos = bucketIdx;

            i++;
            bucketIdx = (firstHash + i * secondHash) % bucketsCount;
        }
        if (firstDeletedPos != -1)
            bucketIdx = firstDeletedPos;
        buckets[bucketIdx] = Elem(key, false, false);
        itemCount++;
        return true;

    }

    bool find(const std::string &key) {
        if (buckets.empty()) {
            return false;
        }
        size_t firstHash = hashFunc1(key, bucketsCount);
        size_t secondHash = hashFunc2(key, bucketsCount);
        size_t bucketIdx = firstHash;
        int i = 1;
        while ((!buckets[bucketIdx].empty || buckets[bucketIdx].del) && buckets[bucketIdx].key != key) {
            bucketIdx = (firstHash + i * secondHash) % bucketsCount;
            if (bucketIdx == firstHash)
                break;
            i++;
        }
        if (!buckets[bucketIdx].empty && buckets[bucketIdx].key == key && !buckets[bucketIdx].del)
            return true;
        return false;
    }

    bool erase(const std::string &key) {
        if (buckets.empty()) {
            return false;
        }

        int i = 1;
        size_t firstHash = hashFunc1(key, bucketsCount);
        size_t secondHash = hashFunc2(key, bucketsCount);
        size_t bucketIdx = firstHash;

        while ((!buckets[bucketIdx].empty || buckets[bucketIdx].del) && buckets[bucketIdx].key != key) {
            bucketIdx = (firstHash + i * secondHash) % bucketsCount;
            if (bucketIdx == firstHash)
                break;
            i++;
        }
        if (!buckets[bucketIdx].empty && buckets[bucketIdx].key == key && !buckets[bucketIdx].del){
                buckets[bucketIdx].empty = true;
                buckets[bucketIdx].del = true;
                buckets[bucketIdx].key = "";
                return true;
        }
        return false;
    }

    void print() {
        for (int i = 0; i < bucketsCount; i++)
            std::cout << buckets[i].key << std::endl;
    }

private:
    const float LIMIT = 0.75;

    struct Elem {
        std::string key;
        bool empty;
        bool del;

        Elem(std::string a_key, bool a_empty, bool a_del) : key(std::move(a_key)), empty(a_empty), del(a_del) {
        }
    };

    std::vector<Elem> buckets;
    size_t itemCount;
    size_t bucketsCount;

    void grow() {
        size_t newBucketsCount = std::max((size_t) 8, bucketsCount * 2);
        std::vector<Elem> newBuckets = std::vector<Elem>(newBucketsCount, Elem("", true, false));
        for (int i = 0; i < bucketsCount; i++) {
            if (buckets[i].empty != 1) {
                std::string key = buckets[i].key;
                size_t firstHash = hashFunc1(key, newBucketsCount);

                size_t secondHash = hashFunc2(key, newBucketsCount);
                int j = 0;
                size_t bucketIdx = firstHash;

                while (!newBuckets[bucketIdx].empty) {
                    j++;
                    bucketIdx = (firstHash + j * secondHash) % newBucketsCount;
                }
                newBuckets[bucketIdx].key = buckets[i].key;
                newBuckets[bucketIdx].empty = false;
            }
        }
        buckets = newBuckets;
        bucketsCount = newBucketsCount;
    };
};

int main() {
    HashTable htable;
    std::string key;
    char operation = '\0';
    while (std::cin >> operation >> key) {
        bool res = false;
        switch (operation) {
            case '+':
                res = htable.insert(key);
                break;
            case '-':
                res = htable.erase(key);
                break;
            case '?':
                res = htable.find(key);
                break;
            default:
                return 1;
        };
        if (res) {
            std::cout << "OK" << std::endl;
        } else {
            std::cout << "FAIL" << std::endl;
        }
    }
    return 0;
}