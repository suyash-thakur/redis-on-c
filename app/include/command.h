#ifndef COMMAND_H
#define COMMAND_H

#include <stdio.h>

typedef enum
{
    GET,
    SET,
    DEL,
    ECHO,
} CommandType;

typedef struct
{
    CommandType type;
    char *key;
    char *value;
} Command;

Command *parse_command(char *buffer);

#endif