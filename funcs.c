#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "funcs.h"

// Internal definitions for arithmetic and complex expression parsers
#define MY_PI 3.14159265358979323846
#define MY_E  2.71828182845904523536

typedef struct {
    double re;
    double im;
} Complex;

static const char *expr_p = NULL;   // real expression parser pointer
static const char *cexpr_p = NULL;  // complex expression parser pointer

// Helper to flush the rest of the current input line from stdin
static void flush_stdin(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        // discard
    }
}

// Real expression parser prototypes
static void skip_spaces(void);
static double parse_expression(void);
static double parse_term(void);
static double parse_factor(void);
static double parse_number(void);

// Complex expression parser prototypes
static void cskip_spaces(void);
static Complex cparse_expression(void);
static Complex cparse_term(void);
static Complex cparse_factor(void);
static Complex cparse_number(void);

// 1) Operations
void op_arithmetic(void)
{
    char line[256];

    printf("\n[Arithmetic expression calculator]\n");
    printf("You can enter expressions using +, -, *, /, parentheses,\n");
    printf("functions sin, cos, tan, asin, acos, atan, ln, log10,\n");
    printf("and constants pi and e.\n");
    printf("Example: 5 + 1.2 + sin(2*pi) - ln(e)\n\n");

    printf("Enter expression: ");
    if (!fgets(line, sizeof(line), stdin)) {
        printf("Input error.\n");
        return;
    }

    expr_p = line;
    double result = parse_expression();
    skip_spaces();
    if (*expr_p != '\0' && *expr_p != '\n') {
        printf("Warning: unexpected input at: \"%s\"\n", expr_p);
    }

    printf("Result = %.10g\n", result);
}

void op_power_root(void)
{
    int choice;
    double a, b, n, result;

    printf("\n[Powers & roots tool]\n");
    printf("1) a^b (power)\n");
    printf("2) Square root (sqrt a)\n");
    printf("3) n-th root (a^(1/n))\n");
    printf("Select option: ");

    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        flush_stdin();
        return;
    }
    flush_stdin();

    switch (choice) {
    case 1:
        printf("Enter a: ");
        if (scanf("%lf", &a) != 1) { printf("Invalid input.\n"); break; }
        printf("Enter b: ");
        if (scanf("%lf", &b) != 1) { printf("Invalid input.\n"); break; }
        flush_stdin();
        result = pow(a, b);
        printf("Result: %.10g\n", result);
        break;
    case 2:
        printf("Enter a (a >= 0): ");
        if (scanf("%lf", &a) != 1) { printf("Invalid input.\n"); break; }
        flush_stdin();
        if (a < 0) {
            printf("Error: cannot take square root of negative number.\n");
        } else {
            result = sqrt(a);
            printf("sqrt(%.10g) = %.10g\n", a, result);
        }
        break;
    case 3:
        printf("Enter a: ");
        if (scanf("%lf", &a) != 1) { printf("Invalid input.\n"); break; }
        printf("Enter n (n != 0): ");
        if (scanf("%lf", &n) != 1) { printf("Invalid input.\n"); break; }
        flush_stdin();
        if (n == 0.0) {
            printf("Error: n cannot be zero.\n");
        } else if (a < 0 && fmod(n, 2.0) != 1.0) {
            printf("Warning: real n-th root of a negative number is undefined for even n.\n");
        }
        result = pow(a, 1.0 / n);
        printf("%.10g ^ (1/%.10g) = %.10g\n", a, n, result);
        break;
    default:
        printf("Invalid option.\n");
        break;
    }
}

void op_trigonometry(void)
{
    int mode, fn;
    double x, result;
    int angle_mode;

    printf("\n[Trigonometric & inverse trigonometric tool]\n");
    printf("1) Trigonometric (sin, cos, tan)\n");
    printf("2) Inverse trigonometric (asin, acos, atan)\n");
    printf("Select mode: ");
    if (scanf("%d", &mode) != 1) {
        printf("Invalid input.\n");
        flush_stdin();
        return;
    }
    flush_stdin();

    if (mode == 1) {
        printf("Select function:\n");
        printf(" 1) sin\n");
        printf(" 2) cos\n");
        printf(" 3) tan\n");
        printf("Choice: ");
        if (scanf("%d", &fn) != 1) {
            printf("Invalid input.\n");
            flush_stdin();
            return;
        }
        flush_stdin();

        printf("Angle input mode:\n");
        printf(" 1) Degrees\n");
        printf(" 2) Radians\n");
        printf("Choice: ");
        if (scanf("%d", &angle_mode) != 1) {
            printf("Invalid input.\n");
            flush_stdin();
            return;
        }
        printf("Enter angle value: ");
        if (scanf("%lf", &x) != 1) {
            printf("Invalid input.\n");
            flush_stdin();
            return;
        }
        flush_stdin();

        if (angle_mode == 1) {
            x = x * MY_PI / 180.0;
        }

        switch (fn) {
        case 1: result = sin(x);  printf("sin = %.10g\n", result); break;
        case 2: result = cos(x);  printf("cos = %.10g\n", result); break;
        case 3: result = tan(x);  printf("tan = %.10g\n", result); break;
        default: printf("Invalid function choice.\n"); break;
        }

    } else if (mode == 2) {
        printf("Select inverse function:\n");
        printf(" 1) asin\n");
        printf(" 2) acos\n");
        printf(" 3) atan\n");
        printf("Choice: ");
        if (scanf("%d", &fn) != 1) {
            printf("Invalid input.\n");
            flush_stdin();
            return;
        }
        printf("Enter input value: ");
        if (scanf("%lf", &x) != 1) {
            printf("Invalid input.\n");
            flush_stdin();
            return;
        }
        flush_stdin();

        printf("Output angle mode:\n");
        printf(" 1) Degrees\n");
        printf(" 2) Radians\n");
        printf("Choice: ");
        if (scanf("%d", &angle_mode) != 1) {
            printf("Invalid input.\n");
            flush_stdin();
            return;
        }
        flush_stdin();

        switch (fn) {
        case 1: result = asin(x); break;
        case 2: result = acos(x); break;
        case 3: result = atan(x); break;
        default: printf("Invalid function choice.\n"); return;
        }

        if (angle_mode == 1) {
            result = result * 180.0 / MY_PI;
        }
        printf("Result = %.10g\n", result);
    } else {
        printf("Invalid mode.\n");
    }
}

