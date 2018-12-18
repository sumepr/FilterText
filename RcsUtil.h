#ifndef RCSUTIL_H
#define RCSUTIL_H

#include<string>
#include<vector>
#include<RcsUtilityData.h>
#include<RcsUtilityRequest.h>
#include<MessageParameter.h>
using namespace std;
#define DLL_EXPORT __declspec(dllexport)
class DLL_EXPORT RcsUtil
{
public:
	RcsUtil();
	virtual ~RcsUtil();
	float getScore(string searchText, string keyword, RcsUtilityData RcsUtilityData);
	RcsUtilityRequest updateSearchTextToSingular(RcsUtilityRequest RcsUtilityRequest);
	static string getHSLevel(string hsCode);
	bool compareRootForms(string keywordToken, string searchTextToken);
	bool getFuzzinessEnabled();
	void setFuzinessEnabled(bool fuzinessEnabled);
protected:

private:
	static const string HS6;// =  "HS6";
	static const string HS4;// =  "HS4";
	static const string HS2;// =  "HS2";
	bool isFuzzinessEnabled;



};

#endif // RCSUTIL_H
