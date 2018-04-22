/**
 *  Implementation of an in-place Merge Sort variant (no sub-array copying)
 *  Uses C++11 STL facilities for debugging and testing.
 */
#include <cassert>
#include <vector>
using off_t = long int;

#ifndef	DEBUG
#define	DEBUG 0
#endif

#include <algorithm>
#include <iostream>
#include <iterator>

template<typename T>
void MERGE(std::vector<T> &a, off_t p, off_t q, off_t r,
	bool (*cmp)(const T &a, const T &b)=[](const T &a, const T &b){return bool(a < b);})
{
	assert(p <= q && q < r);
	assert(a.size() >= r-1);

	auto dumpSubVects = [&]() {
		if (!DEBUG)
			return;
		std::cerr << "A[p..q]: ";
		std::copy(a.begin()+p, a.begin()+q+1, std::ostream_iterator<T>(std::cerr, ","));
		std::cerr << "\nA[q+1..r]: ";
		std::copy(a.begin()+q+1, a.begin()+r+1, std::ostream_iterator<T>(std::cerr, ","));
		std::cerr << "\n";
	};

	off_t i = p;
	off_t j = q+1;
	for (off_t n=p; n <= r; n++) {
		static auto nIter = 0U;
		DEBUG && std::cerr << "\nIteration " << ++nIter << ", i=" << i << ", j=" << j << std::endl;

		assert(i <= q);
		assert(j <= r);
		dumpSubVects();


		if (cmp(a[i], a[j])) {
			DEBUG && std::cerr << "Selecting " << a[i] << " next.\n";
			if (n > q) {
				auto tmp = a[j];
				
			}
			i++;
		} else {
			DEBUG && std::cerr << "Selecting " << a[j] << " next.\n";

			if (n <= q) { // opposite side
				auto tmp = a[i];
				a[i] = a[j];
				off_t k = j;
				while (k < r && cmp(a[k+1], tmp)) { // select position, shifting as needed
					a[k] = a[k+1];
					k++;
				}
				a[k] = tmp;
				i++;
			} else // same side
				j++;
		}

		if (i > q || j > r) {
			DEBUG && std::cerr << "One of the subarrays has no more elements. merge complete.\n";
			break;
		}
	}

	DEBUG && std::cerr << "\nResulting subarrays:\n", dumpSubVects();
}

template<typename T>
void MERGESORT(std::vector<T> &a, off_t p, off_t r)
{
	if (p >= r)
		return;
	MERGESORT(a, p, (p+r)/2);
	MERGESORT(a, (p+r)/2+1, r);
	MERGE(a, p, (p+r)/2, r);
}

template<typename T>
int sortVec(T &&v) {
	std::cout << "Merge sorting vector A: <";
	std::copy(v.begin(), v.end(), std::ostream_iterator<decltype(v[0])>(std::cout, ","));
	std::cout << ">\n";

	MERGESORT(v, 0, v.size()-1);

	std::cout << "Resulting vector A': <";
	std::copy(v.begin(), v.end(), std::ostream_iterator<decltype(v[0])>(std::cout, ","));
	std::cout << ">\n";
}

int main()
{
	srand(time(NULL));

	sortVec(std::vector<int>{1,3,5,2,4,6});

	std::vector<int> intVec(10);
	std::generate(intVec.begin(), intVec.end(), []() { return rand() % 100; });
	sortVec(intVec);

	std::vector<std::string> strVec(10);
	std::generate(strVec.begin(), strVec.end(), []() {
			static char buf[4];
			for (int n = 0; n < sizeof(buf)-1; n++)
				if (rand() % 2)
					buf[n] = 'a' + rand() % 26;
				else
					buf[n] = '0' + rand() % 10;
			buf[sizeof(buf)-1] = '\0';
			return buf;
		});
	sortVec(strVec);
}
