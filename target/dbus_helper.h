/*
Copyright (c) 2019, Intel Corporation

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of Intel Corporation nor the names of its contributors
      may be used to endorse or promote products derived from this software
      without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef __ASD_DBUS_HELPER_H_
#define __ASD_DBUS_HELPER_H_

#include <stdbool.h>
#include "asd_common.h"

typedef struct sd_bus sd_bus;
typedef struct Dbus_Handle Dbus_Handle;
typedef struct sd_bus_error sd_bus_error;
typedef struct sd_bus_message sd_bus_message;

typedef enum
{
    CPU_OWNER,
    BMC_OWNER
} I3c_Ownership;

typedef enum
{
    STATE_UNKNOWN = -1,
    STATE_OFF = 0,
    STATE_ON = 1
} Power_State;

#define MAX_PLATFORM_PATH_SIZE 120

Dbus_Handle* dbus_helper();
STATUS dbus_initialize(Dbus_Handle*);
STATUS dbus_deinitialize(Dbus_Handle*);
STATUS dbus_power_reset(Dbus_Handle*);
STATUS dbus_power_toggle(Dbus_Handle*);
STATUS dbus_power_reboot(Dbus_Handle*);
STATUS dbus_power_on(Dbus_Handle*);
STATUS dbus_power_off(Dbus_Handle*);
int dbus_get_fd(Dbus_Handle*);
int sdbus_callback(sd_bus_message* reply, void* userdata, sd_bus_error* error);
STATUS dbus_process_event(Dbus_Handle* state, ASD_EVENT* event);
STATUS dbus_get_powerstate(Dbus_Handle* state, int* value);
STATUS dbus_get_platform_path(const Dbus_Handle* state, char* path);
STATUS dbus_get_platform_id(const Dbus_Handle* state, uint64_t* pid);
STATUS dbus_read_asd_config(const Dbus_Handle* state, const char* interface,
                            const char* name, char type, void* var);
STATUS dbus_get_asd_interface_paths(const Dbus_Handle* state,
                                    const char* names[],
                                    char interfaces[][MAX_PLATFORM_PATH_SIZE],
                                    int arr_size);
STATUS dbus_get_platform_bus_config(const Dbus_Handle* state,
                                    bus_options* busopt);
STATUS dbus_read_i3c_ownership(const Dbus_Handle* state, I3c_Ownership* owner);
STATUS dbus_req_i3c_ownership(const Dbus_Handle* state, int* token);
STATUS dbus_rel_i3c_ownership(const Dbus_Handle* state, int token);
int match_callback(sd_bus_message* m, void* userdata, sd_bus_error* error);

#endif
