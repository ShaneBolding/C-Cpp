#ifndef PARSER_
#define PARSER_

#include "param.hpp"

class Parser{

	public:
		Parser();
		
		Param* parse(char* input);

};

#endif
