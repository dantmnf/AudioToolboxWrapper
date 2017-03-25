cmake_minimum_required (VERSION 3.0)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" "${CMAKE_MODULE_PATH}")
project (AudioToolboxStub C ASM_YASM)

if(BUILD_SHARED_LIBS)
    message(SEND_ERROR "Why are you building shared libs for a dynamic loading wrapper?")
endif()
set(BUILD_SHARED_LIBS 0)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(LIBDIR lib64)
else()
  set(LIBDIR lib32)
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/${LIBDIR})

add_library(CoreAudioToolboxWrapper src/AudioToolboxEntryWrapper.asm src/AudioToolboxLoader.c)
add_executable(testapp src/testapp.c)
target_link_libraries(CoreAudioToolboxWrapper pathcch shell32)
target_link_libraries(testapp CoreAudioToolboxWrapper)
install(FILES ${LIBDIR}/libpathcch.a DESTINATION lib)
install(FILES bin/atw_ldwrapper DESTINATION bin
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                    GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
install(TARGETS CoreAudioToolboxWrapper
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)