void op_logarithms(void)
{
    double x, base, result;

    printf("\n[Logarithms tool]\n");
    printf("This tool computes log_base(x).\n");
    printf("Enter x (> 0): ");
    if (scanf("%lf", &x) != 1) {
        printf("Invalid input.\n");
        flush_stdin();
        return;
    }
    printf("Enter base (> 0, != 1): ");
    if (scanf("%lf", &base) != 1) {
        printf("Invalid input.\n");
        flush_stdin();
        return;
    }
    flush_stdin();

    if (x <= 0.0) {
        printf("Error: x must be > 0.\n");
        return;
    }
    if (base <= 0.0 || base == 1.0) {
        printf("Error: base must be > 0 and != 1.\n");
        return;
    }

    result = log(x) / log(base);
    printf("log_%.10g(%.10g) = %.10g\n", base, x, result);

    // Also show ln and log10 as extra info
    printf("ln(%.10g) = %.10g\n", x, log(x));
    printf("log10(%.10g) = %.10g\n", x, log10(x));
}

// 2) Linear algebra

// Matrix operations: add, subtract, multiply for matrices up to 3x3
void la_matrix_operations(void)
{
    int rowsA, colsA;
    char op;

    printf("\n[Matrix operations]\n");
    printf("You can work with matrices up to size 3x3.\n");

    printf("Enter number of rows for matrix A (1-3): ");
    if (scanf("%d", &rowsA) != 1) {
        printf("Invalid input.\n");
        flush_stdin();
        return;
    }
    printf("Enter number of columns for matrix A (1-3): ");
    if (scanf("%d", &colsA) != 1) {
        printf("Invalid input.\n");
        flush_stdin();
        return;
    }
    flush_stdin();

    if (rowsA < 1 || rowsA > 3 || colsA < 1 || colsA > 3) {
        printf("Error: dimensions must be between 1 and 3.\n");
        return;
    }

    printf("Enter operation (+, -, *): ");
    if (scanf(" %c", &op) != 1) {
        printf("Invalid input.\n");
        flush_stdin();
        return;
    }
    flush_stdin();

    int rowsB = 0, colsB = 0;

    if (op == '+' || op == '-') {
        rowsB = rowsA;
        colsB = colsA;
        printf("Matrix B will have the same dimensions as A: %dx%d\n", rowsB, colsB);
    } else if (op == '*') {
        printf("Enter number of rows for matrix B (1-3): ");
        if (scanf("%d", &rowsB) != 1) {
            printf("Invalid input.\n");
            flush_stdin();
            return;
        }
        printf("Enter number of columns for matrix B (1-3): ");
        if (scanf("%d", &colsB) != 1) {
            printf("Invalid input.\n");
            flush_stdin();
            return;
        }
        flush_stdin();

        if (rowsB < 1 || rowsB > 3 || colsB < 1 || colsB > 3) {
            printf("Error: dimensions must be between 1 and 3.\n");
            return;
        }
    } else {
        printf("Unsupported operation '%c'. Use +, -, or *.\n", op);
        return;
    }

    // Check compatibility
    if ((op == '+' || op == '-') &&
        (rowsA != rowsB || colsA != colsB)) {
        printf("Error: for addition/subtraction, matrices must have the same dimensions.\n");
        return;
    }

    if (op == '*' && colsA != rowsB) {
        printf("Error: for multiplication, number of columns of A must equal number of rows of B.\n");
        return;
    }

    double A[3][3] = {0};
    double B[3][3] = {0};
    double C[3][3] = {0};

    printf("Enter elements of matrix A (row by row):\n");
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsA; ++j) {
            printf("A[%d][%d] = ", i + 1, j + 1);
            if (scanf("%lf", &A[i][j]) != 1) {
                printf("Invalid input.\n");
                flush_stdin();
                return;
            }
        }
    }

    printf("Enter elements of matrix B (row by row):\n");
    for (int i = 0; i < rowsB; ++i) {
        for (int j = 0; j < colsB; ++j) {
            printf("B[%d][%d] = ", i + 1, j + 1);
            if (scanf("%lf", &B[i][j]) != 1) {
                printf("Invalid input.\n");
                flush_stdin();
                return;
            }
        }
    }
    flush_stdin();

    int rowsC = 0, colsC = 0;

    if (op == '+' || op == '-') {
        rowsC = rowsA;
        colsC = colsA;
        for (int i = 0; i < rowsA; ++i) {
            for (int j = 0; j < colsA; ++j) {
                if (op == '+') {
                    C[i][j] = A[i][j] + B[i][j];
                } else {
                    C[i][j] = A[i][j] - B[i][j];
                }
            }
        }
    } else { // multiplication
        rowsC = rowsA;
        colsC = colsB;
        for (int i = 0; i < rowsA; ++i) {
            for (int j = 0; j < colsB; ++j) {
                double sum = 0.0;
                for (int k = 0; k < colsA; ++k) {
                    sum += A[i][k] * B[k][j];
                }
                C[i][j] = sum;
            }
        }
    }

    printf("Result matrix (%dx%d):\n", rowsC, colsC);
    for (int i = 0; i < rowsC; ++i) {
        for (int j = 0; j < colsC; ++j) {
            printf("%10.4f ", C[i][j]);
        }
        printf("\n");
    }
}

// Solve linear system up to 3x3 using Gaussian elimination
void la_solve_linear_system(void)
{
    int n;
    printf("\n[Solve linear system]\n");
    printf("Enter number of unknowns (1-3): ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input.\n");
        flush_stdin();
        return;
    }
    flush_stdin();

    if (n < 1 || n > 3) {
        printf("Error: number of unknowns must be between 1 and 3.\n");
        return;
    }

    double aug[3][4] = {0}; // augmented matrix [A|b]

    printf("Enter coefficients of matrix A (row by row):\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("A[%d][%d] = ", i + 1, j + 1);
            if (scanf("%lf", &aug[i][j]) != 1) {
                printf("Invalid input.\n");
                flush_stdin();
                return;
            }
        }
    }

    printf("Enter constants vector b:\n");
    for (int i = 0; i < n; ++i) {
        printf("b[%d] = ", i + 1);
        if (scanf("%lf", &aug[i][n]) != 1) {
            printf("Invalid input.\n");
            flush_stdin();
            return;
        }
    }
    flush_stdin();

    const double EPS = 1e-9;

    // Gaussian elimination with partial pivoting
    for (int col = 0; col < n; ++col) {
        int pivot = col;
        for (int row = col + 1; row < n; ++row) {
            if (fabs(aug[row][col]) > fabs(aug[pivot][col])) {
                pivot = row;
            }
        }

        if (fabs(aug[pivot][col]) < EPS) {
            printf("System has no unique solution (pivot is zero).\n");
            return;
        }

        if (pivot != col) {
            for (int k = col; k <= n; ++k) {
                double tmp = aug[col][k];
                aug[col][k] = aug[pivot][k];
                aug[pivot][k] = tmp;
            }
        }

        for (int row = col + 1; row < n; ++row) {
            double factor = aug[row][col] / aug[col][col];
            for (int k = col; k <= n; ++k) {
                aug[row][k] -= factor * aug[col][k];
            }
        }
    }

    double x[3] = {0};

    for (int i = n - 1; i >= 0; --i) {
        double sum = aug[i][n];
        for (int j = i + 1; j < n; ++j) {
            sum -= aug[i][j] * x[j];
        }
        if (fabs(aug[i][i]) < EPS) {
            printf("System has no unique solution (zero on diagonal).\n");
            return;
        }
        x[i] = sum / aug[i][i];
    }

    printf("Solution:\n");
    for (int i = 0; i < n; ++i) {
        printf("x%d = %.10g\n", i + 1, x[i]);
    }
}

