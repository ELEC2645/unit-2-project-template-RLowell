#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "funcs.h"


// =============================
// Function prototypes
// =============================

// Top-level control
void run_main_menu(void);

// Menu printers
void print_main_menu(void);
void print_operations_menu(void);
void print_linear_algebra_menu(void);
void print_statistics_menu(void);
void print_root_finder_menu(void);
void print_geometry_menu(void);
void print_geometry_2d_menu(void);
void print_geometry_3d_menu(void);
void print_geometry_coord_menu(void);
void print_complex_menu(void);

// Menu handlers
void handle_main_selection(int choice);
void handle_operations_selection(int choice);
void handle_linear_algebra_selection(int choice);
void handle_statistics_selection(int choice);
void handle_root_selection(int choice, double A, double B, double C, double D);
void handle_geometry_selection(int choice);
void handle_geometry_2d_selection(int choice);
void handle_geometry_3d_selection(int choice);
void handle_geometry_coord_selection(int choice);
void handle_complex_selection(int choice);

// Input helper
int get_int_in_range(const char *prompt, int min, int max);

int main(void)
{
    run_main_menu();
    return 0;
}


// =============================
// Main menu loop
// =============================

void run_main_menu(void)
{
    int choice;
    do {
        print_main_menu();
        choice = get_int_in_range("Select option: ", 0, 6);
        handle_main_selection(choice);
    } while (choice != 0); // 0 = exit
}


// =============================
// Menu printing functions
// =============================

void print_main_menu(void)
{
    printf("\n========== MATH TOOLKIT =========\n");
    printf(" 1) Operations (arithmetic / trig / logs / powers)\n");
    printf(" 2) Linear algebra (matrices / linear systems)\n");
    printf(" 3) Basic statistics\n");
    printf(" 4) Root-finding methods\n");
    printf(" 5) Geometry & shapes\n");
    printf(" 6) Complex numbers / phasors\n");
    printf(" 0) Exit\n");
    printf("=================================\n");
}

void print_operations_menu(void)
{
    printf("\n-------- Operations menu --------\n");
    printf(" 1) Arithmetic expression calculator\n");
    printf(" 2) Powers & roots\n");
    printf(" 3) Trigonometric & inverse trigonometric functions\n");
    printf(" 4) Logarithms (general base)\n");
    printf(" 0) Back to main menu\n");
    printf("---------------------------------\n");
}

void print_linear_algebra_menu(void)
{
    printf("\n------ Linear algebra menu ------\n");
    printf(" 1) Matrix operations (add / subtract / multiply, up to 3x3)\n");
    printf(" 2) Solve linear system (up to 3x3)\n");
    printf(" 3) Determinant of a matrix (1x1–3x3)\n");
    printf(" 0) Back to main menu\n");
    printf("---------------------------------\n");
}

void print_statistics_menu(void)
{
    printf("\n------ Basic statistics menu -----\n");
    printf(" 1) Mean / variance / std dev (dataset)\n");
    printf(" 2) Minimum and maximum (dataset)\n");
    printf(" 3) Normalisation to [0, 1] (dataset)\n");
    printf(" 0) Back to main menu\n");
    printf("----------------------------------\n");
}

void print_root_finder_menu(void)
{
    printf("\n------- Root finder menu --------\n");
    printf(" 1) Bisection method\n");
    printf(" 2) Newton-Raphson method\n");
    printf(" 3) Secant method\n");
    printf(" 0) Back to main menu\n");
    printf("---------------------------------\n");
}

void print_geometry_menu(void)
{
    printf("\n------ Geometry & shapes menu ----\n");
    printf(" 1) 2D Shapes (area & perimeter)\n");
    printf(" 2) 3D Geometry (surface area & volume)\n");
    printf(" 3) Coordinate geometry\n");
    printf(" 0) Back to main menu\n");
    printf("----------------------------------\n");
}

void print_geometry_2d_menu(void)
{
    printf("\n------ 2D Shapes menu -----------\n");
    printf(" 1) Circle (area & circumference)\n");
    printf(" 2) Rectangle (area & perimeter)\n");
    printf(" 3) Triangle (area & perimeter)\n");
    printf(" 4) Trapezoid (area & perimeter)\n");
    printf(" 0) Back to Geometry menu\n");
    printf("---------------------------------\n");
}

