#ifndef _LIBCOMMAND_H_
#define _LIBCOMMAND_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

typedef int(*command_handler_t)(void* data, int argc, char** argv);

typedef struct _command
{
	command_handler_t run;
	char name[128];
} command_t;

/* Search for the command in the commands array and execute the given
	command, passing in all parameters in the line.

	The commands array must be terminated with an entry containing a
	NULL "run" handler.

	Upon finding a matching command, the return value of the command
	is returned. If there is an error, -1 is returned and errno is set.

	Errors:

		ENOMEM - Out of memory.
		EINVAL - No such command
*/
int command_run(char* line, command_t* commands, void* data);

#endif