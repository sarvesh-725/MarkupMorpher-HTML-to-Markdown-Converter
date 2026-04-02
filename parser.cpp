#include "parser.h"
#include <bits/stdc++.h>
using namespace std;


string parse2(vector<string> &tokens, int &tokenIndex, unordered_map<string, int> &sym)
{
    string result = "";
    while (tokenIndex < tokens.size())
    {
        string currentToken = tokens[tokenIndex]; 
        // Check for *** (bold + italic) - token "8"
        if (currentToken == to_string(sym["***"]))
        {
            tokenIndex++; // consume opening ****  
            // Find matching closing ****
            int endIdx = -1;
            for (int i = tokenIndex; i < tokens.size(); i++)
            {
                if (tokens[i] == to_string(sym["***"]))
                {
                    endIdx = i;
                    break;
                }
            }
            
            if (endIdx != -1)
            {
                // Found matching closing **** - extract inner tokens and recursively parse
                vector<string> innerTokens;
                for (int i = tokenIndex; i < endIdx; i++)
                {
                    innerTokens.push_back(tokens[i]);
                }
                int innerIdx = 0;
                string innerContent = parse2(innerTokens, innerIdx, sym);
                result += "<b><i>" + innerContent + "</i></b>";
                tokenIndex = endIdx + 1; // consume closing ****
            }
            else
            {
                // No matching closing ****, treat as plain text
                result += "***";
            }
        }
        // Check for ** (bold) - token "9"
        else if (currentToken == to_string(sym["**"]))
        {
            tokenIndex++; // consume opening **
            
            // Find matching closing **
            int endIdx = -1;
            for (int i = tokenIndex; i < tokens.size(); i++)
            {
                if (tokens[i] == to_string(sym["**"]))
                {
                    endIdx = i;
                    break;
                }
            }
            
            if (endIdx != -1)
            {
                // Found matching closing ** - extract inner tokens and recursively parse
                vector<string> innerTokens;
                for (int i = tokenIndex; i < endIdx; i++)
                {
                    innerTokens.push_back(tokens[i]);
                }
                int innerIdx = 0;
                string innerContent = parse2(innerTokens, innerIdx, sym);
                result += "<b>" + innerContent + "</b>";
                tokenIndex = endIdx + 1; // consume closing **
            }
            else
            {
                // No matching closing **, treat as plain text
                result += "**";
            }
        }
        // Check for * (italic) - single asterisk - token "10"
        else if (currentToken == to_string(sym["*"]))
        {
            tokenIndex++; // consume opening *
            
            // Find matching closing * (must be a single * token, not part of **)
            int endIdx = -1;
            for (int i = tokenIndex; i < tokens.size(); i++)
            {
                if (tokens[i] == to_string(sym["*"]))
                {
                    endIdx = i;
                    break;
                }
            }
            
            if (endIdx != -1)
            {
                // Found matching closing * - extract inner tokens and recursively parse
                vector<string> innerTokens;
                for (int i = tokenIndex; i < endIdx; i++)
                {
                    innerTokens.push_back(tokens[i]);
                }
                int innerIdx = 0;
                string innerContent = parse2(innerTokens, innerIdx, sym);
                result += "<em>" + innerContent + "</em>";
                tokenIndex = endIdx + 1; // consume closing *
            }
            else
            {
                // No matching closing *, treat as plain text
                result += "*";
            }
        }
        // Check for ![ (image) - token "15"
        else if (currentToken == to_string(sym["!["]))
        {
            tokenIndex++; // consume ![
            
            // Parse image: ![alt](url)
            vector<string> altTokens;
            string url = "";
            
            // Collect alt text tokens until ]
            while (tokenIndex < tokens.size() && tokens[tokenIndex] != to_string(sym["]"]))
            {
                altTokens.push_back(tokens[tokenIndex]);
                tokenIndex++;
            }
            
            // Check for closing ]
            if (tokenIndex < tokens.size() && tokens[tokenIndex] == to_string(sym["]"]))
            {
                tokenIndex++; // consume ]
                
                // Parse alt text recursively
                int altIdx = 0;
                string altText = parse2(altTokens, altIdx, sym);
                
                // Check for opening (
                if (tokenIndex < tokens.size() && tokens[tokenIndex] == to_string(sym["("]))
                {
                    tokenIndex++; // consume (
                    
                    // Collect URL until )
                    while (tokenIndex < tokens.size() && tokens[tokenIndex] != to_string(sym[")"]))
                    {
                        url += tokens[tokenIndex];
                        tokenIndex++;
                    }
                    
                    // Check for closing )
                    if (tokenIndex < tokens.size() && tokens[tokenIndex] == to_string(sym[")"]))
                    {
                        tokenIndex++; // consume )
                        result += "<img src=\"" + url + "\" alt=\"" + altText + "\">";
                    }
                    else
                    {
                        result += "![" + altText + "]";
                    }
                }
                else
                {
                    result += "![" + altText + "]";
                }
            }
            else
            {
                result += "![";
            }
        }
        // Check for [ (link) - token "11"
        else if (currentToken == to_string(sym["["]))
        {
            tokenIndex++; // consume [
            
            // Parse link: [text](url)
            vector<string> linkTextTokens;
            string url = "";
            
            // Collect link text tokens until ]
            while (tokenIndex < tokens.size() && tokens[tokenIndex] != to_string(sym["]"]))
            {
                linkTextTokens.push_back(tokens[tokenIndex]);
                tokenIndex++;
            }
            
            // Check for closing ]
            if (tokenIndex < tokens.size() && tokens[tokenIndex] == to_string(sym["]"]))
            {
                tokenIndex++; // consume ]
                
                // Parse link text recursively
                int linkIdx = 0;
                string linkText = parse2(linkTextTokens, linkIdx, sym);
                
                // Check for opening (
                if (tokenIndex < tokens.size() && tokens[tokenIndex] == to_string(sym["("]))
                {
                    tokenIndex++; // consume (
                    
                    // Collect URL until )
                    while (tokenIndex < tokens.size() && tokens[tokenIndex] != to_string(sym[")"]))
                    {
                        url += tokens[tokenIndex];
                        tokenIndex++;
                    }
                    
                    // Check for closing )
                    if (tokenIndex < tokens.size() && tokens[tokenIndex] == to_string(sym[")"]))
                    {
                        tokenIndex++; // consume )
                        result += "<a href=\"" + url + "\">" + linkText + "</a>";
                    }
                    else
                    {
                        result += "[" + linkText + "]";
                    }
                }
                else
                {
                    result += "[" + linkText + "]";
                }
            }
            else
            {
                result += "[";
            }
        }
        // Plain text or other tokens
        else
        {
            result += currentToken;
            tokenIndex++;
        }
    }
    
    return result;
}