// Determinant of a 1x1–3x3 matrix
void la_determinant(void)
{
    int n;
    printf("\n[Determinant]\n");
    printf("Enter matrix size n (1-3) for an n x n matrix: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input.\n");
        flush_stdin();
        return;
    }
    flush_stdin();

    if (n < 1 || n > 3) {
        printf("Error: n must be between 1 and 3.\n");
        return;
    }

    double a[3][3] = {0};

    printf("Enter elements of the matrix (row by row):\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("A[%d][%d] = ", i + 1, j + 1);
            if (scanf("%lf", &a[i][j]) != 1) {
                printf("Invalid input.\n");
                flush_stdin();
                return;
            }
        }
    }
    flush_stdin();

    double det = 0.0;

    if (n == 1) {
        det = a[0][0];
    } else if (n == 2) {
        det = a[0][0] * a[1][1] - a[0][1] * a[1][0];
    } else { // n == 3
        det =
            a[0][0] * (a[1][1] * a[2][2] - a[1][2] * a[2][1]) -
            a[0][1] * (a[1][0] * a[2][2] - a[1][2] * a[2][0]) +
            a[0][2] * (a[1][0] * a[2][1] - a[1][1] * a[2][0]);
    }

    printf("det(A) = %.10g\n", det);
}

// 3) Statistics

// Internal helper for statistics: read a dataset from user
static int read_dataset(double **out_data, size_t *out_n);

// Read an arbitrary-size dataset from the user into a dynamically allocated array.
// Returns 1 on success, 0 on failure. Caller must free(*out_data) on success.
static int read_dataset(double **out_data, size_t *out_n)
{
    if (!out_data || !out_n) {
        return 0;
    }

    printf("\nEnter data values separated by spaces (e.g. 1 2 4 3 6 7):\n");
    printf("> ");

    char line[1024];
    if (!fgets(line, sizeof(line), stdin)) {
        printf("Input error.\n");
        return 0;
    }

    // Parse the line using strtod
    size_t capacity = 8;
    size_t n = 0;
    double *data = (double *)malloc(capacity * sizeof(double));
    if (!data) {
        printf("Memory allocation failed.\n");
        return 0;
    }

    char *p = line;
    while (*p != '\0') {
        // Skip leading whitespace
        while (*p != '\0' && isspace((unsigned char)*p)) {
            p++;
        }
        if (*p == '\0' || *p == '\n') {
            break;
        }

        char *endptr = NULL;
        double value = strtod(p, &endptr);
        if (endptr == p) {
            // No valid number found at this position
            printf("Invalid number starting at: \"%s\"\n", p);
            free(data);
            return 0;
        }

        if (n == capacity) {
            capacity *= 2;
            double *tmp = (double *)realloc(data, capacity * sizeof(double));
            if (!tmp) {
                printf("Memory allocation failed during resize.\n");
                free(data);
                return 0;
            }
            data = tmp;
        }

        data[n++] = value;
        p = endptr;
    }

    if (n == 0) {
        printf("No valid numbers were entered.\n");
        free(data);
        return 0;
    }

    *out_data = data;
    *out_n = n;
    return 1;
}

void stat_mean_variance_std(void)
{
    printf("\n[Mean / variance / standard deviation tool]\n");

    double *data = NULL;
    size_t n = 0;
    if (!read_dataset(&data, &n)) {
        return;
    }

    if (n == 0) {
        printf("No data.\n");
        free(data);
        return;
    }

    double sum = 0.0;
    for (size_t i = 0; i < n; ++i) {
        sum += data[i];
    }
    double mean = sum / (double)n;

    double sq_sum = 0.0;
    for (size_t i = 0; i < n; ++i) {
        double diff = data[i] - mean;
        sq_sum += diff * diff;
    }

    double var_pop = 0.0;
    double var_sample = 0.0;
    double std_pop = 0.0;
    double std_sample = 0.0;

    var_pop = (n > 0) ? (sq_sum / (double)n) : 0.0;
    std_pop = sqrt(var_pop);

    printf("\nMean = %.10g\n", mean);
    printf("Population variance  (sigma^2) = %.10g\n", var_pop);
    printf("Population std. dev. (sigma)   = %.10g\n", std_pop);

    if (n > 1) {
        var_sample = sq_sum / (double)(n - 1);
        std_sample = sqrt(var_sample);
        printf("Sample variance      (s^2)     = %.10g\n", var_sample);
        printf("Sample std. dev.     (s)       = %.10g\n", std_sample);
    } else {
        printf("Sample variance / std. dev. undefined for n = 1.\n");
    }

    free(data);
}

void stat_min_max(void)
{
    printf("\n[Min / max tool]\n");

    double *data = NULL;
    size_t n = 0;
    if (!read_dataset(&data, &n)) {
        return;
    }

    if (n == 0) {
        printf("No data.\n");
        free(data);
        return;
    }

    double minv = data[0];
    double maxv = data[0];
    for (size_t i = 1; i < n; ++i) {
        if (data[i] < minv) minv = data[i];
        if (data[i] > maxv) maxv = data[i];
    }

    printf("\nMinimum value = %.10g\n", minv);
    printf("Maximum value = %.10g\n", maxv);

    free(data);
}

