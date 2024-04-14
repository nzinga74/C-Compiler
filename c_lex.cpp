#include <iostream>
#include "./tokens/type_token.h"
#include "file_reader.h"
#include "lex_analiser.h"
#include "./tokens/token.h"
#include <algorithm>
#include <vector>
#include "utils.h"

using namespace std;

int main()
{
    LexAnaliser *analiser = new LexAnaliser();
    vector<Token *> tokens;
    Token *token = NULL;
    while ((token = analiser->nextToken())->name != TOKEN_END)
    {
        tokens.push_back(token);
    };
    int c = 0;
    for (Token *token : tokens)
    {
        if (token->name != TOKEN_NOT_FOUND)
        {
            cout << token->lexama << " -> ";
            Utils::imprimirToken(token->name);
            cout << "-->" << token->line;
            cout << endl;
        }
        else
        {
            c++;
        }
    }

    cout << c;

    return 0;
}