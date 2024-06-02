add_executable(main
    main.c
    usb/device_callbacks.c
    usb/device_descriptor.c
    usb/hid.c
    usb/usb.c
    matrix.c
    setup.c
)

# Enable compiler warnings.
target_compile_options(main PRIVATE -Wall -Wextra)

# Make sure TinyUSB can find tusb_config.h
target_include_directories(main PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        )

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(main PUBLIC
    pico_stdlib              # for core functionality
    pico_unique_id
    pico_cyw43_arch_none     # we need Wifi to access the GPIO, but we don't need anything else
    tinyusb_device
    tinyusb_board)

# Uncomment this line to enable fix for Errata RP2040-E5 (the fix requires use of GPIO 15)
# target_compile_definitions(main PUBLIC PICO_RP2040_USB_DEVICE_ENUMERATION_FIX=1)

# enable usb output, disable uart output
pico_enable_stdio_usb(main 0)
pico_enable_stdio_uart(main 1)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(main)
