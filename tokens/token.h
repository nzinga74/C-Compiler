#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>
#include "type_token.h"
using namespace std;

class Token
{
public:
    TypeToken name;
    string lexama;
    int line;
    Token(TypeToken name, string lexema, int line)
    {
        this->name = name;
        this->lexama = lexema;
        this->line = line;
    }
};
#endif