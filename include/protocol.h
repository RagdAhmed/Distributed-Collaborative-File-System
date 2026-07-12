#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

typedef struct {
    uint32_t command;
    uint32_t filename_len;
    uint64_t payload_len;
} MessageHeader;

#define CMD_UPLOAD 1
#define CMD_DOWNLOAD 2
#define CMD_DELETE 3
#define CMD_LIST 4
#define CMD_OK 5
#define CMD_ERROR 6
#define CMD_LIST_RESPONSE 7

#endif