# libcommand - Command Line parser for C

libcommand is a simple command line parser for C. You simply create an array of command handlers with associated names, and then call `command_run` with your 
input line (presumably from readline or gets), the command array, and an optional extra data parameter and watch the magic happen.

## Functions

### `int command_run(char* line, command_t* commands, void* data)`

	Parses the line into argc/argv and calls the cooresponding command in the commands array.

	Parameters:
		* line - the input line you retrieved from the user
		* commands - the array of commands. the last entry should have a NULL `run` callback.
		* data - optional. this should hold other data you need passed to the callback.
	Return Value:
		* If a command is matched, then the return value of the callback is returned.
		* On error, -1 is returned and `errno` is set appropriately.
	Errors:
		* ENOMEM - No memory could be allocated for argv.
		* EINVAL - No such command found in the command array.

## Types

### `typedef int(*command_handler_t)(void* data, int argc, char** argv)`

	The function type for handler functions. This takes an argc/argv pair and a data parameter from the calling function.

	The return value is passed back to the main function.

### `typedef struct _command command_t`

	Defines the command structure. This structure contains at least two items:

	* `name`: Character array indicating the command name
	* `run`: A `command_handler_t` to call when found in the input line.

