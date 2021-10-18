#ifndef CLE_DATA_H
#define CLE_DATA_H

struct vec3i {
	int x, y, z;
};
typedef struct vec3i vec3i;

struct vec3f {
	float x, y, z;
};
typedef struct vec3f vec3f;

struct vec3d {
	double x, y, z;
};
typedef struct vec3d vec3d;

struct vec2i {
	int x, y, z;
};
typedef struct vec2i vec2i;

struct vec2f {
	float x, y;
};
typedef struct vec2f vec2f;

struct vec2d {
	double x, y;
};
typedef struct vec2d vec2d;

struct rgba {
	float r, g, b, a;
};
typedef struct rgba rgba;
#endif /* CLE_DATA_H */
