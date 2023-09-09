//
//  main.cpp
//  rectangleOverlapFast
//
//  Created by matt on 9/9/23.
//


//  How to build example:
//    g++ -std=c++17 -o rectangleOverlap  rectangleOverlap.cpp main.cpp
//
//  You can run this from the command line by following instructions in "usage" below.
//  You can run with plotting using the Python test harness distributed with this software
//  After building the C++ executable as shown above, edit the Python source to point
//  the "path" variable to your executable. Then just run the Python program and it
//  will execute a series of test cases, which you can add to.
//


#include "rectangleOverlap.hpp"
#include <iostream>

void usage() {
    std::cout << "Usage:\n";
    std::cout << "viewportOverlap x1, y1, w1, h1, r1, x2, y2, w2, h2, r2\n\n";
    std::cout << "where:\n";
    std::cout << " (x1,y1) = center of rectangle 1\n";
    std::cout << " w1 = width of rectangle 1\n";
    std::cout << " h1 = height of rectangle 1\n";
    std::cout << " rotation angle in degrees of rectangle 1\n";
    std::cout << " (x2,y2) = center of rectangle 2\n";
    std::cout << " w2 = width of rectangle 2\n";
    std::cout << " h2 = height of rectangle 2\n";
    std::cout << " rotation angle in degrees of rectangle 2\n";
}

int main(int argc, const char * argv[]) {
    if (argc != 11){
        // number of command line input parameters is invalid
        usage();
        exit(-1);
    }
    
    double x1,y1,w1,h1,r1,x2,y2,w2,h2,r2;  // Input parameters
    
    try{
        // Convert input parameters to double
        x1 = std::stod(argv[1]);
        y1 = std::stod(argv[2]);
        w1 = std::stod(argv[3]);
        h1 = std::stod(argv[4]);
        r1 = std::stod(argv[5]);
        
        x2 = std::stod(argv[6]);
        y2 = std::stod(argv[7]);
        w2 = std::stod(argv[8]);
        h2 = std::stod(argv[9]);
        r2 = std::stod(argv[10]);
    }
    catch(std::invalid_argument e){
        // Input parameters are invalid
        usage();
        exit(-1);
    }
    
    // Instantiate the two rectangles rect1 & rect2
    ro::Rectangle rect1(x1,y1,w1,h1,r1);
    ro::Rectangle rect2(x2,y2,w2,h2,r2);

    // Compute whether the two rectangles are separated/disjunct from one another
    bool separated = rect1.separated(rect2);

    if (separated){
        std::cout << "Rectangles separated";
        //a->print();
        std::cout << std::endl;
        std::cout << "\nRect1:\n";
        rect1.print();
        std::cout << "\nRect2:\n";
        rect2.print();
        std::cout << std::endl;
        
        return 0;
    }
    else {
        std::cout << "Rectangles are overlapped\n\n";
        std::cout << "Rect1:\n";
        rect1.print();
        std::cout << "Rect2:\n";
        rect2.print();
        
        return 1;
    }
}



