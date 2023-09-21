#ifndef RT_H
#define RT_H

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

}

#endif
