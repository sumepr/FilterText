#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include<iostream>
#include<string>
#include<vector>
using namespace std;
#define DLL_EXPORT __declspec(dllexport)
class DLL_EXPORT StringUtils
{
public:
	StringUtils();
	virtual ~StringUtils();
	static int getLevenshteinDistance(string keywordToken, string searchTextToken);
	static bool isEmpty(string token);
	static bool isNotEmpty(string token);
	static vector<string> tokenize(string token, char delimiter);
	static bool isOneWord(string input);
protected:

private:
};

#endif // STRINGUTILS_H