void parselist(vector<vector<string>> &tokenizedLines, unordered_map<string, int> &sym, ofstream &outFile, int &index)
{
   
    function<string(int, int&)> buildList = [&](int currentLevel, int &pos) -> string {
        string result = "<ul>\n";
        
        while (pos < tokenizedLines.size()) {
            vector<string> line = tokenizedLines[pos];
            
            // Check if this line is a list item
            if (line.empty() || line[0] != to_string(sym["- "])) {
                break;
            }
            
            // Get space count (second token)
            int spaceCount = 0;
            if (line.size() > 1) {
                spaceCount = stoi(line[1]);
            }
            
            // If space count is less than current level, we've gone up a level
            if (spaceCount < currentLevel) {
                break;
            }
            
            // If space count matches current level, it's a sibling item
            if (spaceCount == currentLevel) {
                // Parse the content after "- " and space count
                int tokenIdx = 2;
                string content = parse2(line, tokenIdx, sym);
                
                // Check if next item is nested (peek ahead)
                bool hasNested = false;
                int nextSpaceCount = currentLevel;
                if (pos + 1 < tokenizedLines.size()) {
                    vector<string> nextLine = tokenizedLines[pos + 1];
                    if (!nextLine.empty() && nextLine[0] == to_string(sym["- "])) {
                        if (nextLine.size() > 1) {
                            nextSpaceCount = stoi(nextLine[1]);
                        }
                        if (nextSpaceCount > currentLevel) {
                            hasNested = true;
                        }
                    }
                }
                
                if (hasNested) {
                    result += "<li>" + content + "\n";
                    pos++;
                    // Recursively process nested list with the actual next space count
                    result += buildList(nextSpaceCount, pos);
                    result += "</li>\n";
                } else {
                    result += "<li>" + content + "</li>\n";
                    pos++;
                }
            }
           
            else {
                break;
            }
        }
        
        result += "</ul>\n";
        return result;
    };
    
    int currentLevel = 0;
    
    // Get the space count of the first list item
    if (tokenizedLines[index].size() > 1) {
        currentLevel = stoi(tokenizedLines[index][1]);
    }
    
    // Build the nested list structure
    string listHTML = buildList(currentLevel, index);
    outFile << listHTML;
}

