# Logan Bateman
# 2020

cmake_policy(VERSION 3.19)
cmake_minimum_required(VERSION 3.19)

project(BTKBControl VERSION 0.1.0)

include(ExternalProject)

ExternalProject_Add(4809
    PREFIX 4809
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/4809"
    INSTALL_COMMAND cmake -E echo "Skipping install step."
)

ExternalProject_Add(32u4
    PREFIX 32u4
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/32u4"
    INSTALL_COMMAND cmake -E echo "Skipping install step."
)

# add_subdirectory(./4809)
# add_subdirectory(./32u4)

# target_compile_definitions(glfw PRIVATE GLFW_BUILD_DOCS=OFF )