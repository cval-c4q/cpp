#ifndef	STRINGS_H
#define	STRINGS_H

#include <cstddef>
#include <string>

class Strings {
	std::string *d_string = nullptr;
	size_t d_size = 0;

	public:
		Strings() = default;
		Strings(size_t, const char *const *);
		Strings(const Strings &other);
		Strings(Strings &&other) noexcept;
		~Strings();

		Strings &operator=(Strings &other);

		void display() const;
		const std::string &at(size_t i) const;
		size_t size() const;
		void swap(Strings &other);
};

#endif /* STRINGS_H */