// Main parsing function - recursive descent parser
void parsefun(vector<vector<string>> &tokenizedLines, 
              unordered_map<string, int> &sym, 
              int index, 
              ofstream &outFile)
{
    // Base case: reached end of lines
    if (index >= tokenizedLines.size())
    {
        return;
    }
    vector<string> currentLine = tokenizedLines[index];
    // Skip empty lines
    if (currentLine.empty())
    {
        parsefun(tokenizedLines, sym, index + 1, outFile);
        return;
    }
    
    string firstToken = currentLine[0];

    // Phase 1: Check for headings
    if (firstToken == to_string(sym["###### "]))
    {
        // H6 heading
        int tokenIdx = 1;
        string content = parse2(currentLine, tokenIdx, sym);
        outFile << "<h6>" << content << "</h6>" << endl;
        parsefun(tokenizedLines, sym, index + 1, outFile);
        return;
    }
    else if (firstToken == to_string(sym["##### "]))
    {
        // H5 heading
        int tokenIdx = 1;
        string content = parse2(currentLine, tokenIdx, sym);
        outFile << "<h5>" << content << "</h5>" << endl;
        parsefun(tokenizedLines, sym, index + 1, outFile);
        return;
    }
    else if (firstToken == to_string(sym["#### "]))
    {
        // H4 heading
        int tokenIdx = 1;
        string content = parse2(currentLine, tokenIdx, sym);
        outFile << "<h4>" << content << "</h4>" << endl;
        parsefun(tokenizedLines, sym, index + 1, outFile);
        return;
    }
    else if (firstToken == to_string(sym["### "]))
    {
        // H3 heading
        int tokenIdx = 1;
        string content = parse2(currentLine, tokenIdx, sym);
        outFile << "<h3>" << content << "</h3>" << endl;
        parsefun(tokenizedLines, sym, index + 1, outFile);
        return;
    }
    else if (firstToken == to_string(sym["## "]))
    {
        // H2 heading
        int tokenIdx = 1;
        string content = parse2(currentLine, tokenIdx, sym);
        outFile << "<h2>" << content << "</h2>" << endl;
        parsefun(tokenizedLines, sym, index + 1, outFile);
        return;
    }
    else if (firstToken == to_string(sym["# "]))
    {
        // H1 heading
        int tokenIdx = 1;
        string content = parse2(currentLine, tokenIdx, sym);
        outFile << "<h1>" << content << "</h1>" << endl;
        parsefun(tokenizedLines, sym, index + 1, outFile);
        return;
    }
    
    // Phase 2: Check for lists
    if (firstToken == to_string(sym["- "]))
    {
        parselist(tokenizedLines, sym, outFile, index);
        parsefun(tokenizedLines, sym, index, outFile);
        return;
    }
    
    // Phase 3: Other (paragraph)
    int tokenIdx = 0;
    string content = parse2(currentLine, tokenIdx, sym);
    outFile << "<p>" << content << "</p>" << endl;
    parsefun(tokenizedLines, sym, index + 1, outFile);
}