void stat_normalise_0_1(void)
{
    printf("\n[Normalisation tool]\n");
    printf("This will normalise your data to the range [0, 1].\n");

    double *data = NULL;
    size_t n = 0;
    if (!read_dataset(&data, &n)) {
        return;
    }

    if (n == 0) {
        printf("No data.\n");
        free(data);
        return;
    }

    double minv = data[0];
    double maxv = data[0];
    for (size_t i = 1; i < n; ++i) {
        if (data[i] < minv) minv = data[i];
        if (data[i] > maxv) maxv = data[i];
    }

    if (maxv == minv) {
        printf("All values are equal (%.10g). Normalisation to [0,1] is undefined (division by zero).\n", minv);
        free(data);
        return;
    }

    printf("\nNormalised values (x' = (x - min) / (max - min)):\n");
    for (size_t i = 0; i < n; ++i) {
        double norm = (data[i] - minv) / (maxv - minv);
        printf("x[%zu]' = %.10g\n", i + 1, norm);
    }

    free(data);
}

// ============================
// Internal helpers for root-finding
// We solve f(x) = 0 for a user-defined cubic:
//     f(x) = A x^3 + B x^2 + C x + D
// The coefficients A, B, C, D are provided by the user
// in each root-finding function.
// ============================
static double poly_f(double x, double A, double B, double C, double D)
{
    // Horner's rule for numerical stability: (((A x + B) x + C) x + D)
    return ((A * x + B) * x + C) * x + D;
}

static double poly_fprime(double x, double A, double B, double C, double D)
{
    // Derivative of A x^3 + B x^2 + C x + D is 3 A x^2 + 2 B x + C
    return 3.0 * A * x * x + 2.0 * B * x + C;
}

// 4) Root-finding

// Bisection method for f(x) = 0 on an interval [a, b]
void root_bisection(double A, double B, double C, double D)
{
    printf("\n[Bisection method tool]\n");
    printf("We solve f(x) = A x^3 + B x^2 + C x + D = 0 using the bisection method.\n");
    printf("Using coefficients: A = %.10g, B = %.10g, C = %.10g, D = %.10g\n", A, B, C, D);

    double a, b;
    printf("Enter left endpoint a: ");
    if (scanf("%lf", &a) != 1) {
        printf("Invalid input.\n");
        flush_stdin();
        return;
    }
    printf("Enter right endpoint b: ");
    if (scanf("%lf", &b) != 1) {
        printf("Invalid input.\n");
        flush_stdin();
        return;
    }
    flush_stdin();

    if (a >= b) {
        printf("Error: must have a < b.\n");
        return;
    }

    double fa = poly_f(a, A, B, C, D);
    double fb = poly_f(b, A, B, C, D);
    if (fa * fb > 0.0) {
        printf("Error: f(a) and f(b) must have opposite signs.\n");
        printf("f(a) = %.10g, f(b) = %.10g\n", fa, fb);
        return;
    }

    int max_iter;
    double tol;
    printf("Enter tolerance (e.g. 1e-6): ");
    if (scanf("%lf", &tol) != 1 || tol <= 0.0) {
        printf("Invalid tolerance.\n");
        flush_stdin();
        return;
    }
    printf("Enter maximum iterations (e.g. 100): ");
    if (scanf("%d", &max_iter) != 1 || max_iter <= 0) {
        printf("Invalid iteration count.\n");
        flush_stdin();
        return;
    }
    flush_stdin();

    double mid = 0.0;
    double fmid = 0.0;
    int iter;

    for (iter = 1; iter <= max_iter; ++iter) {
        mid = 0.5 * (a + b);
        fmid = poly_f(mid, A, B, C, D);

        // Uncomment the next line if you want to see iteration details
        // printf("Iter %d: a=%.10g, b=%.10g, mid=%.10g, f(mid)=%.10g\n", iter, a, b, mid, fmid);

        if (fabs(fmid) < tol || 0.5 * (b - a) < tol) {
            break;
        }

        if (fa * fmid < 0.0) {
            b = mid;
            fb = fmid;
        } else {
            a = mid;
            fa = fmid;
        }
    }

    printf("Approximate root x ≈ %.10g\n", mid);
    printf("f(x) = %.10g\n", poly_f(mid, A, B, C, D));
    printf("Iterations used: %d\n", iter);
}

// Newton-Raphson method for f(x) = 0
void root_newton_raphson(double A, double B, double C, double D)
{
    printf("\n[Newton-Raphson method tool]\n");
    printf("We solve f(x) = A x^3 + B x^2 + C x + D = 0 using the Newton-Raphson method.\n");
    printf("Using coefficients: A = %.10g, B = %.10g, C = %.10g, D = %.10g\n", A, B, C, D);

    double x0;
    printf("Enter initial guess x0: ");
    if (scanf("%lf", &x0) != 1) {
        printf("Invalid input.\n");
        flush_stdin();
        return;
    }
    flush_stdin();

    double tol;
    int max_iter;
    printf("Enter tolerance (e.g. 1e-6): ");
    if (scanf("%lf", &tol) != 1 || tol <= 0.0) {
        printf("Invalid tolerance.\n");
        flush_stdin();
        return;
    }
    printf("Enter maximum iterations (e.g. 100): ");
    if (scanf("%d", &max_iter) != 1 || max_iter <= 0) {
        printf("Invalid iteration count.\n");
        flush_stdin();
        return;
    }
    flush_stdin();

    double x = x0;
    int iter;
    const double EPS = 1e-12;

    for (iter = 1; iter <= max_iter; ++iter) {
        double fx = poly_f(x, A, B, C, D);
        double dfx = poly_fprime(x, A, B, C, D);

        if (fabs(dfx) < EPS) {
            printf("Derivative too small (near zero) at iteration %d, x = %.10g. Aborting.\n", iter, x);
            break;
        }

        double x_next = x - fx / dfx;

        // Uncomment if you want detailed output
        // printf("Iter %d: x=%.10g, f(x)=%.10g\n", iter, x, fx);

        if (fabs(x_next - x) < tol || fabs(poly_f(x_next, A, B, C, D)) < tol) {
            x = x_next;
            break;
        }

        x = x_next;
    }

    printf("Approximate root x ≈ %.10g\n", x);
    printf("f(x) = %.10g\n", poly_f(x, A, B, C, D));
    printf("Iterations used: %d\n", iter);
}

