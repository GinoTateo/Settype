/*
 * Author: Varick Erickson 3/31/2021
 */



#include <string>
#include <iostream>
#include "SetType.h"
using namespace std;

void PrintSet(SetType<char>& set) {
    set.ResetIterator();

    cout << "{ ";
    for (int i = 0; i < set.Size(); i++) {
        cout << set.GetNextItem() << " ";
    }
    cout << "}" << ", size = " << set.Size() << endl;
}

int main() {

    SetType<char> setA;
    SetType<char> setB;
    SetType<char> setC;
    SetType<char> setD;


    for (char c = 'a'; c <= 'z'; c++) {
        setA.Add(c);
    }

    for (char c = 'a'; c <= 'z'; c+=2) {
        setB.Add(c);
    }

    for (char c = '0'; c <= '9'; c++) {
        setC.Add(c);
    }

    // Print out both sets
    cout << "setA: ";
    PrintSet(setA);
    cout << "setB: ";
    PrintSet(setB);
    cout << "setC: ";
    PrintSet(setC);

    cout << endl;

    // Very basic contains and remove tests
    cout << "Contains and Removes" << endl;
    cout << "--------------------------" << endl;
    if (setA.Contains('a'))
        cout << "setA contains 'a'" << endl;
    cout << "Removing 'a' from setA" << endl;
    setA.Remove('a');
    if (setA.Contains('a'))
        cout << "Uh oh... setA still contains 'a'" << endl;
    else
        cout << "Woot! setA does NOT contain 'a'" << endl;

    cout << endl;

    cout << "Union test" << endl;
    cout << "----------" << endl;
    SetType<char> unionBC;
    unionBC = setB + setC;  // Trying union
    cout << "Union B and C: ";
    PrintSet(unionBC);

    cout << endl;

    // Tests the MakeEmpty
    setA.MakeEmpty();
    setB.MakeEmpty();

    // setA will contain {a, b, c, d}
    for (char c = 'a'; c < 'e'; c++) {
        setA.Add(c);
    }

    // setB will contain {b, d, e}
    setB.Add('b');
    setB.Add('d');
    setB.Add('e');

    cout << "setA: ";
    PrintSet(setA);
    cout << "setB: ";
    PrintSet(setB);
    cout << endl;

    cout << "Difference test" << endl;
    cout << "---------------" << endl;
    SetType<char> diffAB;
    diffAB = setA - setB;  // Trying difference
    cout << "Difference A and B: ";
    PrintSet(diffAB);
    SetType<char> diffBA;
    diffBA = setB - setA;  // Trying difference
    cout << "Difference B and A: ";
    PrintSet(diffBA);

    cout << endl;

    cout << "Intersection test" << endl;
    cout << "-----------------" << endl;
    SetType<char> intersectAB;
    intersectAB = setA*setB;  // Trying intersect
    cout << "Intersection A and B: ";
    PrintSet(intersectAB);

    cout << endl;

    cout << "Iterator test" << endl;
    cout << "-------------" << endl;
    try {
        setA.ResetIterator();

        cout << "{ ";
        for (int i = 0; i < setA.Size(); i++) {
            cout << setA.GetNextItem() << " ";
        }
        cout << "}" << ", size = " << setA.Size() << endl;
        setA.GetNextItem();

    }
    catch (IteratorOutOfBounds& error) {
        cout << "Error caught successfully" << endl;
        cout << error.Msg() << endl;
    }

    return 0;
}