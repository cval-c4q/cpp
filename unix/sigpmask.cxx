#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <signal.h>
#include <exception>

#include "signames.h"
#include "errout.h"

void pr_sigset(const sigset_t *sset) {
	for (size_t i = 0; i < sizeof signametbl/sizeof(struct signame); i++) {
		std::cout << std::left;
		std::cout << std::setw(8) << signametbl[i].name
			<< ": " << (sset ? !!sigismember(sset, signametbl[i].signo) : signametbl[i].signo)
			<< ((i+1) % 5 ? "\t" : "\n");
	}
}

int main() {
	try {
		std::cout << "sizeof(sigset_t): " << sizeof(sigset_t)
			<< ", NSIG: " << NSIG << "\n";

		sigset_t sset;
		if (sigprocmask(0, NULL, &sset) < 0)
			ERROUT("%s: sigprocmask() failed", __func__);

		std::cout << "\nSignal name/signo table:\n";
		pr_sigset(nullptr);

		std::cout << "\nCurrent signal mask:\n";
		pr_sigset(&sset);

		signal(SIGINT, [](int signo) {
				std::cout << "\nCaught SIG" << sig_to_str(signo) << "!\n";

				sigset_t sset;
				if (sigprocmask(0, NULL, &sset) < 0)
					ERROUT("%s: sigprocmask() failed", __func__);
				std::cout << "SIG" << sig_to_str(signo) << " signal mask:\n";
				pr_sigset(&sset);

				std::cout << "SIG" << sig_to_str(signo) << ": sleeping for 5s...\n";
				sleep(5);

				if (sigpending(&sset) < 0)
					ERROUT("%s: sigpending() failed", __func__);
				std::cout << "SIG" << sig_to_str(signo) << ": pending signals:\n";
				pr_sigset(&sset);
		});

		pause();
	} catch (const std::exception &err) {
		std::cerr << "Exception occurred: " << err.what() << "\n";
		exit(EXIT_FAILURE);
	}

	return 0;
}
