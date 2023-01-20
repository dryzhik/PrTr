//G'
// E::=A{|A}
// A::=S{&S}
// S::=T{>>T}|T{<<T}
// T::=~F|F
// F ::= (E)|i

#include <iostream>
#include "parser.h"

int main()
{
    Parser Parser;
    Parser.showResult();
    int result = (1&~6);
 
    std::cout << result << std::endl;
    
}
