set(TARGET service)

set(SOURCES
    main.cpp
)

set(INCLUDE_DIRECTORIES
    ${CMAKE_SOURCE_DIR}/userver/core/include
    ${CMAKE_SOURCE_DIR}/userver/postgresql/include
)

set(LIBARIES
    userver-core
    userver-postgresql
)

add_executable(${TARGET} ${SOURCES})
target_include_directories(${TARGET} PRIVATE ${INCLUDE_DIRECTORIES})
target_link_libraries(${TARGET} PRIVATE ${LIBARIES})
