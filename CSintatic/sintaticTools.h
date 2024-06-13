#ifndef SINTATIC_TOOLS
#define SINTATIC_TOOLS
#include <iostream>
#include <algorithm>
#include <cctype>
#include <regex>
#include <string>
#include <unordered_map>
#include "../tokens/type_token.h"
#include "../tokens/token.h"

class SintaticTools
{
public:
    static bool isTypeDef(TypeToken token)
    {

        unordered_map<TypeToken, string> typeDef = {
            {TOKEN_INT, "TOKEN_INT"},
            {TOKEN_FLOAT, "TOKEN_FLOAT"},
            {TOKEN_DOUBLE, "TOKEN_DOUBLE"},
            {TOKEN_CHAR, "TOKEN_CHAR"},
            {TOKEN_VOID, "TOKEN_VOID"}};
        int count = typeDef.count(token);
        if (count > 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    static bool isVarDecl(TypeToken token)
    {
        unordered_map<TypeToken, string> varDecl = {
            {TOKEN_SEMICOLON, ";"},
            {TOKEN_OPEN_BRACKET, "["},
            {TOKEN_ATRIB, "="},
            {TOKEN_COMMA, ","}};
        int count = varDecl.count(token);
        if (count > 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    static bool isFuncDecl(TypeToken token)
    {
        if (token == TOKEN_OPEN_PARENTHESE)
            return true;
        return false;
    }
    static bool isComStmt(TypeToken token)
    {
        if (token == TOKEN_OPEN_BRACE)
            return true;
        return false;
    }
    static bool isIfStmt(TypeToken token)
    {
        if (token == TOKEN_IF)
            return true;
        return false;
    }
    static bool isWhileStmt(TypeToken token)
    {
        if (token == TOKEN_WHILE)
            return true;
        return false;
    }
    static bool isEmptyParams(TypeToken token)
    {
        if (token == TOKEN_CLOSE_PARENTHESE)
            return true;
        return false;
    }
    static bool isReturnStmt(TypeToken token)
    {
        if (token == TOKEN_RETURN)
            return true;
        return false;
    }
    static bool isBreakStml(TypeToken token)
    {
        if (token == TOKEN_BREAK)
            return true;
        return false;
    }
    static bool isForStml(TypeToken token)
    {
        if (token == TOKEN_FOR)
            return true;
        return false;
    }
    static bool isDoStml(TypeToken token)
    {
        if (token == TOKEN_DO)
            return true;
        return false;
    }
    static bool isPrintStml(TypeToken token)
    {
        if (token == TOKEN_PRINTF)
            return true;
        return false;
    }
    static bool isStmt(TypeToken token)
    {
        if (
            isComStmt(token) ||
            isIfStmt(token) ||
            isWhileStmt(token) ||
            isReturnStmt(token) ||
            isBreakStml(token) ||
            isForStml(token) ||
            isDoStml(token) ||
            isExpStmt(token) ||
            isPrintStml(token))

        {
            return true;
        }
        return false;
    }

    static bool isExpStmt(TypeToken token)
    {
        unordered_map<TypeToken, string> expStmt = {

            {TOKEN_ID, "id"},
            {TOKEN_OPR_PLUS, "+"},
            {TOKEN_OPR_SUBS, "-"},
            {TOKEN_NOT, "!"},
            {TOKEN_VALUE_INT, "INT_LIT"},
            {TOKEN_VALUE_FLOAT, "FLOAT_LIF"},
            {TOKEN_VALUE_DOUBLE, "DOUBLE_LIF"},
            {TOKEN_VALUE_STRING, "DOUBLE_STRING"},
        };
        int count = expStmt.count(token);
        if (count > 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    static bool isKeyWord(TypeToken token)
    {
        unordered_map<TypeToken, string> keywords = {

            {TOKEN_IF, "if"},
            {TOKEN_FOR, "for"},
            {TOKEN_WHILE, "while"},
            {TOKEN_RETURN, "return"},
            {TOKEN_BREAK, "break"},

        };
        int count = keywords.count(token);
        if (count > 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    static bool isExp3(TypeToken token)
    {
        unordered_map<TypeToken, string> exp3 = {

            {TOKEN_OR, "||"},
            {TOKEN_ATRIB, "="},
            {TOKEN_EGUAL, "=="},
            {TOKEN_LESS_IGUAL_THAN, "<="},
            {TOKEN_LESS_THAN, "<"},
            {TOKEN_GREAT_THAN, ">"},
            {TOKEN_GREAT_IGUAL_THAN, ">="},
            {TOKEN_AND, "&&"},
            {TOKEN_DIFFERENT, "!="},
            {TOKEN_OPR_PLUS, "+"},
            {TOKEN_OPR_SUBS, "-"},
            {TOKEN_MOD, "%"},
            {TOKEN_OPR_MULT, "*"},
            {TOKEN_OPR_MUL_EGUAL, "*="},
            {TOKEN_OPR_DIV, "/"},
            {TOKEN_OPR_PLUS_EGUAL, "+="},
            {TOKEN_OPR_SUBS_EGUAL, "-="},
        };
        int count = exp3.count(token);
        if (count > 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};
#endif