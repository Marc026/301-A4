#include <string>
#include <iostream>
#include "SetType.h"

using namespace std;

template<class T>
SetType<T>::SetType() {
    // Create an array of forward_lists and initially set to an empty forward_list
    buckets = new forward_list<T>[DEFAULT_BUCKETS];

    // Your code here
    numBuckets = DEFAULT_BUCKETS;
    numElems = 0;
    maxLoad = DEFAULT_LOAD_FACTOR;
}

template<class T>
SetType<T>::SetType(int numBucks) {
    numBuckets = numBucks;
    numElems = 0;
    maxLoad = DEFAULT_LOAD_FACTOR;
}

template<class T>
void SetType<T>::Add(T elem) {
    int bucket = GetHashIndex(elem);
    bool found = false;

    for (auto it = buckets[bucket].begin(); it != buckets[bucket].end(); ++it) {
        if (*it == elem && Contains(elem)) {
            found = true;
            break;
        }
    }

    if (!found && !Contains(elem)) {
        buckets[bucket].push_front(elem);
        numElems++;
    }
}

template<class T>
void SetType<T>::Remove(T elem) {
    int bucket = GetHashIndex(elem);
    for (auto it = buckets[bucket].begin(); it != buckets[bucket].end(); ++it) {
        if (*it == elem && Contains(elem)) {
            buckets[bucket].remove(*it);
            --numElems;
            return;
        }
    }
}

template<class T>
bool SetType<T>::Contains(T elem) {
    int bucket = GetHashIndex(elem);
    for (auto it = buckets[bucket].begin(); it != buckets[bucket].end(); ++it) {
        if (*it == elem) {
            return true;
        }
    }
    return false;
}

template<class T>
void SetType<T>::MakeEmpty() {
    for (int i = 0; i < numBuckets; ++i) {
        buckets[i].clear();
    }
    numElems = 0;
    ResetIterator();
}

template<class T>
double SetType<T>::LoadFactor() const {
    return 0;
}

template<class T>
void SetType<T>::ResetIterator() {

}

template<class T>
void SetType<T>::copySet(const SetType &otherSet) {
    // Copy over bucket count and max load factor
    this->numBuckets = otherSet.numBuckets;
    this->maxLoad = otherSet.maxLoad;
    // Allocate new buckets array
    this->buckets = new forward_list<T>[this->numBuckets];
    // Loop through each bucket in otherSet
    for (int i = 0; i < otherSet.numBuckets; i++) {
        // Loop through each item in the bucket
        for (auto const& elem : otherSet.buckets[i]) {
            // Calculate the hash index for the item
            int index = this->GetHashIndex(elem);
            // Add the item to the appropriate bucket
            this->buckets[index].push_front(elem);
            // Increase the number of elements in the set
            this->numElems++;
        }
    }
}

template<class T>
SetType<T>::SetType(SetType &otherSet) {
    // This should make use of copySet
}

template<class T>
SetType<T>::~SetType() {
    delete [] buckets;
}


template<class T>
SetType<T> SetType<T>::operator+(T elem) {
    SetType<T> result;

    // Your code here

    return result;
}

template<class T>
SetType<T> SetType<T>::operator-(T elem) {
    SetType<T> result;

    // Your code here

    return result;
}

template<class T>
SetType<T> SetType<T>::operator+(SetType& otherSet) {
    SetType<T> result;

    // Your code here

    return result;
}

template<class T>
SetType<T> SetType<T>::operator*(SetType& otherSet) {
    SetType<T> result;

    // Your code here

    return result;
}

template<class T>
SetType<T> SetType<T>::operator-(SetType& otherSet) {
    SetType<T> result;

    // Your code here

    return result;
}

template<class T>
T SetType<T>::GetNextItem() {
    // Returns the current item and then move to the next item
    T item;

    // Your code here

    return item;
}

template<class T>
int SetType<T>::GetHashIndex(const T& key) {
    // This is done... No touching!
    unordered_map<T,T> mapper;
    typename unordered_map<T,T>::hasher hashFunction = mapper.hash_function();
    return static_cast<int>(hashFunction(key) % numBuckets);
}


template<class T>
void SetType<T>::SetMaxLoad(double max) {
    // This function is done
    if (max < 0.1)
        maxLoad = 0.1;
    else
        maxLoad = max;
}

template<class T>
SetType<T>& SetType<T>::operator=(SetType const &other) {

    // Your code here
    // Check for self-assignment
    if (this != &other) {
        // Clear current set
        this->MakeEmpty();
        // Copy over data from otherSet
        this->copySet(other);
    }

    return *this;
}


template<class T>
void SetType<T>::Rehash(int newNumBuckets) {
    SetType<T> rehashedSet(newNumBuckets);

    // Your code here

    *this = rehashedSet;
}