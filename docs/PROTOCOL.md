# DCFS Wire Protocol

Length-prefixed binary protocol over TCP. Every message is a fixed-size
header followed by an optional filename and an optional payload.

## Header

```c
typedef struct {
    uint32_t command;
    uint32_t filename_len;
    uint64_t payload_len;
} MessageHeader;
```

`command` : Message type, see table below
`filename_len` : Bytes of filename following the header (0 if none) 
`payload_len` : Bytes of payload following the filename (0 if none) 

## Commands

| Value | Name               | Sent by | Payload                          |
|-------|--------------------|---------|-----------------------------------|
| 1     | `CMD_UPLOAD`        | client  | filename + file content           |
| 2     | `CMD_DOWNLOAD`      | client  | filename                          |
| 3     | `CMD_DELETE`        | client  | filename                          |
| 4     | `CMD_LIST`          | client  | none                               |
| 5     | `CMD_OK`            | server  | none                               |
| 6     | `CMD_ERROR`         | server  | error string                      |
| 7     | `CMD_LIST_RESPONSE` | server  | filenames, `\n`-separated         |

## Message layouts

```
CMD_UPLOAD         [header][filename][file content]
CMD_DOWNLOAD        [header][filename]
CMD_DELETE          [header][filename]
CMD_LIST             [header]
CMD_OK                [header]
CMD_ERROR            [header][error string]
CMD_LIST_RESPONSE    [header][filenames separated by '\n']
```

## Read procedure

1. Read `sizeof(MessageHeader)` bytes, parse it.
2. If `filename_len > 0`, read that many bytes as the filename.
3. If `payload_len > 0`, read that many bytes as the payload.

All reads/writes must use loop-until-complete helpers (`send_all` /
`recv_all`) since a single `send()`/`recv()` is not guaranteed to
transfer the full amount requested.

## Not yet defined

Replication, node registration, heartbeats, versioning — will get their
own command values in later phases.
