//
//  rectangleOverlap.cpp
//  rectangleOverlapFast
//
//  Created by matt on 9/9/23.
//
//

#include "rectangleOverlap.hpp"

namespace ro {

Point::Point(double const x, double const y){
    this->x = x;
    this->y = y;
};

void Point::print() const {
    std::cout << "(" << x << ", "  << y << ")   ";
};

Extrema::Extrema() : min(std::numeric_limits<double>::max()), max(std::numeric_limits<double>::lowest()){};

void Rectangle::rotate(double const r){
    // rotate the rectangle r degrees
    double cosAngle = cos(r * M_PI / 180);
    double sinAngle = sin(r * M_PI / 180);
    
    for (int i = 0; i < 4; i++){ // For each vertex
        double x1 = m_vertices[i].x - m_xCenter;
        double y1 = m_vertices[i].y - m_yCenter;
        
        double x2 = x1 * cosAngle - y1 * sinAngle;
        double y2 = x1 * sinAngle + y1 * cosAngle;
        
        m_vertices.at(i).x = x2 + m_xCenter;
        m_vertices.at(i).y = y2 + m_yCenter;
    }
};

// Each rectangle has two slopes which are mutually perpendicular. We call the
// non-negative finite one the "nominal" slope of the rectangle. We call the
// other one, which is either +inf or a negative finite number the "ortho" slope.
// The nominal slope is guaranteed to be finite and non-negative.
// Each rectangle slope m implies a projection axis.
// A finite slope m implies the projection axis (1,m).
// If slope m is infinite, then m implies the projection axis (0,1).
// If the rectangles have equal slope, i.e., if they are parallel, only two axes need be considered.
// If the rectangles' slopes differ, four axes must be considered.

enum slopeKind {nominal=0, ortho=1};

Rectangle::Rectangle(const double x, const double y, const double w, const double h, const double r){
    // Make a rectangle given center (x,y), width w, height h, and rotation angle r in degrees
    m_xCenter = x;
    m_yCenter = y;
    
    // Distance from center to side, horizontally and vertically
    double dw = w/2;
    double dh = h/2;
    
    // Initialize the rectangle unrotated, then rotate it
    m_vertices.emplace_back(x - dw,y - dh);
    m_vertices.emplace_back(x + dw,y - dh);
    m_vertices.emplace_back(x + dw,y + dh);
    m_vertices.emplace_back(x - dw,y + dh);
    
    if (r != 0.0){
        rotate(r);
    }

    // Compute the nominal and ortho slopes of this rectangle and store them in member variables
    computeSlopes();
    
    // Compute the min and max projections (extrema) of this rectangle's vertices onto the each
    // of its own two axes. We name these projection axes the nominal axis and the ortho axis,
    // corresponding to the nominal and ortho slopes.
    m_extrema[nominal] = projectionExtrema(m_slope[nominal]);
    m_extrema[ortho]   = projectionExtrema(m_slope[ortho]);
};

Extrema Rectangle::projectionExtrema(double const theSlope) const {
    // Project this rectangle's vertices onto the projection axis implied by theSlope.
    // If theSlope is finite,   the implied projection axis is (1, theSlope).
    // If theSlope is infinite, the implied projection axis is (0, 1).
    
    // Compute the minimum and maximum of the projections of this rectangle's vertices
    // onto the axis implied by theSlope.

    // Return the min and max as an Extrema object.
    
    Extrema extrema;        // Will hold return value
    
    if (isinf(theSlope)){
        // Slope is infinite; axis is the y-axis, represented by (0,1)
        for (auto p = m_vertices.begin(); p != m_vertices.end(); p++){
            double pr = p->y;  // Projection onto axis (0,1) is just the y-component of vertex
            if (pr > extrema.max) extrema.max = pr;
            if (pr < extrema.min) extrema.min = pr;
        };
        
        return extrema;
    }
    else{
        // Slope is finite; axis is represented by (1,theSlope)
        for (auto p = m_vertices.begin(); p != m_vertices.end(); p++){
            double pr = p->x + p->y * theSlope;
            if (pr > extrema.max) extrema.max = pr;
            if (pr < extrema.min) extrema.min = pr;
        };
        
        return extrema;
    }
};

void Rectangle::print() const {
    std::cout << "Rectangle vertices: ";
    for (auto it = m_vertices.begin(); it != m_vertices.end(); it++){
        std::cout << "(" << (*it).x << ", "  << (*it).y << ")   ";
    };
    std::cout << std::endl;
}

void Rectangle::computeSlopes(){
    // Compute this rectangle's nominal and ortho slopes and store them as members. Nominal and
    // ortho slopes are slopes of the sides of the rectangle. The nominal slope is guaranteed to
    // be finite and greater than or equal to zero. Since the ortho slope is at
    // right angles to the nominal slope, it will be generally be less than zero except in the case
    // where it is +inf, which is the case in which the nominal slope = 0.
    
    // Get two consecutive vertices of the rectangle; call them p1, p2
    auto it = m_vertices.begin();
    Point p1 = *it++;
    Point p2 = *it;
    
    if (p1.x - p2.x != 0) {
        double m = (p1.y - p2.y) / (p1.x - p2.x);
        if (m == 0){
            m_slope[nominal] = 0;
            m_slope[ortho] = std::numeric_limits<double>::infinity();
        }
        else if (m > 0) {
            m_slope[nominal] = m;
            m_slope[ortho] = -1/m;
        }
        else{
            m_slope[nominal] = -1/m;
            m_slope[ortho] = m;
        };
    }
    else{
        m_slope[nominal] = 0;
        m_slope[ortho] = std::numeric_limits<double>::infinity();
    }
};

bool Rectangle::disjunct(const Extrema (&extrema)[2]) const {
    // The array that is passed in, extrema, represents the projection of another rectangle's vertices
    // onto the axes of this rectangle. We compare extrema[nominal] and extrema[ortho] with the
    // corresponding members of this rectangle to check for overlap. For every projection axis, we compute
    //          bool disjunct = max2 < min1 || max1 < min2
    // where 1 and 2 refer to the two rectangles.
    // The min and max refer to the extrema of the projections of the vertices of the rectangles
    // onto a specific axis. Input array extrema[2] has dimension 2 representing nominal and ortho axes.

    for (int i = nominal; i <= ortho; i++){
        if (m_extrema[i].max < extrema[i].min)   return true;
        if (extrema[i].max   < m_extrema[i].min) return true;
    };
    
    return false;
};

bool Rectangle::separated(const Rectangle& rect) const {
    // Computes whether this rectangle is separated from Rectangle rect.
    // Separated means rectangles do not overlap.
    
    // Test for separation on every projection axis.
    // For each projection axis,
    //     bool separated = max2 < min1 || max1 < min2
    // where 1 and 2 refer to the two rectangles, this and rect.
    // If separated is true for any single axis, return true without checking other axes.
    
    // Return false only after having checked every axis for separation and verified
    // that separated was always false.

    if (m_slope[nominal] == rect.m_slope[nominal]){
        // Case where the two rectangles have the same slope
        return disjunct(rect.m_extrema);
    }
    else {
        // Case where the two rectangles have different slopes.
        
        // Calculate the missing projection extrema.
        Extrema thisExtrema[2];  // Extrema of this rectangle's vertices projected onto rect's axes
        Extrema rectExtrema[2];  // Extrema of rect's vertices projected onto this rectangle's axes
        
        for (auto i = 0; i<2; i++){ // For nominal & ortho axes
            // Project this rectangle's vertices on rect's axis
            thisExtrema[i] = projectionExtrema(rect.m_slope[i]);
            // Project rect's vertices on this rectangle's axis
            rectExtrema[i] = rect.projectionExtrema(m_slope[i]);
        }

        // Check projection of this rectangle's vertices onto rect's axes
        if (disjunct(rectExtrema)) return true;
        
        // Check projection of rect's vertices on this rectangle's axes
        if (rect.disjunct(thisExtrema)) return true;

        // Rectangles' projections are overlapped on every axis
        return false;
        };
};
    
} // end of namespace ro


