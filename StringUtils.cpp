#include<pch.h>
#include "stdafx.h"
#include "StringUtils.h"

StringUtils::StringUtils()
{
	//ctor
}

StringUtils::~StringUtils()
{
	//dtor
}

vector<string> StringUtils::tokenize(string searchText, char delimiter) {

	vector<string> searchTextTokenList;
	string temp = "";
	for (int i = 0; i < searchText.length(); ++i) {

		if (searchText[i] == delimiter) {
			searchTextTokenList.push_back(temp);
			temp = "";
		}
		else {
			temp += searchText[i];
		}

	}
	if (temp.length() != 0) {
		searchTextTokenList.push_back(temp);
	}
	return searchTextTokenList;

}

bool StringUtils::isEmpty(string input) {
	return !input.length();
}

bool StringUtils::isNotEmpty(string input) {
	return input.length();
}

bool StringUtils::isOneWord(string input) {
	for (int i = 0; i < input.length(); ++i) {
		if (input[i] == ' ') {
			return false;
		}
	}
	return true;
}
int StringUtils::getLevenshteinDistance(string keywordToken, string searchTextToken) {
	const size_t m(keywordToken.size());
	const size_t n(searchTextToken.size());

	if (m == 0) return n;
	if (n == 0) return m;

	size_t *costs = new size_t[n + 1];

	for (size_t k = 0; k <= n; k++) costs[k] = k;

	size_t i = 0;
	for (std::string::const_iterator it1 = keywordToken.begin(); it1 != keywordToken.end(); ++it1, ++i)
	{
		costs[0] = i + 1;
		size_t corner = i;

		size_t j = 0;
		for (std::string::const_iterator it2 = searchTextToken.begin(); it2 != searchTextToken.end(); ++it2, ++j)
		{
			size_t upper = costs[j + 1];
			if (*it1 == *it2)
			{
				costs[j + 1] = corner;
			}
			else
			{
				size_t t(upper < corner ? upper : corner);
				costs[j + 1] = (costs[j] < t ? costs[j] : t) + 1;
			}

			corner = upper;
		}
	}

	size_t result = costs[n];
	delete[] costs;

	return result;
}

