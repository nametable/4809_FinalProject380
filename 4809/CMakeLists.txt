set(CMAKE_TOOLCHAIN_FILE uno-wifi-rev2-4809.cmake)

project(main)

# file( GLOB LIB_SOURCES *.cpp local/*.cpp remote/*.cpp utility/*.cpp)

add_executable(main_4809 
    # /home/logan/.arduino15/packages/arduino/tools/CMSIS-Atmel/1.2.0/CMSIS/Device/ATMEL/samd21/source/system_samd21.c
    main.cpp
    Serial.cpp
)

# target_include_directories(arduinoble
#     PUBLIC ./
# )