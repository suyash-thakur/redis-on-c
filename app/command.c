#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/resp_parser.h"
#include "include/command.h"

int isCommand(char *buffer)
{
    return strcmp(buffer, "GET") == 0 || strcmp(buffer, "SET") == 0 || strcmp(buffer, "DEL") == 0 || strcmp(buffer, "ECHO") == 0;
}

CommandType getCommandType(char *command)
{
    if (strcmp(command, "GET") == 0)
    {
        return GET;
    }
    else if (strcmp(command, "SET") == 0)
    {
        return SET;
    }
    else if (strcmp(command, "DEL") == 0)
    {
        return DEL;
    }
    else if (strcmp(command, "ECHO") == 0)
    {
        return ECHO;
    }
    else
    {
        return INVALID;
    }
}

Commands parseCommands(char *buffer)
{
    Commands commands;
    commands.size = 0;
    size_t index = 0;
    size_t commandIndex = 0;

    RESPQueue respQueue;
    initQueue(&respQueue, 10);

    parseRedisCommand(&respQueue, buffer);

    commands.commands = malloc(respQueue.size * sizeof(Command));

    while (index < respQueue.size)
    {

        if (index == 0)
        {
            if (isCommand(respQueue.commands[index].value))
            {
                commands.commands[commandIndex].type = getCommandType(respQueue.commands[index].value);
                index++;
                commandIndex++;
            }
            else
            {
                printf("Invalid command\n");
                return commands;
            }
        }
        else
        {
            if (isCommand(respQueue.commands[index].value))
            {
                commands.commands[commandIndex].type = getCommandType(respQueue.commands[index].value);
                commandIndex++;
                index++;
            }
            else
            {
                commands.commands[commandIndex - 1].values = respQueue.commands[index].value;
                index++;
            }
        }
    }
    freeQueue(&respQueue);
    commands.size = commandIndex;
    printf("Command size: %zu\n", commands.size);

    return commands;
}

void freeCommands(Commands *commands)
{
    for (size_t i = 0; i < commands->size; i++)
    {
        free(commands->commands[i].key);
        free(commands->commands[i].values);
    }
    free(commands->commands);
}