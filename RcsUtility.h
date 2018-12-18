#ifndef RCSUTILITY_H
#define RCSUTILITY_H
#include<RcsUtilityRequest.h>
#include<RcsUtilityValidator.h>
#include<RcsUtilityData.h>
#include<RcsSearchReply.h>
#include<string>
#include<Message.h>
#include<MessageParameter.h>
#include<RcsUtil.h>
#include<RcsUtilityDataLoad.h>
#include<RcsUtilityReply.h>
#include<RcsUtilityValidator.h>
#include<RcsUtilityData.h>
#include<RcsUtil.h>
#include<map>
using namespace std;
#define DLL_EXPORT __declspec(dllexport)
class DLL_EXPORT RcsUtility
{
public:
	RcsUtility();
	virtual ~RcsUtility();
	RcsUtilityReply getDetails(RcsUtilityRequest RcsUtilityRequest, string path);
	const float MATCHING_THRESHOLD = 100;
	RcsUtilityRequest removeSpecialCharactersFromSearchText(RcsUtilityRequest RcsUtilityRequest);
	void updateSearchTextToSingular(RcsUtilityRequest rcsUtilityRequest);
	vector<RcsUtilityData> filterRcsUtilityDataBasedOnCountryAndIeFlag(vector<RcsUtilityData> rcsUtilityList, RcsUtilityRequest rcsUtilityRequest);
	vector<RcsUtilityData> getFilteredRcsUtilityData(vector<RcsUtilityData> list, string id);
	RcsUtilityReply populateRcsReply(RcsUtilityReply rcsUtilityReply, vector<RcsUtilityData> filteredRcsUtilityDatas);
	RcsUtilityRequest removeStopWords(RcsUtilityRequest RcsUtilityRequest);
	vector<RcsUtilityData> filterDataWhenDestinationAndOriginCountryProvider(RcsUtilityRequest rcsUtilityRequest, vector<RcsUtilityData>filteredRcsUtilityDataList,
		RcsUtilityData rcsUtilityData, bool * isExportProhibitted, bool * isImportProhibitted);
	vector<RcsUtilityData> filterRcsDataWhenOnlyCarrierCodeIsProvided(RcsUtilityRequest rcsUtilityRequest, vector<RcsUtilityData>filteredRcsUtilityDataList,
		RcsUtilityData rcsUtilityData);
	vector<RcsUtilityData> filterRcsDataWhenOnlyOriginCountryIsProvided(RcsUtilityRequest rcsUtilityRequest, vector<RcsUtilityData>filteredRcsUtilityDataList,
		RcsUtilityData rcsUtilityData);
	vector<RcsUtilityData> filterRcsDataWhenOnlyDestinationCountryIsProvided(RcsUtilityRequest rcsUtilityRequest, vector<RcsUtilityData> filteredRcsUtilityData,
		RcsUtilityData rcsUtilityData);
	bool isCarrierCode(string countryCode);
	bool isEuropeanCountry(string countryCode);
	map<string, vector<RcsUtilityData> > filterDataWhenCarrierAndOriginAndDestinationCodeProvided(map<string, vector<RcsUtilityData> >hsCodeMap, RcsUtilityData rcsUtilityData);

	vector<RcsUtilityData> filterDataForMatchingOriginAndDestinationCodeProvided(vector<RcsUtilityData> filteredRcsUtilityDataList,
		map<string, vector<RcsUtilityData> >hsCodeMap, RcsUtilityRequest rcsUtilityRequest);

protected:

private:

	const string IMPORT_FLAG = "1";
	const string EXPORT_FLAG = "0";



};

#endif // RCSUTILITY_H