// Secant method for f(x) = 0
void root_secant(double A, double B, double C, double D)
{
    printf("\n[Secant method tool]\n");
    printf("We solve f(x) = A x^3 + B x^2 + C x + D = 0 using the secant method.\n");
    printf("Using coefficients: A = %.10g, B = %.10g, C = %.10g, D = %.10g\n", A, B, C, D);

    double x0, x1;
    printf("Enter first initial guess x0: ");
    if (scanf("%lf", &x0) != 1) {
        printf("Invalid input.\n");
        flush_stdin();
        return;
    }
    printf("Enter second initial guess x1: ");
    if (scanf("%lf", &x1) != 1) {
        printf("Invalid input.\n");
        flush_stdin();
        return;
    }
    flush_stdin();

    double tol;
    int max_iter;
    printf("Enter tolerance (e.g. 1e-6): ");
    if (scanf("%lf", &tol) != 1 || tol <= 0.0) {
        printf("Invalid tolerance.\n");
        flush_stdin();
        return;
    }
    printf("Enter maximum iterations (e.g. 100): ");
    if (scanf("%d", &max_iter) != 1 || max_iter <= 0) {
        printf("Invalid iteration count.\n");
        flush_stdin();
        return;
    }
    flush_stdin();

    double f0 = poly_f(x0, A, B, C, D);
    double f1 = poly_f(x1, A, B, C, D);
    const double EPS = 1e-12;
    int iter;

    for (iter = 1; iter <= max_iter; ++iter) {
        if (fabs(f1 - f0) < EPS) {
            printf("Denominator too small at iteration %d. Aborting.\n", iter);
            break;
        }

        double x2 = x1 - f1 * (x1 - x0) / (f1 - f0);
        double f2 = poly_f(x2, A, B, C, D);

        // Uncomment for iteration details
        // printf("Iter %d: x0=%.10g, x1=%.10g, x2=%.10g, f(x2)=%.10g\n", iter, x0, x1, x2, f2);

        if (fabs(x2 - x1) < tol || fabs(f2) < tol) {
            x1 = x2;
            f1 = f2;
            break;
        }

        x0 = x1;
        f0 = f1;
        x1 = x2;
        f1 = f2;
    }

    printf("Approximate root x ≈ %.10g\n", x1);
    printf("f(x) = %.10g\n", poly_f(x1, A, B, C, D));
    printf("Iterations used: %d\n", iter);
}

// 5) Geometry & shapes

void geo_circle(void)
{
    printf("\n[Circle geometry tool]\n");
    printf("Compute area and circumference of a circle from radius r.\n");

    double r;
    printf("Enter radius r (> 0): ");
    if (scanf("%lf", &r) != 1) {
        printf("Invalid input.\n");
        flush_stdin();
        return;
    }
    flush_stdin();

    if (r <= 0.0) {
        printf("Error: radius must be > 0.\n");
        return;
    }

    double area = MY_PI * r * r;
    double circ = 2.0 * MY_PI * r;

    printf("Area          = %.10g\n", area);
    printf("Circumference = %.10g\n", circ);
}

void geo_rectangle(void)
{
    printf("\n[Rectangle geometry tool]\n");
    printf("Compute area and perimeter of a rectangle.\n");

    double w, h;
    printf("Enter width  (> 0): ");
    if (scanf("%lf", &w) != 1) {
        printf("Invalid input.\n");
        flush_stdin();
        return;
    }
    printf("Enter height (> 0): ");
    if (scanf("%lf", &h) != 1) {
        printf("Invalid input.\n");
        flush_stdin();
        return;
    }
    flush_stdin();

    if (w <= 0.0 || h <= 0.0) {
        printf("Error: width and height must be > 0.\n");
        return;
    }

    double area = w * h;
    double per  = 2.0 * (w + h);

    printf("Area      = %.10g\n", area);
    printf("Perimeter = %.10g\n", per);
}

void geo_triangle(void)
{
    printf("\n[Triangle geometry tool]\n");
    printf("Compute area and (approximate) perimeter of a right triangle\n");
    printf("from base and height (treated as the two perpendicular legs).\n");

    double base, height;
    printf("Enter base  (> 0): ");
    if (scanf("%lf", &base) != 1) {
        printf("Invalid input.\n");
        flush_stdin();
        return;
    }
    printf("Enter height (> 0): ");
    if (scanf("%lf", &height) != 1) {
        printf("Invalid input.\n");
        flush_stdin();
        return;
    }
    flush_stdin();

    if (base <= 0.0 || height <= 0.0) {
        printf("Error: base and height must be > 0.\n");
        return;
    }

    double area = 0.5 * base * height;
    double hyp  = sqrt(base * base + height * height);
    double per  = base + height + hyp;

    printf("Assuming a right triangle with base and height as legs.\n");
    printf("Area      = %.10g\n", area);
    printf("Perimeter = %.10g\n", per);
}

void geo_trapezoid(void)
{
    printf("\n[Trapezoid geometry tool]\n");
    printf("Compute area and perimeter of an isosceles trapezoid\n");
    printf("from bases b1, b2 and height h.\n");

    double b1, b2, h;
    printf("Enter base b1 (> 0): ");
    if (scanf("%lf", &b1) != 1) {
        printf("Invalid input.\n");
        flush_stdin();
        return;
    }
    printf("Enter base b2 (> 0): ");
    if (scanf("%lf", &b2) != 1) {
        printf("Invalid input.\n");
        flush_stdin();
        return;
    }
    printf("Enter height h (> 0): ");
    if (scanf("%lf", &h) != 1) {
        printf("Invalid input.\n");
        flush_stdin();
        return;
    }
    flush_stdin();

    if (b1 <= 0.0 || b2 <= 0.0 || h <= 0.0) {
        printf("Error: bases and height must be > 0.\n");
        return;
    }

    double area = 0.5 * (b1 + b2) * h;

    // Assume isosceles trapezoid: two equal non-parallel sides
    double diff = 0.5 * fabs(b1 - b2);
    double leg  = sqrt(h * h + diff * diff);
    double per  = b1 + b2 + 2.0 * leg;

    printf("Assuming an isosceles trapezoid.\n");
    printf("Area      = %.10g\n", area);
    printf("Perimeter = %.10g\n", per);
}

