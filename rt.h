#ifndef RT_H
#define RT_H

namespace rt {

	struct tuple {
		double x, y, z, w; 
	};

	bool is_point(tuple const& t) {
		return t.w == 1.0;
	}
	bool is_vector(tuple const& t) {
		return t.w == 0.0;
	}
}

#endif
