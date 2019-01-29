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
    std::set< double> uniqueSideLen;
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

//computes all length and slope data for sides and counts unique lengths.
void measureSides(std::vector<Quadrilateral>& quadrilaterals){
    for(Quadrilateral& quadrilateral: quadrilaterals){
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
}

//reads in input and maps it to a quadrilateral
Quadrilateral readInputAsQuad(std::fstream& inputStream){
    Quadrilateral quadrilateral;
    inputStream >> quadrilateral.bRight.x;
    inputStream >> quadrilateral.bRight.y;
    inputStream >> quadrilateral.tRight.x;
    inputStream >> quadrilateral.tRight.y;
    inputStream >> quadrilateral.tLeft.x;
    inputStream >> quadrilateral.tLeft.y;
    return quadrilateral;
}

//Expects quadrilateral to have all side values
void getInnerAngles(std::vector<Quadrilateral>& quadrilaterals){
    //check to see if we have all sides
    for(Quadrilateral& quadrilateral : quadrilaterals){
//        if(!hasAllSides(quadrilateral)){
//            std::cout << "Error: need all sides to get angles" << std::endl;
//            throw;
//        };
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
    
}

void measureQuadrilaterals(std::vector<Quadrilateral>& quadrilaterals){
    //measure sides
    measureSides(quadrilaterals);
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
void classifyQuadrilaterals(std::vector<Quadrilateral>& quadrilaterals){
    for(Quadrilateral& quadrilateral : quadrilaterals){
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
}

void printToFile(std::string filename, const std::vector<Quadrilateral>& quadrilaterals){
    std::ofstream filestream;
    filestream.open(filename);
    for(int i = 0; i < quadrilaterals.size(); i++){
//        filestream << "***********************************" << std::endl;
        filestream << quadrilaterals[i].type << std::endl;
    }
    filestream.close();
}

int main(int argc, const char * argv[]) {
    std::fstream file;
    
    file.open(argv[1]);
    std::vector<Quadrilateral> quadrilaterals;
    //read in inputs
    while(file.good()){
       Quadrilateral quadrilateral = readInputAsQuad(file);
        quadrilaterals.push_back(quadrilateral);
    }
    measureQuadrilaterals(quadrilaterals);
    classifyQuadrilaterals(quadrilaterals);
    printToFile(argv[2], quadrilaterals);
    return 0;
}
