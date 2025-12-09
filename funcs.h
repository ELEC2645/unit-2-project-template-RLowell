#ifndef FUNCS_H
#define FUNCS_H

// 1) Operations tools
void op_arithmetic(void);
void op_power_root(void);
void op_trigonometry(void);
void op_logarithms(void);

// 2) Linear algebra tools
void la_matrix_operations(void);
void la_solve_linear_system(void);
void la_determinant(void);

// 3) Statistics tools (operate on arbitrary-length datasets)
void stat_mean_variance_std(void);
void stat_min_max(void);
void stat_normalise_0_1(void);

// 4) Root-finding tools
void root_bisection(double A, double B, double C, double D);
void root_newton_raphson(double A, double B, double C, double D);
void root_secant(double A, double B, double C, double D);

// 5) Geometry & shapes tools
void geo_circle(void);
void geo_rectangle(void);
void geo_triangle(void);
void geo_trapezoid(void);
void geo_sphere(void);
void geo_cylinder(void);
void geo_cone(void);
void geo_box(void);
void geo_two_point_distance(void);
void geo_vector_length(void);
void geo_point_line_distance(void);

// 6) Complex numbers / phasors tools
void cx_basic_operations(void);
void cx_cartesian_polar_convert(void);
void cx_magnitude_phase(void);

#endif // !FUNCS_H
