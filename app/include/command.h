#ifndef COMMAND_H
#define COMMAND_H

#include <stdio.h>

typedef enum
{
    GET,
    SET,
    DEL,
    ECHO,
    INVALID
} CommandType;

typedef struct
{
    CommandType type;
    char *key;
    char *values;
} Command;

typedef struct
{
    Command *commands;
    size_t size;
} Commands;

Commands parseCommands(char *buffer);
void freeCommands(Commands *commands);

#endif