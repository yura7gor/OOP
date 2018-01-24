#include "ParseDig.h"

ParseDig::ParseDig()
{}

ParseDig::ParseDig(ParseDig &d)
{
	decomp = d.decomp;
}

ParseDig::~ParseDig()
{
	decomp.clear();
}

void ParseDig::decompose(uint64_t x)
{
	for (uint64_t div = 2; div < sqrt(x); div += 2)
	{
		while (x % div == 0)
		{
			decomp.push_back(div);
			x /= div;
		}
		if (div == 2)
			div--;
	}
	if (x != 1)
		decomp.push_back(x);
}

std::string ParseDig::print() const
{
	std::ostringstream oss;
	for (auto i = decomp.begin(); i < decomp.end(); i++)
	{
		oss << *i;
		if ((i + 1) != decomp.end())
			oss << " * ";
	}
	oss << " = " << check() << "\n";
	return oss.str();
}

std::string ParseDig::short_print() const
{
	std::ostringstream oss;
	uint64_t temp = decomp.front();
	int deg = 0;
	for (auto i = decomp.begin(); i < decomp.end(); i++)
	{
		if (temp != *i)
		{
			if (deg != 1)
				oss << temp << "^" << deg << " * ";
			else
				oss << temp << " * ";
			temp = *i;
			deg = 1;
		}
		else
			deg++;
		if ((i + 1) == decomp.end())
		{
			if (deg != 1)
				oss << temp << "^" << deg;
			else
				oss << temp;
		}
	}
	oss << " = " << check() << "\n";
	return oss.str();
}

uint64_t ParseDig::check() const
{
	uint64_t res = 1;
	for (uint64_t i : decomp)
		res *= i;
	return res;
}

void ParseDig::clear()
{
	decomp.clear();
}
