//
// Created by we7289 on 3/31/2021.
//

#define CATCH_CONFIG_MAIN
#include <iostream>
#include <istream>
#include <set>
#include "catch.hpp"
#include "../SetType.h"

TEST_CASE("SetType Tests") {

    SECTION("Add and Contains Tests - 5pts") {
        SetType<int> testSet;

        REQUIRE(!testSet.Contains(100));

        // Adds 0, 2, 4, 6, ... , 100
        for (int i = 0; i < 100; i+=2) {
            testSet.Add(i);
            REQUIRE(testSet.Contains(i));
        }

        // Checks 1, 3, 5, ... , 99
        for (int i = 1; i < 100; i+=2) {
            REQUIRE(!testSet.Contains(i));
        }
    }

    SECTION("Assignment/MakeEmpty Tests - 5pts") {
        SetType<int> setA, setB;

        // Adds 0, 2, 4, 6, ... , 100
        for (int i = 0; i < 100; i+=2) {
            setA.Add(i);
            REQUIRE(setA.Contains(i));
        }

        setB = setA;

        // setB should have all the elements in setA
        for (int i = 0; i < 100; i+=2) {
            REQUIRE(setB.Contains(i));
        }

        setA.MakeEmpty();
        REQUIRE(setA.Size() == 0);

        // setB should still have the same elements
        for (int i = 0; i < 100; i+=2) {
            REQUIRE(setB.Contains(i));
        }
    }

    SECTION("Remove Tests - 5pts") {
        SetType<int> testSet;

        for (int i = 0; i < 100; i++) {
            testSet.Add(i);
        }

        // Remove all odd numbers
        for (int i = 1; i < 100; i += 2) {
            testSet.Remove(i);
        }

        // Check to make sure even numbers are there
        for (int i = 0; i < 100; i+=2) {
            REQUIRE(testSet.Contains(i));
        }

        // Check to make sure odd numbers are not there
        for (int i = 1; i < 100; i+=2) {
            REQUIRE(!testSet.Contains(i));
        }
    }

    SECTION("Overload Add/Remove Tests - 5pts") {
        SetType<int> testSet;

        for (int i = 0; i < 100; i++) {
            testSet = testSet+i;
        }

        // Remove all odd numbers
        for (int i = 1; i < 100; i += 2) {
            testSet = testSet-i;
        }

        // Check to make sure even numbers are there
        for (int i = 0; i < 100; i+=2) {
            REQUIRE(testSet.Contains(i));
        }

        // Check to make sure odd numbers are not there
        for (int i = 1; i < 100; i+=2) {
            REQUIRE(!testSet.Contains(i));
        }

        REQUIRE(testSet.Size() == 50);
    }

    SECTION("Union Tests - 5pts") {
        SetType<int> setA;
        SetType<int> setB;
        SetType<int> unionAB;

        // Odd numbers
        for (int i = 0; i < 100; i+=2) {
            setA.Add(i);
        }

        // Even numbers
        for (int i = 1; i < 100; i += 2) {
            setB.Add(i);
        }

        unionAB = setA + setB;

        // Check to make sure even numbers are there
        for (int i = 0; i < 100; i++) {
            REQUIRE(unionAB.Contains(i));
        }

        REQUIRE(unionAB.Size() == 100);
    }

    SECTION("Difference Tests - 5pts") {
        SetType<int> setA;
        SetType<int> setB;
        SetType<int> diffAB, diffBA;

        //   setA = {25, ... , 99}
        for (int i = 25; i < 100; i++) {
            setA.Add(i);
        }

        //   setB = { 0, ... , 74}
        for (int i = 0; i < 75; i++) {
            setB.Add(i);
        }

        //   setA = {25, ... , 99}
        //   setB = { 0, ... , 74}
        // diffAB = {75, ... , 99}
        diffAB = setA - setB;
        for (int i = 75; i <= 99; i++) {
            REQUIRE(diffAB.Contains(i));
        }

        //   setA = {25, ... , 99}
        //   setB = { 0, ... , 74}
        // diffBA = { 0, ... , 24}
        diffBA = setB - setA;
        for (int i = 0; i <= 24; i++) {
            REQUIRE(diffBA.Contains(i));
        }
    }

    SECTION("Intersection Tests - 5pts") {
        SetType<int> setA;
        SetType<int> setB;
        SetType<int> intersectionAB;

        //   setA = {25, ... , 99}
        for (int i = 25; i < 100; i++) {
            setA.Add(i);
        }

        //   setB = { 0, ... , 74}
        for (int i = 0; i < 75; i++) {
            setB.Add(i);
        }

        //           setA = {25, ... , 99}
        //           setB = { 0, ... , 74}
        // intersectionAB = {25, ... , 74}
        intersectionAB = setA*setB;
        for (int i = 25; i <= 74; i++) {
            REQUIRE(intersectionAB.Contains(i));
        }
    }

    SECTION("Rehash Tests - 5pts") {
        double maxLoad = 1;
        int numBuckets = 10;
        set<int> stlSet;
        SetType<int> testSet(numBuckets);
        testSet.SetMaxLoad(maxLoad);

        double load = 0;
        // Add 100 random elements into stlSet and testSet
        // Note we may get slightly less than 100 if we have duplicates.
        for (int i = 0; i < 100; i++) {
            int randVal = rand()%1000;
            testSet.Add(randVal);
            stlSet.insert(randVal);
            load = static_cast<double>(stlSet.size())/numBuckets;
            if (load > maxLoad) {
                numBuckets *= 2;
                load = static_cast<double>(stlSet.size())/numBuckets;
            }

            // cout << load << "\t" << testSet.LoadFactor() << endl;
            REQUIRE(testSet.LoadFactor() == load);
        }
    }

    SECTION("Iterator Tests - 5pts") {
        set<int> stlSet;
        SetType<int> testSet;

        // Add 100 random elements into stlSet and testSet
        // Note we may get slightly less than 100 if we have duplicates.
        for (int i = 0; i < 100; i++) {
            int randVal = rand()%1000;
            testSet.Add(randVal);
            stlSet.insert(randVal);
        }

        REQUIRE(stlSet.size() == testSet.Size());   // should be same size

        // Iterate through testSet
        testSet.ResetIterator();
        for (int i = 0; i < stlSet.size(); i++) {
            REQUIRE(stlSet.find(testSet.GetNextItem()) != stlSet.end());
        }

        REQUIRE_THROWS(testSet.GetNextItem(), IteratorOutOfBounds());
    }
}