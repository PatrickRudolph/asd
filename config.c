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

#include <stdint.h>
#include <stdlib.h>
#include "logging.h"
#include "config.h"

STATUS set_config_defaults(config *config, const i2c_options *i2c)
{
	if (config == NULL || i2c == NULL) {
		return ST_ERR;
	}
	config->jtag.mode = JTAG_DRIVER_MODE_SOFTWARE;
	config->jtag.chain_mode = JTAG_CHAIN_SELECT_MODE_SINGLE;
	config->remote_logging.logging_level = IPC_LogType_Off;
	config->remote_logging.logging_stream = 0;

	for (int i = 0; i < MAX_I2C_BUSES; i++) {
		config->i2c.allowed_buses[i] = false;
	}

	if (i2c->enable) {
		config->i2c.allowed_buses[i2c->bus] = true;
	}
	config->i2c.enable_i2c = i2c->enable;
	config->i2c.default_bus = i2c->bus;

	return ST_OK;
}
