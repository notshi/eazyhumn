cmake_minimum_required(VERSION 3.13)

# initialize pico-sdk from GIT
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_FETCH_FROM_GIT on)

# pico_sdk_import.cmake is a single file copied from this SDK
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(ezhm)


# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(ezhm
    main.c
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(ezhm pico_stdlib hardware_i2c pico_bootsel_via_double_reset )

pico_enable_stdio_usb(ezhm ENABLED)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(ezhm)

