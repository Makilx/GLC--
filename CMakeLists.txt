cmake_minimum_required(VERSION 3.15.0)
project(GLEngine VERSION 1.0)

# Define macro for importing GitHub repos
include(FetchContent)

macro(ImportRepo NAME REPO COMMIT)
    message(
        STATUS 
        "Module: ${NAME} @ ${COMMIT}"
    )

    FetchContent_Declare(
        ${NAME}
        GIT_REPOSITORY ${REPO}
        GIT_TAG        ${COMMIT}      # exact commit from lockfile
        GIT_SHALLOW    TRUE
        UPDATE_DISCONNECTED FALSE
    )

    FetchContent_MakeAvailable(${NAME})
endmacro()

# Source
add_executable(
    GLEngine

    "src/Init.cpp"
    "src/app/App.cpp"
    "src/renderer/Window.cpp"
    "src/renderer/Renderer.cpp"
    "src/renderer/objects/Buffer.cpp"
    "src/renderer/objects/ArrayObject.cpp"
    "src/renderer/objects/Mesh.cpp"
    "src/renderer/objects/Shader.cpp"
    "src/renderer/objects/Texture.cpp"
    "src/input/Input.cpp"
)

# Imports


# GLAD
ImportRepo(glad https://github.com/Dav1dde/glad.git 5bf3eda)
add_library(glad STATIC ${glad_SOURCE_DIR}/src/glad.c)
target_include_directories(glad PUBLIC ${glad_SOURCE_DIR}/include)
target_link_libraries(GLEngine PUBLIC glad)

# GLFW
ImportRepo(GLFW https://github.com/glfw/glfw.git 3.4)
target_link_libraries(GLEngine PUBLIC glfw)

# GLM
ImportRepo(GLM https://github.com/g-truc/glm.git 1.0.1)

# STB
ImportRepo(STBImage https://github.com/nothings/stb.git GIT_TAG main)

# Include
target_include_directories(
    GLEngine
    PUBLIC

    "${CMAKE_SOURCE_DIR}/include"

    # Import includes
    "${glad_SOURCE_DIR}/include"
    "${glfw_SOURCE_DIR}/include"
    "${glm_SOURCE_DIR}"
    "${stbimage_SOURCE_DIR}"
)
