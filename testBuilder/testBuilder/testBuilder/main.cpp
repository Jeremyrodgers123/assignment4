//
//  main.cpp
//  testBuilder
//
//  Created by Jeremy Rodgers on 2/2/19.
//  Copyright © 2019 Jeremy Rodgers. All rights reserved.
//


#include "shapes.hpp"
#include "tests.hpp"
using namespace std;



//TODO: build each output randomly using it's defined parameters.

//parallelogram
    //oposite sides are equal
    //the length of the oposite side ==
        //get length, compare
    //adjacent angles are sublementary

void makeTests(string fileName){
    string coordinatesFileName = fileName;
    vector<string> possibleOutShapes;
    string expectedOutFileName =  string("expected") + coordinatesFileName;
    std::ofstream expectedOutStream;
    expectedOutStream.open(expectedOutFileName);
    std::ofstream coordinatesOutStream;
    coordinatesOutStream.open(coordinatesFileName);
    pickRandomOutput(possibleOutShapes, expectedOutStream, coordinatesOutStream);
    expectedOutStream.close();
}

void unitTestSuite(){
    //testRandomTF();
    testRhombus();
    testParallelagram();
    testTrapizoid();
    //testGetPoint();
  
}

int main(int argc, const char * argv[]) {
    srand(time(0));
    //makeTests(argv[1]);
    unitTestSuite();

    return 0;
}


