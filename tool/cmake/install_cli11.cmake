
set(CLI11_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/CLI11)

function(download_cli11)
    file(MAKE_DIRECTORY ${CLI11_INCLUDE_DIR})

    set(CLI11_HEADER_PATH ${CLI11_INCLUDE_DIR}/CLI11.hpp)

    if(NOT EXISTS ${CLI11_HEADER_PATH})
        file(DOWNLOAD
        https://github.com/CLIUtils/CLI11/releases/download/v2.4.2/CLI11.hpp
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

download_cli11()

function(link_cli11 target)
    target_include_directories(${target} PRIVATE ${CLI11_INCLUDE_DIR})
endfunction()
