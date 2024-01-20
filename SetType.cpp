// Created by: Gino Tateo 2022

#include <string>
#include <iostream>
#include "SetType.h"

using namespace std;

template<class T>
SetType<T>::SetType() {
    // Create an array of forward_lists and initially set to an empty forward_list
    buckets = new forward_list<T>[DEFAULT_BUCKETS];

    numElems = 0;                                                       // Book keeping, number of elements

    //Buckets
    buckets->clear();                                                   // Clears the buckets
    numBuckets = DEFAULT_BUCKETS;                                       // Book keeps v
    maxLoad = DEFAULT_LOAD_FACTOR;
    currBucket = 0;

    //Iter
    iterCount = 0;
    bucketIter = buckets[currBucket].begin();                           // Sets the iter
}

template<class T>
SetType<T>::SetType(int numBucks) {
    numBuckets = numBucks;                                              // set number of buckets.
    buckets = new forward_list<T>[numBuckets];                          // create an array of forward_list of size numBuckets.
    numElems = 0;                                                       // set number of numElems.
    maxLoad = DEFAULT_LOAD_FACTOR;                                      // set load
    currBucket = 0;

    //Iter
    iterCount = 0;
    bucketIter = buckets[currBucket].begin();                           // point bucketIter to start element
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

    result = *this;             // Set to this set
    result.Add(elem);           // Add elem

    return result;
}

template<class T>
SetType<T> SetType<T>::operator-(T elem) {
    SetType<T> result;

    result = *this;             // Set to this Set
    result.Remove(elem);        // Remove T elem

    return result;
}

template<class T>
SetType<T> SetType<T>::operator+(SetType& otherSet) {
    SetType<T> result;

    result = *this;                                 // Set to this Set
    otherSet.ResetIterator();                       // Reset Iter
    for(int i=0;i<otherSet.Size();i++){             // Iter through set
        result.Add(otherSet.GetNextItem());   // Add elems from otherset
    }

    return result;
}

template<class T>
SetType<T> SetType<T>::operator*(SetType& otherSet) {

    // Two sets
    SetType<T> result;
    SetType<T> diff;

    // Set result = to this
    result = *this;

    // Find the different set
    diff = result-otherSet;

    // Subtract to different set to find the common set
    result=result-diff;

    // Return the intersection
    return result;
}

template<class T>
SetType<T> SetType<T>::operator-(SetType& otherSet) {
    SetType<T> result;

    result = *this;                                     // Set to this
    otherSet.ResetIterator();                           // Reset the iter
    for(int i=0;i<otherSet.Size();i++){                 // Iter through the size
        result.Remove(otherSet.GetNextItem());    // Remove otherset get next item
    }

    return result;          // Return the difference set
}

template<class T>
T SetType<T>::GetNextItem() {
    T item;

    if(iterCount >= numElems) throw IteratorOutOfBounds();       // error handling for iter out of bounds

    while(bucketIter == buckets[currBucket].end()) {
        currBucket++;
        bucketIter = buckets[currBucket].begin();               // sets to the starts
    }

    item = *bucketIter;
    iterCount++;
    ++bucketIter;
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
    // Call copy
    copySet(other);

    // Set the iterator back to 0 position
    ResetIterator();
    return *this;
}


template<class T>
void SetType<T>::Rehash(int newNumBuckets) {
    SetType<T> rehashedSet(newNumBuckets);

    ResetIterator();                                    // Set iter back to begin

    for(int i=0;i<Size();i++){                          // Walk through set with size()
        rehashedSet.Add(GetNextItem());           // Get next item
    }

    *this = rehashedSet;                                // Set rehashed set to this
}

template<class T>
void SetType<T>::Add(T elem) {

    if(!Contains(elem)) {                            // Checks to see if the element is in the set.



        int bucket = GetHashIndex(elem);        // Gets the intended bucket
        buckets[bucket].push_front(elem);            // Adds element to the front
        numElems++;                                  // Book keeping

        if(LoadFactor() > maxLoad) {                 // Checks loadfactor
            Rehash(2 * numBuckets);
        }

    }
}

template<class T>
void SetType<T>::Remove(T elem) {
    if (Contains(elem)) {                     // If the elem exists
        int bucket = GetHashIndex(elem); // Find the bucket
        buckets[bucket].remove(elem);         // Remove the bucket
        numElems--;                           // Book keeping
    }
}

template<class T>
bool SetType<T>::Contains(T elem) {
    int bucket = GetHashIndex(elem);                                         // Calculate bucket.

    for (auto it = buckets[bucket].begin(); it != buckets[bucket].end(); ++it)    // Iter to find elem in bucket
        if (*it == elem) {                                                        // If it =s elem return true.
            return true;
        }
    return false;
}

template<class T>
void SetType<T>::MakeEmpty() {
    for(int i=0;i<numBuckets;i++){
        buckets[i].clear();                     // Clear bucket
    }
    numElems = 0;
}

template<class T>
double SetType<T>::LoadFactor() const {
    double a;
    double b;
    a = double (numElems);              // Cast numelems to keep precision
    b = double (numBuckets);            // Cast numbuckets to keep precision

    if(numBuckets > 0)
        return a/b;                       // numElems/numBuckets, Have to cast numElems to keep precision
    return 0;
}

template<class T>
void SetType<T>::ResetIterator() {

    bucketIter = buckets->begin();              // Set back to beginning
    currBucket = 0;                             // Update Variables
    iterCount = 0;

}

template<class T>
void SetType<T>::copySet(const SetType &otherSet) {

    // Prep the new set
    MakeEmpty();
    numBuckets = otherSet.numBuckets;
    maxLoad = otherSet.maxLoad;
    buckets->clear();
    buckets = new forward_list<T>[numBuckets];
    numElems = otherSet.numElems;

    // Copy
    for(int i=0;i<otherSet.numBuckets;i++){
        buckets[i].insert_after(buckets[i].before_begin(), otherSet.buckets[i].begin(), otherSet.buckets[i].end());
    }

}


