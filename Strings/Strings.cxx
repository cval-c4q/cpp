#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <stdexcept>
#include "Strings.h"

void DEBUG(const char *fmt, ...) {
#ifndef	NDEBUG
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
#endif
}

/**
 *  direct constructor
 */
Strings::Strings(size_t argc, const char *const *argv)
{
	if (argc > 0 && argv == nullptr)
		throw std::invalid_argument("NULL argv with nonzero argc");

	d_size = argc;
	d_string = new std::string[argc];
	for (size_t i = 0; i < argc; i++)
		d_string[i] = argv[i];

	DEBUG("%s(): this=%p, d_string=%p, d_size: %zu\n", __func__, this, d_string, d_size);
}

/**
 *  Copy constructor
 */
Strings::Strings(const Strings &other)
	: d_size(other.d_size),
	  d_string(new std::string[other.d_size])
{
	for (size_t i = 0; i < other.d_size; i++)
		d_string[i] = other.d_string[i];

	DEBUG("%s(copy): this=%p, d_string=%p, d_size: %zu\n", __func__, this, d_string, d_size);
}

/**
 *  Move constructor
 */
Strings::Strings(Strings &&other) noexcept
{
	DEBUG("%s(move): this=%p, d_string=%p, d_size: %zu\n", __func__, this, d_string, d_size);

	swap(other);
}

/**
 *  Destructor
 */
Strings::~Strings()
{
	DEBUG("%s: this=%p, d_string=%p, d_size: %zu\n", __func__, this, d_string, d_size);

	if (d_string != nullptr)
		delete[] d_string;
}

/**
 *  Overloaded assignment
 */
Strings &Strings::operator=(Strings &other)
{
	DEBUG("%s: this: %p, other: %p\n", __func__, this, &other);
	DEBUG("%s: before: d_string: %p, d_size: %zu\n", __func__, d_string, d_size);

	Strings tmp{other};
	swap(tmp);

	DEBUG("%s:  after: d_string: %p, d_size: %zu\n", __func__, d_string, d_size);
	return *this;
}

void Strings::swap(Strings &other) {
	DEBUG("%s: this: %p, other: %p\n", __func__, this, &other);

	uint8_t buffer[sizeof(Strings)];
	memcpy(buffer, this, sizeof(Strings));
	memcpy(this, &other, sizeof(Strings));
	memcpy(&other, buffer, sizeof(Strings));
}

size_t Strings::size() const
{
	return d_size;
}

void Strings::display() const
{
	printf("size: %zu, strings: %p\n", d_size, d_string);
	for (size_t i = 0; i < d_size; i++)
		printf("%p[%zu]: %s\n", this, i, d_string[i].c_str());
}

const std::string &Strings::at(size_t i) const {
	if (d_string == nullptr || i >= d_size)
		throw std::out_of_range("out-of-bounds access");
	return d_string[i];
}

