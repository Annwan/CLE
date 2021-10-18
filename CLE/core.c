#include "core.h"

#define MAX_SHADER_LEN 100000

int CLE_main(int w, int h, const char *title,
                     CLE_init_callback onStart,
                     CLE_update_callback onUpdate,
                     void * state) {
  // enable some features
  glewExperimental = true;
  // if we cant init glfw, abort
  if (!glfwInit()) {
    fprintf(stderr, "Failed to initialize GLFW\n");
    return -1;
  }

  // 4x antialias
  glfwWindowHint(GLFW_SAMPLES, 4);
  // GL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  // We want modern GL
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Ok time to create the window
  GLFWwindow* window;
  window = glfwCreateWindow(w, h, title, NULL, NULL);
  if (window == NULL) {
    fprintf(stderr, "Failed to create window\n");
    glfwTerminate();
    return -1;
  }

  // tell GL taht we are going to work with the new window
  glfwMakeContextCurrent(window);
  glewExperimental = true;

  // Init glew
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Couldnt initialize GLEW\n");
    return -1;
  }

  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  // run onStart callback
  if (!onStart(window, state)) {
    fprintf(stderr, "onStart callback failed");
    return -1;
  }

  // repeatedly run onUpdate callback
  clock_t last = clock();
  bool cont;
  do {
    clock_t current = clock();
    glfwPollEvents();
    cont = onUpdate(window, state, (double)(current - last) / CLOCKS_PER_SEC);
    glfwSwapBuffers(window);
    last = current;
  } while (cont && !glfwWindowShouldClose(window));

  return 0;
};

GLuint CLE_load_shaders_from_file(const char *vertex_file_path,
                        const char *fragment_file_path) {

  // Read the vertex shader
  FILE * vertex_file = fopen(vertex_file_path, "r");
  if (vertex_file == NULL) return 0;
  fseek(vertex_file, 0, SEEK_END);
  int vertex_shader_len = ftell(vertex_file);
  fseek(vertex_file, 0, SEEK_SET);
  char * vertex_source = (char *)calloc(vertex_shader_len + 1, sizeof(char));
  if (vertex_source == NULL) return 0;
  fread(vertex_source, sizeof(char), vertex_shader_len, vertex_file);
  fclose(vertex_file);

  // Read fragment shader
  FILE * frag_file = fopen(fragment_file_path, "r");
  if (frag_file == NULL) return 0;
  fseek(frag_file, 0, SEEK_END);
  int frag_shader_len = ftell(frag_file);
  fseek(frag_file, 0, SEEK_SET);
  char * frag_source = (char *)calloc(frag_shader_len + 1, sizeof(char));
  if (frag_source == NULL) return 0;
  fread(frag_source, sizeof(char), frag_shader_len, frag_file);
  fclose(frag_file);

  return CLE_load_shaders_from_source(vertex_source, frag_source);
}

GLuint CLE_load_shaders_from_source(const char * vertex_source, const char * frag_source){
  GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
  GLuint frag_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
  GLint res = GL_FALSE;
  int info_len = 0;

  // compile vertex shader
  fprintf(stderr, "Compiling vertex shader\n");
  glShaderSource(vertex_shader_id, 1, (const char * const *)&vertex_source, NULL);
  glCompileShader(vertex_shader_id);

  // check compilation
  glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &res);
  glGetShaderiv(vertex_shader_id, GL_INFO_LOG_LENGTH, &info_len);
  if (info_len > 0) {
    char* vertex_shader_error_message = (char*)calloc(info_len + 1, sizeof(char));
    glGetShaderInfoLog(vertex_shader_id, info_len, NULL, vertex_shader_error_message);
    fprintf(stderr, "%s\n", vertex_shader_error_message);
    free(vertex_shader_error_message);
  }

  // compile fragment shader
  fprintf(stderr, "Compiling fragment shader\n");
  glShaderSource(frag_shader_id, 1, (const char * const *)&frag_source, NULL);
  glCompileShader(frag_shader_id);

  //check compilation
  glGetShaderiv(frag_shader_id, GL_COMPILE_STATUS, &res);
  glGetShaderiv(frag_shader_id, GL_INFO_LOG_LENGTH, &info_len);
  if (info_len > 0) {
    char* frag_shader_error_message = (char*)calloc(info_len + 1, sizeof(char));
    glGetShaderInfoLog(frag_shader_id, info_len, NULL, frag_shader_error_message);
    fprintf(stderr, "%s\n", frag_shader_error_message);
    free(frag_shader_error_message);
  }

  // Link the program
  fprintf(stderr, "Linking program\n");
  GLuint prog_id = glCreateProgram();
  glAttachShader(prog_id, vertex_shader_id);
  glAttachShader(prog_id, frag_shader_id);
  glLinkProgram(prog_id);

  // Check linking
  glGetProgramiv(prog_id, GL_LINK_STATUS, &res);
  glGetProgramiv(prog_id, GL_INFO_LOG_LENGTH, &info_len);
  if (info_len > 0) {
    char * prog_error_message = (char*)calloc(info_len + 1, sizeof(char));
    glGetProgramInfoLog(prog_id, info_len, NULL, prog_error_message);
    fprintf(stderr, "%s\n", prog_error_message);
    free(prog_error_message);
  }

  glDetachShader(prog_id, vertex_shader_id);
  glDetachShader(prog_id, frag_shader_id);

  glDeleteShader(vertex_shader_id);
  glDeleteShader(frag_shader_id);

  return prog_id;
}
