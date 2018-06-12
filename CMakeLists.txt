cmake_minimum_required(VERSION 3.2)
project(TheTube C CXX)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_DIRECTORY "src/")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin/")

set(CMAKE_INCLUDE_CURRENT_DIR ON) # Find includes in corresponding build directories

if (MSVC_VERSION GREATER_EQUAL "1900")
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("/std:c++17" _cpp_latest_flag_supported)
    if (_cpp_latest_flag_supported)
        add_compile_options("/std:c++17")
    endif()
endif()

if(MSVC)
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif()



include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE SOURCE_FILES "${SOURCE_DIRECTORY}*.cpp")
file(GLOB_RECURSE HEADER_FILES "${SOURCE_DIRECTORY}*.h" "${SOURCE_DIRECTORY}*.hpp")

# Needed for having the good directory tree in the Visual studio project
foreach(source IN LISTS SOURCE_FILES)
    get_filename_component(source_path "${source}" PATH)
	file(RELATIVE_PATH source_path_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${source_path}")
    string(REPLACE "/" "\\" source_path_msvc "${source_path_rel}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()

foreach(header IN LISTS HEADER_FILES)
    get_filename_component(header_path "${header}" PATH)
	file(RELATIVE_PATH header_path_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${header_path}")
    string(REPLACE "/" "\\" header_path_msvc "${header_path_rel}")
    source_group("${header_path_msvc}" FILES "${header}")
endforeach()

add_executable (${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

# GLFW
set(GLFW_DIR "${LIB_DIR}/glfw")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory("${GLFW_DIR}")
target_link_libraries(TheTube glfw ${GLFW_LIBRARIES})
set_target_properties(glfw PROPERTIES FOLDER "Libraries")

# GLAD + KHR
set(GLAD_DIR "${LIB_DIR}/glad")
add_library("glad" "${GLAD_DIR}/src/glad.c" "${GLAD_DIR}/include/glad/glad.h")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLAD_DIR}/include")
target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")
set(KHR_DIR "${LIB_DIR}/KHR")
target_include_directories("glad" PRIVATE "${KHR_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${KHR_DIR}/include")
set_target_properties("glad" PROPERTIES FOLDER "Libraries")

#imgui
set(IMGUI_DIR "${LIB_DIR}/imgui/")
file(GLOB IMGUI_SOURCE_FILES "${IMGUI_DIR}*.cpp")
file(GLOB IMGUI_HEADER_FILES "${IMGUI_DIR}*.h" "${IMGUI_DIR}*.hpp")
add_library("imgui" ${IMGUI_SOURCE_FILES} ${IMGUI_HEADER_FILES})
target_include_directories("imgui" PRIVATE "${GLAD_DIR}/include")
target_include_directories("imgui" PRIVATE "${KHR_DIR}/include")
target_include_directories("imgui" PRIVATE "${IMGUI_DIR}")
target_include_directories(${PROJECT_NAME} PRIVATE "${IMGUI_DIR}")
set(KHR_DIR "${LIB_DIR}/KHR")
target_link_libraries("imgui" "glad" "${CMAKE_DL_LIBS}")
target_link_libraries("imgui" glfw ${GLFW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} "imgui" "${CMAKE_DL_LIBS}")
set_target_properties(imgui PROPERTIES FOLDER "Libraries")


