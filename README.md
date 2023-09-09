# rectangleOverlapFast
Faster implementation of rectangleOverlap
# rectangleOverlap
Given two rectangles in (x,y) space, computes whether or not they overlap one another.  
If they do not overlap, optionally provides their axis of separation.

**How to use:**  
Instantiate a rectangle rect like this: 
 
  ```
Rectangle rect = new Rectangle(x, y, w, h, r)  
  ```
  
  where  
   (x,y) = center of rect  
   (w,h) = width and height of rect  
     r   = rotation in degrees of rect  

Given two rectangles, rect1 and rect2,  

  ```     
bool disjunct = rect1.separated(rect2) 
  ```     
    
returns true iff the two rectangles are separated/disjunct, i.e., if they do **not** overlap/intersect.  

  ```
disjunct = rect2.separated(rect1)  
  ```
returns the same value.  

**Axis of Separation**  
The fast version does not return the axis of separation

**How to build example:**  
 g++ -std=c++17 -o rectangleOverlap  rectangleOverlap.cpp main.cpp  


