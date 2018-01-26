if(EnableTesting)
    add_subdirectory(test)
endif(EnableTesting)
project(libeternity VERSION ${PACKAGE_VERSION} LANGUAGES C)
set(sources src/args.c src/error.c src/util.c
    src/engine.c src/io.c src/etmath.c)
configure_file(config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/include/config.h @ONLY)
add_library(libeternity STATIC ${sources})
SET_TARGET_PROPERTIES(libeternity PROPERTIES PREFIX "")
target_include_directories(libeternity PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)
target_link_libraries(libeternity glfw GLEW m)
install(TARGETS libeternity
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
