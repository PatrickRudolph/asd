/*
Copyright (c) 2023, Intel Corporation

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
#include "dbus_helper.h"

#include <safe_mem_lib.h>
#include <safe_str_lib.h>
#include <stdio.h>
#include <stdlib.h>

Dbus_Handle* __attribute__((weak)) dbus_helper()
{
    return malloc(sizeof(void *));
}

int __attribute__((weak)) dbus_get_fd(Dbus_Handle*)
{
    return -1;
}

STATUS __attribute__((weak)) dbus_initialize(Dbus_Handle* state)
{
    return ST_OK;
}

STATUS __attribute__((weak)) dbus_deinitialize(Dbus_Handle* state)
{
    return ST_OK;
}

STATUS __attribute__((weak)) dbus_power_reset(Dbus_Handle* state)
{
    return ST_OK;
}

STATUS __attribute__((weak)) dbus_power_off(Dbus_Handle* state)
{
    return ST_OK;
}

STATUS __attribute__((weak)) dbus_power_on(Dbus_Handle* state)
{
    return ST_OK;
}

STATUS __attribute__((weak)) dbus_power_toggle(Dbus_Handle* state)
{
    return ST_OK;
}

STATUS __attribute__((weak)) dbus_get_powerstate(Dbus_Handle* state, int* value)
{
    *value = STATE_UNKNOWN;
    return ST_OK;
}

STATUS __attribute__((weak)) dbus_process_event(Dbus_Handle* state, ASD_EVENT* event)
{
    return ST_OK;
}

STATUS __attribute__((weak)) dbus_read_asd_config(const Dbus_Handle* state, const char* interface,
                            const char* name, char type, void* var)
{
    return ST_ERR;
}

STATUS __attribute__((weak)) dbus_get_platform_bus_config(const Dbus_Handle* state,
                                    bus_options* busopt)
{
    return ST_ERR;
}

STATUS __attribute__((weak)) dbus_read_i3c_ownership(const Dbus_Handle* state, I3c_Ownership* owner)
{
    return ST_ERR;
}

STATUS __attribute__((weak)) dbus_req_i3c_ownership(const Dbus_Handle* state, int* token)
{
    return ST_ERR;

}

STATUS __attribute__((weak)) dbus_rel_i3c_ownership(const Dbus_Handle* state, int token)
{
    return ST_ERR;
}
