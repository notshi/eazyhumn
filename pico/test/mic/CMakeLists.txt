cmake_minimum_required(VERSION 3.13)


set(PICO_SDK_FETCH_FROM_GIT on)
include(../../pico_sdk_import.cmake)



project(main)

pico_sdk_init()

add_executable(main
    main.c
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(main pico_stdlib hardware_i2c hardware_adc pico_bootsel_via_double_reset )

pico_enable_stdio_usb(main ENABLED)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(main)






