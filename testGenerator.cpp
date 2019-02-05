//
//  main.cpp
//  testBuilder
//
//  Created by Jeremy Rodgers on 2/2/19.
//  Copyright © 2019 Jeremy Rodgers. All rights reserved.
//


#include "shapes.hpp"
#include <sys/time.h>
//#include "tests.hpp"
using namespace std;



//TODO: build each output randomly using it's defined parameters.

//parallelogram
    //oposite sides are equal
    //the length of the oposite side ==
        //get length, compare
    //adjacent angles are sublementary

void makeTests(string coordinatesFileName, string expectedOutFileName){
    vector<string> possibleOutShapes;
    std::ofstream expectedOutStream;
    expectedOutStream.open(expectedOutFileName);
    std::ofstream coordinatesOutStream;
    coordinatesOutStream.open(coordinatesFileName);
    pickRandomOutput(possibleOutShapes, expectedOutStream, coordinatesOutStream);
    expectedOutStream.close();
}

//void unitTestSuite(){
//    //testRandomTF();
//    testRhombus();
//    testParallelagram();
//    testTrapizoid();
//    //testGetPoint();
//    testKite();
//    testGetNextYCoordinate();
//    testGenerateError3();
//    testGenerateError4();
//}

int main(int argc, const char * argv[]) {
    struct timeval time;
    gettimeofday(&time,NULL);
    srand((time.tv_sec * 1000) + (time.tv_usec / 1000));
    makeTests(argv[1] , argv[2]);
    //unitTestSuite();
    return 0;
}


