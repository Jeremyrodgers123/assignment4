//
//  shapes.hpp
//  testBuilder
//
//  Created by Jeremy Rodgers on 2/2/19.
//  Copyright © 2019 Jeremy Rodgers. All rights reserved.
//

#ifndef shapes_hpp
#define shapes_hpp

#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <set>
#include <map>
#include <sstream>
using namespace std;

struct Point{
    double x = 0;
    double y = 0;
    double innerAngle = 0; //angle inside shape at the location of the point
};

struct Side{
    double len;
    double slope;
    int rise;
    int run;
};

struct Quadrilateral {
    std::string type;
    Point bLeft;//bottom left
    Point bRight;
    Point tRight;
    Point tLeft;
    Side sideA;// bleft to bright
    Side sideB;// bright to tright
    Side sideC;// tright to tLeft
    Side sideD;// tLeft to bLeft
    Side dividingLine;
    int parallelCount = 0;
    int rightAngleCount = 0;
    std::set<double> uniqueSideLen;
   
};

bool areEqual(double a, double b);

double calcDistance(const Point& a, const Point& b);

void countUniqueSides(Quadrilateral& quadrilateral);

double calcSlope(const Point& a, const Point& b);

int randomNum(const int& max);

void ensureNotEquals(const int& max, const int& a, int& b);

void initErrorTypes(vector<string>& shapeTypes);

void setPoint(Point& point, const double& x, const double& y, const double& angle);

void setPoint(Point& point, const double& x, const double& y);

void setSide(Side& side, const double& len, const double& slope);

Quadrilateral buildSquare();

Quadrilateral buildRectangle();

Quadrilateral buildParallelagram();

void outputCoordinates(Quadrilateral quadrilateral, std::ofstream& coordinatesOutStream);

Quadrilateral createShape(const int& shapeNum );

void pickRandomOutput(vector<string>& possibleOutShapes, ofstream& expectedOutStream, std::ofstream& coordinatesOutStream);

int randomNum(const int& min, const int& max);

double findNewY(double distance, int xVal, const Point& b);

Point getNewPoint(double outsideAngle, double radius);

Quadrilateral changeRiseAndRun(Quadrilateral& quadrilateral);

bool randomTrueFalse();

void printPoints(Quadrilateral quadrilateral);

void calcAllDistance(Quadrilateral& quadrilateral);

Quadrilateral buildTrapezoid();

vector<Point> moveAlongTrapazoidLine(const Point& min, const Point& max, const int& gcd, Quadrilateral& quadrilateral);

Quadrilateral buildKite();

Point getMidpoint(Point& point1, Point& point2);

Side findRiseAndRun(Point& point1, Point& point2);

double nextYCoordinateOnLine(Point& point1, Point& point2, int anyX);
string generateError1();
string generateError2();
string generateError3();
string generateError4();

bool hasSameYVals(double y1, double y2);
bool hasCoincidingPoints (std::vector<double>& points);
vector<double> convertToDoubleVector(Quadrilateral quadrilateral);
double isColinear(Point point0, Point point1, Point point2);

#endif /* shapes_hpp */
