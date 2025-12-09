# Scientific & Engineering Math Toolkit (CLI)

This project is a **command‑line scientific and math toolkit** written in C, using a menu‑driven user interface.  

---

## Features Overview

The main menu provides six categories of tools:

1. **Operations (General Math)**  
   - **Arithmetic expression calculator**  
     - Supports expressions such as `5 + 1.2 + sin(2*pi) - ln(e)`  
     - Handles `+ - * /`, parentheses, floating‑point numbers, and constants `pi`, `e`  
     - Uses a custom expression parser (no external libraries)
   - **Powers & roots**  
     - Computes `a^b`, `b`‑th roots, etc.
   - **Trigonometric & inverse trigonometric functions**  
     - Wraps standard `sin / cos / tan` and `asin / acos / atan` (and related functions)
   - **Logarithms (general base)**  
     - Computes `log_b(x)` for any base `b > 0, b != 1`, not only `ln` or `log10`

2. **Linear Algebra**  
   - **Matrix operations**
     - Supports matrices from size `1×1` up to `3×3`
     - Addition, subtraction, and multiplication  
     - Dimension checks to ensure operations are valid (e.g. inner dimensions for multiplication)
   - **Solve linear system**
     - Solves linear systems up to `3×3`
     - Uses row operations / elimination; reports if the system has no solution or infinitely many solutions
   - **Determinant**
     - Computes determinants of `1×1`, `2×2`, and `3×3` matrices

3. **Basic Statistics**  
   For a dataset entered in a single line (e.g. `1 2 4 3 6 7`), the toolkit can compute:
   - **Mean**
   - **Variance / Standard deviation**  
     - Distinguishes between **population** and **sample** measures
   - **Minimum / Maximum**
   - **Normalisation to [0, 1]**

4. **Root‑Finding**  
   Focused on cubic polynomials of the form:
   \[
     f(x) = A x^3 + B x^2 + C x + D
   \]
   - The user first enters the coefficients **A, B, C, D**
   - Then, within a sub‑menu, can repeatedly choose different methods to compare:
     - **Bisection method**
     - **Newton–Raphson method**
     - **Secant method**
   - Each method can use user‑defined intervals / initial guesses, tolerances, and maximum iteration counts (implementation dependent)

5. **Geometry & Shapes**  
   - **2D Shapes (area & perimeter)**
     - **Circle**: input radius `r`, compute area and circumference  
     - **Rectangle**: input width and height  
     - **Triangle**: input base and height (assumed right‑angled triangle, base and height are the legs)  
     - **Trapezoid**: input top base, bottom base, and height (assumed isosceles trapezoid)
   - **3D Geometry (volume & surface area)**
     - **Sphere**: input radius `r`  
     - **Cylinder**: input radius and height  
     - **Cone**: right circular cone, input radius and height  
     - **Box / Rectangular prism**: input length, width, and height
   - **Coordinate geometry**
     - Distance between two points (2D or 3D)
     - Vector length (2D or 3D)
     - Distance from a point to a line in 2D, where the line is given in general form \(Ax + By + C = 0\)

6. **Complex Numbers / Phasors**  
   - **Basic complex operations (expression calculator)**
     - Supports expressions such as `(1+2j) - 2 + 2*(3.5-6j)`  
     - Uses `j` (or `J`) as the imaginary unit; supports `+ - * /`, parentheses, floating‑point numbers, and constants `pi`, `e`
   - **Cartesian <-> polar conversion**
     - First choose the direction:
       - Cartesian → Polar: input `x, y`, output magnitude `r` and phase (radians and degrees)  
       - Polar → Cartesian: input `r, θ` (in degrees or radians), output `x, y`
   - **Magnitude and phase**
     - Enter a complex number or complex expression `a + bj`
     - Outputs:
       - Magnitude `|z|`
       - Phase in radians
       - Phase in degrees

---

## Project Structure

Typical file layout:

```text
.
├── main.c      // Menu system and user interaction
├── funcs.c     // Implementations of all math / engineering tools
├── funcs.h     // Function prototypes
└── README.md   // Project documentation (this file)
```

- `main.c`  
  Prints the main menu and all sub‑menus, dispatching to functions implemented in `funcs.c`.
- `funcs.c`  
  Implements all computation logic (expression parsing, matrix operations, statistics, geometry, complex numbers, etc.).
- `funcs.h`  
  Declares the public interfaces used by `main.c`.

---

## Building and Running

### Using gcc / clang (command line)

From the project directory:

```bash
gcc main.c funcs.c -lm -o math_toolkit
# or
clang main.c funcs.c -lm -o math_toolkit
```

Notes:

- `-lm` links against the math library (`sin`, `cos`, `sqrt`, `log`, etc.).
- The output executable is named `math_toolkit` (you can choose a different name).

Run:

```bash
./math_toolkit
```

### Using Xcode (macOS)

1. Create a new **Command Line Tool** project, language **C**.
2. Add `main.c`, `funcs.c`, and `funcs.h` to the project.
3. Select the target and click **Run** (or press ⌘R).
4. Use the Xcode console for input / output interaction.

---

## Basic Usage

1. When the program starts, the **main menu** is displayed:
   - Enter the corresponding number (0–6) and press Enter to choose a tool category.
2. Inside each sub‑menu:
   - Again, use the numbers to select a specific function.
   - `0` generally means “back to previous menu” or “exit”.
3. Numeric input:
   - Values are treated as floating‑point numbers.
   - Common formats such as `3`, `-2.5`, `1e-3` are supported by `scanf`.
4. Complex expressions:
   - Use `j` or `J` as the imaginary unit, e.g. `1+2j`, `-3.5j`.
   - Parentheses and all four basic operations are supported, e.g. `(1+2j) - 2 + 2*(3.5-6j)`.
5. Pay attention to the prompts and units printed by the program:
   - For example, whether an angle is expected / reported in degrees or radians.
   - Whether a geometric quantity is an area, perimeter, volume, or surface area.

---

## Design Highlights & Educational Value

- **Modular design**  
  - The menu system and core functionality are clearly separated (`main.c` vs `funcs.c`), making the code easier to read, maintain, and extend.
- **Expression parsing**  
  - A simple in‑house expression parser is implemented for both real and complex expressions, illustrating basic ideas of parsing, operator precedence, and evaluation.
- **Numerical methods in practice**  
  - The root‑finding module implements classic numerical algorithms (Bisection / Newton–Raphson / Secant), which can be compared in terms of convergence behaviour and robustness.
- **Engineering‑oriented tools**  
  - Geometry, complex numbers / phasors, and statistics are all directly relevant to engineering mathematics, circuits, signals, and systems modules.
