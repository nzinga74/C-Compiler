#include <iostream>
#include "./tokens/type_token.h"
#include "./CLexic/lex_analiser.h"
#include "./tokens/token.h"
#include <algorithm>
#include <vector>
#include "./CLexic/utils.h"
#include "./CSintatic/parser.h"

using namespace std;

int main(int argc, char *argv[])
{
    string filename = argv[1];
    LexAnaliser *analiser = new LexAnaliser(filename);
    Parser *cSintatic = new Parser(analiser);
    cSintatic->program();
    // vector<Token *> tokens;
    // Token *token = NULL;
    //  while ((token = analiser->nextToken())->name != TOKEN_END)
    //  {
    //      tokens.push_back(token);
    //  };
    //  int c = 0;
    //  for (Token *token : tokens)
    //  {
    //      if (token->name != TOKEN_NOT_FOUND)
    //      {
    //          cout << token->lexama << " -> ";
    //          Utils::imprimirToken(token->name);
    //          cout << "-->" << token->line;
    //          cout << endl;
    //      }
    //      else
    //      {
    //          c++;
    //      }
    //  }

    // cout << c;

    return 0;
}