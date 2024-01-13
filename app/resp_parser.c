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

void parseBulkString(char *buffer, size_t *index)
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

    printf("%s\n", string);
    printf("\n");
}

void parseArray(char *buffer, size_t *index)
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

        parseBulkString(buffer, index);
    }
}

void parseRedisCommand(char *buffer)
{
    size_t index = 0;

    switch (buffer[index])
    {
    case '*':
        parseArray(buffer, &index);
        break;
    default:
        printf("Unknown command type\n");
    }
}