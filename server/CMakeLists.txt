cmake_minimum_required(VERSION 2.8.10 FATAL_ERROR)
project(at-scale-debug C)

find_package (PkgConfig REQUIRED)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sysroot/include)
pkg_check_modules (SAFEC REQUIRED libsafec)
# Define HAVE_C99 to include sprintf_s macro in safec library
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DHAVE_C99")
include_directories (${SAFEC_INCLUDE_DIRS})
include_directories (${ASD_DIR}/include)
link_directories (${SAFEC_LIBRARY_DIRS})
link_directories (${ASD_DIR}/target)

pkg_check_modules(SDBUS QUIET libsystemd)
if(${SDBUS_FOUND})
# Use results of pkg_check_modules() call.
include_directories(${SDBUS_INCLUDE_DIRS})
link_directories(${SDBUS_LIBRARY_DIRS})
add_definitions(-DENABLE_DBUS)
endif(${SDBUS_FOUND})

if(NOT ${BUILD_UT})
    add_executable(asd asd_main.c ext_network.c authenticate.c
            session.c config.c ext_tcp.c auth_none.c ext_tls.c
            auth_pam.c asd_target_interface.c asd_server_api.c
            logging.c)
    target_link_libraries(asd ${JOURNALD_LIBRARIES} libssl.a libcrypto.a -lpam
                          asd_target ${SAFEC_LIBRARIES} ${SDBUS_LIBRARIES})
    install (TARGETS asd DESTINATION bin)

    # Copy pam-asd to etc/pam.d
    install (
        FILES ${CMAKE_CURRENT_SOURCE_DIR}/pam-asd
        DESTINATION /etc/pam.d/
        RENAME asd
    )
endif(NOT ${BUILD_UT})