void geo_sphere(void)
{
    printf("\n[Sphere geometry tool]\n");
    printf("Compute surface area and volume of a sphere from radius r.\n");

    double r;
    printf("Enter radius r (> 0): ");
    if (scanf("%lf", &r) != 1) {
        printf("Invalid input.\n");
        flush_stdin();
        return;
    }
    flush_stdin();

    if (r <= 0.0) {
        printf("Error: radius must be > 0.\n");
        return;
    }

    double area = 4.0 * MY_PI * r * r;
    double vol  = (4.0 / 3.0) * MY_PI * r * r * r;

    printf("Surface area = %.10g\n", area);
    printf("Volume       = %.10g\n", vol);
}

void geo_cylinder(void)
{
    printf("\n[Cylinder geometry tool]\n");
    printf("Compute surface area and volume of a cylinder.\n");

    double r, h;
    printf("Enter radius r (> 0): ");
    if (scanf("%lf", &r) != 1) {
        printf("Invalid input.\n");
        flush_stdin();
        return;
    }
    printf("Enter height h (> 0): ");
    if (scanf("%lf", &h) != 1) {
        printf("Invalid input.\n");
        flush_stdin();
        return;
    }
    flush_stdin();

    if (r <= 0.0 || h <= 0.0) {
        printf("Error: radius and height must be > 0.\n");
        return;
    }

    double base_area = MY_PI * r * r;
    double lateral   = 2.0 * MY_PI * r * h;
    double area      = 2.0 * base_area + lateral;
    double vol       = base_area * h;

    printf("Surface area = %.10g\n", area);
    printf("Volume       = %.10g\n", vol);
}

void geo_cone(void)
{
    printf("\n[Cone geometry tool]\n");
    printf("Compute surface area and volume of a right circular cone.\n");

    double r, h;
    printf("Enter radius r (> 0): ");
    if (scanf("%lf", &r) != 1) {
        printf("Invalid input.\n");
        flush_stdin();
        return;
    }
    printf("Enter height h (> 0): ");
    if (scanf("%lf", &h) != 1) {
        printf("Invalid input.\n");
        flush_stdin();
        return;
    }
    flush_stdin();

    if (r <= 0.0 || h <= 0.0) {
        printf("Error: radius and height must be > 0.\n");
        return;
    }

    double slant = sqrt(r * r + h * h);
    double base_area = MY_PI * r * r;
    double lateral   = MY_PI * r * slant;
    double area      = base_area + lateral;
    double vol       = (1.0 / 3.0) * base_area * h;

    printf("Surface area = %.10g\n", area);
    printf("Volume       = %.10g\n", vol);
}

void geo_box(void)
{
    printf("\n[Box / rectangular prism geometry tool]\n");
    printf("Compute surface area and volume of a box (rectangular prism).\n");

    double l, w, h;
    printf("Enter length l (> 0): ");
    if (scanf("%lf", &l) != 1) {
        printf("Invalid input.\n");
        flush_stdin();
        return;
    }
    printf("Enter width  w (> 0): ");
    if (scanf("%lf", &w) != 1) {
        printf("Invalid input.\n");
        flush_stdin();
        return;
    }
    printf("Enter height h (> 0): ");
    if (scanf("%lf", &h) != 1) {
        printf("Invalid input.\n");
        flush_stdin();
        return;
    }
    flush_stdin();

    if (l <= 0.0 || w <= 0.0 || h <= 0.0) {
        printf("Error: length, width, and height must be > 0.\n");
        return;
    }

    double area = 2.0 * (l * w + l * h + w * h);
    double vol  = l * w * h;

    printf("Surface area = %.10g\n", area);
    printf("Volume       = %.10g\n", vol);
}

void geo_two_point_distance(void)
{
    printf("\n[Two-point distance tool]\n");
    printf("Compute the distance between two points in 2D or 3D.\n");

    int dim;
    printf("Enter dimension (2 or 3): ");
    if (scanf("%d", &dim) != 1) {
        printf("Invalid input.\n");
        flush_stdin();
        return;
    }

    if (dim != 2 && dim != 3) {
        printf("Error: dimension must be 2 or 3.\n");
        flush_stdin();
        return;
    }

    double x1, y1, z1 = 0.0;
    double x2, y2, z2 = 0.0;

    if (dim == 2) {
        printf("Enter point P1 (x1 y1): ");
        if (scanf("%lf %lf", &x1, &y1) != 2) {
            printf("Invalid input.\n");
            flush_stdin();
            return;
        }
        printf("Enter point P2 (x2 y2): ");
        if (scanf("%lf %lf", &x2, &y2) != 2) {
            printf("Invalid input.\n");
            flush_stdin();
            return;
        }
    } else { // dim == 3
        printf("Enter point P1 (x1 y1 z1): ");
        if (scanf("%lf %lf %lf", &x1, &y1, &z1) != 3) {
            printf("Invalid input.\n");
            flush_stdin();
            return;
        }
        printf("Enter point P2 (x2 y2 z2): ");
        if (scanf("%lf %lf %lf", &x2, &y2, &z2) != 3) {
            printf("Invalid input.\n");
            flush_stdin();
            return;
        }
    }
    flush_stdin();

    double dx = x2 - x1;
    double dy = y2 - y1;
    double dz = z2 - z1;
    double dist = sqrt(dx * dx + dy * dy + dz * dz);

    printf("Distance = %.10g\n", dist);
}

void geo_vector_length(void)
{
    printf("\n[Vector length tool]\n");
    printf("Compute the magnitude of a vector in 2D or 3D.\n");

    int dim;
    printf("Enter dimension (2 or 3): ");
    if (scanf("%d", &dim) != 1) {
        printf("Invalid input.\n");
        flush_stdin();
        return;
    }

    if (dim != 2 && dim != 3) {
        printf("Error: dimension must be 2 or 3.\n");
        flush_stdin();
        return;
    }

    double vx, vy, vz = 0.0;
    if (dim == 2) {
        printf("Enter vector components (vx vy): ");
        if (scanf("%lf %lf", &vx, &vy) != 2) {
            printf("Invalid input.\n");
            flush_stdin();
            return;
        }
    } else { // 3D
        printf("Enter vector components (vx vy vz): ");
        if (scanf("%lf %lf %lf", &vx, &vy, &vz) != 3) {
            printf("Invalid input.\n");
            flush_stdin();
            return;
        }
    }
    flush_stdin();

    double len = sqrt(vx * vx + vy * vy + vz * vz);
    printf("Vector length = %.10g\n", len);
}

