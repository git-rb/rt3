#ifndef RT_H
#define RT_H

#include <cmath>

namespace rt {

	bool appx_equal(double a, double b) {
		return std::abs(a-b) < 0.00001;
	}

	struct tuple {
		double x, y, z, w; 
	};
	bool operator== (tuple const& a, tuple const& b) {
		return appx_equal(a.x, b.x) &&
			appx_equal(a.y, b.y) &&
			appx_equal(a.z, b.z) &&
			appx_equal(a.w, b.w);
	}

	auto operator+ (tuple const& a, tuple const& b) {
		return tuple {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
	}
	auto operator- (tuple const& a, tuple const& b) {
		return tuple {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
	}
	auto operator- (tuple const& t) {
		return tuple {-t.x, -t.y, -t.z, -t.w};
	}
	auto operator* (tuple const& t, double f) {
		return tuple {t.x * f, t.y * f, t.z * f, t.w * f};
	}
	auto operator/ (tuple const& t, double f) {
		return tuple {t.x / f, t.y / f, t.z / f, t.w / f};
	}

	bool is_point(tuple const& t) {
		return t.w == 1.0;
	}
	bool is_vector(tuple const& t) {
		return t.w == 0.0;
	}
	auto point(double x, double y, double z) {
		return tuple {x,y,z,1.0};
	}
	auto vector(double x, double y, double z) {
		return tuple {x,y,z,0.0};
	}

	auto dot(tuple const& a, tuple const& b) {
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}
	auto magnitude(tuple const& t) {
		return std::sqrt(dot(t,t));
	}
	auto normalize(tuple const& t) {
		return t / magnitude(t);
	}
	auto cross(tuple const& a, tuple const& b) {
		return vector(a.y * b.z - a.z * b.y,
				a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x);
	}



	struct color {
		double r, g, b;
	};

	auto operator== (color const& a, color const& b) {
		return appx_equal(a.r, b.r) &&
			appx_equal(a.g, b.g) &&
			appx_equal(a.b, b.b);
	}
	auto operator+ (color const& a, color const& b) {
		return color {a.r + b.r, a.g + b.g, a.b + b.b};
	}
	auto operator- (color const& a, color const& b) {
		return color {a.r - b.r, a.g - b.g, a.b - b.b};
	}
	auto operator* (color const& c, double f) {
		return color {c.r * f, c.g * f, c.b * f};
	}
	auto operator* (color const& a, color const& b) {
		return color {a.r * b.r, a.g * b.g, a.b * b.b};
	}



}

#endif
