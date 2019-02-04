//
//  shapes.cpp
//  testBuilder
//
//  Created by Jeremy Rodgers on 2/2/19.
//  Copyright © 2019 Jeremy Rodgers. All rights reserved.
//

#include "shapes.hpp"

vector<string> shapeTypes {"quadrilateral", "parallelagram", "rhombus", "square", "rectangle", "trapezoid", "kite"};

bool areEqual(double a, double b){
    if(a == INFINITY && b == INFINITY){
        return true;
    }
    return fabs(a - b) < 0.0000001;
}

// uses distance formula to calculate the distance between two points
double calcDistance(const Point& a, const Point& b){
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

double toRadians(double degrees){
    return ( degrees * M_PI ) / 180;
}
Point getNewPoint(double outsideAngle, double radius){
    double x = radius * sin(toRadians(outsideAngle));
    double y = radius * cos (toRadians(outsideAngle));
    //double ans = radians * (180 / M_PI);
    Point point;
    point.x = x;
    point.y = y;
    return point;
}

Point getMidpoint(Point& point1, Point& point2){
   double x = (point1.x + point2.x)/2;
   double y = (point1.y +point2.y)/2;
    Point midpoint;
    setPoint(midpoint, x, y);
    cout << "Midpoint " << "( " << x << ", "<< y << " )" << endl;
    return midpoint;
}

//counts the number of unique sides in a quadrilateral
void countUniqueSides(Quadrilateral& quadrilateral){
    quadrilateral.uniqueSideLen.insert(quadrilateral.sideA.len);
    quadrilateral.uniqueSideLen.insert(quadrilateral.sideB.len);
    quadrilateral.uniqueSideLen.insert(quadrilateral.sideC.len);
    quadrilateral.uniqueSideLen.insert(quadrilateral.sideD.len);
}
//https://www.geeksforgeeks.org/c-program-find-gcd-hcf-two-numbers/
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}


Side findRiseAndRun(Point& point1, Point& point2){
    Side riseNRun;
    double x = (point1.x + point2.x)/2;
    double y = (point1.y +point2.y)/2;
    riseNRun.rise = y;
    riseNRun.run = x;
    cout << "Rise and Run " << "(Rise: " << x << ", Run: "<< y << " )" << endl;
    return riseNRun;
}

