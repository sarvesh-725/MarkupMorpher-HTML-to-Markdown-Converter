#include "lex.h"

vector<vector<string>> lexfun(vector<string> &v, unordered_map<string,int> &sym)
{
    vector<vector<string>> out;
    for (string &ln : v)
    {
        vector<string> t;
        int i = 0, n = ln.size();

        if (ln.rfind("######",0)==0) { t.push_back(to_string(sym["######"])); i=6; }
        else if (ln.rfind("#####",0)==0) { t.push_back(to_string(sym["#####"])); i=5; }
        else if (ln.rfind("####",0)==0) { t.push_back(to_string(sym["####"])); i=4; }
        else if (ln.rfind("###",0)==0) { t.push_back(to_string(sym["###"])); i=3; }
        else if (ln.rfind("##",0)==0) { t.push_back(to_string(sym["##"])); i=2; }
        else if (ln.rfind("#",0)==0) { t.push_back(to_string(sym["#"])); i=1; }
        else if (ln.rfind("-",0)==0) { 

            //encode the initial space before - as a separate token
            
            t.push_back(to_string(sym["-"])); i=1; 
        
        }
        string buf;

        while (i<n)
        {
            if (ln.substr(i,4)=="****")
            {
                if (!buf.empty()) { t.push_back(buf); buf=""; }
                t.push_back(to_string(sym["****"]));
                i+=4;
            }
            else if (ln.substr(i,2)=="**")
            {
                if (!buf.empty()) { t.push_back(buf); buf=""; }
                t.push_back(to_string(sym["**"]));
                i+=2;
            }
            else if (ln[i]=='[')
            {
                if (!buf.empty()) { t.push_back(buf); buf=""; }
                t.push_back(to_string(sym["["]));
                i++;
            }
            else if (ln[i]==']')
            {
                if (!buf.empty()) { t.push_back(buf); buf=""; }
                t.push_back(to_string(sym["]"]));
                i++;
            }
            else if (ln[i]=='(')
            {
                if (!buf.empty()) { t.push_back(buf); buf=""; }
                t.push_back(to_string(sym["("]));
                i++;
            }
            else if (ln[i]==')')
            {
                if (!buf.empty()) { t.push_back(buf); buf=""; }
                t.push_back(to_string(sym[")"]));
                i++;
            }
            else if (ln[i]=='!' && i+1<n && ln[i+1]=='[')
            {
                if (!buf.empty()) { t.push_back(buf); buf=""; }
                t.push_back(to_string(sym["!["]));
                i+=2;
            }
            else
            {
                buf.push_back(ln[i]);
                i++;
            }
        }
        if (!buf.empty()) t.push_back(buf);

        out.push_back(t);
    }
    return out;
}

