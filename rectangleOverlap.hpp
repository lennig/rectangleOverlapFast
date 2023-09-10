//
//  rectangleOverlap.hpp
//  rectangleOverlapFast
//
//  Created by matt on 9/9/23.
//

#pragma once

// Computes whether two rectangles in (x,y) space overlap each other
//

// How to use:
//  Instantiate a rectangle rect like this:
//    Rectangle rect = new Rectangle(x, y, w, h, r)
// where
//   (x,y) = center of rect
//   (w,h) = width and height of rect
//     r   = rotation in degrees of rect

//  Given two rectangles, rect1 and rect2,
//    bool areSeparated = rect1.separated(rect2)
//  returns true iff the two rectangles are disjunct, i.e., non-overlapping.
//    areSeparated = rect2.separated(rect1)
//  returns the same value.
//

//
// The algorithm implemented here is the one described in this article:
// https://jkh.me/files/tutorials/Separating%20Axis%20Theorem%20for%20Oriented%20Bounding%20Boxes.pdf
// which is a special case (for rectangles) of the Separating Axis Theorem for convex polygons

// There is a Python test harness to excercise rectangleOverlap:
//     testHarness.py
// The above Python script is distributed with rectangleOverlapFast on github
// Edit testHarness.py to point to your executable

// This is the fast version of the algorithm. The main overlap computation requires a maximum of
// 16 multiplications to test for overlap.

// This version does not return the axis of separation. If you're interested in getting the axis
// of separation, use the slower version here:
//      https://github.com/lennig/rectangleOverlap

// How to build example:
// g++ -std=c++17 -o rectangleOverlap  rectangleOverlap.cpp main.cpp

#pragma once

#include <iostream>
#include <cfloat>
#include <vector>

namespace ro {

// Class Point
class Point {
public:
    double x;
    double y;
    
    Point(double const x, double const y);
    void print() const;
};

class Extrema {
    // Class to hold the minimum and maximum resulting from the
    // projection of a rectangle's vertices onto a projection axis
public:
    double min;
    double max;
    Extrema();
};

// Class Rectangle
class Rectangle {
private:
    void rotate(double const rotationDegrees);
    void computeSlopes();
    bool disjunct(const Extrema (&extrema)[2]) const;
    Extrema projectionExtrema(double const theSlope) const;
    double m_xCenter;
    double m_yCenter;
public:
    bool separated(const Rectangle& rect) const;
    bool operator % (const Rectangle& rect);
    Rectangle(double const x, double const y, double const w, double const h, double const r);
    void print() const;
    
    std::vector<Point> m_vertices;
    double m_slope[2];    // Nominal and ortho slopes of this rectangle, which determine projection axes
    Extrema m_extrema[2]; // Extrema for self-projections onto both axes: m_extrema[nominal] and m_extrema[ortho]
};

} // end namespace ro




