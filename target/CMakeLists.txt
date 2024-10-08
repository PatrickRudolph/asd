cmake_minimum_required(VERSION 2.8.10 FATAL_ERROR)
project(at-scale-debug-target C)

find_package (PkgConfig REQUIRED)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sysroot/include)
pkg_check_modules (SAFEC REQUIRED libsafec)
# Define HAVE_C99 to include sprintf_s macro in safec library
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DHAVE_C99")
include_directories (${SAFEC_INCLUDE_DIRS})
include_directories (${ASD_DIR}/include)

pkg_check_modules (CJSON REQUIRED libcjson)
if(${CJSON_FOUND})
# Use results of pkg_check_modules() call.
include_directories(${CJSON_INCLUDE_DIRS})
link_directories(${CJSON_LIBRARY_DIRS})
endif(${CJSON_FOUND})

pkg_check_modules(JOURNALD QUIET libsystemd)
if(${JOURNALD_FOUND})
# Use results of pkg_check_modules() call.
include_directories(${JOURNALD_INCLUDE_DIRS})
link_directories(${JOURNALD_LIBRARY_DIRS})
add_definitions(-DENABLE_SD_JOURNAL)
endif(${JOURNALD_FOUND})

# Set APB_FREQ to EXTRA_OECMAKE on bb recipe to modify JTAG frequency
if(${APB_FREQ})
    add_definitions( -DAPB_FREQ=${APB_FREQ} )
endif(${APB_FREQ})

# Set I2C_STUB and/or I3C_STUB to EXTRA_OECMAKE on bb recipe to remove
# i2c/i3c features and dependencies respectively.
set(I2C_MSG_BUILDER "i2c_msg_builder.c")
set(I2C_HANDLER "i2c_handler.c")
set(I3C_HANDLER "i3c_handler.c")
set(SPP_HANDLER "spp_handler.c" "i3c_debug_handler.c")
if(${ENABLE_DBUS})
    set(DBUS_SRC "dbus_helper.c")
endif(${ENABLE_DBUS})

if(${I2C_STUB})
    if(${I3C_STUB})
        set(I2C_MSG_BUILDER "i2c_msg_builder_stub.c")
    endif(${I3C_STUB})
endif(${I2C_STUB})

if(${I2C_STUB})
    set(I2C_HANDLER "i2c_handler_stub.c")
endif(${I2C_STUB})

if(${I3C_STUB})
    set(I3C_HANDLER "i3c_handler_stub.c")
endif(${I3C_STUB})

if(${SPP_STUB})
    set(SPP_HANDLER "spp_handler_stub.c")
endif(${SPP_STUB})

if(NOT ${BUILD_UT})
    add_library(asd_target STATIC asd_msg.c jtag_handler.c 
            target_handler.c dbus_stub.c ${DBUS_SRC} ${I2C_MSG_BUILDER} ${I2C_HANDLER}
            ${I3C_HANDLER} gpio.c vprobe_handler.c
            ${SPP_HANDLER} asd_target_api.c asd_server_interface.c)
    target_link_libraries(asd_target -lm ${JOURNALD_LIBRARIES} -lgpiod ${CJSON_LIBRARIES})
endif(NOT ${BUILD_UT})
