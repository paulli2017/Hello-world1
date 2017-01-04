// LongestPalindromicString.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include <algorithm>

using std::string;

string AddBoundaries(string inputStr)
{
  string output = "";
  int len = inputStr.length();    
  for (int i = 0; i < len; i++) {    
    output += "#"; 
    output += inputStr[i];     
  }
  output += "#";

  return output;  
}

string RemoveBoundaries(string inputStr)
{
  int len = inputStr.length(); 
  string output = "";
  for (int i = 0; i < (len)/2; i++) {
    output += inputStr[i*2 + 1];
  }  

  return output;  
}

string FindLongestPalindromeSubstr(string inputStr)
{
  //step1: prepossing the string, to add boundaries
  string strBoundary = AddBoundaries(inputStr);

  //step2: find the LPS using Manacher's algorithm
  int len = strBoundary.length();
  int p[200];
  string strLPS;
  memset(p, 0, sizeof(int) * len);
  p[1] = 1; 
  
  int center = 0;
  int right = 0;
  int mirrorleft = 0;
  int mirrorright = 0;

  for (int i = 1; i < len; i++) {
    if (i > right) {
      p[i] = 0; 
      mirrorleft = i - 1; 
      mirrorright = i + 1;
    }
    else {
      int i2 = center * 2 - i;
      if ( p[i2] < (right -i)) {
        p[i] = p[i2]; 
        mirrorleft = -1;
      }
      else {
        p[i] = right - i;
        mirrorright = right + 1;
        mirrorleft = i*2 - mirrorright;
      }
    }

    while((mirrorleft >= 0) && (mirrorright < len) && (strBoundary[mirrorleft] == strBoundary[mirrorright])) {
      p[i]++;
      mirrorleft--; 
      mirrorright++;
    }

    if((i + p[i]) > right) {
      center = i; 
      right = i + p[i];
    }
  }

  int maxLen = 0; 
  int pos = 0;
  for ( int i = 1; i < len; i++) {
    if (maxLen < p[i]) {
      maxLen = p[i]; 
      pos = i;
    }
  }

  strLPS = strBoundary.substr(pos - p[pos], 2*p[pos] + 1);  

  //step3: remove the boundaries
  string result = RemoveBoundaries(strLPS);

  return result;  
}

int main(int argc, char* argv[])
{
  std::vector<string> vStr;
  vStr.push_back("babcbabcbaccba");
  vStr.push_back("abaaba");
  vStr.push_back("abababa");
  vStr.push_back("abcbabcbabcba");
  vStr.push_back("forgeeksskeegfor");
  vStr.push_back("caba");
  vStr.push_back("abacdfgdcaba");
  vStr.push_back("abacdfgdcabba");
  vStr.push_back("abacdedcaba");
  vStr.push_back("maddam");
  vStr.push_back("jsdfjdsfhracecarksdfjsdkfmalayalamcheck");
  vStr.push_back("risetovotesirthepeoplearewaiting");
  vStr.push_back("abc");

  int maxLen = 0;
  string maxStr;
  int lineNum = 0;

  printf("Test started:\n");
  printf("*******************\n");
  for ( int i = 0; i < (int)vStr.size(); i++) {
    string str_lps = FindLongestPalindromeSubstr(vStr[i]);  
    size_t startPos = vStr[i].find(str_lps.c_str());
    string lpsStr = vStr[i].substr(startPos, str_lps.length());

    printf("The longest palindrome in \"%s\"\n",  vStr[i].c_str()); 
    printf("is: \"%s\"\n", lpsStr.c_str());
    printf("starting position at: %u in original string\n", startPos);
    printf("\n*******************\n");

    if (lpsStr.length() > maxLen) {
      maxLen = lpsStr.length();
      lineNum = i;
      maxStr = lpsStr;
    }    
  }

  printf("The longest palindrome is %s at %u\n", maxStr.c_str(), lineNum);

	return 0;
}

