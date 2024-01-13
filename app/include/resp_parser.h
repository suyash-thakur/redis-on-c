#include <stdio.h>
#include <stddef.h>

#ifndef REDIS_PARSER_H
#define REDIS_PARSER_H

typedef enum
{
    SIMPLE_STRING,
    ERROR,
    INTEGER,
    BULK_STRING,
    ARRAY,
    UNKNOWN
} RESPType;

typedef struct
{
    RESPType type;
    char *value; // Assuming value is a string for simplicity
} RESPCommand;

typedef struct
{
    RESPCommand *commands;
    size_t size;
    size_t capacity;
} RESPQueue;

void initQueue(RESPQueue *queue, size_t capacity);
void enqueue(RESPQueue *queue, RESPCommand command);
void freeQueue(RESPQueue *queue);

RESPCommand parseBulkString(RESPQueue *respQueue, char *buffer, size_t *index);
void parseArray(RESPQueue *respQueue, char *buffer, size_t *index);
void parseRedisCommand(RESPQueue *respQueue, char *buffer);

#endif // REDIS_PARSER_H