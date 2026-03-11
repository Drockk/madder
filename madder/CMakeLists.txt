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
        ${CMAKE_CURRENT_SOURCE_DIR}/madder/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/madder/include/madder
)

add_subdirectory(madder/include)
add_subdirectory(madder/source)
