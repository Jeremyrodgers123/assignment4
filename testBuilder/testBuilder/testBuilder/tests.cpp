//
//  tests.cpp
//  testBuilder
//
//  Created by Jeremy Rodgers on 2/2/19.
//  Copyright © 2019 Jeremy Rodgers. All rights reserved.
//

#include "tests.hpp"

void testRhombus(){
    Quadrilateral quadrilateral = createShape(2);
    std::ofstream coordinatesOutStream;
    coordinatesOutStream.open("test.txt");
    outputCoordinates(quadrilateral, coordinatesOutStream);
}

void testParallelagram(){
    Quadrilateral shape = createShape(1);
    std::ofstream coordinatesOutStream;
    coordinatesOutStream.open("test.txt");
    outputCoordinates(shape, coordinatesOutStream);
}

void testTrapizoid(){
    Quadrilateral shape = createShape(5);
    std::ofstream coordinatesOutStream;
    coordinatesOutStream.open("test.txt");
    outputCoordinates(shape, coordinatesOutStream);
}

void testKite(){
    Quadrilateral shape = createShape(6);
    std::ofstream coordinatesOutStream;
    coordinatesOutStream.open("test.txt");
    outputCoordinates(shape, coordinatesOutStream);
}
//TODO: DELETE
void testGetNextYCoordinate(){
    Quadrilateral kite = buildKite();
    //get midpoint of B and D
    //Point midpoint = getMidpoint(kite.tLeft, kite.bRight);
    printPoints(kite);
}

void testGetPoint(){
    getNewPoint(50, 12);
}

void testRandomTF(){
    for( int i = 0; i < 100; i++){
        int val = randomTrueFalse();
        cout << val << endl;
    }
}

void testGenerateError3(){
    generateError3();
}

void testGenerateError4(){
    generateError4();
}
