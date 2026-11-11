# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.28.0)

set(BOARD_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/../../zephyr_board/stm32_h743xih6_custom_boot)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(bootloader)

target_sources(app PRIVATE 
    src/main.c
    src/app_boot.c
    api/api_ymodem.c
    api/api_uart.c
)

target_include_directories(app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/api
)
