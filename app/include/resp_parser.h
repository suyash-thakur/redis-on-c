
#ifndef REDIS_PARSER_H
#define REDIS_PARSER_H

#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    SIMPLE_STRING,
    ERROR,
    INTEGER,
    BULK_STRING,
    ARRAY,
    UNKNOWN
} RESPType;

void parseBulkString(char *buffer, size_t *index);

void parseArray(char *buffer, size_t *index);

void parseRedisCommand(char *buffer);

#endif // REDIS_PARSER_H