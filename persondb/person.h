#ifndef	_PERSON_H
#define	_PERSON_H

#include <string>

class Person {
	std::string d_name;	// name of person
	std::string d_address;	// address
	std::string d_phone;	// telephone number
	size_t d_mass;		// mass in kg

	public:
		void setName(std::string const &name);
		void setAddress(std::string const &address);
		void setPhone(std::string const &phone);
		void setMass(size_t mass);

		std::string const &name() const;
		std::string const &address() const;
		std::string const &phone() const;
		size_t mass() const;
};

#endif	/* _PERSON_H */

