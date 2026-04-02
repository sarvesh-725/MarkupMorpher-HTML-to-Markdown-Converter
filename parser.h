#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>

using namespace std;

// Main parsing function - processes tokenized lines and converts to HTML
void parsefun(vector<vector<string>> &tokenizedLines, 
              unordered_map<string, int> &sym, 
              int index, 
              ofstream &outFile);

// Parse inline elements (bold, italic, links, images) - returns HTML string
string parse2(vector<string> &tokens, 
              int &tokenIndex, 
              unordered_map<string, int> &sym);

// Parse list items (empty for now)
void parselist(vector<vector<string>> &tokenizedLines,
               unordered_map<string, int> &sym, 
               ofstream &outFile, 
               int &index);

#endif

