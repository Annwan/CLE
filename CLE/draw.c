#include "draw.h"

#define INCBIN_PREFIX CLE_file_
#define INCBIN_STYLE INCBIN_STYLE_SNAKE 
#include "incbin.h"

INCBIN(basic_vertex_shader, "shaders/basic_vertex.glsl")

void CLE_draw_triangle(vec3d a, vec3d b, vec3d c, rgba color) {
		
}
