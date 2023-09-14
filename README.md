# rectangleOverlapFast
Faster implementation of rectangleOverlap

Given two rectangles in (x,y) space, computes whether or not they overlap one another.  

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


Equivalently, you can use the separated-from operator % for rectangles to compute whether or not two rectangles are disjunct:

```
disjunct = rect1 % rect2;         // true iff rect1 and rect2 are separated i.e. disjunct
```


which is always equal to 


```
disjunct = rect2 % rect1;        // true iff rect1 and rect2 are separated/disjunct
```





**Axis of Separation**  
The fast version does not return the axis of separation. If you need the axis of separation, use rectangleOverlap
instead. It can be found here: https://github.com/lennig/rectangleOverlap

**How to build example:**  
 g++ -std=c++17 -o rectangleOverlap  rectangleOverlap.cpp main.cpp  


