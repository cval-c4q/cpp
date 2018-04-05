/**
 *   Solution by <>
 *   Write a program to copy its input to its output, replacing each string
 *   of one or more blanks by a single blank.
 */

#include <iostream>
#include <cctype>

int main()
{
	char c;
	while (std::cin.get(c)) {
		if (isblank(c) && isblank(std::cin.peek()))
			continue;
		else
			std::cout.put(c);
	}

	return 0;
}
