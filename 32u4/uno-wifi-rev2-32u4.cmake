# avr gcc toolchain configuration for 32u4

# We are cross compiling so we don't want compiler tests to run, as they will fail
# include(CMakeForceCompiler)

# Indicate we aren't compiling for an OS
set(CMAKE_SYSTEM_NAME Generic)

# Set processor type
set(CMAKE_SYSTEM_PROCESSOR avr)

# Override compiler
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(CMAKE_C_COMPILER /home/logan/.arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino5/bin/avr-gcc)
set(CMAKE_CXX_COMPILER /home/logan/.arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino5/bin/avr-g++)

# Set other tools
set(OBJSIZE ${COMPILER_PREFIX}avr-size)
set(OBJCOPY ${COMPILER_PREFIX}avr-objcopy)
set(OBJDUMP ${COMPILER_PREFIX}avr-objdump)
set(DEBUGGER ${COMPILER_PREFIX}avr-gdb)

# Remove preset linker flags
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "") 
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "") 
set(CMAKE_SHARED_LIBRARY_LINK_ASM_FLAGS "")

# Set library options
set(SHARED_LIBS OFF)
set(STATIC_LIBS ON)

add_link_options(
    # -B /home/logan/Downloads/ATMEGA_pack/gcc/dev/atmega4809 
    # -I/home/logan/Downloads/ATMEGA_pack/include 
    -mmcu=atmega32u4
)

add_compile_options(
    -O3 
    -Wall 
    # -B /home/logan/Downloads/ATMEGA_pack/gcc/dev/atmega4809 
    # -I/home/logan/Downloads/ATMEGA_pack/include 
    -mmcu=atmega32u4
    -D__AVR_atmega32u4__
    -DF_CPU=16000000
)