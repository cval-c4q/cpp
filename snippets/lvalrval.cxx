#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

void foo(const std::vector<int> &v) {
	std::cout << __func__ << " - &cv: <";
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, ","));
	std::cout << ">\n";
}

void foo(std::vector<int> &&v) {
	std::cout << __func__ << " - &&rv: <";
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, ","));
	std::cout << ">\n";
}

void bar(const std::vector<int> &v) {
	std::cout << __func__ << " - &cv: <";
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, ","));
	std::cout << ">\n";
}

int main() {
	std::vector<int> v{1,2,3};

	foo(v);                       // lval ref call
	foo(std::vector<int>{4,5,6}); // rval ref call

	bar(v);                       // const lval ref call
	bar(std::vector<int>{7,8,9}); // const lval ref with temp call
}
