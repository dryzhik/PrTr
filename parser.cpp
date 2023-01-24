#include "parser.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <cctype>
#include <cmath>

Parser::Parser()
{
	input = readInput();
	symbol = scan();
	result = 0;
}

Parser::~Parser()
{
}

std::string Parser::readInput()
{
	std::string userInput;
	std::cin >> userInput;
	return userInput;
}

void Parser::showResult()
{	
	result = e();
	
	if (symbol != END)
	{
		std::cout << "Incorrect input" << std::endl;
		exit(-1);
	}
	
	std::cout << "Result:" << " "<< result << std::endl;
}

int Parser::scan()
{
	while (1)
	{
		char token = input[0];
		input.erase(0, 1);
		
		if (token == ' ' || token == '\t' || token == '\n' || token == '\r') break;
		else if (token == '|')  return BOR;
		else if (token == '&')  return BAND;
		else if (token == '<' && input[0] == '<')
		{
			input.erase(0, 1);
			return LSHIFT;
		}
		else if (token == '>' && input[0] == '>')
		{
			input.erase(0, 1);
			return RSHIFT;
		}
		else if (token == '~')  return TILDA;
		else if (token == '(')  return LBRACE;
		else if (token == ')')  return RBRACE;
		else if (token >= '0' && token <= '9')
		{
			value = token - '0';
			char token = input[0];
			while (token >= '0' && token <= '9')
			{
				value = value * 10 + token - '0';
				input.erase(0, 1);
				token = input[0];
			}
			return INT;
		}
		else if (token == EOF || token == '\0') return END;
		else
		{
			std::cout << "Unknown input" << std::endl;
			exit(0);
		}
	}
	return 0;
}

int Parser::e()
{
	int resA = a();
	while (symbol == BOR)
	{
		symbol = scan();
		resA |= t();
	}
	
	return resA;
}

int Parser::a()
{
	int resS = s();
	while (symbol == BAND)
	{
		symbol = scan();
		resS &= t();
	}
	return resS;
}

int Parser::s()
{
	int resT = t();
	while (symbol == LSHIFT || symbol == RSHIFT)
	{
		if (symbol == LSHIFT)
		{
			symbol = scan();
			resT <<= t();
		}
		if (symbol == RSHIFT)
		{
			symbol = scan();
			resT >>= t();
		}
	}
	return resT;
}

int Parser::t()
{
	int resF = 0;
	if (symbol == TILDA)
	{
		symbol = scan();
		resF = f();
		resF = ~(resF);
	}
	else
	{
		resF = f();
	}
	return resF;
}

int Parser::f()
{
	if (symbol == LBRACE)
	{
		symbol = scan();
		int resE = e();
		if (symbol != RBRACE)
		{
			std::cout << "Brace disballance" << std::endl;
			exit(-1);
		}
		symbol = scan();
		return resE;
	}
	else if (symbol == INT)
	{
		int resI = value;
		symbol = scan();
		return resI;
	}
	else
	{
		std::cout << "Incorrect input" << std::endl;
		exit(-1);
	}
}
