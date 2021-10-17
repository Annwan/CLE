#include "CLE/core.h"
#include <stdbool.h>

struct AppState {
  GLuint vertexBuffer;
  GLuint triShader;
};

static const GLfloat tri[] = {
  -1.0f, -1.0f, 0.0f,
  1.0f,  -1.0f, 0.0f,
  0.0f,  1.0f,  0.0f
};

bool onStart(GLFWwindow* w, void * s) {
  struct AppState *st = (struct AppState*) s;
  glGenBuffers(1, &(st->vertexBuffer));
  glBindBuffer(GL_ARRAY_BUFFER, st->vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(tri), tri, GL_STATIC_DRAW);

  st->triShader = CLE_load_shaders_from_file("triver.glsl", "trifrag.glsl");
  return true;
}

bool onUpdate(GLFWwindow* w, void* s, double e) {
  struct AppState *st = (struct AppState*) s;
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glUseProgram(st->triShader);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, st->vertexBuffer);
  glVertexAttribPointer(0, 3,
                        GL_FLOAT, GL_FALSE,
                        0, (void*)0);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glDisableVertexAttribArray(0);
  //printf("Elapsed time: %f\n", e);
  return glfwGetKey(w, GLFW_KEY_ESCAPE) != GLFW_PRESS;
}

int main() {
  struct AppState s;
  return CLE_main(800, 600, "Test window", onStart, onUpdate, &s);
}
