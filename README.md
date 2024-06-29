# College-Project-2
## An interesting Mandelbrot set visualization that uses SDL library 


### What is this project about ?

Retaining the knowledge gained while learning C++, We made a visualization of a fractal known as Mandelbrot. It basically is a graph that works with the equation given bellow 

$$ f(z) = z^2 +c $$

The Mandelbrot set is defined by a simple iterative process involving complex numbers. The basic idea is to take a complex number 
c and repeatedly apply a function to it. Specifically, the Mandelbrot set is the set of all complex numbers 
C for which the function does not diverge to infinity when iterated starting from  z = 0.

### What is the process involved in it ?

#### Iteration Process

1. Start with a complex number \(c\).
2. Initialize \(z<sub>0</sub> = 0\).
3. Apply the function iteratively: \(z<sub>n+1</sub> = z<sub>n</sub><sup>2</sup> + c\).
4. Check if the magnitude of \(z<sub>n</sub>\) remains bounded (i.e., \(|z<sub>n</sub>| \leq 2\)) as \(n\) increases.


