set(CMAKE_TOOLCHAIN_FILE uno-wifi-rev2-32u4.cmake)

project(main)

add_executable(main_32u4
    main.c
    usb.c
    matrix.c
    serial.c
)

# target_include_directories(main
#     PRIVATE ./
# )