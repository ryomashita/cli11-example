
set(CLI11_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/CLI11)
set(CLI11_VERSION v2.4.2)

function(download_cli11)
    file(MAKE_DIRECTORY ${CLI11_INCLUDE_DIR})

    set(CLI11_HEADER_PATH ${CLI11_INCLUDE_DIR}/CLI11.hpp)

    if(NOT EXISTS ${CLI11_HEADER_PATH})
        file(DOWNLOAD
        https://github.com/CLIUtils/CLI11/releases/download/${CLI11_VERSION}/CLI11.hpp
        ${CLI11_HEADER_PATH}
        STATUS CLI11_DOWNLOAD_STATUS
        )
        # check download status
        list(GET CLI11_DOWNLOAD_STATUS 0 CLI11_DOWNLOAD_STATUS_CODE)
        if(NOT CLI11_DOWNLOAD_STATUS_CODE EQUAL 0)
            message(FATAL_ERROR "Failed to download CLI11.hpp")
        endif()
    endif()
endfunction()

function(include_cli11 target)
    target_include_directories(${target} PRIVATE ${CLI11_INCLUDE_DIR})
    # -> Include with `#include <CLI11.hpp>`
endfunction()

function(install_cli11)
    include(FetchContent)
    FetchContent_Declare(
        cli11_proj
        QUIET
        GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
        GIT_TAG ${CLI11_VERSION}
    )
    FetchContent_MakeAvailable(cli11_proj)
endfunction()

function(link_cli11 target)
    target_link_libraries(${target} PRIVATE CLI11::CLI11)
    # -> Include with `#include <CLI/CLI.hpp>`
endfunction()

download_cli11()
install_cli11()