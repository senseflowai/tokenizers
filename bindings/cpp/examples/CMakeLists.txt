set(EXAMPLES_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")


file(GLOB CPP_FILES "${EXAMPLES_SOURCE_DIR}/*.cpp")

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

foreach(CPP_FILE ${CPP_FILES})
    get_filename_component(EXECUTABLE_NAME "${CPP_FILE}" NAME_WE)
    message(STATUS "Build example: ${EXECUTABLE_NAME}")

    add_executable(${EXECUTABLE_NAME} "${CPP_FILE}")
    target_link_libraries(${EXECUTABLE_NAME} ${LIB_NAME})
endforeach()