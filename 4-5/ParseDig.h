#pragma once
#include <cstdint>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

class ParseDig
{
private:
	std::vector<std::uint64_t> decomp;
public:
	ParseDig();
	~ParseDig();
	ParseDig(ParseDig &);
	void decompose(uint64_t);
	std::string print() const;
	std::string short_print() const;
	uint64_t check() const;
	void clear();
};
