cmake_minimum_required (VERSION 3.10)
project (cl_engine VERSION 0.1 LANGUAGES C)

set (C_STANDARD 99)
set (C_STANDARD_REQUIRED True)

add_subdirectory(CLE)
add_subdirectory(src)
