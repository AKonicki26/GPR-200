file(
 GLOB_RECURSE CORE_INC CONFIGURE_DEPENDS
 RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
 *.h *.hpp
)

file(
 GLOB_RECURSE CORE_SRC CONFIGURE_DEPENDS
 RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
 *.c *.cpp
)

set(CORE_INC_DIR
 ${CMAKE_CURRENT_SOURCE_DIR}
 CACHE PATH "CORE INCLUDE SOURCE PATH"
)

add_library(core STATIC ${CORE_SRC} ${CORE_INC}
        ak/Shader.cpp
        ak/Shader.h
        ak/Texture2D.cpp
        ak/Texture2D.h
        ak/Camera.cpp
        ak/Camera.h)

find_package(OpenGL REQUIRED)

target_link_libraries(core PUBLIC IMGUI)
target_link_libraries(core PUBLIC IMGUI glm)

install (TARGETS core DESTINATION lib)
install (FILES ${CORE_INC} DESTINATION include/core)

