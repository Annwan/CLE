cmake_minimum_required ( VERSION 3.13 )

add_executable(example example.c triver.glsl trifrag.glsl)
target_link_libraries(example CLE GL glfw GLEW)
target_include_directories(example BEFORE PUBLIC ..)
target_link_directories(example PUBLIC ..)
