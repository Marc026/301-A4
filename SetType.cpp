#include <string>
#include <iostream>
#include "SetType.h"

using namespace std;

template<class T>
SetType<T>::SetType() {
    // Create an array of forward_lists and initially set to an empty forward_list
    buckets = new forward_list<T>[DEFAULT_BUCKETS];

    // Your code here
    numBuckets = DEFAULT_BUCKETS;   //set values to default values or 0
    numElems = 0;                   //set values to default values or 0
    maxLoad = DEFAULT_LOAD_FACTOR;  //set values to default values or 0
    currBucket = 0;                 //set values to default values or 0
    iterCount = 0;                  //set values to default values or 0
}

template<class T>
SetType<T>::SetType(int numBucks) {
    numBuckets = numBucks;                  //set numBuckets to test size
    buckets = new forward_list<T>[numBucks];    //make new array of forward list w/ numBucks
    numElems = 0;                           //set values to default values or 0
    maxLoad = DEFAULT_LOAD_FACTOR;
    currBucket = 0;
    iterCount = 0;
}

template<class T>
void SetType<T>::Add(T elem) {
    int bucket = GetHashIndex(elem);    //find which bucket elem goes into

    for (auto it = buckets[bucket].begin(); it != buckets[bucket].end(); it++) {
        if (*it == elem) {                  //look at every value in bucket
            return;                         //and if elem exists already, return
        }
    }
    buckets[bucket].push_front(elem);       //else push to front of bucket
    numElems++;                             //book-keeping

    if (LoadFactor() > maxLoad) {           //check load factor of bucket
        Rehash(2*numBuckets);   //call Rehash
    }
}

template<class T>
void SetType<T>::Remove(T elem) {
    int bucket = GetHashIndex(elem);    //find which bucket elem goes into

    for (auto it = buckets[bucket].begin(); it != buckets[bucket].end(); it++) {
        if (*it == elem) {                  //look at every value in bucket
            buckets[bucket].remove(*it);    //and if elem exists already, remove it
            numElems--;                     //book-keeping
            return;
        }
    }
}

template<class T>
bool SetType<T>::Contains(T elem) {
    int bucket = GetHashIndex(elem);
    for (auto it = buckets[bucket].begin(); it != buckets[bucket].end(); ++it) {
        if (*it == elem) {                  //look at every value in bucket
            return true;                    //and if elem exists already, return true
        }
    }
    return false;                           //else return false
}

template<class T>
void SetType<T>::MakeEmpty() {
    for (int i = 0; i < numBuckets; ++i) {  //for every bucket
        buckets[i].clear();                 //delete everything inside bucket
    }
    numElems = 0;           //reset book-keeping
    ResetIterator();        //Call ResetIterator func
}

template<class T>
double SetType<T>::LoadFactor() const {
    return static_cast<double>(numElems)/numBuckets;    //formula to calculate & return LoadFactor
}


template<class T>
void SetType<T>::ResetIterator() {
    currBucket = 0;                     //resets values to 0
    iterCount = 0;                      // and back to the beginning of array
    bucketIter = buckets[currBucket].begin();
}

template<class T>
void SetType<T>::copySet(const SetType &otherSet) {
    this->numBuckets = otherSet.numBuckets;     // Copy over bucket count and max load factor
    this->maxLoad = otherSet.maxLoad;
    this->buckets = new forward_list<T>[this->numBuckets];// Allocate new buckets array

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
    delete [] buckets;  //deletes buckets
}


template<class T>
SetType<T> SetType<T>::operator+(T elem) {
    SetType<T> result;  //make result object
    result = *this;     //point to this

    // Your code here
    result.Add(elem);   //overloaded add elem

    return result;
}

template<class T>
SetType<T> SetType<T>::operator-(T elem) {
    SetType<T> result;  //make result object
    result = *this;     //point to this

    // Your code here
    result.Remove(elem);//overloaded remove elem

    return result;
}

template<class T>
SetType<T> SetType<T>::operator+(SetType& otherSet) {
    SetType<T> result(numBuckets);  //make result object of numBuckets

    // Your code here
    // Add all elements of this set to the result
    for (int i = 0; i < numBuckets; i++) {
        for (T elem : buckets[i]) {
            result.Add(elem);
        }
    }

    // Add all elements of the other set to the result
    for (int i = 0; i < otherSet.numBuckets; i++) {
        for (T elem : otherSet.buckets[i]) {
            result.Add(elem);
        }
    }

    return result;
}

template<class T>
SetType<T> SetType<T>::operator*(SetType& otherSet) {
    SetType<T> result;

    // Your code here
    // Add all elements of this set to the result
    for (int i = 0; i < numBuckets; i++) {
        for (auto it = buckets[i].begin(); it != buckets[i].end(); ++it) {
            if (otherSet.Contains(*it)) {
                result.Add(*it);
            }
        }
    }

    return result;
}

template<class T>
SetType<T> SetType<T>::operator-(SetType& otherSet) {
    SetType<T> result(numBuckets);

    // Your code here
    // Iterate over the elements in this set
    for (int i = 0; i < numBuckets; i++) {
        for (T elem : buckets[i]) {
            // Check if the element is not present in the other set
            if (!otherSet.Contains(elem)) {
                // Add the element to the result set
                result.Add(elem);
            }
        }
    }

    return result;
}

template<class T>
T SetType<T>::GetNextItem() {
    // Returns the current item and then move to the next item
    T item;

    // Your code here
    // If there are no more elements
    if (iterCount >= numElems) {
        throw IteratorOutOfBounds();
    }

    // Find the first non-empty bucket
    while (bucketIter == buckets[currBucket].end()) {
        currBucket++;
        if (currBucket >= numBuckets) {
            throw IteratorOutOfBounds();
        }
        bucketIter = buckets[currBucket].begin();
    }

    // Get the current item and move to the next item
    item = *bucketIter;
    bucketIter++;
    iterCount++;

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
    //make rehashedSet object of newNumBuckets
    SetType<T> rehashedSet(newNumBuckets);

    // Add all elements of this set to the result
    for(int i = 0; i < this->numBuckets; i++){
        for(auto it = buckets[i].begin(); it != buckets[i].end(); ++it){
            rehashedSet.Add(*it);
        }
    }

    *this = rehashedSet;
}