#include <stdexcept>
#include <string>
#include "person.h"

void Person::setName(std::string const &name) {
	d_name = name;
}

void Person::setAddress(std::string const &address) {
	d_address = address;
}

void Person::setPhone(std::string const &phone) {
	if (phone.find_first_not_of("0123456789") == std::string::npos)
		d_phone = phone;
	else if (phone.empty())
		d_phone = " - not available - ";
	else
		throw new std::invalid_argument(std::string{__func__} + ": Invalid phone number format");
}

void Person::setMass(size_t mass) {
	d_mass = mass;
}

std::string const &Person::name() const {
	return d_name;
}

std::string const &Person::address() const {
	return d_address;
}

std::string const &Person::phone() const {
	return d_phone;
}

size_t Person::mass() const {
	return d_mass;
}

