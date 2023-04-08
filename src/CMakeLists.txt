set(TARGET service)

set(SOURCES
    main.cpp
)

set(INCLUDE_DIRECTORIES
    ${CMAKE_SOURCE_DIR}/userver/core
)

set(LIBARIES
    userver-core
)

add_executable(${TARGET} ${SOURCES})
target_include_directories(${TARGET} PRIVATE ${INCLUDE_DIRECTORIES})
target_link_libraries(${TARGET} PRIVATE ${LIBARIES})
