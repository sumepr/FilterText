#ifndef RCSUTILITYDATA_H
#define RCSUTILITYDATA_H

#include<string>
using namespace std;
#define DLL_EXPORT __declspec(dllexport)
class DLL_EXPORT RcsUtilityData
{
public:
	RcsUtilityData();
	virtual ~RcsUtilityData();

	string getHsCode();
	void setHsCode(string hsCode);

	string getKeywordId();
	void setKeywordId(string keywordId);

	string getKeyword();
	void setKeyword(string keyword);

	string getCountryCode();
	void setCountryCode(string countryCode);

	string getIeFlag();
	void setIeFlag(string ieFlag);


	float getScore();
	void setScore(float score);

	void setCleanedDescription(string _cleanedDescription);
	string getCleanedDescription();

	void setSubjectDescription(string _subjectDescription);
	string getSubjectDescription();

	string getHsLevel();
	void setHsLevel(string _hsCode);



protected:

private:
	string hsCode;
	string keywordId;
	string keyWord;
	string countryCode;
	string ieFlag;
	float score;
	string cleanedDescription;
	string subjectDescription;
	string hsLevel;
};

#endif // RCSUTILITYDATA_H
