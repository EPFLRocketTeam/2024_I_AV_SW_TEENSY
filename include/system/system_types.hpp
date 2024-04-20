#ifndef INC_2024_I_AV_TEENSY_SYSTEM_TYPES_HPP
#define INC_2024_I_AV_TEENSY_SYSTEM_TYPES_HPP

#include <cstdint>

typedef uint32_t time_millis_t;

typedef double scalar;

struct Vect3 {
	scalar x;
	scalar y;
	scalar z;
};

struct Quaternion {
	scalar s;
	Vect3 v;
};


#endif //INC_2024_I_AV_TEENSY_SYSTEM_TYPES_HPP
