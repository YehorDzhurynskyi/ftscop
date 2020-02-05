cmake_minimum_required(VERSION 3.1)

project(scop)

add_subdirectory(glad)

# Download and unpack SDL2 at configure time
configure_file(CMakeLists.txt.in SDL2-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/SDL2-download )
if(result)
  message(FATAL_ERROR "CMake step for SDL2 failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/SDL2-download )
if(result)
  message(FATAL_ERROR "Build step for SDL2 failed: ${result}")
endif()

# Add SDL2 directly to our build. This defines
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/SDL2-src
                 ${CMAKE_CURRENT_BINARY_DIR}/SDL2-build
                 EXCLUDE_FROM_ALL)

add_executable(scop
    src/main.c
    src/shader.h
    src/shader.c
    src/camera.h
    src/camera.c

    src/ft_strlen.c
    src/ft_memcpy.c
    src/ft_strchr.c
    src/ft_strnchr.c
    src/ft_isalpha.c
    src/ft_atoi.c
    src/ft_atod.c
    src/ft_strncmp.c
    src/ft_isws.c
    src/ft_isdigit.c

    src/vec/rgba2vec.c
    src/vec/to_vec3.c
    src/vec/vec2rgba.c
    src/vec/vec_add.c
    src/vec/vec_cross.c
    src/vec/vec_dot.c
    src/vec/vec_length.c
    src/vec/vec_mult.c
    src/vec/vec_normalize.c
    src/vec/vec_reflect.c
    src/vec/vec_scalar.c
    src/vec/vec_sub.c

    src/mat/mat3_determinant.c
    src/mat/mat4_determinant.c
    src/mat/mat_create.c
    src/mat/mat_identity.c
    src/mat/mat_inverse.c
    src/mat/mat_mat_mult.c
    src/mat/mat_minor.c
    src/mat/mat_scalar.c
    src/mat/mat_transpose.c
    src/mat/mat_vec_mult.c
    src/mat/vec_mat_mult.c
)

target_link_libraries(scop
    PUBLIC
        glad
        SDL2
)

target_include_directories(scop
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/libft/include
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/libft/
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/src
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

add_custom_command(TARGET scop POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:SDL2> $<TARGET_FILE_DIR:scop>
)

add_custom_command(TARGET scop POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/resources"
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)