void geo_point_line_distance(void)
{
    printf("\n[Point-to-line distance tool]\n");
    printf("Compute distance from a point (x0, y0) to a line Ax + By + C = 0 in 2D.\n");

    double A, B, C;
    printf("Enter line coefficients A, B, C (for Ax + By + C = 0): ");
    if (scanf("%lf %lf %lf", &A, &B, &C) != 3) {
        printf("Invalid input.\n");
        flush_stdin();
        return;
    }

    if (fabs(A) < 1e-12 && fabs(B) < 1e-12) {
        printf("Error: A and B cannot both be zero (invalid line).\n");
        flush_stdin();
        return;
    }

    double x0, y0;
    printf("Enter point coordinates x0, y0: ");
    if (scanf("%lf %lf", &x0, &y0) != 2) {
        printf("Invalid input.\n");
        flush_stdin();
        return;
    }
    flush_stdin();

    double num = fabs(A * x0 + B * y0 + C);
    double den = sqrt(A * A + B * B);
    double dist = num / den;

    printf("Distance from point to line = %.10g\n", dist);
}

// 6) Complex numbers / phasors

void cx_basic_operations(void)
{
    printf("\n[Basic complex operations tool]\n");
    printf("You can enter expressions with complex numbers using +, -, *, / and parentheses.\n");
    printf("Use 'j' as the imaginary unit, e.g. (1+2j) - 2 + 2*(3.5-6j)\n");
    printf("Real numbers are also allowed (they are treated as having zero imaginary part).\n\n");

    char line[256];
    printf("Enter complex expression: ");
    if (!fgets(line, sizeof(line), stdin)) {
        printf("Input error.\n");
        return;
    }

    cexpr_p = line;
    Complex result = cparse_expression();
    cskip_spaces();
    if (*cexpr_p != '\0' && *cexpr_p != '\n') {
        printf("Warning: unexpected input at: \"%s\"\n", cexpr_p);
    }

    printf("Result = %.10g %c %.10gj\n",
           result.re,
           (result.im < 0.0 ? '-' : '+'),
           fabs(result.im));
}

void cx_cartesian_polar_convert(void)
{
    printf("\n[Cartesian <-> polar conversion tool]\n");
    printf("1) Cartesian -> polar   (x + jy  ->  r, theta)\n");
    printf("2) Polar -> Cartesian   (r, theta -> x + jy)\n");
    printf("Select mode: ");

    int mode;
    if (scanf("%d", &mode) != 1) {
        printf("Invalid input.\n");
        flush_stdin();
        return;
    }
    flush_stdin();

    if (mode == 1) {
        double x, y;
        printf("Enter Cartesian components x and y (for z = x + jy): ");
        if (scanf("%lf %lf", &x, &y) != 2) {
            printf("Invalid input.\n");
            flush_stdin();
            return;
        }
        flush_stdin();

        double r = sqrt(x * x + y * y);
        double theta = atan2(y, x);
        double theta_deg = theta * 180.0 / MY_PI;

        printf("Magnitude r           = %.10g\n", r);
        printf("Phase angle (radians) = %.10g\n", theta);
        printf("Phase angle (degrees) = %.10g\n", theta_deg);
    } else if (mode == 2) {
        double r, theta;
        int angle_mode;

        printf("Enter magnitude r (>= 0): ");
        if (scanf("%lf", &r) != 1) {
            printf("Invalid input.\n");
            flush_stdin();
            return;
        }
        printf("Enter angle theta: ");
        if (scanf("%lf", &theta) != 1) {
            printf("Invalid input.\n");
            flush_stdin();
            return;
        }
        printf("Angle input mode:\n");
        printf(" 1) Degrees\n");
        printf(" 2) Radians\n");
        printf("Choice: ");
        if (scanf("%d", &angle_mode) != 1) {
            printf("Invalid input.\n");
            flush_stdin();
            return;
        }
        flush_stdin();

        if (r < 0.0) {
            printf("Warning: negative magnitude, using |r| instead.\n");
            r = fabs(r);
        }

        if (angle_mode == 1) {
            theta = theta * MY_PI / 180.0;
        }

        double x = r * cos(theta);
        double y = r * sin(theta);

        printf("Cartesian form: x = %.10g, y = %.10g\n", x, y);
        printf("Complex form:   z = %.10g %c %.10gj\n",
               x,
               (y < 0.0 ? '-' : '+'),
               fabs(y));
    } else {
        printf("Invalid mode.\n");
    }
}

void cx_magnitude_phase(void)
{
    printf("\n[Magnitude and phase tool]\n");
    printf("Enter a complex number z in the form a + bj (you may also use parentheses and operations):\n");
    printf("z = ");

    char line[256];
    if (!fgets(line, sizeof(line), stdin)) {
        printf("Input error.\n");
        return;
    }

    cexpr_p = line;
    Complex z = cparse_expression();
    cskip_spaces();
    if (*cexpr_p != '\0' && *cexpr_p != '\n') {
        printf("Warning: unexpected input at: \"%s\"\n", cexpr_p);
    }

    double r = sqrt(z.re * z.re + z.im * z.im);
    double theta = atan2(z.im, z.re);
    double theta_deg = theta * 180.0 / MY_PI;

    printf("z = %.10g %c %.10gj\n",
           z.re,
           (z.im < 0.0 ? '-' : '+'),
           fabs(z.im));
    printf("Magnitude |z|        = %.10g\n", r);
    printf("Phase (radians)      = %.10g\n", theta);
    printf("Phase (degrees)      = %.10g\n", theta_deg);
}


static Complex c_make(double re, double im)
{
    Complex z;
    z.re = re;
    z.im = im;
    return z;
}

static Complex c_add(Complex a, Complex b)
{
    return c_make(a.re + b.re, a.im + b.im);
}

static Complex c_sub(Complex a, Complex b)
{
    return c_make(a.re - b.re, a.im - b.im);
}

static Complex c_mul(Complex a, Complex b)
{
    // (a + jb)*(c + jd) = (ac - bd) + j(ad + bc)
    double re = a.re * b.re - a.im * b.im;
    double im = a.re * b.im + a.im * b.re;
    return c_make(re, im);
}

static Complex c_div(Complex a, Complex b)
{
    double denom = b.re * b.re + b.im * b.im;
    if (denom == 0.0) {
        printf("Warning: division by zero in complex expression, returning 0.\n");
        return c_make(0.0, 0.0);
    }
    double re = (a.re * b.re + a.im * b.im) / denom;
    double im = (a.im * b.re - a.re * b.im) / denom;
    return c_make(re, im);
}

static void cskip_spaces(void)
{
    while (*cexpr_p == ' ' || *cexpr_p == '\t') {
        cexpr_p++;
    }
}

