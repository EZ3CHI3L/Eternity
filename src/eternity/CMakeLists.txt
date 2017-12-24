set(sources src/eternity.c)
add_executable(eternity ${sources})
target_link_libraries(eternity libeternity OpenGL glfw)
install(TARGETS eternity
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
