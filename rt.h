#ifndef RT_H
#define RT_H

#include <cmath>
#include <algorithm>
#include <vector>
#include <sstream>
#include <format>

namespace rt {

	constexpr bool appx_equal(double a, double b) {
		return std::abs(a-b) < 0.00001;
	}

	struct tuple {
		double x, y, z, w; 
	};

	tuple mk_tuple(std::array<double, 4> const& a) {
		return {a[0], a[1], a[2], a[3]};
	}
	std::array<double,4> mk_array(tuple const& a) {
		return {a.x, a.y, a.z, a.w};
	}

	constexpr bool operator== (tuple const& a, tuple const& b) {
		return appx_equal(a.x, b.x) &&
			appx_equal(a.y, b.y) &&
			appx_equal(a.z, b.z) &&
			appx_equal(a.w, b.w);
	}

	constexpr auto operator+ (tuple const& a, tuple const& b) {
		return tuple {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
	}
	constexpr auto operator- (tuple const& a, tuple const& b) {
		return tuple {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
	}
	constexpr auto operator- (tuple const& t) {
		return tuple {-t.x, -t.y, -t.z, -t.w};
	}
	constexpr auto operator* (tuple const& t, double f) {
		return tuple {t.x * f, t.y * f, t.z * f, t.w * f};
	}
	constexpr auto operator/ (tuple const& t, double f) {
		return tuple {t.x / f, t.y / f, t.z / f, t.w / f};
	}

	constexpr bool is_point(tuple const& t) {
		return t.w == 1.0;
	}
	constexpr bool is_vector(tuple const& t) {
		return t.w == 0.0;
	}
	constexpr auto point(double x, double y, double z) {
		return tuple {x,y,z,1.0};
	}
	constexpr auto vector(double x, double y, double z) {
		return tuple {x,y,z,0.0};
	}

	constexpr auto dot(tuple const& a, tuple const& b) {
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}
	constexpr auto magnitude(tuple const& t) {
		return std::sqrt(dot(t,t));
	}
	constexpr auto normalize(tuple const& t) {
		return t / magnitude(t);
	}
	constexpr auto cross(tuple const& a, tuple const& b) {
		return vector(a.y * b.z - a.z * b.y,
				a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x);
	}



	struct color {
		double r, g, b;
	};

	constexpr auto operator== (color const& a, color const& b) {
		return appx_equal(a.r, b.r) &&
			appx_equal(a.g, b.g) &&
			appx_equal(a.b, b.b);
	}
	constexpr auto operator+ (color const& a, color const& b) {
		return color {a.r + b.r, a.g + b.g, a.b + b.b};
	}
	constexpr auto operator- (color const& a, color const& b) {
		return color {a.r - b.r, a.g - b.g, a.b - b.b};
	}
	constexpr auto operator* (color const& c, double f) {
		return color {c.r * f, c.g * f, c.b * f};
	}
	constexpr auto operator* (color const& a, color const& b) {
		return color {a.r * b.r, a.g * b.g, a.b * b.b};
	}


	struct canvas {
		using size_type = std::vector<color>::size_type;

		constexpr canvas(size_type width, size_type height)
			:w {width}, h {height}, pixels {w * h, color {0,0,0}} {}

		constexpr auto width() const { return w; }
		constexpr auto height() const { return h; }

		constexpr void write_pixel(size_type x, size_type y, color c) {
			pixels[y * w + x] = c;
		}
		constexpr auto pixel_at(size_type x, size_type y) const {
			return pixels[y * w + x];
		}

		constexpr auto to_ppm() const {
			std::ostringstream o;
			o << std::format("P3\n{} {}\n255\n", w, h);
			for (auto const& p : pixels)
				o << std::format("{} {} {}\n",
						std::clamp<int>(p.r * 256, 0, 255),
						std::clamp<int>(p.g * 256, 0, 255),
						std::clamp<int>(p.b * 256, 0, 255));
			return o.str();
		}

	private:
		size_type w, h;
		std::vector<color> pixels;
	};


	template <std::size_t rows = 4, std::size_t cols = 4>
	struct matrix {
		constexpr matrix(std::initializer_list<double> l) {
			std::copy_n(l.begin(), std::max(l.size(), vals.size()), vals.begin());
		}
		constexpr matrix() {}

		constexpr double operator[] (std::size_t r, std::size_t c) const { return vals[r * cols + c]; }
		constexpr double& operator[] (std::size_t r, std::size_t c) { return vals[r * cols + c]; }
		constexpr double at_idx(std::size_t idx) const { return vals[idx]; }

	private:
		std::array<double, cols * rows> vals {};

	};

	template <std::size_t rows, std::size_t cols>
	constexpr bool operator== (matrix<rows,cols> const& a, matrix<rows,cols> const& b) {
		for (auto i {0uz}; i < rows * cols; ++i)
			if (!appx_equal(a.at_idx(i), b.at_idx(i))) return false;
		return true;
	}

	template <std::size_t rows, std::size_t cols>
	constexpr tuple operator* (matrix<rows, cols> const& a, tuple const& t) {
		std::array<double, 4> result {};
		auto ts = mk_array(t);
		for (auto r {0uz}; r < rows; ++r) 
			for (auto c {0uz}; c < cols; ++c) 
				result[r] += a[r,c] * ts[c];
		return mk_tuple(result);
	}

	template <std::size_t rows, std::size_t cols>
	constexpr matrix<rows,cols> operator* (matrix<rows,cols> const& a, matrix<rows,cols> const& b) {
		matrix<rows,cols> result {};
		for (auto r {0uz}; r < rows; ++r)
			for (auto c {0uz}; c < cols; ++c)
				for (auto i {0uz}; i < cols; ++i)
					result[r, c] += a[r, i] * b[i, c];
		return result;
	}

	constexpr matrix identity_matrix 
		{ 1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1 };

	template <std::size_t rows, std::size_t cols>
	constexpr auto transpose(matrix<rows, cols> const& m) {
		matrix<cols, rows> res;
		for (auto r {0uz}; r < rows; ++r)
			for (auto c {0uz}; c < cols; ++c)
				res[c, r] = m[r, c];
		return res;
	}
}

#endif
