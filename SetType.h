#ifndef SET_TYPE
#define SET_TYPE

#include<string>
#include<iostream>
#include<forward_list>
#include<unordered_map>
using namespace std;

class IteratorOutOfBounds {
public:
    string Msg() {
        return "Iterator is out of bounds.  Nothing left to iterate over.";
    }
};

const int DEFAULT_BUCKETS = 10;
const double DEFAULT_LOAD_FACTOR = 1.0;

template<class T>
class SetType
{
public:
    // Constructors
    //Function:
    //Default Constructor setting up an array of forward lists
    //Precondition:
    //STL library and new and empty array of forward lists is made
    //Postcondition:
    //all variables required are initialized
    SetType();

    //Function:
    //2nd constructor setting up an array of forward lists
    //Precondition:
    //STL library and new and empty array of forward lists is made
    //Postcondition:
    //all variables required are initialized
    explicit SetType(int numBucks);

    //Function:
    //Makes use of copySet
    //Precondition:
    //none
    //Postcondition:
    //copySet is properly initialized
    SetType(SetType& otherSet);

    //Function:
    //Destructor
    //Precondition:
    //none
    //Postcondition:
    //all buckets are deleted
    ~SetType();

    //Function:
    //Adds element to specific bucket
    //Precondition:
    //bucket index is found
    //Postcondition:
    //element added in proper bucket
    void Add(T elem);

    //Function:
    //Removes element from specific bucket
    //Precondition:
    //bucket index is found
    //Postcondition:
    //element removed from specific bucket
    void Remove(T elem);

    //Function:
    //checks if buckets contain specific element
    //Precondition:
    //bucket index is found
    //Postcondition:
    //returns true or false of element being contained
    bool Contains(T elem);

    //Function:
    //deletes all inside buckets and resets iterators
    //Precondition:
    //none
    //Postcondition:
    //none
    void MakeEmpty();

    //Function:
    //returns number of elements in array
    //Precondition:
    //none
    //Postcondition:
    //returns numElems
    int Size() const {
        return numElems;
    }

    //Function:
    //checks if the bucket is too full
    //Precondition:
    //none
    //Postcondition:
    //if needed, rehash is called
    double LoadFactor() const;

    //Function:
    //calculates how many elements should be in each bucket
    //Precondition:
    //none
    //Postcondition:
    //none
    void SetMaxLoad(double max);

    //Function:
    //doubles number of buckets and equlas out the load in each bucket
    //Precondition:
    //a bucket is overloaded with too many elements than it can handle
    //Postcondition:
    //buckets are balanced
    void Rehash(int newNumBuckets);

    //Function:
    //Overloaded Add operator
    //Precondition:
    //none
    //Postcondition:
    //none
    SetType operator+(T elem);				      // Add

    //Function:
    //Overloaded Remove operator
    //Precondition:
    //none
    //Postcondition:
    //none
    SetType operator-(T elem);				      // Remove

    //Function:
    //Union of two lists
    //Precondition:
    //none
    //Postcondition:
    //none
    SetType operator+(SetType& otherSet);         // Union

    //Function:
    //Difference of two lists
    //Precondition:
    //none
    //Postcondition:
    //none
    SetType operator-(SetType& otherSet);         // Difference

    //Function:
    //Intersection of two lists
    //Precondition:
    //none
    //Postcondition:
    //none
    SetType operator*(SetType& otherSet);         // Intersection

    //Function:
    //makes a deep copy of a list into otherSet
    //Precondition:
    //none
    //Postcondition:
    //none
    SetType& operator=(SetType const& otherSet);  // Assignment (does deep copy)

    //Function:
    //resets back to the beginning of bucket list
    //Precondition:
    //none
    //Postcondition:
    //none
    void ResetIterator();	// Reset iterator

    //Function:
    //move to the next item
    //Precondition:
    //none
    //Postcondition:
    //none
    T GetNextItem();

private:
    forward_list<T>* buckets;	// An array of forward_list's
                                // (each index is a forward_list)

    int numBuckets;     // total number of buckets

    int GetHashIndex(const T& key);    // Gets the hash index given the elem

    int numElems;       // total number of elements

    double maxLoad;     // load factor of the Set

    // This function is used by the
    // copy constructor and the assignment operator.
    void copySet(const SetType& otherSet);

    // Iterator variables
    int currBucket;											// What bucket is the iterator on?
    int iterCount;                                          // What element are we on?
    mutable typename forward_list<T>::iterator bucketIter;	// The iterator of the current bucket

    // Any other private functions and variables you want/need
};



#include "SetType.cpp"

#endif