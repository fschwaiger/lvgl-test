cmake_minimum_required(VERSION 3.12.4)
project(lvgl_test C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# do NOT build demos and examples
set(CONFIG_LV_BUILD_DEMOS OFF)
set(CONFIG_LV_BUILD_EXAMPLES OFF)

# contains the lvgl library
add_subdirectory(lvgl)

# contains the SDL2 library
find_package(SDL2 REQUIRED)

# the main executable
list(APPEND SRC_FILES src/main.c src/widget/rpm.c)
add_executable(lvgl_test ${SRC_FILES})

# in order to find lv_conf.h
target_include_directories(lvgl_test PRIVATE ${PROJECT_SOURCE_DIR})

# link the lvgl and SDL2 libraries
target_link_libraries(lvgl_test PRIVATE lvgl SDL2::SDL2 m)