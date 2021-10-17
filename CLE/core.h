#ifndef CLE_CORE_H
#define CLE_CORE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef bool (*CLE_update_callback)(GLFWwindow *win, void *state,
                                    double elapsedTime);

typedef bool (*CLE_init_callback)(GLFWwindow *win, void *state);

int CLE_main(int w, int h, const char *title, CLE_init_callback onStart,
             CLE_update_callback onUpdate, void *state);

GLuint CLE_load_shaders_from_file(const char *vertex_file_path,
                                  const char *fragment_file_path);

GLuint CLE_load_shaders_from_source(const char *vert_source,
                                    const char *frag_source);




#endif /* CLE_CORE_H */
