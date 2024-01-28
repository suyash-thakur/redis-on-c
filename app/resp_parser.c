#include <stdio.h>
#include <stdlib.h>
#include "include/resp_parser.h"

void initQueue(RESPQueue *queue, size_t capacity)
{
    queue->commands = malloc(capacity * sizeof(RESPCommand));
    queue->size = 0;
    queue->capacity = capacity;
}

void enqueue(RESPQueue *queue, RESPCommand command)
{
    if (queue->size < queue->capacity)
    {
        queue->commands[queue->size++] = command;
    }
    else
    {
        printf("Queue is full. Cannot enqueue.\n");
    }
}

void freeQueue(RESPQueue *queue)
{
    free(queue->commands);
}

RESPCommand parseBulkString(RESPQueue *respQueue, char *buffer, size_t *index)
{
    (*index)++;

    int length = 0;
    while (buffer[*index] != '\r')
    {
        length = length * 10 + (buffer[(*index)++] - '0');
    }

    (*index) += 2;

    printf("Bulk String: ");
    char *string = malloc(length + 1);
    for (int i = 0; i < length; i++)
    {
        string[i] = buffer[(*index)++];
    }

    (*index) += 2;

    string[length] = '\0';

    RESPCommand command = {BULK_STRING, string};
    return command;
}

void parseArray(RESPQueue *respQueue, char *buffer, size_t *index)
{
    (*index)++;

    int elements = 0;
    while (buffer[*index] != '\r')
    {
        elements = elements * 10 + (buffer[(*index)++] - '0');
    }

    (*index) += 2;

    for (int i = 0; i < elements; i++)
    {
        RESPCommand element = parseBulkString(respQueue, buffer, index);
        element.type = BULK_STRING;
        enqueue(respQueue, element);
    }
}

void parseRedisCommand(RESPQueue *respQueue, char *buffer)
{
    size_t index = 0;

    switch (buffer[index])
    {
    case '*':
    {
        parseArray(respQueue, buffer, &index);
        break;
    }
    default:
        printf("Unknown command type %c\n", buffer[index]);
    }
}