static Complex cparse_number(void)
{
    cskip_spaces();
    char *endptr;
    double value = strtod(cexpr_p, &endptr);
    if (endptr == cexpr_p) {
        printf("Error: expected number at \"%s\"\n", cexpr_p);
        return c_make(0.0, 0.0);
    }
    cexpr_p = endptr;

    // Optional 'j' or 'J' suffix indicates pure imaginary number
    if (*cexpr_p == 'j' || *cexpr_p == 'J') {
        cexpr_p++;
        return c_make(0.0, value);
    } else {
        return c_make(value, 0.0);
    }
}

static Complex cparse_factor(void)
{
    cskip_spaces();

    // unary + or -
    if (*cexpr_p == '+') {
        cexpr_p++;
        return cparse_factor();
    } else if (*cexpr_p == '-') {
        cexpr_p++;
        Complex z = cparse_factor();
        z.re = -z.re;
        z.im = -z.im;
        return z;
    }

    // Parenthesised expression
    if (*cexpr_p == '(') {
        cexpr_p++; // skip '('
        Complex val = cparse_expression();
        cskip_spaces();
        if (*cexpr_p == ')') {
            cexpr_p++;
        } else {
            printf("Error: missing ')' in complex expression\n");
        }
        return val;
    }

    // Imaginary unit alone: j or J => 0 + 1j
    if (*cexpr_p == 'j' || *cexpr_p == 'J') {
        cexpr_p++;
        return c_make(0.0, 1.0);
    }

    // Constants like pi, e (treated as real constants)
    if (isalpha((unsigned char)*cexpr_p)) {
        char name[16];
        int i = 0;
        while (isalpha((unsigned char)*cexpr_p) && i < (int)sizeof(name) - 1) {
            name[i++] = (char)tolower((unsigned char)*cexpr_p);
            cexpr_p++;
        }
        name[i] = '\0';

        if (strcmp(name, "pi") == 0) {
            return c_make(MY_PI, 0.0);
        }
        if (strcmp(name, "e") == 0) {
            return c_make(MY_E, 0.0);
        }

        printf("Error: unknown identifier \"%s\" in complex expression\n", name);
        return c_make(0.0, 0.0);
    }

    // Numeric literal (possibly with trailing j)
    return cparse_number();
}

static Complex cparse_term(void)
{
    Complex value = cparse_factor();
    while (1) {
        cskip_spaces();
        if (*cexpr_p == '*') {
            cexpr_p++;
            Complex rhs = cparse_factor();
            value = c_mul(value, rhs);
        } else if (*cexpr_p == '/') {
            cexpr_p++;
            Complex rhs = cparse_factor();
            value = c_div(value, rhs);
        } else {
            break;
        }
    }
    return value;
}

static Complex cparse_expression(void)
{
    Complex value = cparse_term();
    while (1) {
        cskip_spaces();
        if (*cexpr_p == '+') {
            cexpr_p++;
            Complex rhs = cparse_term();
            value = c_add(value, rhs);
        } else if (*cexpr_p == '-') {
            cexpr_p++;
            Complex rhs = cparse_term();
            value = c_sub(value, rhs);
        } else {
            break;
        }
    }
    return value;
}

// ============================
// Internal expression parser helpers
// ============================

static void skip_spaces(void)
{
    while (*expr_p == ' ' || *expr_p == '\t') {
        expr_p++;
    }
}

static double parse_number(void)
{
    skip_spaces();
    char *endptr;
    double value = strtod(expr_p, &endptr);
    if (endptr == expr_p) {
        printf("Error: expected number at \"%s\"\n", expr_p);
        return 0.0;
    }
    expr_p = endptr;
    return value;
}

static double parse_factor(void)
{
    skip_spaces();

    // unary + or -
    if (*expr_p == '+') {
        expr_p++;
        return parse_factor();
    } else if (*expr_p == '-') {
        expr_p++;
        return -parse_factor();
    }

    // Parenthesised expression
    if (*expr_p == '(') {
        expr_p++;
        double val = parse_expression();
        skip_spaces();
        if (*expr_p == ')') {
            expr_p++;
        } else {
            printf("Error: missing ')'\n");
        }
        return val;
    }

    // Function or constant name
    if (isalpha((unsigned char)*expr_p)) {
        char name[16];
        int i = 0;
        while (isalpha((unsigned char)*expr_p) && i < (int)sizeof(name) - 1) {
            name[i++] = (char)tolower((unsigned char)*expr_p);
            expr_p++;
        }
        name[i] = '\0';

        if (strcmp(name, "pi") == 0) {
            return MY_PI;
        }
        if (strcmp(name, "e") == 0) {
            return MY_E;
        }

        skip_spaces();
        if (*expr_p != '(') {
            printf("Error: expected '(' after function name \"%s\"\n", name);
            return 0.0;
        }
        expr_p++; // skip '('
        double arg = parse_expression();
        skip_spaces();
        if (*expr_p == ')') {
            expr_p++;
        } else {
            printf("Error: missing ')' after function argument\n");
        }

        if (strcmp(name, "sin") == 0)   return sin(arg);
        if (strcmp(name, "cos") == 0)   return cos(arg);
        if (strcmp(name, "tan") == 0)   return tan(arg);
        if (strcmp(name, "asin") == 0)  return asin(arg);
        if (strcmp(name, "acos") == 0)  return acos(arg);
        if (strcmp(name, "atan") == 0)  return atan(arg);
        if (strcmp(name, "ln") == 0)    return log(arg);
        if (strcmp(name, "log10") == 0) return log10(arg);

        printf("Error: unknown function \"%s\"\n", name);
        return 0.0;
    }

    // Number
    return parse_number();
}

static double parse_term(void)
{
    double value = parse_factor();
    while (1) {
        skip_spaces();
        if (*expr_p == '*') {
            expr_p++;
            double rhs = parse_factor();
            value *= rhs;
        } else if (*expr_p == '/') {
            expr_p++;
            double rhs = parse_factor();
            value /= rhs;
        } else {
            break;
        }
    }
    return value;
}

static double parse_expression(void)
{
    double value = parse_term();
    while (1) {
        skip_spaces();
        if (*expr_p == '+') {
            expr_p++;
            double rhs = parse_term();
            value += rhs;
        } else if (*expr_p == '-') {
            expr_p++;
            double rhs = parse_term();
            value -= rhs;
        } else {
            break;
        }
    }
    return value;
}
