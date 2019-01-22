cmake_minimum_required (VERSION 3.0)
project (AudioToolboxStub C)

set(BUILD_SHARED_LIBS 0)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(AudioToolboxWrapper STATIC src/AudioToolboxLoader.c)

if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
target_compile_options(AudioToolboxWrapper PRIVATE -fno-ident
                      -fno-unwind-tables -fno-asynchronous-unwind-tables 
					  -nostdlib -nostartfiles -nodefaultlibs)
endif()

add_executable(testapp src/testapp.c)
target_link_libraries(AudioToolboxWrapper shell32)
target_link_libraries(testapp AudioToolboxWrapper)
install(FILES bin/atw_ldwrapper DESTINATION bin
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                    GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
install(TARGETS AudioToolboxWrapper
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)
