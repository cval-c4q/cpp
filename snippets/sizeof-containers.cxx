#include <array>
#include <vector>
#include <string>

#include <typeinfo>
template<class T>
std::string infoT(const T &t) {
	return std::string{"sizeof "} + typeid(t).name() + ": " + std::to_string(sizeof(t))
		+ ", logical size: " + std::to_string(t.size());
}

#include <iostream>
int main() {
	std::array<int, 32> a;
	std::vector<int> v(100);
	std::string s {"Lorem ipsum dolor sit amet"};
	std::cout << infoT(a) << "\n";
	std::cout << infoT(v) << "\n";
	std::cout << infoT(s) << "\n";
}
