//
//  main.cpp
//  assignment03
//
//  Created by Jeremy Rodgers on 1/17/19.
//  Copyright © 2019 Jeremy Rodgers. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <set>
#include <sstream>
#include <map>
struct Point{
    double x = 0;
    double y = 0;
    double innerAngle = 0; //angle inside shape at the location of the point
};

struct Side{
    double len;
    double slope;
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

//checks if two double values are equal within a tolerance.
bool areEqual(double a, double b){
    return fabs(a - b) < 0.0000001;
}
// uses distance formula to calculate the distance between two points
double calcDistance(const Point& a, const Point& b){
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}
/**
 calculates an angle given 3 sides of a triangle.
 oppositeSideOfAngle is the length of the side oposite the angle you are trying to calculate
 sideX and SideY are side lengths other than the side opposite the angle you are trying to calculate
**/
double calcInnerAngle(const double& sideX, const double& sideY, const double& oppositeSideOfAngle){
    double x2 = pow(sideX, 2.0);
    double y2 = pow(sideY, 2.0);
    double opp2 = pow(oppositeSideOfAngle, 2);
    double radians = acos((x2 + y2 - opp2) / (2 * sideX * sideY));
    double ans = radians * (180 / M_PI);
    return ans;
}

double isColinear(Point point0, Point point1, Point point2){
    // equation for area of  a triangle boorrowed from http://xoax.net/cpp/ref/cpp_examples/incl/area_three_point_triangle/
    
    double area = ((point1.x - point0.x)*(point2.y - point0.y) - (point2.x - point0.x)*(point1.y - point0.y))/2.0;
    return (areEqual(area, 0)) ? true : false;
}

bool isBetweenPoints(Point A, Point B, Point C, Point D){
    
    return false;
}

Point findMax(std::vector<Point> list){
    double maxX = INT_MIN;
    double maxY = INT_MIN;
    for(int i = 0; i < list.size(); i++){
        if(list[i].x > maxX){
            maxX = list[i].x;
        }
        if(list[i].y > maxY){
            maxY = list[i].y;
        }
    }
    Point max;
    max.x = maxX;
    max.y = maxY;
    return max;
}

Point findMin(std::vector<Point> list){
    double minX = INT_MAX;
    double minY = INT_MAX;
    for(int i = 0; i < list.size(); i++){
        if(list[i].x < minX){
            minX = list[i].x;
        }
        if(list[i].y < minY){
            minY = list[i].y;
        }
    }
    Point min;
    min.x = minX;
    min.y = minY;
    return min;
}

bool lineIntersects(Point& A, Point& B, Point& C, Point& D)
{
    // Line AB represented as a1x + b1y = c1
    double a1 = B.y - A.y;
    double b1 = A.x - B.x;
    double c1 = (a1 * A.x) + (b1 * A.y);
    
    // Line CD represented as a2x + b2y = c2
    double a2 = D.y - C.y;
    double b2 = C.x - D.x;
    double c2 = a2*(C.x)+ b2*(C.y);
    
    double determinant = a1*b2 - a2*b1;
    
    // The lines are parallel, return false
    if (determinant == 0)
    {
        return false;
    }
    else
    {
        double x = ( b2 * c1 - b1 * c2 )/determinant;
        double y = (a1 * c2 - a2 * c1 )/determinant;
        std::vector<Point> points = std::vector<Point> { A ,B ,C, D};
        Point max = findMax(points);
        Point min = findMin(points);
        Point intersection;
        intersection.x = x;
        intersection.y = y;
        
        if(intersection.x < max.x && intersection.x > min.x && intersection.y < max.y && intersection.y > min.y){
            return true;
        }
        return false;
    }
}

/**
    calculates the slope of a line given two points
    if a value is divided by 0 the equation returns infinity
 **/
double calcSlope(const Point& a, const Point& b){
    double num = b.y - a.y;
    double den = b.x - a.x;
//    double ans = num
    if(den == 0){
        return INFINITY;
    }
    double ret =  (num)/(den); // equation to get the slope of a line;
    return ret;
}
// returns true is two sides are parallel. Otherwise false
bool areParallel(const Side& sideX, const Side& sideY){
    if(sideX.slope == INFINITY && sideY.slope == INFINITY){
        return true;
    }
    if(!areEqual(sideX.slope, sideY.slope)){
        return false;
    }
    return true;
}

//counts the number of parallel sides on a quadrilateral
void countParallels(Quadrilateral& quadrilateral){
    if(areParallel(quadrilateral.sideA, quadrilateral.sideC)){
        quadrilateral.parallelCount++;
    };
    if(areParallel(quadrilateral.sideB, quadrilateral.sideD)){
        quadrilateral.parallelCount++;
    };
}
//counts the number of right angels in a quadrilateral
void countRightAngles(Quadrilateral& quadrilateral){
    if(areEqual(quadrilateral.bLeft.innerAngle, 90)){
        quadrilateral.rightAngleCount ++;
    }
    if(areEqual(quadrilateral.bRight.innerAngle, 90)){
        quadrilateral.rightAngleCount ++;
    }
    if(areEqual(quadrilateral.tRight.innerAngle, 90)){
        quadrilateral.rightAngleCount ++;
    }
    if(areEqual(quadrilateral.tLeft.innerAngle, 90)){
        quadrilateral.rightAngleCount ++;
    }
}
//counts the number of unique sides in a quadrilateral
void countUniqueSides(Quadrilateral& quadrilateral){
    quadrilateral.uniqueSideLen.insert(quadrilateral.sideA.len);
    quadrilateral.uniqueSideLen.insert(quadrilateral.sideB.len);
    quadrilateral.uniqueSideLen.insert(quadrilateral.sideC.len);
    quadrilateral.uniqueSideLen.insert(quadrilateral.sideD.len);
}


//checks that a quadrilateral has all of its sides
bool hasAllSides(const Quadrilateral& quadrilateral){
    if(quadrilateral.sideA.len <= 0 ||
       quadrilateral.sideB.len <= 0 ||
       quadrilateral.sideC.len <= 0 ||
       quadrilateral.sideD.len <= 0 ||
       quadrilateral.dividingLine.len <= 0){
        return false;
    }
    return true;
}


void measureSides(Quadrilateral& quadrilateral){
    quadrilateral.sideA.len = calcDistance(quadrilateral.bLeft, quadrilateral.bRight);
    quadrilateral.sideB.len = calcDistance(quadrilateral.bRight, quadrilateral.tRight);
    quadrilateral.sideC.len = calcDistance(quadrilateral.tRight, quadrilateral.tLeft);
    quadrilateral.sideD.len = calcDistance(quadrilateral.tLeft, quadrilateral.bLeft);
    quadrilateral.dividingLine.len = calcDistance(quadrilateral.tLeft, quadrilateral.bRight);
    //printQuadSides(quadrilateral);
    quadrilateral.sideA.slope = calcSlope(quadrilateral.bLeft, quadrilateral.bRight);
    quadrilateral.sideB.slope = calcSlope(quadrilateral.bRight, quadrilateral.tRight);
    quadrilateral.sideC.slope = calcSlope(quadrilateral.tRight, quadrilateral.tLeft);
    quadrilateral.sideD.slope = calcSlope(quadrilateral.tLeft, quadrilateral.bLeft);
    quadrilateral.dividingLine.slope = calcSlope(quadrilateral.tLeft, quadrilateral.bRight);
    countUniqueSides(quadrilateral);
}

//computes all length and slope data for sides and counts unique lengths.
void measureAllSides(std::vector<Quadrilateral>& quadrilaterals){
    for(Quadrilateral& quadrilateral: quadrilaterals){
        measureSides(quadrilateral);
    }
}
void hasVaidInputStream(std::istream& inputStream, std::ofstream& outputStream){
    if(inputStream.fail()){
        outputStream << "error 1" << std::endl;
        outputStream.close();
        exit(1);
    }
}

bool inputRangeIsValid(const double& coordinate){
    if(coordinate < 0 || coordinate > 100){
        return false;
    }
    return true;
}

void printError(int errorNum, std::ofstream& outputStream ){
    outputStream << "error " << errorNum << std::endl;
    std::cout << "error " << errorNum << std::endl;
    outputStream.close();
    exit(1);
}
bool hasSameYVals(double y1, double y2){
    return y1 == y2;
}

bool hasCoincidingPoints (std::vector<double>& points){
    for(int x1 = 0; x1 < points.size(); x1 += 2){
        for(int x2 = x1+2; x2 < points.size(); x2 += 2){
            if( points[x1] == points[x2] && hasSameYVals(points[ x1 +1 ], points[ x2 + 1 ] ) ){
                return true;
            }
        }
        
    }
    return false;
}
//reads in input and maps it to a quadrilateral
Quadrilateral readInputAsQuad(std::fstream& inputStream, std::ofstream& outputStream){
    std::string line;
    std::getline(inputStream, line);
   std::istringstream stream (line);
    std::vector<double> points;
    double val;
    
    while(stream.good()){
        hasVaidInputStream(inputStream, outputStream);
        stream >> val;
        if(!inputRangeIsValid(val)){
            printError(1, outputStream);
        }
        points.push_back(val);
    }
    
    if (points.size() != 6){
        printError(1, outputStream);
    }
    
    if(hasCoincidingPoints(points)){
        printError(2, outputStream);
    }
    Point point0, point1, point2, point3;
    point0.x = 0;
    point0.y = 0;
    point1.x = points[0];
    point1.y = points[1];
    point2.x = points[2];
    point2.y = points[3];
    point3.x = points[4];
    point3.y = points[5];
    if(isColinear(point0, point1, point3) || isColinear(point1, point2, point3)){
        printError(4, outputStream);
    };
    
    if(lineIntersects(point0, point1, point2, point3 ) || lineIntersects(point1, point2, point3, point0)){
        printError(4, outputStream);
    };
    
    Quadrilateral quadrilateral;
    quadrilateral.bRight = point1;
    quadrilateral.tRight = point2;
    quadrilateral.tLeft  = point3;
    return quadrilateral;
}
//Expects quadrilateral to have all side values
void getInnerAngles(Quadrilateral& quadrilateral){
    //Splits the quadrilateral into 2 triangles so to be able to find the angles.
    //triangle 1
    quadrilateral.bLeft.innerAngle = calcInnerAngle(quadrilateral.sideA.len, quadrilateral.sideD.len, quadrilateral.dividingLine.len);
    double bRightAnglePart1= calcInnerAngle(quadrilateral.sideA.len, quadrilateral.dividingLine.len, quadrilateral.sideD.len);
    double tLeftAnglePart1= calcInnerAngle(quadrilateral.sideD.len, quadrilateral.dividingLine.len, quadrilateral.sideA.len);
    //triangel 2
    quadrilateral.tRight.innerAngle = calcInnerAngle(quadrilateral.sideC.len, quadrilateral.sideB.len, quadrilateral.dividingLine.len);
    double bRightAnglePart2= calcInnerAngle(quadrilateral.sideB.len, quadrilateral.dividingLine.len, quadrilateral.sideC.len);
    double tLeftAnglePart2= calcInnerAngle(quadrilateral.sideC.len, quadrilateral.dividingLine.len, quadrilateral.sideB.len);
    
    quadrilateral.bRight.innerAngle = bRightAnglePart1 + bRightAnglePart2;
    quadrilateral.tLeft.innerAngle = tLeftAnglePart1 + tLeftAnglePart2;
    countRightAngles(quadrilateral);
}

void getInnerAngles(std::vector<Quadrilateral>& quadrilaterals){
    //check to see if we have all sides
    for(Quadrilateral& quadrilateral : quadrilaterals){
        getInnerAngles(quadrilateral);
    }
}

void measureQuadrilaterals(std::vector<Quadrilateral>& quadrilaterals){
    //measure sides
    measureAllSides(quadrilaterals);
     //get angles
    getInnerAngles(quadrilaterals);
}

void classifyAsSquareOrRectangle(Quadrilateral& quadrilateral){
    if(quadrilateral.uniqueSideLen.size() == 1){
        quadrilateral.type = "square";
        std::cout << "square" << std::endl;
    }else if(quadrilateral.uniqueSideLen.size() == 2) {
        quadrilateral.type = "rectangle";
        std::cout << "rectangle" << std::endl;
    }
}

/**
 determine quadrilateral classification as a square, rectangle, rhombus,
 parallelagram, trapezoid, kite or qauadrilateral.
 **/
void classifyQuadrilateral(Quadrilateral& quadrilateral){
    countParallels(quadrilateral);
    if(quadrilateral.parallelCount == 2){
        //SQUARE AND RECTANGLE
        if(quadrilateral.rightAngleCount == 4){
            classifyAsSquareOrRectangle(quadrilateral);
        }
        //RHOMBUS
        if(quadrilateral.rightAngleCount == 0){
            if(quadrilateral.uniqueSideLen.size() == 1){
                quadrilateral.type = "rhombus";
                std::cout << "rhombus" << std::endl;
            }else{
                quadrilateral.type = "parallelagram";
                std::cout << "parallelagram" << std::endl;
            }
        }
        //Trapizoid
    }else if(quadrilateral.parallelCount == 1){
        quadrilateral.type = "trapezoid";
        std::cout << "trapezoid" << std::endl;
    }else{
        //check if kite
        if(quadrilateral.uniqueSideLen.size() == 2){
            quadrilateral.type = "kite";
            std::cout << "kite" << std::endl;
        }else{
            quadrilateral.type = "quadrilateral";
            std::cout << "quadrilateral" << std::endl;
        }
    }
}

void classifyQuadrilaterals(std::vector<Quadrilateral>& quadrilaterals){
    for(Quadrilateral& quadrilateral : quadrilaterals){
        classifyQuadrilateral(quadrilateral);
    }
}

void printToFile(std::ofstream& outputStream, const std::vector<Quadrilateral>& quadrilaterals){
    for(int i = 0; i < quadrilaterals.size(); i++){
        //        filestream << "***********************************" << std::endl;
        outputStream << quadrilaterals[i].type << std::endl;
    }
    outputStream.close();
}

int main(int argc, const char * argv[]) {
    std::fstream inputStream;
    inputStream.open(argv[1]);
    
    std::ofstream outputStream;
    outputStream.open(argv[2]);
    
    std::vector<Quadrilateral> quadrilaterals;
    //read in inputs
    hasVaidInputStream(inputStream, outputStream);
    while(inputStream.good()){
        Quadrilateral quadrilateral = readInputAsQuad(inputStream, outputStream);
        measureSides(quadrilateral);
        getInnerAngles(quadrilateral);
        classifyQuadrilateral(quadrilateral);
        outputStream << quadrilateral.type << std::endl;
        //TODO: classify the quadrilateral;
        //TODO: print the quadrilateral;
        quadrilaterals.push_back(quadrilateral);
    }
    outputStream.close();
    //TODO: change to measure a single quadrilateral
    //measureQuadrilaterals(quadrilaterals);
    
    //classifyQuadrilaterals(quadrilaterals);
    //printToFile(outputStream, quadrilaterals);
    return 0;
}
