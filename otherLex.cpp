#include "otherLex.h"
#include <bits/stdc++.h>

using namespace std;

// Check if a line ends with 2 or more whitespaces
bool hasTrailingWhitespace(const string &line)
{
    if (line.length() < 2)
    {
        return false;
    }
    int spaceCount = 0;
    for (int i = line.length() - 1; i >= 0; i--)
    {
        if (line[i] == ' ')
        {
            spaceCount++;
        }
        else if (line[i] == '\t')
        {
            // Tabs count as whitespace but we need at least 2 spaces
            continue;
        }
        else
        {
            break;
        }
    }
    return spaceCount >= 2;
}

// Check if a line starts with a block-level character (heading, list, etc.)
bool startsWithBlockCharacter(const vector<string> &tokens, unordered_map<string, int> &sym)
{
    if (tokens.empty())
    {
        return false;
    }
    
    string firstToken = tokens[0];
    
    // Check for heading markers
    if (firstToken == to_string(sym["######"]) || 
        firstToken == to_string(sym["#####"]) ||
        firstToken == to_string(sym["####"]) ||
        firstToken == to_string(sym["###"]) ||
        firstToken == to_string(sym["##"]) ||
        firstToken == to_string(sym["#"]))
    {
        return true;
    }
    
    // Check for list marker
    if (firstToken == to_string(sym["-"]))
    {
        return true;
    }
    
    return false;
}

vector<vector<string>> otherLexFun(vector<vector<string>> &tokenizedLines, 
                                    vector<string> &originalLines, 
                                    unordered_map<string, int> &sym)
{
    vector<vector<string>> output;
    
    for (size_t i = 0; i < tokenizedLines.size(); i++)
    {
        const auto &tokens = tokenizedLines[i];
        
        // If current line is empty, add it as is
        if (tokens.empty())
        {
            output.push_back(tokens);
            continue;
        }
        
        // If current line starts with block character, add it separately
        if (startsWithBlockCharacter(tokens, sym))
        {
            output.push_back(tokens);
            continue;
        }
        
        // Check if previous line had trailing whitespace (>=2 spaces)
        bool prevLineHadTrailingWhitespace = false;
        if (i > 0 && i - 1 < originalLines.size())
        {
            prevLineHadTrailingWhitespace = hasTrailingWhitespace(originalLines[i - 1]);
        }
        
        // If previous line had trailing whitespace, treat current line as separate
        if (prevLineHadTrailingWhitespace)
        {
            output.push_back(tokens);
        }
        else
        {
            // Previous line did NOT have trailing whitespace
            // Check if we can concatenate with the last non-empty line in output
            if (!output.empty() && !output.back().empty() && 
                !startsWithBlockCharacter(output.back(), sym))
            {
                // Remove the last line from output
                vector<string> lastLine = output.back();
                output.pop_back();
                
                // Combine the strings: merge last line tokens and current line tokens
                vector<string> combined;
                // Add all tokens from last line
                for (const auto &tok : lastLine)
                {
                    combined.push_back(tok);
                }
                // Add a space separator
                combined.push_back(" ");
                // Add all tokens from current line
                for (const auto &tok : tokens)
                {
                    combined.push_back(tok);
                }
                
                // Add the combined line back to output
                output.push_back(combined);
            }
            else
            {
                // No previous line to concatenate with, add as new line
                output.push_back(tokens);
            }
        }
    }
    
    return output;
}
