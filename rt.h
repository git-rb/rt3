#ifndef RT_H
#define RT_H

#include <cmath>
#include <algorithm>
#include <vector>
#include <sstream>
#include <format>

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


	struct canvas {
		using size_type = std::vector<color>::size_type;

		canvas(size_type width, size_type height)
			:w {width}, h {height}, pixels {w * h, color {0,0,0}} {}

		auto width() const { return w; }
		auto height() const { return h; }

		void write_pixel(size_type x, size_type y, color c) {
			pixels[y * w + x] = c;
		}
		auto pixel_at(size_type x, size_type y) const {
			return pixels[y * w + x];
		}

		auto to_ppm() const {
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


	template <std::size_t w = 4, std::size_t h = 4>
	struct matrix {
		matrix(std::initializer_list<double> l) {
			auto pl = l.begin();
			for (auto& v : vals)
				v = (pl != l.end()) ? *pl++ : 0.0;
		}

		double operator[] (std::size_t r, std::size_t c) const { return vals[r * w + c]; }
		double& operator[] (std::size_t r, std::size_t c) { return vals[r * w + c]; }

		bool operator== (matrix const& b) const {
			for (auto i {0uz}; i < vals.size(); ++i) 
				if (!appx_equal(vals[i],b.vals[i])) return false;
			return true;
		}

		matrix operator* (matrix const& b) const {
			matrix<w,h> result {};
			for (auto r {0uz}; r < h; ++r)
				for (auto c {0uz}; c < w; ++c)
					for (auto i {0uz}; i < w; ++i)
						result[r, c] += (*this)[r, i] * b[i, c];
			return result;
		}

		tuple operator* (tuple const& t) const {
			std::array<double, 4> result {};
			for (auto r {0uz}; r < h; ++r) {
				result[r] += (*this)[r, 0] * t.x;
				result[r] += (*this)[r, 1] * t.y;
				result[r] += (*this)[r, 2] * t.z;
				result[r] += (*this)[r, 3] * t.w;
			}
			return {result[0], result[1], result[2], result[3]};
		}
	private:
		std::array<double, w * h> vals;

	};


}

#endif
