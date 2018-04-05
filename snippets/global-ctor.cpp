#include <iostream>

class Tst {
	public:
	Tst() {
		std::cout << "Gloal Ctor...\n";
	}
	~Tst() {
		std::cout << "Global Dtor...\n";
	}
};

Tst tst;

int main() {
	return 0;
}

