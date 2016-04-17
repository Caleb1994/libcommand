/*
* @Author: caleb
* @Date:   2016-04-17 15:38:51
* @Last Modified by:   caleb
* @Last Modified time: 2016-04-17 15:57:46
*/
#include "command.h"
#include <stdio.h>
#include <stdlib.h>

int command_run(char* line, command_t* cmd, void* data)
{
	char* last = (strlen(line)-1) + line;
	char* iter = line-1;
	int argc;
	char** argv;
	int i = 0, result = 0;

	// Empty line
	if( *line == '\0' ) return 0;

	// Strip whitespace
	while( *line == ' ' || *line == '\t' ){
		line++;
	}
	for(; *last == ' ' || *last == '\t'; last--){
		*last = 0;
	}

	// Count arguments
	for(argc = 0; iter != NULL;
		argc++, iter = strchr(iter+1, ' '));
	// allocate argument array
	argv = calloc(argc, sizeof(char*));
	if( argv == NULL ){
		return -1;
	}

	for(char* tok = strtok(line, " \t\n");
		tok != NULL; tok = strtok(NULL, " \t\n") )
	{
		argv[i++] = tok;
	}

	for(i = 0; cmd[i].run != NULL; ++i){
		if( strcmp(cmd[i].name, argv[0]) == 0 ){
			result = cmd[i].run(data, argc, argv);
			break;
		}
	}
	if( cmd[i].name == NULL ){
		errno = EINVAL;
		return -1;
	}

	free(argv);

	return result;
}