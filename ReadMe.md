# 📈 Newton Polynomial Approximator & Visualizer

This project is a C++ application that parses user-defined mathematical functions, approximates them using Newton's Interpolating Polynomials, calculates the approximation error, and visually plots both the original function and the approximation in a separate window.

## ✨ Features
* **Dynamic Function Parsing:** Enter any standard mathematical function as a string (e.g., `sin(x) + log(x)`), and the program evaluates it on the fly.
* **Newton Polynomial Interpolation:** Approximates the parsed function over a user-defined interval $[a, b]$ using $n$ dynamically generated points.
* **Error Calculation:** Computes the absolute error $E(x) = |f(x) - P_{n-1}(x)|$ between the true function and the polynomial approximation.
* **Graphical Visualization:** Opens a separate graphical window plotting the original function, the approximated polynomial, and the sampled points for direct visual comparison.

## 🧰 Dependencies
To build and run this project, you will need the following libraries:
* **[ExprTk / muparser]**: For evaluating the mathematical string expressions.
* **[Plotting Library Name, e.g., matplotlib-cpp / gnuplot-iostream / SFML]**: Used to render the coordinate system and plot the curves in a standalone window.

## 🚀 How It Works

1. **Input:** The user is prompted to enter a function $f(x)$, an interval (e.g., $[0, 1]$), and the number of interpolation points $n$.
2. **Sampling:** The program calculates the step size and evaluates $f(x)$ at $n$ evenly spaced points across the interval to generate $(x, y)$ coordinate pairs.
3. **Divided Differences:** The program builds a divided difference table to calculate the coefficients for the Newton polynomial.
4. **Interpolation:** The Newton polynomial is constructed: 
   $$P(x) = f[x_0] + f[x_0, x_1](x - x_0) + \dots + f[x_0, \dots, x_n](x - x_0)\dots(x - x_{n-1})$$
5. **Plotting:** Both $f(x)$ and $P(x)$ are heavily sampled (e.g., 1000 points) and sent to the plotting backend to be drawn on the screen.

## 🛠️ Usage / Building

*(Note: Update these instructions based on your specific build system, like CMake or Make)*

```bash
# Clone the repository
git clone [https://github.com/CriticalDMG/newton-approximator.git](https://github.com/yourusername/newton-approximator.git)
cd newton-approximator

# Compile the project 
g++ main.cpp -o approximator -O3

# Run the executable
./approximator