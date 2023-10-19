#include "simshell.h"

/**
 * get_signalint - Handle crtl + c
 * @sig: handler signal
 */
void get_signalint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
