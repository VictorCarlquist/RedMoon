#include <vector>
#include <iostream>

#ifndef __UTIL__
#define __UTIL__


namespace red{

    std::vector<std::string> split(std::string l , std::string delimiter)
	{
        std::vector<std::string> c;
		size_t current;
		size_t next = -1;
		do
		{
			current = next + 1;
			next = l.find_first_of( delimiter, current );
            c.push_back(l.substr( current, next - current ));
		}
        while (next != std::string::npos);
		return c;
	}

}
#endif
