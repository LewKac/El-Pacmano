cmake_minimum_required (VERSION 3.14 FATAL_ERROR)
project(El_Pacmano VERSION 1.0.0)

# Add dependencies
add_subdirectory(external)

# Create .exe file (essentially)
add_executable(${PROJECT_NAME})

# Add additional source files here
target_sources(
    ${PROJECT_NAME}
    PRIVATE
	# Group made files
    ${CMAKE_CURRENT_LIST_DIR}/src/entity.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/ghost.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/manager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/pacman.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/pizza.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/wall.cpp

    ${CMAKE_CURRENT_LIST_DIR}/headers/entity.h
    ${CMAKE_CURRENT_LIST_DIR}/headers/ghost.h
    ${CMAKE_CURRENT_LIST_DIR}/headers/manager.h
    ${CMAKE_CURRENT_LIST_DIR}/headers/pacman.h
    ${CMAKE_CURRENT_LIST_DIR}/headers/pizza.h
    ${CMAKE_CURRENT_LIST_DIR}/headers/wall.h
	
    ${CMAKE_CURRENT_LIST_DIR}/external/imgui/imconfig.h
    ${CMAKE_CURRENT_LIST_DIR}/external/imgui/imgui.cpp
    ${CMAKE_CURRENT_LIST_DIR}/external/imgui/imgui_draw.cpp
    ${CMAKE_CURRENT_LIST_DIR}/external/imgui/imgui.h
    ${CMAKE_CURRENT_LIST_DIR}/external/imgui/imgui_impl_glfw.cpp
    ${CMAKE_CURRENT_LIST_DIR}/external/imgui/imgui_impl_glfw.h
    ${CMAKE_CURRENT_LIST_DIR}/external/imgui/imgui_impl_opengl3.cpp
    ${CMAKE_CURRENT_LIST_DIR}/external/imgui/imgui_impl_opengl3.h
    ${CMAKE_CURRENT_LIST_DIR}/external/imgui/imgui_internal.h
    ${CMAKE_CURRENT_LIST_DIR}/external/imgui/imgui_widgets.cpp



	#Helper files
    ${CMAKE_CURRENT_LIST_DIR}/src/glutil.cpp
    ${CMAKE_CURRENT_LIST_DIR}/headers/glutil.h

)

# Set include directories
target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/headers
    ${CMAKE_CURRENT_LIST_DIR}/src
    ${CMAKE_CURRENT_LIST_DIR}/external/imgui
    
	
)

# Link with external libraries
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    glad::glad
    gfx::gfx
    glm
    glfw
    stbimage::stbimage
)

# Enable C++ 17
target_compile_features(
    ${PROJECT_NAME}
    PRIVATE
    cxx_std_17
)

# Copy resources to binary directory
add_custom_target(
    copy_shaders ALL
    ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
    COMMAND ${CMAKE_COMMAND} -E echo "Copied resource directory to binary directory ${CMAKE_CURRENT_BINARY_DIR}"
)

