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
    src/app.h
    src/app.c
    src/app_poll_events.c

    src/scene/scene.h
    src/scene/scene.c
    src/scene/mesh.h
    src/scene/mesh.c
	src/scene/actor.c
	src/scene/actor_trs.c
	src/scene/actor_init.c
	src/scene/actor_translate.c
	src/scene/actor_rotate.c
    src/scene/actor_colorize.c
    src/scene/camera.c

    src/renderer/renderer.h
    src/renderer/renderer.c
    src/renderer/shader.h
    src/renderer/shader.c
    src/renderer/texture.c
    src/renderer/renderer_scene.c
    src/renderer/renderer_interactor.c
    src/renderer/renderer_interactor_translation.c
    src/renderer/renderer_interactor_rotation.c
    src/renderer/renderer_interactor_scaling.c
    src/renderer/renderer_procedure.c
    src/renderer/renderer_gfx_init.c
    src/renderer/renderer_gfx_delete.c
    src/renderer/renderer_init_circle.c
    src/renderer/renderer_init_cone.c
    src/renderer/renderer_init_cube.c
    src/renderer/renderer_init_grid.c
    src/renderer/renderer_init_noshading.c
    src/renderer/renderer_init_phong.c

    src/input/input.h
    src/input/input_camera_handler.c
    src/input/input_scene_handler.c
    src/input/input_interactor.c

    src/objparser/objparser.h
    src/objparser/objparser_common.c
    src/objparser/objparser_skip_if_match.c
    src/objparser/objparser_read_int.c
    src/objparser/objparser_read_float.c
    src/objparser/objparser_parse.c
    src/objparser/objparser_vertexdata.c
    src/objparser/objparser_polygonal.c

    src/libft/ft_strlen.c
    src/libft/ft_memset.c
    src/libft/ft_memcpy.c
    src/libft/ft_strchr.c
    src/libft/ft_strnchr.c
    src/libft/ft_isalpha.c
    src/libft/ft_atoi.c
    src/libft/ft_atod.c
    src/libft/ft_strcmp.c
    src/libft/ft_strncmp.c
    src/libft/ft_isws.c
    src/libft/ft_isdigit.c

    src/libft/vec/rgba2vec.c
    src/libft/vec/to_vec3.c
    src/libft/vec/vec2rgba.c
    src/libft/vec/vec_add.c
    src/libft/vec/vec_cross.c
    src/libft/vec/vec_dot.c
    src/libft/vec/vec_length.c
    src/libft/vec/vec_mult.c
    src/libft/vec/vec_normalize.c
    src/libft/vec/vec_reflect.c
    src/libft/vec/vec_scalar.c
    src/libft/vec/vec_sub.c

    src/libft/mat/mat3_determinant.c
    src/libft/mat/mat4_determinant.c
    src/libft/mat/mat_create.c
    src/libft/mat/mat_identity.c
    src/libft/mat/mat_inverse.c
    src/libft/mat/mat_mat_mult.c
    src/libft/mat/mat_minor.c
    src/libft/mat/mat_scalar.c
    src/libft/mat/mat_transpose.c
    src/libft/mat/mat_vec_mult.c
    src/libft/mat/vec_mat_mult.c
)

function(epi_pack_sources)
    if(NOT MSVC OR NOT WIN32)
		message(WARNING "This function doesn't support selected platform, it's necessary replace slashes by back-slashes only on WIN platform")
		return()
    endif()
    foreach(_source IN ITEMS ${ARGN})
        if (IS_ABSOLUTE "${_source}")
            file(RELATIVE_PATH _source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source}")
        else()
            set(_source_rel "${_source}")
        endif()
        get_filename_component(_source_path "${_source_rel}" PATH)
        string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
        source_group("${_source_path_msvc}" FILES "${_source}")
    endforeach()
endfunction()

# Download and unpack googletest at configure time
configure_file(gtest_Extern.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

get_target_property(scop_SRCs scop SOURCES)
epi_pack_sources(${scop_SRCs})

target_link_libraries(scop
    PUBLIC
        glad
        SDL2
)

set_target_properties(scop
	PROPERTIES
		LINKER_LANGUAGE "C"
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

if (UNIX)
	message(STATUS "linking libft")

	add_subdirectory(libft)

	target_link_libraries(scop
		PUBLIC
			ft
	)
	
	target_compile_options(scop
		PRIVATE
			-Wall -Werror -Wunused
	)
endif ()

if (0)
set_target_properties(gtest
	PROPERTIES
		LINKER_LANGUAGE "CXX"
        CXX_STANDARD 17
)

add_executable(scop_test
    test/scop_test_main.cpp
    test/scop_test.cpp
    test/scop_test.h
)
target_link_libraries(scop_test
    PUBLIC
        scop
        gtest
)

set_target_properties(scop_test
	PROPERTIES
		LINKER_LANGUAGE "CXX"
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)
add_test(NAME scoptest COMMAND scop_test)
endif()

add_custom_command(TARGET scop POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:SDL2> $<TARGET_FILE_DIR:scop>
)

add_custom_command(TARGET scop POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/resources"
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)
