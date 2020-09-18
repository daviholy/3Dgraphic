cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)
project(glfwTest)
set(prefix "")
if(${CMAKE_HOST_UNIX})
    set(prefix ".a")
elseif(CMAKE_HOST_WIN32)
    set (prefix ".lib")
endif()
include_directories(dependencies)
find_library(GLFW_LIBRARY
        NAMES "glfw3${prefix}"
        PATHS  dependencies)
find_library(ASSIMP
        NAMES "assimp${prefix}"
        PATHS dependencies)
find_library(ZLIB
        NAMES "zlibstatic${prefix}"
        PATHS dependencies)
find_library(XML
        NAMES "IrrXML${prefix}"
        PATHS dependencies)

set(glad "dependencies/glad/glad.c")
set (ImGui
     dependencies/imgui/imgui.cpp
     dependencies/imgui/imgui_demo.cpp
     dependencies/imgui/imgui_draw.cpp
        dependencies/imgui/imgui_impl_glfw.cpp
        dependencies/imgui/imgui_impl_opengl3.cpp
        dependencies/imgui/imgui_widgets.cpp)
add_executable(3D main.cpp Shader.cpp TextureBuilder.cpp Camera.cpp ${glad} ${ImGui} Mesh.cpp Mesh.h)
target_link_options(3D PRIVATE -ldl -pthread)
target_link_libraries(3D ${GLFW_LIBRARY} ${ZLIB} ${XML} ${ASSIMP})