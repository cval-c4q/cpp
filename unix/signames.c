#include <stddef.h>
#include <signal.h>
#include "signames.h"

const char *sig_to_str(int signo)
{
	unsigned i;
	if (signo <= 0 || signo >= NSIG)
		return NULL;
	for (i = 0; i < sizeof(signametbl)/sizeof(struct signame); i++) {
		if (signo == signametbl[i].signo)
			return signametbl[i].name;
	}
	
	return NULL; /* Not found */
}
