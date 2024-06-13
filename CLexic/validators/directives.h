#ifndef DIRECTIVES_H
#define DIRECTIVES_H
#include <iostream>
#include "../../tokens/type_token.h"
#include "../file_reader.h"
#include "../../tokens/token.h"
#include <algorithm>
#include <cctype>
#include <unordered_map>

using namespace std;

class Directives
{
private:
    FileReader *reader;

public:
    Directives(FileReader *reader)
    {
        this->reader = reader;
    }
    TypeToken directives(string key)
    {
        unordered_map<string, TypeToken> directivesList = {
            {"#include", TOKEN_MACRO_INCLUDE},
            {"#define", TOKEN_MACRO_DEFINE},
            {"#undef", TOKEN_MACRO_UNDEF},
            {"#if", TOKEN_MACRO_IF},
            {"#ifdef", TOKEN_MACRO_IFDEF},
            {"#ifndef", TOKEN_MACRO_IFNDEF},
            {"#else", TOKEN_MACRO_ELSE},
            {"#elif", TOKEN_MACRO_ELIF},
            {"#endif", TOKEN_MACRO_ENDIF},
            {"#pragma", TOKEN_MACRO_PRAGMA},
            {"#error", TOKEN_MACRO_ERROR},
            {"#warning", TOKEN_MACRO_WARNING},
            {"#line", TOKEN_MACRO_LINE},
            {"#pragma once", TOKEN_MACRO_ONCE}};
        int count = directivesList.count(key);

        if (count > 0)
        {
            return directivesList[key];
        }
        else
        {
            return TOKEN_NOT_FOUND;
        }
    }
    Token *directivesValidator()
    {
        char ch = reader->readNextCaracter();
        if (ch == '#')
        {
            while ((ch = reader->readNextCaracter()) && isalpha(ch))
                ;

            reader->goBack();
            string lexema = reader->getLexema();
            TypeToken token = directives(lexema);
            return new Token(token, lexema, reader->getLine());
        }
        return NULL;
    }
};

#endif