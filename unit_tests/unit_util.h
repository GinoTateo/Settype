/**
 * Created by Varick Erickson on 3/31/2021.
 *
 * You should not remove or change any of the tests in this file.
 * These are the same tests that will be used to grade your assignment.
 *
 * Provides utility functions for the tests. DO NOT MODIFY!
 */

#ifndef UNIT_UTIL_H
#define UNIT_UTIL_H

#include <iostream>
#include <fstream>
#include <vector>


// Read words from a file.  Ignores extra white space.
template<class T>
vector<string> read_values(string filename) {
    ifstream valFile;
    valFile.open(filename);
    if (dictFile.fail()) {
        INFO(filename << " did not open.");
        INFO("Did you set $PROJECT_DIR$?");
        INFO("Did you move the file?");
        FAIL();
    }

    vector<T> elems;
    T elem;
    while(dictFile >> elem) {
        elems.push_back(elem);
    }

    return elems;
}

#endif
