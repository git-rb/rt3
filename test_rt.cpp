
#include "rt.h"
#include "simtest.h"


int main() {
	using namespace rt;
	using namespace simtest;


	// tuples, vectors and points
	//
	test("A tuple with w=1.0 is a point", [] {
			auto a = tuple {4.3, -4.2, 3.1, 1.0};
			check(a.x == 4.3);
			check(a.y == -4.2);
			check(a.z == 3.1);
			check(a.w == 1.0);
			check(is_point(a));
		});

	test("a tuple with w=0.0 is a vector", [] {
			auto a = tuple {4.3, -4.2, 3.1, 0.0};
			check(is_vector(a));
		});

	test("point() creates tuples with w=1.0", [] {
			auto p = point(4, -4, 3);
			check(p == tuple {4, -4, 3, 1});
		});

	test("vector() creates tuple with w=0.0", [] {
			auto v = vector(4, -4, 3);
			check(v == tuple {4, -4, 3, 0});
		});


	
	// tuple operations
	//
	test("adding tuples", [] {
			auto t1 = tuple(3, -2, 5, 1);
			auto t2 = tuple(-2, 3, 1, 0);
			check(t1 + t2 == tuple(1, 1, 6, 1));
		});

	test("Subtracting two points", [] {
			auto p1 = point(3, 2, 1);
			auto p2 = point(5, 6, 7);
			check(p1 - p2 == vector(-2, -4, -6));
		});

	test("Subtracting a vector from a point", [] {
			auto p = point(3, 2, 1);
			auto v = vector(5, 6, 7);
			check(p - v == point(-2, -4, -6));
		});
	
	test("Subtracting two vectors", [] {
			auto v1 = vector(3, 2, 1); 
			auto v2 = vector(5, 6, 7);
		});

	test("Subtracting a vector from zero vector", [] {
			auto zero = vector(0, 0, 0);
			auto v = vector(1, -2, 3);
			check(zero - v == vector(-1, 2, -3));
		});

	test("Negating a tuple", [] {
			auto a = tuple {1, -2, 3, -4};
			check(-a == tuple(-1, 2, -3, 4));
		});

	test("Multiplying a tuple by a scalar", [] {
			auto a = tuple(1, -2, 3, -4);
			check(a * 3.5 == tuple(3.5, -7, 10.5, -14));
		});

	test("Multiplying a tuple by a fraction", [] {
			check(tuple{1, -2, 3, -4} * 0.5 == tuple {0.5, -1, 1.5, -2});
		});

	test("Dividing tuple by scalar", [] {
			auto a = tuple {1, -2, 3, -4};
			check(a/2 == tuple {0.5, -1, 1.5, -2});
		});



	// vector operations
	//
	test("Computing magnitude of vector(1, 0, 0)", [] {
			auto v = vector(1, 0, 0);
			check(magnitude(v) == 1.0);
		});

	test("Computing magnitude of vector(0, 1, 0)", [] {
			auto v = vector(0, 1, 0);
			check(magnitude(v) == 1.0);
		});

	test("Computing magnitude of vector(0, 0, 1)", [] {
			auto v = vector(0, 0, 1);
			check(magnitude(v) == 1.0);
		});

	test("Computing magnitude of vector(1, 2, 3)", [] {
			auto v = vector(1, 2, 3);
			check(magnitude(v) == std::sqrt(14));
		});

	test("Computing magnitude of vector(-1, -2, -3)", [] {
			auto v = vector(1, 2, 3);
			check(magnitude(v) == std::sqrt(14));
		});

	test("Normalizing vector (4, 0, 0) gives (1, 0 ,0)", [] {
			auto v = vector(4, 0, 0);
			check(normalize(v) == vector(1, 0, 0));
		});

	test("Normalizing vector (1, 2, 3)", [] {
			auto v = vector(1, 2, 3);
			auto f = std::sqrt(14);
			check(normalize(v) == vector(1 / f, 2 / f, 3 / f));
		});

	test("Magnitude of a normalized vector", [] {
			auto v = vector(1, 2, 3);
			auto norm = normalize(v);
			check(magnitude(norm) == 1);
		});

	test("Dot product of two tuples", [] {
			auto a = vector(1, 2, 3);
			auto b = vector(2, 3, 4);
			check(dot(a, b) == 20);
		});

	test("Cross product of two vectors", [] {
			auto a = vector(1, 2, 3);
			auto b = vector(2, 3, 4);
			check(cross(a, b) == vector(-1, 2, -1));
			check(cross(b, a) == vector(1, -2, 1));
		});



	//colors
	//
	test("Colors are tuples", [] {
			auto c = color {-0.5, 0.4, 1.7};
			check(c.r == -0.5);
			check(c.g == 0.4);
			check(c.b == 1.7);
		});
	test("Adding color", [] {
			auto c1 = color {0.9, 0.6, 0.75};
			auto c2 = color {0.7, 0.1, 0.25};
			check(c1 + c2 == color {1.6, 0.7, 1.0});
			color r = c1 + c2;
			check(r == color {1.6, 0.7, 1.0});
		});
	test("Subtracting colors", [] {
			auto c1 = color {0.9, 0.6, 0.75};
			auto c2 = color {0.7, 0.1, 0.25};
			check(c1 - c2 == color {0.2, 0.5, 0.5});
		});
	test("Multiplying a color by a scalar", [] {
			auto c = color {0.2, 0.3, 0.4};
			check(c * 2 == color {0.4, 0.6, 0.8});
		});
	test("Multiplying a colors", [] {
			auto c1 = color {1, 0.2, 0.4};
			auto c2 = color {0.9, 1, 0.1};
			check(c1 * c2 == color {0.9, 0.2, 0.04});
		});



	//canvas
	//
	test("Creating a canvas", [] {
			auto c = canvas {10, 20};
			check(c.width() == 10);
			check(c.height() == 20);
		});
	test("Writing pixels to a canvas", [] {
			auto c = canvas {10, 20};
			auto red = color {1, 0, 0};
			c.write_pixel(2, 3, red);
			check(c.pixel_at(2, 3) == red);
		});
	test("save canvas", [] {
			auto c = canvas {5, 3};

			auto c1 = color {1.5, 0, 0};
			auto c2 = color {0, 0.5, 0};
			auto c3 = color {-0.5, 0, 1};
			c.write_pixel(0, 0, c1);
			c.write_pixel(2, 1, c2);
			c.write_pixel(4, 2, c3);
			auto ppm = c.to_ppm();

			check(ppm == "P3\n5 3\n255\n255 0 0\n0 0 0\n0 0 0\n0 0 0\n0 0 0\n"
					"0 0 0\n0 0 0\n0 128 0\n0 0 0\n0 0 0\n"
					"0 0 0\n0 0 0\n0 0 0\n0 0 0\n0 0 255\n");
		});
			


	//matrix
	//
	test("constructing a 4x4 matrix", [] {
			auto m = matrix<4,4> 
				{1, 2, 3, 4, 5.5, 6.5, 7.5, 8.5, 9, 10, 11, 12, 13.5, 14.5, 15.5, 16.5};
			check(m[0,0] == 1);
			check(m[0,3] == 4);
			check(m[1,0] == 5.5);
			check(m[1,2] == 7.5);
			check(m[2,2] == 11);
			check(m[3,0] == 13.5);
			check(m[3,2] == 15.5);
		});

	test("2x2 matrix ought to be representable", [] {
			auto m = matrix<2,2>
				{-3, 5, 1, -2};
			check(m[0,0] == -3);
			check(m[0,1] == 5);
			check(m[1,0] == 1);
			check(m[1,1] == -2);
		});

	test("3x3 matrix ought to be representable", [] {
			auto m = matrix<3,3>
				{-3, 5, 0, 1, -2, -7, 0, 1, 1};
			check(m[0,0] == -3);
			check(m[1,1] == -2);
			check(m[2,2] == 1);
		});

	test("Matrix equality with identical matrices", [] {
			auto a = matrix
			{	1, 2, 3, 4,
				5, 6, 7, 8,
				9, 8, 7, 6,
				5, 4, 3, 2 };
			auto b = matrix
			{	1, 2, 3, 4,
				5, 6, 7, 8,
				9, 8, 7, 6,
				5, 4, 3, 2 };
			check(a == b);
		});

	test("Matrix equality with different matrices", [] {
			auto a = matrix
			{	1, 2, 3, 4,
				5, 6, 7, 8,
				9, 8, 7, 6,
				5, 4, 3, 2 };
			auto b = matrix
			{ 2, 3, 4, 5,
			  6, 7, 8, 9,
				8, 7, 6, 5,
				4, 3, 2, 1 };
			check(a != b);
		});

	test("Multiplying two matrices", [] {
			auto a = matrix
			{	1, 2, 3, 4,
				5, 6, 7, 8,
				9, 8, 7, 6,
				5, 4, 3, 2 };
			auto b = matrix
			{	-2, 1, 2, 3,
				3, 2, 1, -1,
				4, 3, 6, 5,
				1, 2, 7, 8 };
			check(a * b == matrix
					{	20, 22, 50, 48,
						44, 54, 114, 108,
						40, 58, 110, 102,
						16, 26, 46, 42 });
		});

	test("Matrix multiplied by a tuple", [] {
			auto a = matrix
			{	1, 2, 3, 4,
				2, 4, 4, 2,
				8, 6, 4, 1,
				0, 0, 0, 1 };
			auto b = tuple {1, 2, 3, 1};
			auto r = a * b;
			check(a * b == tuple {18, 24, 33, 1});
		});

	test("Multiplying a matrix by the identity matrix", [] {
			auto a = matrix 
			{	0, 1, 2, 4,
				1, 2, 4, 8,
				2, 4, 8, 16,
				4, 8, 16, 32 };
			check(a * identity_matrix == a);
		});

	test("Transposing a matrix", [] {
			auto a = matrix
			{	0, 9, 3, 0,
				9, 8, 0, 8,
				1, 8, 5, 3,
				0, 0, 5, 8 };
			check(transpose(a) == matrix
					{	0, 9, 1, 0,
						9, 8, 8, 0,
						3, 0, 5, 5,
						0, 8, 3, 8 });
		});

	test("Transposing the identify matrix", [] {
			check(identity_matrix == transpose(identity_matrix));
		});

	test("Calculating the determinant of a 2x2 matrix", [] {
			auto a = matrix<2,2> {	1, 5, -3, 2};
			check(determinant(a) == 17);
		});


	test("row_view gets a row", [] {
			auto a = matrix<4,4> {
				1, 2, 3, 4,
				5, 6, 7, 8,
				9, 0, -1, -2,
				-3, -4, -5, -6};
			check(a.row_view(2)[0] == 9);
			check(a.row_view(2)[2] == -1);
		});

	test("col_view gets a col", [] {
			auto a = matrix<4,4> {
				1, 2, 3, 4,
				5, 6, 7, 8,
				9, 0, -1, -2,
				-3, -4, -5, -6};
			check(a.col_view(2)[0] == 3);
			check(a.col_view(2)[2] == -1);
		});
	/*
	test("Submatrix of a 3x3 matrix is a 2x2 matrix", [] {
			auto a = matrix<3,3> 
			{	1, 5, 0,
				-3, 2, 7,
				0, 6, -3 };
			auto res = submatrix(a, 0, 2);
			std::cout << res[0,1];
			check(res == matrix<2,2> {-3, 2, 0, 6});
		});
		*/
}
