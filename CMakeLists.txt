cmake_minimum_required(VERSION 3.2)

project(async VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/bulkmt)

configure_file(version.h.in version.h)

add_library(bulkmt SHARED
        bulkmt/console_logger.cpp
        bulkmt/file_logger.cpp
        bulkmt/interpreter.cpp
        bulkmt/observer.h
        bulkmt/commands_storage.cpp
        bulkmt/metricks.cpp
        bulkmt/third_party/picosha2/picosha2.h
        )
target_link_libraries(bulkmt -pthread)

add_library(async SHARED
        async_otus/async.cpp
        async_otus/handles_storage.cpp
        async_otus/handle.cpp)
target_link_libraries(async bulkmt)

add_executable(async_test main.cpp)
target_link_libraries(async_test async pthread)

set_target_properties(bulkmt async async_test PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS -Wpedantic -Wall -Wextra
        )

install(TARGETS
        bulkmt async async_test

        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
install(FILES
        async_otus/async.h
        async_otus/handles_storage.h
        async_otus/handle.h

        DESTINATION include/async_otus)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT artyom.sorokoumov@gmail.com)

include(CPack)
