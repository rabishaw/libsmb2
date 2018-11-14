/* -*-  mode:c; tab-width:8; c-basic-offset:8; indent-tabs-mode:nil;  -*- */
/*
   Copyright (C) 2016 by Ronnie Sahlberg <ronniesahlberg@gmail.com>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation; either version 2.1 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program; if not, see <http://www.gnu.org/licenses/>.
*/
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "smb2.h"
#include "libsmb2.h"
#include "libsmb2-private.h"

static int
smb2_encode_echo_request(struct smb2_context *smb2,
                         struct smb2_pdu *pdu)
{
        uint8_t *buf;
        int len;
        struct smb2_iovec *iov;

        len = 4;

        buf = (uint8_t*)malloc(len);
        if (buf == NULL) {
                smb2_set_error(smb2, "Failed to allocate echo buffer");
                return -1;
        }
        memset(buf, 0, len);

        iov = smb2_add_iovector(smb2, &pdu->out, buf, len, free);

        smb2_set_uint16(iov, 0, SMB2_ECHO_REQUEST_SIZE);

        return 0;
}

struct smb2_pdu *
smb2_cmd_echo_async(struct smb2_context *smb2,
                    smb2_command_cb cb, void *cb_data)
{
        struct smb2_pdu *pdu;
        
        pdu = smb2_allocate_pdu(smb2, SMB2_ECHO, cb, cb_data);
        if (pdu == NULL) {
                return NULL;
        }

        if (smb2_encode_echo_request(smb2, pdu)) {
                smb2_free_pdu(smb2, pdu);
                return NULL;
        }
        
        if (smb2_pad_to_64bit(smb2, &pdu->out) != 0) {
                smb2_free_pdu(smb2, pdu);
                return NULL;
        }

        return pdu;
}

int
smb2_process_echo_fixed(struct smb2_context *smb2,
                        struct smb2_pdu *pdu)
{
        return 0;
}
