#ifndef RCSUTILITYDATALOAD_H
#define RCSUTILITYDATALOAD_H

#include<RcsUtilityData.h>
#include<iostream>
#include<string>
#include<vector>

using namespace std;
#define DLL_EXPORT __declspec(dllexport)
class DLL_EXPORT RcsUtilityDataLoad
{
public:
	RcsUtilityDataLoad();
	virtual ~RcsUtilityDataLoad();
	char * path;
	vector<RcsUtilityData> getRcsUtilityDataList();
	void setRcsUtilityDataList(vector<RcsUtilityData> RcsUtilityDataList);


	vector<RcsUtilityData> readDataFromFlatFile(string path);

	vector<RcsUtilityData> rcsUtilityDataList;
	long double dataLoadStartTime;
	long double fileLoadDate;
	RcsUtilityData data;
	static RcsUtilityDataLoad * getInstance();

protected:

private:
	static RcsUtilityDataLoad* instance;
	int daysLapsed;




};

#endif // RCSUTILITYDATALOAD_H