void print_geometry_3d_menu(void)
{
    printf("\n------ 3D Geometry menu ---------\n");
    printf(" 1) Sphere (surface area & volume)\n");
    printf(" 2) Cylinder (surface area & volume)\n");
    printf(" 3) Cone (surface area & volume)\n");
    printf(" 4) Box / rectangular prism (surface area & volume)\n");
    printf(" 0) Back to Geometry menu\n");
    printf("---------------------------------\n");
}

void print_geometry_coord_menu(void)
{
    printf("\n------ Coordinate geometry menu --\n");
    printf(" 1) Distance between two points\n");
    printf(" 2) Vector length\n");
    printf(" 3) Distance from point to line (2D)\n");
    printf(" 0) Back to Geometry menu\n");
    printf("---------------------------------\n");
}

void print_complex_menu(void)
{
    printf("\n--- Complex numbers / phasors menu ---\n");
    printf(" 1) Basic complex operations (expression calculator)\n");
    printf(" 2) Cartesian <-> polar conversion\n");
    printf(" 3) Magnitude and phase\n");
    printf(" 0) Back to main menu\n");
    printf("-------------------------------------\n");
}


// =============================
// Menu handlers
// =============================

void handle_main_selection(int choice)
{
    switch (choice) {
    case 1: {
        int sub_choice;
        do {
            print_operations_menu();
            sub_choice = get_int_in_range("Select operations tool: ", 0, 4);
            handle_operations_selection(sub_choice);
        } while (sub_choice != 0);
        break;
    }
    case 2: {
        int sub_choice;
        do {
            print_linear_algebra_menu();
            sub_choice = get_int_in_range("Select linear algebra tool: ", 0, 3);
            handle_linear_algebra_selection(sub_choice);
        } while (sub_choice != 0);
        break;
    }
    case 3: {
        int sub_choice;
        do {
            print_statistics_menu();
            sub_choice = get_int_in_range("Select statistics tool: ", 0, 3);
            handle_statistics_selection(sub_choice);
        } while (sub_choice != 0);
        break;
    }
    case 4: {
        double A, B, C, D;
        printf("\n[Root-finding for cubic f(x) = A x^3 + B x^2 + C x + D]\n");
        printf("Enter coefficient A: ");
        if (scanf("%lf", &A) != 1) {
            printf("Invalid input.\n");
            int c; while ((c = getchar()) != '\n' && c != EOF) {}
            break;
        }
        printf("Enter coefficient B: ");
        if (scanf("%lf", &B) != 1) {
            printf("Invalid input.\n");
            int c; while ((c = getchar()) != '\n' && c != EOF) {}
            break;
        }
        printf("Enter coefficient C: ");
        if (scanf("%lf", &C) != 1) {
            printf("Invalid input.\n");
            int c; while ((c = getchar()) != '\n' && c != EOF) {}
            break;
        }
        printf("Enter coefficient D: ");
        if (scanf("%lf", &D) != 1) {
            printf("Invalid input.\n");
            int c; while ((c = getchar()) != '\n' && c != EOF) {}
            break;
        }
        int c; while ((c = getchar()) != '\n' && c != EOF) {}

        int sub_choice;
        do {
            print_root_finder_menu();
            sub_choice = get_int_in_range("Select root-finding method: ", 0, 3);
            handle_root_selection(sub_choice, A, B, C, D);
        } while (sub_choice != 0);
        break;
    }
    case 5: {
        int sub_choice;
        do {
            print_geometry_menu();
            sub_choice = get_int_in_range("Select geometry category: ", 0, 3);
            handle_geometry_selection(sub_choice);
        } while (sub_choice != 0);
        break;
    }
    case 6: {
        int sub_choice;
        do {
            print_complex_menu();
            sub_choice = get_int_in_range("Select complex-number tool: ", 0, 3);
            handle_complex_selection(sub_choice);
        } while (sub_choice != 0);
        break;
    }
    case 0:
        printf("\nExiting... Goodbye!\n");
        break;
    default:
        // Should not happen because get_int_in_range enforces range
        printf("Unknown option.\n");
        break;
    }
}

void handle_operations_selection(int choice)
{
    switch (choice) {
    case 1:
        op_arithmetic();
        break;
    case 2:
        op_power_root();
        break;
    case 3:
        op_trigonometry();   // handles both trig and inverse trig
        break;
    case 4:
        op_logarithms();
        break;
    case 0:
        // back
        break;
    default:
        printf("Invalid operations menu option.\n");
        break;
    }
}

