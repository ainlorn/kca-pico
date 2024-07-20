pico_sdk_init()
add_executable(kca-pico
        main.c
        usb_descriptors.c
        btn.c encoder.c lever.c
)

pico_enable_stdio_usb(kca-pico 1)
pico_enable_stdio_uart(kca-pico 0)

target_compile_options(kca-pico PRIVATE -O3)
target_include_directories(kca-pico PRIVATE ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(kca-pico PRIVATE
        pico_stdlib pico_multicore hardware_adc
        tinyusb_device tinyusb_board)

pico_add_extra_outputs(kca-pico)

add_custom_command(TARGET kca-pico POST_BUILD
        COMMAND cp kca-pico.uf2 ${CMAKE_CURRENT_LIST_DIR}/..)
