#define CATCH_CONFIG_MAIN
#include <iostream>
#include <istream>
#include <set>
#include "catch.hpp"
#include "../SetType.h"

TEST_CASE("SetType Tests") {

    SECTION("Add and Contains Tests - 5pts") {
        SetType<int> testSet;

        //REQUIRE(!testSet.Contains(100));
        if (testSet.Contains(100)) {
            INFO("testSet found 100 in the test.");
            INFO("testSet is supposed to be empty.");
            FAIL();
        }

        // Adds 0, 2, 4, 6, ... , 100
        for (int i = 0; i < 100; i+=2) {
            testSet.Add(i);
            // REQUIRE(testSet.Contains(i));
            if (!testSet.Contains(i)) {
                INFO("testSet did not contain " << i);
                INFO("after adding " << i << " to the set");
                FAIL();
            }
        }

        // Checks 1, 3, 5, ... , 99
        for (int i = 1; i < 100; i+=2) {
            //REQUIRE(!testSet.Contains(i));
            if (testSet.Contains(i)) {
                INFO("testSet contained " << i);
                INFO("testSet should NOT contain " << i);
                FAIL();
            }
        }
    }

    SECTION("Assignment/MakeEmpty Tests - 5pts") {
        SetType<int> setA, setB;

        // Adds 0, 2, 4, 6, ... , 100
        for (int i = 0; i < 100; i+=2) {
            setA.Add(i);
            // REQUIRE(setA.Contains(i));
            if (!setA.Contains(i)) {
                INFO("setA did not contain " << i);
                INFO("after adding " << i << " to the set");
                FAIL();
            }
        }

        setB = setA;

        if (setB.Size() != setA.Size()) {
            INFO("setB should be same size as setA");
            INFO("after running setB = setA");
            INFO("Check your operator=");
            INFO("setA.Size(): " << setA.Size());
            INFO("setB.Size(): " << setB.Size());
            FAIL();
        }

        // setB should have all the elements in setA
        for (int i = 0; i < 100; i+=2) {
            // REQUIRE(setB.Contains(i));
            if (!setB.Contains(i)) {
                INFO("setB did not contain " << i);
                INFO("setB should have " << i << " after setting setB = setA");
                INFO("Check your operator=");
                FAIL();
            }
        }

        setA.MakeEmpty();
        //REQUIRE(setA.Size() == 0);
        if (setA.Size() != 0) {
            INFO("setA.MakeEmpty() did not make set empty.");
            INFO("setA.Size(): " << setA.Size());
            FAIL();
        }

        // setB should still have the same elements
        for (int i = 0; i < 100; i+=2) {
            //REQUIRE(setB.Contains(i));
            if (!setB.Contains(i)) {
                INFO("setB did not contain " << i);
                INFO("Check your operator=");
                INFO("You may have a shallow copy");
                FAIL();
            }
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
            //REQUIRE(testSet.Contains(i));
            if (!testSet.Contains(i)) {
                INFO("testSet should contain " << i);
                FAIL();
            }
        }

        // Check to make sure odd numbers are not there
        for (int i = 1; i < 100; i+=2) {
            //REQUIRE(!testSet.Contains(i));
            if (testSet.Contains(i)) {
                INFO("testSet should NOT contain " << i);
                FAIL();
            }
        }
    }

    SECTION("Overload Add/Remove Tests - 5pts") {
        SetType<int> testSet;

        // Add all numbers 0 - 99
        for (int i = 0; i < 100; i++) {
            testSet = testSet+i;
        }

        // Remove all odd numbers
        for (int i = 1; i < 100; i += 2) {
            testSet = testSet-i;
        }

        // Check to make sure even numbers are there
        for (int i = 0; i < 100; i+=2) {
            //REQUIRE(testSet.Contains(i));
            if (!testSet.Contains(i)) {
                INFO("testSet should contain " << i);
                FAIL();
            }
        }

        // Check to make sure odd numbers are not there
        for (int i = 1; i < 100; i+=2) {
            //REQUIRE(!testSet.Contains(i));
            if (testSet.Contains(i)) {
                INFO("testSet should NOT contain " << i);
                FAIL();
            }
        }

        if(testSet.Size() != 50) {
            INFO("testSet should contain 50 elements");
            INFO("testSet.Size() is " << testSet.Size());
            FAIL();
        }
    }

    SECTION("Union Tests - 5pts") {
        SetType<int> setA;
        SetType<int> setB;
        SetType<int> unionAB;

        set<int> stlSetA;
        set<int> stlSetB;

        // Even numbers
        for (int i = 0; i < 100; i+=2) {
            setA.Add(i);
            stlSetA.insert(i);
        }

        // Odd numbers
        for (int i = 1; i < 100; i += 2) {
            setB.Add(i);
            stlSetB.insert(i);
        }

        unionAB = setA + setB;

        // Make sure setA did not change in size
        if (setA.Size() != 50) {
            INFO("setA size changed after union operation");
            INFO("..setA.Size() is " << setA.Size());
            INFO("Expected size is 50");
            FAIL();
        }

        // Make sure setB did not change in size
        if (setB.Size() != 50) {
            INFO("setA size changed after union operation");
            INFO("..setB.Size() is " << setB.Size());
            INFO("Expected size is 50");
            FAIL();
        }

        // Make sure setA did not change
        for (int i = 0; i < 100; i+=2) {
            if (!setA.Contains(i)) {
                INFO("setA did not contain " << i);
                INFO("Your operator+ is changing setA");
                INFO("unionAB = setA + setB;");
                FAIL();
            }
        }

        // Make sure setB did not change in size
        for (int i = 1; i < 100; i += 2) {
            if (!setB.Contains(i)) {
                INFO("setB did not contain " << i);
                INFO("Your operator+ is changing setB");
                INFO("unionAB = setA + setB;");
                FAIL();
            }
        }

        // Check to make sure even numbers are there
        for (int i = 0; i < 100; i++) {
            //REQUIRE(unionAB.Contains(i));
            if (!unionAB.Contains(i)) {
                INFO("expected unionAB set to contain " << i);
                FAIL();
            }
        }

        // REQUIRE(unionAB.Size() == 100);
        if (unionAB.Size() != 100) {
            INFO("...unionAB size is " << unionAB.Size());
            INFO("..Expected size is 100");
            FAIL();
        }
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

        //   setA = {25, ... , 99}
        //   setB = { 0, ... , 74}
        // diffBA = { 0, ... , 24}
        diffBA = setB - setA;

        // Make sure setA did not change in size
        if (setA.Size() != 75) {
            INFO("setA size changed after difference operation");
            INFO("..setA.Size() is " << setA.Size());
            INFO("Expected size is 75");
            FAIL();
        }

        // Make sure setB did not change in size
        if (setB.Size() != 75) {
            INFO("setB size changed after difference operation");
            INFO("..setB.Size() is " << setB.Size());
            INFO("Expected size is 75");
            FAIL();
        }

        // Make sure setA did not change
        for (int i = 25; i < 100; i++) {
            if (!setA.Contains(i)) {
                INFO("setA did not contain " << i);
                INFO("operator- is changing setA");
                INFO("diffAB = setA - setB;");
                FAIL();
            }
        }

        // Make sure setB did not change
        for (int i = 0; i < 75; i++) {
            if (!setB.Contains(i)) {
                INFO("setB did not contain " << i);
                INFO("operator- is changing setB");
                INFO("diffAB = setA - setB;");
                FAIL();
            }
        }


        for (int i = 75; i <= 99; i++) {
            // REQUIRE(diffAB.Contains(i));
            if (!diffAB.Contains(i)) {
                INFO("expected diffAB set to contain " << i);
                FAIL();
            }
        }

        for (int i = 0; i <= 24; i++) {
            // REQUIRE(diffBA.Contains(i));
            if (!diffBA.Contains(i)) {
                INFO("expected diffBA set to contain " << i);
                FAIL();
            }
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

        // Make sure setA did not change in size
        if (setA.Size() != 75) {
            INFO("setA size changed after intersection operation");
            INFO("..setA.Size() is " << setA.Size());
            INFO("Expected size is 75");
            FAIL();
        }

        // Make sure setB did not change in size
        if (setB.Size() != 75) {
            INFO("setB size changed after intersection operation");
            INFO("..setB.Size() is " << setB.Size());
            INFO("Expected size is 75");
            FAIL();
        }

        // Make sure setA did not change
        for (int i = 25; i < 100; i++) {
            if (!setA.Contains(i)) {
                INFO("setA did not contain " << i);
                INFO("operator* is changing setA");
                INFO("intersectionAB = setA*setB;");
                FAIL();
            }
        }

        // Make sure setB did not change
        for (int i = 0; i < 75; i++) {
            if (!setB.Contains(i)) {
                INFO("setB did not contain " << i);
                INFO("operator* is changing setB");
                INFO("intersectionAB = setA*setB;");
                FAIL();
            }
        }

        for (int i = 25; i <= 74; i++) {
            // REQUIRE(intersectionAB.Contains(i));
            if (!intersectionAB.Contains(i)) {
                INFO("intersectionAB is missing " << i);
                FAIL();
            }
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
            // REQUIRE(testSet.LoadFactor() == load);
            if (testSet.LoadFactor() != load) {
                INFO("Incorrect load factor");
                INFO("Your Load Factor: " << testSet.LoadFactor());
                INFO("........Expected: " << load);
                FAIL();
            }
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
            //REQUIRE(stlSet.find(testSet.GetNextItem()) != stlSet.end());
            int item;
            try {
                item = testSet.GetNextItem();
            }
            catch (...) {
                INFO("testSet.GetNextItem() threw an error");
                INFO("on iteration" << i);
                FAIL();
            }

            if (stlSet.find(item) == stlSet.end()) {
                INFO("Did not find " << item);
                INFO("on iteration" << i);
                INFO("Your iterator may not be returning values correctly");
                FAIL();
            }
        }

        REQUIRE_THROWS(testSet.GetNextItem(), IteratorOutOfBounds());
    }
}