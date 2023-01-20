//G'
// E::=A{|A}
// A::=S{&S}
// S::=T{>>T}|T{<<T}
// T::=~F|F
// F ::= (E)|i
#pragma once
#include <string>

enum {
	BOR,    // |
	BAND,   // &
	LSHIFT, // <<
	RSHIFT, // >>
	TILDA,  // ~
	LBRACE, // (
	RBRACE, // )
	INT,    // i
	END     //end of file
};

class Parser
{
public:
	Parser();
	~Parser();
	int scan();
	std::string readInput();
	void showResult();

	int symbol = -1;
	int value;
	std::string input;
	int result;

private:
	int e();
	int a();
	int s();
	int t();
	int f();
};

