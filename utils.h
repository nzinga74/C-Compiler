#ifndef UTILS_H
#define UTILS_H
#include <unordered_map>
#include <iostream>
#include "./tokens/type_token.h"
#include "file_reader.h"
#include "./tokens/token.h"
#include <algorithm>
#include <cctype>
#include <regex>
#include <string>
using namespace std;

class Utils
{
public:
    static bool isEnter(char ch)
    {
        if (ch == '\n')
            return true;
        return false;
    }
    static bool isWhiteSpace(char ch)
    {
        if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n' || isspace(ch))
            return true;
        return false;
    }
    static bool isHeader(string str)
    {
        regex regex("^<([a-zA-Z]+[0-9]*)\\.h>$");
        return regex_match(str, regex);
    }
    static bool isAlnumAndPoint(char ch)
    {
        if (ch == '.' || isalnum(ch))
            return true;
        return false;
    }
    static bool isValidHeaderCaracter(char ch)
    {
        if ((ch == '\n' || ch == '>' || (!isAlnumAndPoint(ch))))
            return false;

        return true;
    }
    static void imprimirToken(TypeToken token)
    {
        unordered_map<TypeToken, string> tokens = {
            {TOKEN_ID, "TOKEN_ID"},
            {TOKEN_OPEN_PARENTHESE, "TOKEN_OPEN_PARENTHESE"},
            {TOKEN_CLOSE_PARENTHESE, "TOKEN_CLOSE_PARENTHESE"},
            {TOKEN_OPEN_BRACKET, "TOKEN_OPEN_BRACKET"},
            {TOKEN_CLOSE_BRACKET, "TOKEN_CLOSE_BRACKET"},
            {TOKEN_OPEN_BRACE, "TOKEN_OPEN_BRACE"},
            {TOKEN_CLOSE_BRACE, "TOKEN_CLOSE_BRACE"},
            {TOKEN_SEMICOLON, "TOKEN_SEMICOLON"},
            {TOKEN_SIMPLE_COMMENT, "TOKEN_SIMPLE_COMMENT"},
            {TOKEN_MULTLINE_COMMENT, "TOKEN_MULTLINE_COMMENT"},
            {TOKEN_ATRIB, "TOKEN_ATRIB"},
            {TOKEN_QUESTION, "TOKEN_QUESTION"},
            {TOKEN_TWO_POINT, "TOKEN_TWO_POINT"},
            {TOKEN_POINT, "TOKEN_POINT"},
            {TOKEN_COMMA, "TOKEN_COMMA"},
            {TOKEN_ARROW, "TOKEN_ARROW"},
            {TOKEN_SCOPE, "TOKEN_SCOPE"},
            {TOKEN_OPR_PLUS, "TOKEN_OPR_PLUS"},
            {TOKEN_OPR_PLUS_EGUAL, "TOKEN_OPR_PLUS_EGUAL"},
            {TOKEN_OPR_DOUBLE_PLUS, "TOKEN_OPR_DOUBLE_PLUS"},
            {TOKEN_OPR_MULT, "TOKEN_OPR_MULT"},
            {TOKEN_OPR_MUL_EGUAL, "TOKEN_OPR_MUL_EGUAL"},
            {TOKEN_OPR_DOUBLE_MULT, "TOKEN_OPR_DOUBLE_MULT"},
            {TOKEN_OPR_DIV, "TOKEN_OPR_DIV"},
            {TOKEN_OPR_DIV_EGUAL, "TOKEN_OPR_DIV_EGUAL"},
            {TOKEN_OPR_DOUBLE_DIV, "TOKEN_OPR_DOUBLE_DIV"},
            {TOKEN_OPR_SUBS, "TOKEN_OPR_SUBS"},
            {TOKEN_OPR_DOUBLE_SUBS, "TOKEN_OPR_DOUBLE_SUBS"},
            {TOKEN_OPR_SUBS_EGUAL, "TOKEN_OPR_SUBS_EGUAL"},
            {TOKEN_MOD, "TOKEN_MOD"},
            {TOKEN_MOD_EGUAL, "TOKEN_MOD_EGUAL"},
            {TOKEN_BIT_OR, "TOKEN_BIT_OR"},
            {TOKEN_BIT_AND, "TOKEN_BIT_AND"},
            {TOKEN_BIT_NOT, "TOKEN_BIT_NOT"},
            {TOKEN_BIT_XOR, "TOKEN_BIT_XOR"},
            {TOKEN_OR, "TOKEN_OR"},
            {TOKEN_AND, "TOKEN_AND"},
            {TOKEN_NOT, "TOKEN_NOT"},
            {TOKEN_DIFFERENT, "TOKEN_DIFFERENT"},
            {TOKEN_RIGHT_SHIFT, "TOKEN_RIGHT_SHIFT"},
            {TOKEN_LEFT_SHIFT, "TOKEN_LEFT_SHIFT"},
            {TOKEN_GREAT_THAN, "TOKEN_GREAT_THAN"},
            {TOKEN_GREAT_IGUAL_THAN, "TOKEN_GREAT_IGUAL_THAN"},
            {TOKEN_LESS_THAN, "TOKEN_LESS_THAN"},
            {TOKEN_LESS_IGUAL_THAN, "TOKEN_LESS_IGUAL_THAN"},
            {TOKEN_EGUAL, "TOKEN_EGUAL"},
            {TOKEN_DIF, "TOKEN_DIF"},
            {TOKEN_IF, "TOKEN_IF"},
            {TOKEN_WHILE, "TOKEN_WHILE"},
            {TOKEN_DO, "TOKEN_DO"},
            {TOKEN_ELSE, "TOKEN_ELSE"},
            {TOKEN_SWITCH, "TOKEN_SWITCH"},
            {TOKEN_CASE, "TOKEN_CASE"},
            {TOKEN_BREAK, "TOKEN_BREAK"},
            {TOKEN_FOR, "TOKEN_FOR"},
            {TOKEN_CONTINUE, "TOKEN_CONTINUE"},
            {TOKEN_FINALLY, "TOKEN_FINALLY"},
            {TOKEN_AUTO, "TOKEN_AUTO"},
            {TOKEN_CONST, "TOKEN_CONST"},
            {TOKEN_ENUM, "TOKEN_ENUM"},
            {TOKEN_EXTERN, "TOKEN_EXTERN"},
            {TOKEN_GOTO, "TOKEN_GOTO"},
            {TOKEN_REGISTER, "TOKEN_REGISTER"},
            {TOKEN_STATIC, "TOKEN_STATIC"},
            {TOKEN_SIZEOF, "TOKEN_SIZEOF"},
            {TOKEN_TYPEDEF, "TOKEN_TYPEDEF"},
            {TOKEN_UNION, "TOKEN_UNION"},
            {TOKEN_VOLALILE, "TOKEN_VOLATILE"}, // Corrigir: TOKEN_VOLATILE
            {TOKEN_STRUCT, "TOKEN_STRUCT"},
            {TOKEN_INT, "TOKEN_INT"},
            {TOKEN_FLOAT, "TOKEN_FLOAT"},
            {TOKEN_CHAR, "TOKEN_CHAR"},
            {TOKEN_DOUBLE, "TOKEN_DOUBLE"},
            {TOKEN_LONG, "TOKEN_LONG"},
            {TOKEN_SHORT, "TOKEN_SHORT"},
            {TOKEN_SIGNED, "TOKEN_SIGNED"},
            {TOKEN_UNSIGNED, "TOKEN_UNSIGNED"},
            {TOKEN_VOID, "TOKEN_VOID"},
            {TOKEN_END, "TOKEN_END"},
            {TOKEN_RETURN, "TOKEN_RETURN"},
            {TOKEN_NOT_FOUND, "TOKEN_NOT_FOUND"},
            {TOKEN_VALUE_INT, "TOKEN_VALUE_INT"},
            {TOKEN_VALUE_DOUBLE, "TOKEN_VALUE_DOUBLE"},
            {TOKEN_VALUE_FLOAT, "TOKEN_VALUE_FLOAT"},
            {TOKEN_VALUE_STRING, "TOKEN_VALUE_STRING"},
            {TOKEN_MACRO_INCLUDE, "TOKEN_MACRO_INCLUDE"},
            {TOKEN_HEADER, "TOKEN_HEADER"},
        };
        int count = tokens.count(token);
        if (count > 0)
        {
            cout << tokens[token];
        }
    }
};

#endif