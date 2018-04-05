#include <cstdlib>
#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << ": LOG-FILE\n";
		return EXIT_FAILURE;
	}

	std::ofstream errlog;
	std::streambuf *saved_buff = nullptr;
	if (errlog.open(argv[1]); !errlog) {
		std::cerr << "Error opening " << argv[1] << " as log file.\n";
		return EXIT_FAILURE;
	} else {
		saved_buff = std::cerr.rdbuf(errlog.rdbuf());
		std::cerr << "Successfully starting logging to file " << argv[1] << ".\n";
	}

	std::cerr << "Several messages to stderr, msg1\n";
	std::cerr << "Several messages to stderr, msg2\n";

	std::cerr.rdbuf(saved_buff);
	std::cerr << "Program terminating...\n";
	return EXIT_SUCCESS;
}
