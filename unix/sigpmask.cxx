#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <exception>

#include "signames.h"
#include "errout.h"


int main() {
	try {
		std::cout << "sizeof(sigset_t): " << sizeof(sigset_t) << "\n";
		std::cout << "NSIG: " << NSIG << "\n";

		sigset_t sset;
		if (sigprocmask(0, NULL, &sset) < 0)
			ERROUT("sigprocmask() failed");

	} catch (const std::exception &err) {
		std::cerr << "Exception occurred: " << err.what() << "\n";
		exit(EXIT_FAILURE);
	}

	return 0;
}
