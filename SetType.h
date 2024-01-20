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
    SetType();
    explicit SetType(int numBucks);
    SetType(SetType& other);

    ~SetType();

    void Add(T elem);
    void Remove(T elem);
    bool Contains(T elem);
    void MakeEmpty();
    int Size() const {
        return numElems;
    }

    double LoadFactor() const;
    void SetMaxLoad(double max);
    void Rehash(int newNumBuckets);

    SetType operator+(T elem);				      // Add
    SetType operator-(T elem);				      // Remove
    SetType operator+(SetType& otherSet);         // Union
    SetType operator-(SetType& otherSet);         // Difference
    SetType operator*(SetType& otherSet);         // Intersection
    SetType& operator=(SetType const& otherSet);  // Assignment (does deep copy)

    void ResetIterator();	// Reset iterator
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