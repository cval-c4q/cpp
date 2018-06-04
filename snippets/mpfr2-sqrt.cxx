#include <iostream>
#include <string>	// std::stoul
#include <mpfr.h>

std::ostream & operator<<(std::ostream &o, mpfr_t f) {
	size_t n = mpfr_snprintf(nullptr, 0, "%Re", f);
	char *buf = new char[n+1];
	mpfr_snprintf(buf, n, "%Re", f);
	o << buf;
	delete[] buf;
	return o;
}

int main(int argc, char *argv[])
{
	std::cout << "MPFR version: " << MPFR_VERSION_STRING << "\n";
	std::cout << "MPFR precision (bits), min=" << MPFR_PREC_MIN << ", max=" << MPFR_PREC_MAX << "\n";
	std::cout << "MPFR default precision (bits): " << mpfr_get_default_prec() << "\n";

	/*
	 *  read-in precisiopn, default to 256
	 */
	mpfr_prec_t prec;
	if (argc > 1)
		prec = std::stoull(argv[1]);
	else
		prec = 256;

	std::cout << "Using precision: " << prec << "\n";

	/*
	 *  read-in x, defaulting to 2
	 */
	mpfr_t x;
	mpfr_init2(x, prec);
	if (argc > 2)
		mpfr_set_str(x, argv[2], 10, MPFR_RNDN);
	else
		mpfr_set_d(x, 2.0, MPFR_RNDN); // default is sqrt(2)

	/*
	 *  Number of iterations, default is 10
	 */
	unsigned long num_iterations;
	if (argc > 3)
		num_iterations = std::stoul(argv[3]);
	else
		num_iterations = 10;


	mpfr_t guess, avg;
	mpfr_init2(guess, prec);
	mpfr_init2(avg, prec);
	mpfr_set_d(guess, 1.0, MPFR_RNDN);
	for (unsigned long i = 0; i < num_iterations; i++) {
		mpfr_div(avg, x, guess, MPFR_RNDN);
		mpfr_add(avg, avg, guess, MPFR_RNDN);
		mpfr_div_ui(guess, avg, 2, MPFR_RNDN);
		// std::cout << "Iteration " << i+1 << "\n";
		// std::cout << "\t1. avg = " << avg << ", guess = " << guess << ", x = " << x << "\n";
	}

	std::cout << "Result: " << guess << "\n";

	return 0;
}
