#include <cerrno>
#include <cstdarg>
#include <cstring>
#include <climits>
#include <stdexcept>
#include <memory>

static void ERROUT(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	std::shared_ptr<char> buf(new char[LINE_MAX]);
	size_t n = vsnprintf(buf.get(), LINE_MAX, fmt, ap);
	va_end(ap);
	throw std::runtime_error(std::string{buf.get()} + ": " + strerror(errno));
}

