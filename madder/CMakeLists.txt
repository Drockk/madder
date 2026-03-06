# =============================================================================
# Madder Library
# =============================================================================
add_library(madder SHARED)
add_library(madder::madder ALIAS madder)

target_link_libraries(madder
    PUBLIC
        asio
        spdlog
        STDEXEC::stdexec
)

target_include_directories(madder
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/madder
)

add_subdirectory(include)
add_subdirectory(source)