void handle_linear_algebra_selection(int choice)
{
    switch (choice) {
    case 1:
        la_matrix_operations();
        break;
    case 2:
        la_solve_linear_system();
        break;
    case 3:
        la_determinant();
        break;
    case 0:
        break;
    default:
        printf("Invalid linear algebra menu option.\n");
        break;
    }
}

void handle_statistics_selection(int choice)
{
    switch (choice) {
    case 1:
        stat_mean_variance_std();
        break;
    case 2:
        stat_min_max();
        break;
    case 3:
        stat_normalise_0_1();
        break;
    case 0:
        break;
    default:
        printf("Invalid statistics menu option.\n");
        break;
    }
}

void handle_root_selection(int choice, double A, double B, double C, double D)
{
    switch (choice) {
    case 1:
        root_bisection(A, B, C, D);
        break;
    case 2:
        root_newton_raphson(A, B, C, D);
        break;
    case 3:
        root_secant(A, B, C, D);
        break;
    case 0:
        // back
        break;
    default:
        printf("Invalid root finder menu option.\n");
        break;
    }
}

void handle_geometry_selection(int choice)
{
    switch (choice) {
    case 1: {
        int sub_choice;
        do {
            print_geometry_2d_menu();
            sub_choice = get_int_in_range("Select 2D shape: ", 0, 4);
            handle_geometry_2d_selection(sub_choice);
        } while (sub_choice != 0);
        break;
    }
    case 2: {
        int sub_choice;
        do {
            print_geometry_3d_menu();
            sub_choice = get_int_in_range("Select 3D shape: ", 0, 4);
            handle_geometry_3d_selection(sub_choice);
        } while (sub_choice != 0);
        break;
    }
    case 3: {
        int sub_choice;
        do {
            print_geometry_coord_menu();
            sub_choice = get_int_in_range("Select coordinate geometry tool: ", 0, 3);
            handle_geometry_coord_selection(sub_choice);
        } while (sub_choice != 0);
        break;
    }
    case 0:
        // back
        break;
    default:
        printf("Invalid geometry menu option.\n");
        break;
    }
}

void handle_geometry_2d_selection(int choice)
{
    switch (choice) {
    case 1:
        geo_circle();
        break;
    case 2:
        geo_rectangle();
        break;
    case 3:
        geo_triangle();
        break;
    case 4:
        geo_trapezoid();
        break;
    case 0:
        // back
        break;
    default:
        printf("Invalid 2D geometry menu option.\n");
        break;
    }
}

void handle_geometry_3d_selection(int choice)
{
    switch (choice) {
    case 1:
        geo_sphere();
        break;
    case 2:
        geo_cylinder();
        break;
    case 3:
        geo_cone();
        break;
    case 4:
        geo_box();
        break;
    case 0:
        // back
        break;
    default:
        printf("Invalid 3D geometry menu option.\n");
        break;
    }
}

void handle_geometry_coord_selection(int choice)
{
    switch (choice) {
    case 1:
        geo_two_point_distance();
        break;
    case 2:
        geo_vector_length();
        break;
    case 3:
        geo_point_line_distance();
        break;
    case 0:
        // back
        break;
    default:
        printf("Invalid coordinate geometry menu option.\n");
        break;
    }
}

void handle_complex_selection(int choice)
{
    switch (choice) {
    case 1:
        cx_basic_operations();
        break;
    case 2:
        cx_cartesian_polar_convert();
        break;
    case 3:
        cx_magnitude_phase();
        break;
    case 0:
        break;
    default:
        printf("Invalid complex-number menu option.\n");
        break;
    }
}


// =============================
// Input helper
// =============================

int get_int_in_range(const char *prompt, int min, int max)
{
    int value;
    int result;

    while (1) {
        printf("%s", prompt);
        result = scanf("%d", &value);

        if (result != 1) {
            // invalid input, clear buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {
                // discard
            }
            printf("Invalid input, please enter an integer.\n");
            continue;
        }

        if (value < min || value > max) {
            printf("Please enter a value between %d and %d.\n", min, max);
            continue;
        }

        // consume leftover newline if present
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
            // discard
        }

        return value;
    }
}