double nextYCoordinateOnLine(Point& point1, Point& point2, int anyX){
    Side connectingLine = findRiseAndRun(point1, point2);
    double run = connectingLine.run;
    //y - point1.y = connectingLine.rise / connectingLine.run (anyX - point1.x);
    double val =  ((connectingLine.rise * anyX) - (connectingLine.rise * point1.x)
                + (point1.y * connectingLine.run));
    double nextY = fmod(val, run);
    return nextY;//(connectingLine.rise * anyX) % run;
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

int randomNum(const int& max){
    return rand() % (max + 1);
}

int randomNum(const int& min, const int& max){
    return min + (rand() % (max - min + 1));
}

bool randomTrueFalse(){
    int randVal =  rand() % 2;
    return randVal;
}

void ensureNotEquals(const int& max, const int& a, int& b){
    while(areEqual(a, b)){
        b = randomNum(max);
    }
}

void initErrorTypes(vector<string>& shapeTypes){
    shapeTypes.push_back( "error 1");
    shapeTypes.push_back( "error 2");
    shapeTypes.push_back( "error 3");
    shapeTypes.push_back( "error 4");
}

void setPoint(Point& point, const double& x, const double& y, const double& angle){
    point.x = x;
    point.y = y;
    point.innerAngle = angle;
}

void setPoint(Point& point, const double& x, const double& y){
    point.x = x;
    point.y = y;
}

void setSide(Side& side, const double& len, const double& slope){
    side.len = len;
    side.slope = slope;
}

void calcAllDistance(Quadrilateral& quadrilateral){
    quadrilateral.sideA.len = calcDistance(quadrilateral.bLeft, quadrilateral.bRight);
    quadrilateral.sideB.len = calcDistance(quadrilateral.bRight, quadrilateral.tRight);
    quadrilateral.sideC.len = calcDistance(quadrilateral.tRight, quadrilateral.tLeft);
    quadrilateral.sideD.len = calcDistance(quadrilateral.tLeft, quadrilateral.bLeft);
}

void calcAllSlopes(Quadrilateral& quadrilateral){
    quadrilateral.sideA.slope = calcSlope(quadrilateral.bLeft, quadrilateral.bRight);
    quadrilateral.sideB.slope = calcSlope(quadrilateral.bRight, quadrilateral.tRight);
    quadrilateral.sideC.slope = calcSlope(quadrilateral.tRight, quadrilateral.tLeft);
    quadrilateral.sideD.slope = calcSlope(quadrilateral.tLeft, quadrilateral.bLeft);
}

void printPoints(Quadrilateral quadrilateral){
    cout << "***************************" << endl;
    cout << "bLeft" << endl;
    cout << "\tX :" << quadrilateral.bLeft.x << endl;
    cout << "\tY :" << quadrilateral.bLeft.y << endl;
    
    cout << "bRight" << endl;
    cout << "\tX :" << quadrilateral.bRight.x << endl;
    cout << "\tY :" << quadrilateral.bRight.y << endl;
    
    cout << "tLeft" << endl;
    cout << "\tX :" << quadrilateral.tLeft.x << endl;
    cout << "\tY :" << quadrilateral.tLeft.y << endl;
    
    cout << "tRight" << endl;
    cout << "\tX :" << quadrilateral.tRight.x << endl;
    cout << "\tY :" << quadrilateral.tRight.y << endl;
    cout << "***************************" << endl;
}

Quadrilateral buildSquare(){
    Quadrilateral square;
    square.type = "square";
    int squareLength = randomNum(50);
    setPoint(square.bLeft, 0, 0, 90);
    setPoint(square.bRight, squareLength, 0, 90);
    setPoint(square.tRight, squareLength, squareLength, 90);
    setPoint(square.tLeft, 0, squareLength, 90);
    return square;
}

Quadrilateral buildRectangle(){
    Quadrilateral rectangle;
    rectangle.type = "rectangle";
    int squareWidth = randomNum(50);
    int squareHeight = randomNum(50);
    ensureNotEquals(50, squareWidth, squareHeight);
    setPoint(rectangle.bLeft, 0, 0, 90);
    setPoint(rectangle.bRight, squareWidth, 0, 90);
    setPoint(rectangle.tRight, squareWidth, squareHeight, 90);
    setPoint(rectangle.tLeft, 0, squareHeight, 90);
    return rectangle;
}

bool checkValidParamsCreated(const Point& point1, const Point& point2){
    int min = 0;
    int max = 50;
    if(point1.x > max || point1.x < min || point2.x > max || point2.x < min){
        return false;
    }
    if(point1.y > max || point1.y < min || point2.y > max || point2.y < min){
        return false;
    }
    return true;
}

Quadrilateral buildRhombus(){
    Quadrilateral rhombus;
    rhombus.type = "rhombus";
    bool isValid = false;
    while(!isValid){
        int rise = randomNum(50);
        int run = randomNum(50);
        rhombus.sideA.rise = rise;
        rhombus.sideA.run = run;
        rhombus.sideB.rise = rise;
        rhombus.sideB.run = run;
        rhombus.sideC.rise = rise;
        rhombus.sideC.run = run;
        rhombus.sideD.rise = rise;
        rhombus.sideD.run = run;
        setPoint(rhombus.bLeft, 0, 0);
        setPoint(rhombus.bRight, run, rise);
        setPoint(rhombus.tLeft, rise, run); // switch x and y
        setPoint(rhombus.tRight, rise + run, run + rise);
        bool bottomValid = checkValidParamsCreated(rhombus.bLeft, rhombus.bRight);
        bool topValid = checkValidParamsCreated(rhombus.tLeft, rhombus.tRight);
        if(bottomValid && topValid){
            isValid = true;
        }
    }
    
    double SideA = calcDistance(rhombus.bLeft, rhombus.bRight);
    double SideB = calcDistance(rhombus.bRight, rhombus.tRight);
    double SideC = calcDistance(rhombus.tRight, rhombus.tLeft);
    double SideD = calcDistance(rhombus.tLeft, rhombus.bLeft);
   // getNewPoint(30, length);
    
    assert(areEqual(SideA, SideB));
    assert(areEqual(SideB, SideC));
    assert(areEqual(SideC, SideD));
    //printPoints(rhombus);
    return rhombus;
}

void changeRiseAndRun(int& rise, int& run){
   
    bool shouldGrow = randomTrueFalse();
    int changeInRise = randomNum(10);
    int changeInRun = randomNum(10);
    
    if(shouldGrow){
        rise += changeInRise;
        run += changeInRun;
    }else{
        rise -= changeInRise;
        run -= changeInRun;
    }
    return;
}

Quadrilateral buildParallelagram(){
    Quadrilateral parallelagram;
    //parallelagram = buildRhombus();
    //save TL & BL OR BL & BR
    bool changeHorizontally = randomTrueFalse();
    int rise = -1;
    int run = -1;
    Point point1, point2;
    if(changeHorizontally){
        //change TR and BR
        bool isValid = false;
        while(!isValid){
            parallelagram = buildRhombus();
            rise = parallelagram.sideA.rise;
            run = parallelagram.sideA.run;
            changeRiseAndRun(rise, run);
            setPoint(point1, parallelagram.tLeft.x + run, parallelagram.tLeft.y + rise);
            setPoint(point2, parallelagram.bLeft.x + run, parallelagram.bLeft.y + rise);
            isValid = checkValidParamsCreated(point1, point2);
        }
        parallelagram.tRight = point1;
        parallelagram.bRight = point2;
        parallelagram.sideA.rise = rise;
        parallelagram.sideA.run = run;
        parallelagram.sideC.rise = rise;
        parallelagram.sideC.run = run;
        
    }else{
        //changing vertical points TL and TR
        bool isValid = false;
        while(!isValid){
            parallelagram = buildRhombus();
            rise = parallelagram.sideB.rise;
            run = parallelagram.sideB.run;
            changeRiseAndRun(rise, run);
            setPoint(point1, parallelagram.bLeft.x + run, parallelagram.bLeft.y + rise);
            setPoint(point2, parallelagram.bRight.x + run, parallelagram.bRight.y + rise);
            isValid = checkValidParamsCreated(point1, point2);
        }
        parallelagram.tLeft = point1;
        parallelagram.tRight = point2;
        parallelagram.sideB.rise = rise;
        parallelagram.sideB.run = run;
        parallelagram.sideD.rise = rise;
        parallelagram.sideD.run = run;
    }
     parallelagram.type = "parallelagram";
    calcAllDistance(parallelagram);
    calcAllSlopes(parallelagram);
    assert(areEqual(parallelagram.sideA.len, parallelagram.sideC.len));
    assert(areEqual(parallelagram.sideB.len, parallelagram.sideD.len));
    assert(areEqual(parallelagram.sideA.rise, parallelagram.sideC.rise));
    assert(areEqual(parallelagram.sideA.run, parallelagram.sideC.run));
    assert(areEqual(parallelagram.sideB.rise, parallelagram.sideD.rise));
    assert(areEqual(parallelagram.sideD.run, parallelagram.sideD.run));
    //double slopeA = (double)parallelagram.sideA.rise/parallelagram.sideA.run;
    //assert(areEqual(slopeA, parallelagram.sideA.slope));
    //printPoints(parallelagram);
    return parallelagram;
}

vector<Point> moveAlongTrapazoidLine(const Point& min, const Point& max, const int& gcd, Quadrilateral& quadrilateral){
    vector<Point> points;
    int x = quadrilateral.bRight.x;
    int y = quadrilateral.bRight.y;
    bool morePossiblePoints = true;
    while(morePossiblePoints){
        x += (quadrilateral.sideA.run / gcd);
        y += (quadrilateral.sideA.rise / gcd);
        if(x < max.x && y < max.y){
            Point point;
            setPoint(point, x, y);
            points.push_back(point);
        }else{
            morePossiblePoints = false;
        }
    }
    if(points.size() > 0){
        for( Point p : points){
            cout << "point: ("<< p.x <<" , " << p.y << " )" << endl;
            cout << "Rise: " << quadrilateral.sideA.rise << endl;
            cout << "Run: " << quadrilateral.sideA.run << endl;
            cout << "Greatest Common Denominator: " << gcd << endl;
        }
    }else{
        cout << "could find no points" << endl;
    }
    return points;
}

Quadrilateral buildTrapezoid(){
    bool isValid = false;
    int gCD = -1;
    Quadrilateral trapezoid;
    while(!isValid){
        trapezoid = buildParallelagram();
        //Take side A
        gCD = gcd(trapezoid.sideA.rise, trapezoid.sideA.run);

    
        Point min, max;
        setPoint(min, trapezoid.tRight.x, trapezoid.bRight.y);
        setPoint(max, 50, trapezoid.tRight.y);
        vector<Point> possibleBottomPoints, possibleTopPoints;
        possibleBottomPoints = moveAlongTrapazoidLine(min, max, gCD, trapezoid);
        if(possibleBottomPoints.size() > 0){
            isValid = true;
            int sizeBottom = (int) possibleBottomPoints.size() - 1;
            cout << endl;
            cout << "***possible valid response**" <<endl;
            printPoints(trapezoid);
            //TODO: assert no two points are the same
            trapezoid.bRight = possibleBottomPoints[randomNum(sizeBottom)];
            printPoints(trapezoid);
            calcAllSlopes(trapezoid);
            assert(areEqual(trapezoid.sideA.slope, trapezoid.sideC.slope) );
            
        }
        if(isValid){
            setPoint(min, 1, trapezoid.tLeft.y);
            setPoint(max, trapezoid.tRight.x, trapezoid.tRight.y);
            possibleTopPoints = moveAlongTrapazoidLine(min, max, gCD, trapezoid);
            int sizeTop = (int) possibleTopPoints.size() - 1;
            if(sizeTop > 0){
                trapezoid.bRight = possibleTopPoints[randomNum(sizeTop)];
            }
        }
        
    }
    
    //find all x values > than tRight.x < max using increments of run/gcd
    cout << "Rise: " << trapezoid.sideA.rise << endl;
    cout << "Run: " << trapezoid.sideA.run << endl;
    cout << "Greatest Common Denominator: " << gCD << endl;
    trapezoid.type = "trapezoid";
    calcAllSlopes(trapezoid);
    assert(areEqual(trapezoid.sideA.slope, trapezoid.sideC.slope));
    cout << "TRAPEZOID" << endl;
    printPoints(trapezoid);
    cout << "*************" << endl;
    return trapezoid;
}

bool findIntMidpoint(const Side& riseAndRun, double& newX, double& newY){
    while( !(std::floor(newX) == newX) || !(std::floor(newY) == newY)){
        newX += riseAndRun.run;
        newY += riseAndRun.rise;
        if(newX > 50 || newY > 50){
            return false;
        }
    };
    return true;
}

Quadrilateral buildKite(){
    Quadrilateral kite = buildRhombus();
    //get midpoint of B and D
    Point midpoint = getMidpoint(kite.tLeft, kite.bRight);
    Side riseAndRun = findRiseAndRun(kite.bLeft, midpoint);
    
    double newX = midpoint.x + riseAndRun.run;
    double newY = midpoint.y + riseAndRun.rise;
    //check if an integer
    int attempts = 0;
    
    while(!findIntMidpoint(riseAndRun, newX, newY)){
        kite = buildRhombus();
        Point midpoint = getMidpoint(kite.tLeft, kite.bRight);
        Side riseAndRun = findRiseAndRun(kite.bLeft, midpoint);
        newX = midpoint.x + riseAndRun.run;
        newY = midpoint.y + riseAndRun.rise;
        attempts++;
        if (attempts > 10){
            kite = buildSquare();
            newX = kite.tRight.x + 1;
            newY = kite.tRight.y + 1;
            cout << "Kite cheated" << endl;
            break;
        }
    };
    kite.type = "kite";
    kite.tRight.x = newX;
    kite.tRight.y = newY;
    //check to see if integer found
    //if not add again
    //if over 50, break
    //if intPoint not found, pick a new paralellagram and try again
    //try 10 times, if not found pick square
    assert(areEqual(kite.sideA.len, kite.sideC.len));
    assert(areEqual(kite.sideB.len, kite.sideD.len));
     assert(areEqual(kite.sideB.len, kite.sideA.len));
    return kite;
}

void outputCoordinates(Quadrilateral quadrilateral, std::ofstream& coordinatesOutStream){
    coordinatesOutStream << quadrilateral.bRight.x << " " << quadrilateral.bRight.y << " " <<
    quadrilateral.tRight.x << " " << quadrilateral.tRight.y << " " <<
    quadrilateral.tLeft.x << " " << quadrilateral.tLeft.y << " " << endl;
    return;
};

// if line contains the wrong number of points, invalid characters, coordinates out of the range 0..100, or otherwise fails to describe three points (six integer values)
string generateError1(){
     ostringstream sstream;
    string ret = "";
    int path = randomNum(2);
    if(path == 0){
        sstream << randomNum(0, 100) << " " << //1
        randomNum(0, 100) << " " <<//2
        randomNum(0, 100) << " " <<//3
        randomNum(0, 100) << " " <<//4
        randomNum(0, 100) << " " <<//5
        randomNum(0, 100) << " " <<//6
        randomNum(0, 100) << "\n";//7
        ret = sstream.str();
        return ret;
    }else if(path == 1){
        for( int i = 0; i < 6; i++){ //6 is the number of valid points
            int r = rand() % 26;   // generate a random number
            char c = 'a' + r;
            sstream << c;
            if(i != 5){
                sstream << " ";
            }else{
                sstream << "\n";
            }
        }
        return ret;
    }else if(path == 2){
        for( int i = 0; i < 6; i++){ //6 is the number of valid points
            int r = randomNum(100, 200);   // generate a random number
            sstream << r;
            if(i != 5){
                sstream << " ";
            }else{
                sstream << "\n";
            }
        }
        ret = sstream.str();
        return ret;
    }else{
        cout << "problem generating error 1 in generateError1 function";
        cout << "path number: " << path << endl;
        assert(false);
    }
}

string generateError2(){
    string ret = "";
    int point1 = randomNum(0, 100);
    int point2 = randomNum(0, 100);
    for( int i = 0; i < 3; i++){ //6 is the number of valid points
           // generate a random number
        ret += to_string(point1);
        ret += " ";
        ret += to_string(point2);
        if(i != 5){
            ret += " ";
        }
    }
    return ret;
}

string generateError3(){
    ostringstream sstream;
    string ret;
    Point point1, point2, point3;
    setPoint(point1, randomNum(50, 100),randomNum(0, 50));
    setPoint(point2, randomNum(0, 50),randomNum(50, 100));
    setPoint(point3, randomNum(50, 100),randomNum(50, 100));
    sstream << point1.x << " " << point1.y << " " << point2.x << " " << point2.y << " " << point3.x << " " << point3.y << endl;
    ret = sstream.str();
    return ret;
}

string generateError4(){
    ostringstream sstream;
    string ret;
    Point point1, point2, point3;
    int x = randomNum(0, 25);
    int y = randomNum(0, 25);
    setPoint(point1, x,y);
    setPoint(point2, x * 2,y * 2);
    setPoint(point3,x * 3,y * 3);
    sstream << point1.x << " " << point1.y << " " << point2.x << " " << point2.y << " " << point3.x << " " << point3.y << endl;
    ret = sstream.str();
    return ret;
}

string createError(const int& shapeNum ){
    string ret = "";
    switch (shapeNum){
        case 7:
            std::cout << "error 1" <<endl;
            ret = generateError1();
            break;
        case 8:
            std::cout << "error 2" <<endl;
            ret = generateError2();
            break;              //execution of subsequent statements is terminated
        case 9:
            std::cout << "error 3" <<endl;
            ret = generateError3();
            break;
        case 10:
            ret = generateError4();
            std::cout << "error 4" <<endl;
            break;
        default:
            cout << "could not properly classify shape Type";
            cout << "shape number: " << shapeNum << endl;
            assert(false);
    }
    return ret;
}

Quadrilateral buildQuadrilateral(){
    Point bleft, tRight, tLeft;
    setPoint(bleft, randomNum(50, 100),randomNum(0, 50));
    setPoint(tRight, randomNum(50, 100),randomNum(50, 100));
    setPoint(tLeft, randomNum(0, 50),randomNum(50, 100));
   
    
    Quadrilateral quadrilateral;
    quadrilateral.bRight = bleft;
    quadrilateral.tRight = tRight;
    quadrilateral.tLeft = tLeft;
  
    calcAllSlopes(quadrilateral);
    calcAllDistance(quadrilateral);
    //check that slope of A and C !=
    bool isValid = false;
    while(!isValid){
        isValid = true;
        if(areEqual(quadrilateral.sideA.len, quadrilateral.sideC.len)){
            setPoint(bleft, randomNum(0, 50),randomNum(50, 100));
            quadrilateral.bLeft = bleft;
            isValid = false;
        }
        if(areEqual(quadrilateral.sideB.len, quadrilateral.sideD.len)){
            setPoint(tRight, randomNum(0, 50),randomNum(50, 100));
            quadrilateral.tRight = tRight;
            isValid = false;
        }
        if(areEqual(quadrilateral.sideA.slope, quadrilateral.sideC.slope)){
            setPoint(bleft, randomNum(0, 50),randomNum(50, 100));
            quadrilateral.bLeft = bleft;
            isValid = false;
        }
        if(areEqual(quadrilateral.sideB.slope, quadrilateral.sideD.slope)){
            setPoint(tRight, randomNum(0, 50),randomNum(50, 100));
            quadrilateral.tRight = tRight;
            isValid = false;
        }
    }
    quadrilateral.type = "quadrilateral";
    return quadrilateral;
    //check that
}

Quadrilateral createShape(const int& shapeNum ){
    Quadrilateral quadrilateral;
    switch (shapeNum){
        case 0:
            cout << "quadrilateral" <<endl;
            quadrilateral = buildTrapezoid();
            break;
        case 1 :
            std::cout << "parallelagram" <<endl;
            quadrilateral = buildParallelagram();
            break;
        case 2:
             quadrilateral = buildRhombus();
            std::cout << "rhombus" <<endl;
            break;
        case 3:
            std::cout << "square" <<endl;
            quadrilateral = buildSquare();
            break;
        case 4:
            std::cout << "rectangle" <<endl;
            quadrilateral = buildRectangle();
            break;              //execution of subsequent statements is terminated
        case 5:
            std::cout << "trapezoid" <<endl;
             quadrilateral = buildTrapezoid();
            break;
        case 6:
            std::cout << "kite" <<endl;
            quadrilateral = buildKite();
            break;
        default:
            cout << "could not properly classify shape Type";
            cout << "shape number: " << shapeNum << endl;
            assert(false);
    }
    return quadrilateral;
}

void pickRandomOutput(vector<string>& possibleOutShapes, ofstream& expectedOutStream, std::ofstream& coordinatesOutStream){
    int shapeCount = (int) shapeTypes.size() -1;
    int shapeNum = randomNum(shapeCount); //Throw away first random number as it always seems to be 0
    shapeNum = randomNum(shapeCount);
    string firstShapeType = shapeTypes[ shapeNum ];
    possibleOutShapes.push_back( firstShapeType );
    expectedOutStream << firstShapeType << endl;
    cout << firstShapeType <<": "<< shapeNum << endl;
    Quadrilateral quadrilateral = createShape(shapeNum);
    outputCoordinates(quadrilateral, coordinatesOutStream);
    initErrorTypes(shapeTypes);
    int totalShapeTypes = (int) shapeTypes.size() - 1;
    
    for (int i = 0 ; i < 100 ; i++){
        shapeNum = randomNum(totalShapeTypes);
        string shapeType = shapeTypes[ shapeNum ];
        possibleOutShapes.push_back( shapeType );
        expectedOutStream << shapeType << endl;
//
//        cout << endl;
//        cout << endl;
//        cout << endl;
//        cout << "shapeNum: " << shapeNum << endl;
//        cout << "totalShapeTypes: " << totalShapeTypes - 4  << endl;
        if( !(shapeNum > ( totalShapeTypes - 4 ) ) ){
            quadrilateral = createShape(shapeNum);
            outputCoordinates(quadrilateral, coordinatesOutStream);
             //print coordinates
        }else{
            string errorPoints = createError(shapeNum);
            coordinatesOutStream << errorPoints << "error";
             break;
        }

    }
}

