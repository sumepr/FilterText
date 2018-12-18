#include "pch.h"
#include "stdafx.h"
#include "RcsUtility.h"
#include<set>
#include<algorithm>
#include<map>
#include<StringUtils.h>
#include<RcsUtilityReply.h>
#include<RcsUtilityData.h>
#include<Constants.h>
#include<Lemmantization.h>
RcsUtility::RcsUtility()
{
	//ctor

	static RcsUtilityValidator rcsUtilityValidator;


}

RcsUtility::~RcsUtility()
{
	//dtor
}



//Keeps alpha  dot, and percentage. [a-z A-Z . %]
map<string, bool> addedHsCode;//For disallowing repetition.
RcsUtilityRequest RcsUtility::removeSpecialCharactersFromSearchText(RcsUtilityRequest rcsUtilityRequest) {
	//Removed heiphen and numbers
	rcsUtilityRequest = removeStopWords(rcsUtilityRequest);

	string srchText = rcsUtilityRequest.getSearchText();
	string cleanedSearchText = "";
	if (srchText.length()) {
		string temp = "";
		for (int i = 0; i<srchText.length(); ++i) {
			if ((srchText[i] >= 'a' && srchText[i] <= 'z') || (srchText[i] >= 'A' && srchText[i] <= 'Z') || srchText[i] == ' '
				|| srchText[i] == '.' || srchText[i] == '%') {
				temp += srchText[i];
			}
			if (srchText[i] == '-') {
				temp += ' ';
			}
		}


		if (temp[0] != ' ') {
			cleanedSearchText += temp[0];
		}
		for (int i = 1; i<temp.length() - 1; ++i) {

			if (temp[i] == ' '&&temp[i + 1] == ' ') {
				continue;
			}
			else {
				cleanedSearchText += temp[i];
			}

		}


		if (temp[temp.length() - 1] != ' ') {
			cleanedSearchText += temp[temp.length() - 1];
		}

	}

	rcsUtilityRequest.setSearchText(cleanedSearchText);
	return rcsUtilityRequest;
}

/*
* Assumptions: No duplicates in the data
*
*
*/

RcsUtilityReply RcsUtility::getDetails(RcsUtilityRequest rcsUtilityRequest, string path) {



	RcsUtilityReply rcsUtilityReply;
	RcsUtilityValidator rcsUtilityValidator;
	RcsUtil rcsUtil;

	rcsUtilityReply = rcsUtilityValidator.validateRcsUtilityRequest(rcsUtilityRequest, rcsUtilityReply);

	if (rcsUtilityReply.getNotifications().size() != 0) {
		return rcsUtilityReply;
	}
	rcsUtilityRequest = removeSpecialCharactersFromSearchText(rcsUtilityRequest);

	
	rcsUtilityRequest = rcsUtil.updateSearchTextToSingular(rcsUtilityRequest);

	RcsUtilityDataLoad* rcsUtilityDataLoad = RcsUtilityDataLoad::getInstance();
	rcsUtilityDataLoad->readDataFromFlatFile(path);

	//rcsUtilityDataLoad.readDataFromFlatFile();

	//cout<<rcsUtilityDataLoad->getRcsUtilityDataList().size()<<endl;

	vector<RcsUtilityData> rcsUtilityList = getFilteredRcsUtilityData(rcsUtilityDataLoad->getRcsUtilityDataList(), rcsUtilityRequest.getSearchText());
	//cout<<"size before filtering "<<rcsUtilityList.size()<<endl;

	vector<RcsUtilityData> filteredRcsUtilityDatas;
	if (rcsUtilityList.size() != 0) {
		filteredRcsUtilityDatas = filterRcsUtilityDataBasedOnCountryAndIeFlag(rcsUtilityList, rcsUtilityRequest);
		//cout<<"size after filtering "<<filteredRcsUtilityDatas.size()<<endl;
	}



	rcsUtilityReply = populateRcsReply(rcsUtilityReply, filteredRcsUtilityDatas);



	return rcsUtilityReply;


}



vector<RcsUtilityData> RcsUtility::filterRcsUtilityDataBasedOnCountryAndIeFlag(vector<RcsUtilityData> rcsUtilityList, RcsUtilityRequest rcsUtilityRequest) {



	vector<RcsUtilityData> filteredRcsUtilityDataList;
	map<string, vector<RcsUtilityData> > hsCodeMap;
	map<string, bool> hsCodes;
	hsCodeMap.clear();
	hsCodes.clear();
	addedHsCode.clear();
	filteredRcsUtilityDataList.clear();
	for (int i = 0; i<(int)rcsUtilityList.size(); ++i) {
		bool isExportProhibitted = false;
		bool isImportProhibitted = false;
		
		if (StringUtils::isEmpty(rcsUtilityRequest.getDestinationCountryCode()) &&
			StringUtils::isNotEmpty(rcsUtilityRequest.getOriginCountryCode()) &&
			StringUtils::isNotEmpty(rcsUtilityRequest.getCarrierCode())) {

			hsCodeMap = filterDataWhenCarrierAndOriginAndDestinationCodeProvided(hsCodeMap, rcsUtilityList[i]);


		}
		else if (
			StringUtils::isNotEmpty(rcsUtilityRequest.getDestinationCountryCode()) &&
			StringUtils::isEmpty(rcsUtilityRequest.getOriginCountryCode()) &&
			StringUtils::isNotEmpty(rcsUtilityRequest.getCarrierCode())
			) {
			hsCodeMap = filterDataWhenCarrierAndOriginAndDestinationCodeProvided(hsCodeMap, rcsUtilityList[i]);

		}

		else if (StringUtils::isNotEmpty(rcsUtilityRequest.getDestinationCountryCode()) &&
			StringUtils::isEmpty(rcsUtilityRequest.getOriginCountryCode()) &&
			StringUtils::isEmpty(rcsUtilityRequest.getCarrierCode())) {
			//rcsUtilityRequest.setOriginCountryCode("xx");

			
			filteredRcsUtilityDataList = filterRcsDataWhenOnlyDestinationCountryIsProvided(rcsUtilityRequest, filteredRcsUtilityDataList, rcsUtilityList[i]);

		}
		else if (StringUtils::isNotEmpty(rcsUtilityRequest.getOriginCountryCode())
			&& StringUtils::isEmpty(rcsUtilityRequest.getDestinationCountryCode())
			&& StringUtils::isEmpty(rcsUtilityRequest.getCarrierCode())) {
			//rcsUtilityRequest.setDestinationCountryCode("xx");
			filteredRcsUtilityDataList = filterRcsDataWhenOnlyOriginCountryIsProvided(rcsUtilityRequest, filteredRcsUtilityDataList, rcsUtilityList[i]);

		}
		else if (StringUtils::isNotEmpty(rcsUtilityRequest.getCarrierCode()) &&
			StringUtils::isEmpty(rcsUtilityRequest.getDestinationCountryCode()) &&
			StringUtils::isEmpty(rcsUtilityRequest.getOriginCountryCode())) {

			filteredRcsUtilityDataList = filterRcsDataWhenOnlyCarrierCodeIsProvided(rcsUtilityRequest, filteredRcsUtilityDataList, rcsUtilityList[i]);

		}
		else if ((StringUtils::isNotEmpty(rcsUtilityRequest.getDestinationCountryCode()) &&
			StringUtils::isNotEmpty(rcsUtilityRequest.getOriginCountryCode()) &&
			StringUtils::isEmpty(rcsUtilityRequest.getCarrierCode()))) {

			filteredRcsUtilityDataList = filterDataWhenDestinationAndOriginCountryProvider(rcsUtilityRequest, filteredRcsUtilityDataList,
				rcsUtilityList[i], &isExportProhibitted, &isImportProhibitted);

		}
		else if (StringUtils::isNotEmpty(rcsUtilityRequest.getCarrierCode()) &&
			StringUtils::isNotEmpty(rcsUtilityRequest.getDestinationCountryCode()) &&
			StringUtils::isNotEmpty(rcsUtilityRequest.getOriginCountryCode())
			) {

			hsCodeMap = filterDataWhenCarrierAndOriginAndDestinationCodeProvided(hsCodeMap, rcsUtilityList[i]);


		}
		else if (StringUtils::isEmpty(rcsUtilityRequest.getCarrierCode()) &&
			StringUtils::isEmpty(rcsUtilityRequest.getDestinationCountryCode()) &&
			StringUtils::isEmpty(rcsUtilityRequest.getOriginCountryCode())) {

			if (!addedHsCode[rcsUtilityList[i].getHsCode() + rcsUtilityList[i].getKeywordId()]) {
				filteredRcsUtilityDataList.push_back(rcsUtilityList[i]);
				addedHsCode[rcsUtilityList[i].getHsCode() + rcsUtilityList[i].getKeywordId()] = 1;
			}
		}

	}
	filteredRcsUtilityDataList = filterDataForMatchingOriginAndDestinationCodeProvided(filteredRcsUtilityDataList, hsCodeMap, rcsUtilityRequest);


	return filteredRcsUtilityDataList;

}


vector<RcsUtilityData> RcsUtility::filterDataForMatchingOriginAndDestinationCodeProvided(vector<RcsUtilityData> filteredRcsUtilityDataList,
	map<string, vector<RcsUtilityData> >hsCodeMap, RcsUtilityRequest rcsUtilityRequest) {

	map<string, vector<RcsUtilityData> >::iterator it = hsCodeMap.begin();

	// Iterate over the map using Iterator till end.
	string requestCarrierCode;
	while (it != hsCodeMap.end())
	{

		bool isOriginCountryMatched = false;
		bool isDestinationCountryMatched = false;
		bool isCarrierCodeMatched = false;
		vector<RcsUtilityData> mapList = hsCodeMap[it->first];
		/*
		*   "FDXC" => "FXC", "FDXG" => "FXG", "FDXE"=>"FXE"
		*/
		for (int i = 0; i<mapList.size(); ++i) {
			requestCarrierCode = rcsUtilityRequest.getCarrierCode();
			if (requestCarrierCode.length() == 4) {

				if (requestCarrierCode == "FDXC") { requestCarrierCode = "FXC"; }
				if (requestCarrierCode == "FDXG") { requestCarrierCode = "FXG"; }
				if (requestCarrierCode == "FDXE") { requestCarrierCode = "FXE"; }

			}
			//FR
			//come back 
			if (isEuropeanCountry(rcsUtilityRequest.getOriginCountryCode())) {
				if ((mapList[i].getCountryCode() == "WW" ||  mapList[i].getCountryCode() == "EUR" || rcsUtilityRequest.getOriginCountryCode() == mapList[i].getCountryCode()) && mapList[i].getIeFlag() == EXPORT_FLAG) {
					isOriginCountryMatched = true;
				}
			}
			else if ( (mapList[i].getCountryCode()=="WW" || rcsUtilityRequest.getOriginCountryCode() == mapList[i].getCountryCode() )&& mapList[i].getIeFlag() == EXPORT_FLAG) {
				isOriginCountryMatched = true;
			}

			if (isEuropeanCountry(rcsUtilityRequest.getDestinationCountryCode())) {
				if ((mapList[i].getCountryCode() == "WW" || mapList[i].getCountryCode() == "EUR" || rcsUtilityRequest.getDestinationCountryCode() == mapList[i].getCountryCode()) && mapList[i].getIeFlag() == EXPORT_FLAG) {
					isDestinationCountryMatched = true;
				}
			}
			else if ( (mapList[i].getCountryCode() == "WW" || rcsUtilityRequest.getDestinationCountryCode()  == mapList[i].getCountryCode()) && mapList[i].getIeFlag() == IMPORT_FLAG) {
				isDestinationCountryMatched = true;
			}
			if (requestCarrierCode == mapList[i].getCountryCode() || requestCarrierCode == "FXCC" || requestCarrierCode == "FXSP" || requestCarrierCode == "FDXC") {
				isCarrierCodeMatched = true;
			}
			//cout<<isOriginCountryMatched<<" "<<isDestinationCountryMatched<<"d "<<isCarrierCodeMatched<<endl;
			if (isOriginCountryMatched || isDestinationCountryMatched || isCarrierCodeMatched) {
				if (!addedHsCode[mapList[i].getHsCode() + mapList[i].getKeywordId()]) {
					filteredRcsUtilityDataList.push_back(mapList[i]);
					addedHsCode[mapList[i].getHsCode() + mapList[i].getKeywordId()] = 1;
				}
			}
		}
		++it;
	}
	return filteredRcsUtilityDataList;
}
bool RcsUtility::isCarrierCode(string countryCode) {
	string arr[] = { "FDXC", "FDXG", "FDXE", "FXCC", "FXFR", "FXSP", "FXG", "FXE" };
	for (int i = 0; i<8; ++i) {
		if (arr[i] == countryCode) {
			return true;
		}
	}
	return false;

}
bool RcsUtility::isEuropeanCountry(string countryCode) {
	string arr[] = { "AT","BE","BG","CY","CZ","DE","DK","EE","ES","FI","FR","GB","GR","HU","IE","IT","LT","LU","LV","MT","NL","PL","PT","SE","SI","SK" };
	for (int i = 0; i < 26; ++i) {
		if (arr[i] == countryCode) {
			return true;
		}
	}
	return false;

}
map<string, vector<RcsUtilityData> > RcsUtility::filterDataWhenCarrierAndOriginAndDestinationCodeProvided(map<string, vector<RcsUtilityData> >hsCodeMap, RcsUtilityData rcsUtilityData) {

	if (hsCodeMap[rcsUtilityData.getHsCode()].size() == 0) {

		vector<RcsUtilityData> _list;
		_list.push_back(rcsUtilityData);
		hsCodeMap[rcsUtilityData.getHsCode()] = _list;

	}
	else {

		vector<RcsUtilityData> vec = hsCodeMap[rcsUtilityData.getHsCode()];
		vec.push_back(rcsUtilityData);
		hsCodeMap[rcsUtilityData.getHsCode()] = vec;
	}

	return hsCodeMap;
}


vector<RcsUtilityData> RcsUtility::filterDataWhenDestinationAndOriginCountryProvider(RcsUtilityRequest rcsUtilityRequest, vector<RcsUtilityData>filteredRcsUtilityDataList,
	RcsUtilityData rcsUtilityData, bool * isExportProhibitted, bool * isImportProhibitted) {

	bool ip = false;
	bool ep = false;
	if (isEuropeanCountry(rcsUtilityRequest.getOriginCountryCode())) {
		if ((rcsUtilityData.getCountryCode() == "WW" || rcsUtilityData.getCountryCode() == "EUR" || rcsUtilityRequest.getOriginCountryCode() == rcsUtilityData.getCountryCode()) && rcsUtilityData.getIeFlag() == EXPORT_FLAG) {
			ep = 1;
		}
	}
	else if ( (rcsUtilityData.getCountryCode()=="WW" || rcsUtilityRequest.getOriginCountryCode() == rcsUtilityData.getCountryCode() ) && rcsUtilityData.getIeFlag() == EXPORT_FLAG) {
		ep = 1;
	}



	if (isEuropeanCountry(rcsUtilityRequest.getDestinationCountryCode())) {
		if ((rcsUtilityData.getCountryCode() == "WW" || rcsUtilityData.getCountryCode() == "EUR" || rcsUtilityRequest.getDestinationCountryCode() == rcsUtilityData.getCountryCode()) && rcsUtilityData.getIeFlag() == IMPORT_FLAG) {
			ip = 1;
		}
	}
	else if ( (rcsUtilityData.getCountryCode() == "WW" ||rcsUtilityRequest.getDestinationCountryCode() == rcsUtilityData.getCountryCode()) && rcsUtilityData.getIeFlag() == IMPORT_FLAG) {

		ip = 1;
	}

	if (ep || ip) {

		if (!addedHsCode[rcsUtilityData.getHsCode() + rcsUtilityData.getKeywordId()]) {
			filteredRcsUtilityDataList.push_back(rcsUtilityData);
			addedHsCode[rcsUtilityData.getHsCode() + rcsUtilityData.getKeywordId()] = 1;
		}
	}
	//EDIT ADD ALL CARRIER CODE COUNTRIES
	if (isCarrierCode(rcsUtilityData.getCountryCode())) {
		if (!addedHsCode[rcsUtilityData.getHsCode() + rcsUtilityData.getKeywordId()]) {
			filteredRcsUtilityDataList.push_back(rcsUtilityData);
			addedHsCode[rcsUtilityData.getHsCode() + rcsUtilityData.getKeywordId()] = 1;
		}
	}

	return filteredRcsUtilityDataList;
}

vector<RcsUtilityData> RcsUtility::filterRcsDataWhenOnlyCarrierCodeIsProvided(RcsUtilityRequest rcsUtilityRequest, vector<RcsUtilityData>filteredRcsUtilityDataList,
	RcsUtilityData rcsUtilityData) {

	if (rcsUtilityRequest.getCarrierCode() == rcsUtilityData.getCountryCode()) {
		if (!addedHsCode[rcsUtilityData.getHsCode() + rcsUtilityData.getKeywordId()]) {
			filteredRcsUtilityDataList.push_back(rcsUtilityData);
			addedHsCode[rcsUtilityData.getHsCode() + rcsUtilityData.getKeywordId()] = 1;
		}
	}
	return filteredRcsUtilityDataList;
}

vector<RcsUtilityData> RcsUtility::filterRcsDataWhenOnlyOriginCountryIsProvided(RcsUtilityRequest rcsUtilityRequest, vector<RcsUtilityData>filteredRcsUtilityDataList,
	RcsUtilityData rcsUtilityData) {

	if (isEuropeanCountry(rcsUtilityRequest.getDestinationCountryCode())) {
		if ((rcsUtilityData.getCountryCode() == "WW" || rcsUtilityData.getCountryCode() == "EUR" || rcsUtilityRequest.getOriginCountryCode() == rcsUtilityData.getCountryCode()) && rcsUtilityData.getIeFlag() == EXPORT_FLAG) {
			if (!addedHsCode[rcsUtilityData.getHsCode() + rcsUtilityData.getKeywordId()]) {
				filteredRcsUtilityDataList.push_back(rcsUtilityData);
				addedHsCode[rcsUtilityData.getHsCode() + rcsUtilityData.getKeywordId()] = 1;
			}
		}
	}

	else if (rcsUtilityData.getCountryCode()=="WW" || (rcsUtilityRequest.getOriginCountryCode() == rcsUtilityData.getCountryCode()) && rcsUtilityData.getIeFlag() == EXPORT_FLAG) {
		if (!addedHsCode[rcsUtilityData.getHsCode() + rcsUtilityData.getKeywordId()]) {
			filteredRcsUtilityDataList.push_back(rcsUtilityData);
			addedHsCode[rcsUtilityData.getHsCode() + rcsUtilityData.getKeywordId()] = 1;
		}

	}
	if (isCarrierCode(rcsUtilityData.getCountryCode())) {
		if (!addedHsCode[rcsUtilityData.getHsCode() + rcsUtilityData.getKeywordId()]) {
			filteredRcsUtilityDataList.push_back(rcsUtilityData);
			addedHsCode[rcsUtilityData.getHsCode() + rcsUtilityData.getKeywordId()] = 1;
		}
	}
	return filteredRcsUtilityDataList;
}
vector<RcsUtilityData> RcsUtility::filterRcsDataWhenOnlyDestinationCountryIsProvided(RcsUtilityRequest rcsUtilityRequest, vector<RcsUtilityData> filteredRcsUtilityData,
	RcsUtilityData rcsUtilityData) {
	
	if (isEuropeanCountry(rcsUtilityRequest.getDestinationCountryCode())) {
		if ((rcsUtilityData.getCountryCode() == "WW" || rcsUtilityData.getCountryCode() == "EUR" || rcsUtilityRequest.getOriginCountryCode() == rcsUtilityData.getCountryCode()) && rcsUtilityData.getIeFlag() == EXPORT_FLAG) {
			if (!addedHsCode[rcsUtilityData.getHsCode() + rcsUtilityData.getKeywordId()]) {
				filteredRcsUtilityData.push_back(rcsUtilityData);
				addedHsCode[rcsUtilityData.getHsCode() + rcsUtilityData.getKeywordId()] = 1;

			}
		}
	}
	else if ( (rcsUtilityData.getCountryCode()=="WW" || rcsUtilityRequest.getDestinationCountryCode() == rcsUtilityData.getCountryCode() )&& rcsUtilityData.getIeFlag() == IMPORT_FLAG)
		 {
		if (!addedHsCode[rcsUtilityData.getHsCode() + rcsUtilityData.getKeywordId()]) {
			filteredRcsUtilityData.push_back(rcsUtilityData);
			addedHsCode[rcsUtilityData.getHsCode() + rcsUtilityData.getKeywordId()] = 1;

		}

	}

	if (isCarrierCode(rcsUtilityData.getCountryCode())) {
		if (!addedHsCode[rcsUtilityData.getHsCode() + rcsUtilityData.getKeywordId()]) {
			filteredRcsUtilityData.push_back(rcsUtilityData);
			addedHsCode[rcsUtilityData.getHsCode() + rcsUtilityData.getKeywordId()] = 1;
		}
	}


	return filteredRcsUtilityData;

}

/*
Goes through list of RcsUtilityData and check if its score exceeds or equal to threshold
*/
bool cmp(RcsUtilityData a, RcsUtilityData b) {
	return a.getScore() < b.getScore();
}



vector<RcsUtilityData> RcsUtility::getFilteredRcsUtilityData(vector<RcsUtilityData> myList, string id) {


	RcsUtil rcsUtil;
	vector<RcsUtilityData> ret;

	//RcsUtility::MATCHING_THRESHOLD

	// Here we need to pass cleaned keyword.
	//CHECK IF SEARCHTEXT TOKEN matches against subject

	Lemmantization lemmantization;
	string lemmatizedSubject;
	string lemmatizedSearchTextToken;
	vector<string> searchTextTokens = StringUtils::tokenize(id, ' ');
	

	for (int j = 0; j<myList.size(); ++j) {
		
		for (int i = 0; i<searchTextTokens.size(); ++i) {

			vector<string> subjects;
			if (StringUtils::isOneWord(myList[j].getSubjectDescription())) {
				subjects.push_back(myList[j].getSubjectDescription());
			}
			subjects = StringUtils::tokenize(myList[j].getSubjectDescription(), ' ');


			//080300|547|bananas, fresh or dried|BD|0|bananas fresh dried|bananas fresh

			
			for (int k = 0; k<subjects.size(); ++k) {
				lemmatizedSubject = lemmantization.getRoot(subjects[k]);
				lemmatizedSearchTextToken = lemmantization.getRoot(searchTextTokens[i]);
				//StringUtils::getLevenshteinDistance(lemmatizedSubject, lemmatizedSearchTextToken)<=2
				if (lemmatizedSubject == lemmatizedSearchTextToken) {
					float score = rcsUtil.getScore(id, myList[j].getCleanedDescription(), myList[j]);

					//REPLACE WITH MATCHING_THRESHOLD

					if (score >= MATCHING_THRESHOLD) {

						myList[j].setScore(score);
						ret.push_back(myList[j]);

					}

				}
			}


		}





	}
	//NO MATCHES FOUND!!
	if (ret.size() == 0) {
		//cout<<"fuziness activated"<<endl;
		for (int j = 0; j<myList.size(); ++j) {
			for (int i = 0; i<searchTextTokens.size(); ++i) {

				vector<string> subjects;
				if (StringUtils::isOneWord(myList[j].getSubjectDescription())) {
					subjects.push_back(myList[j].getSubjectDescription());
				}
				subjects = StringUtils::tokenize(myList[j].getSubjectDescription(), ' ');


				//080300|547|bananas, fresh or dried|BD|0|bananas fresh dried|bananas fresh


				for (int k = 0; k<subjects.size(); ++k) {
					lemmatizedSubject = lemmantization.getRoot(subjects[k]);
					lemmatizedSearchTextToken = lemmantization.getRoot(searchTextTokens[i]);

					if (StringUtils::getLevenshteinDistance(lemmatizedSubject, lemmatizedSearchTextToken) <= 2) {
						float score = rcsUtil.getScore(id, myList[j].getCleanedDescription(), myList[j]);

						//REPLACE WITH MATCHING_THRESHOLD

						if (score >= MATCHING_THRESHOLD) {

							myList[j].setScore(score);
							ret.push_back(myList[j]);

						}

					}
				}


			}





		}

	}

	sort(ret.begin(), ret.end(), cmp);
	return ret;

}




RcsUtilityRequest RcsUtility::removeStopWords(RcsUtilityRequest rcsUtilityRequest) {

	vector<string> stopWords = { "]", "[", "}", "{", "<", ">", "?", "\"", "\\",
		"/", ")", "(", "!", "@", "#", "$", "%", "^", "&", "*", "_", "+", "=", ";", ":", ",", ".", "~", "`", "i",
		"me", "my", "myself", "we", "our", "ours", "ourselves", "you", "your", "yours", "yourself", "yourselves",
		"he", "him", "his", "himself", "she", "her", "hers", "herself", "it", "its", "itself", "they", "them",
		"their", "theirs", "themselves", "what", "which", "who", "whom", "this", "that", "these", "those", "am",
		"is", "are", "was", "were", "be", "been", "being", "have", "has", "had", "having", "do", "does", "did",
		"doing", "a", "an", "the", "and", "but", "if", "or", "because", "as", "until", "while", "of", "at", "by",
		"for", "with", "about", "against", "between", "into", "through", "during", "before", "after", "above",
		"below", "to", "from", "up", "down", "in", "out", "on", "off", "over", "under", "again", "further", "then",
		"once", "here", "there", "when", "where", "why", "how", "all", "any", "both", "each", "few", "most", "some",
		"such", "no", "nor", "only", "own", "same", "so", "too", "per", "very", "i'm", "you're", "he's", "she's",
		"it's", "we're", "they're", "i've", "you've", "we've", "they've", "i'd", "you'd", "he'd", "she'd", "we'd",
		"they'd", "i'll", "you'll", "he'll", "she'll", "we'll", "they'll", "isn't", "aren't", "wasn't", "weren't",
		"hasn't", "haven't", "hadn't", "doesn't", "don't", "didn't", "won't", "wouldn't", "shan't", "shouldn't",
		"can't", "cannot", "couldn't", "mustn't", "let's", "that's", "who's", "what's", "here's", "there's",
		"when's", "where's", "why's", "how's", "would", "should", "could", "ought", "thereof", "not", "cst", "pm",
		"id", "xx", "xxx", "xxxx", "xxxxx", "xxxxxx", "xxxxxxx", "xxxxxxxx", "xxxxxxxxx", "xxxxxxxxxx", "xxxxxxe",
		"ph", "notes", "location", "updated", "sec", "callback", "initial", "pkg", "will", "memri", "assg", "call",
		"reassign", "back", "adv", "spoke", "pls", "ci", "know", "shpr", "advised", "cb", "com", "closed",
		"generated", "sent", "type", "action", "log", "req", "subcase", "assigned", "made", "search", "cnee",
		"email", "yyzr", "contents", "fedex", "missing", "ipd", "pmcst", "thanks", "trace", "elprc", "phta", "send",
		"shipper", "description", "update", "desc", "need", "part", "info", "queued", "iib", "called", "yyzhq",
		"empty", "qty", "attempted", "pkgs", "queue", "arrived", "asap", "attn", "follow", "states", "hrs",
		"number", "thx", "returned", "more", "reclaimed", "confirm", "take", "loc", "rcpt", "around", "can", "cm",
		"mr", "items", "obc", "activated", "also", "cust", "found", "pics", "show", "air", "txkrc", "avail",
		"please", "int", "see", "needed", "ogq", "thank", "fllw", "get", "rcvd", "received", "us", "wants", "well",
		"yulrc", "claim", "thks", "forward", "inside", "like", "memrt", "provided", "stating", "wanting", "within",
		"ext", "give", "going", "left", "calling", "let", "shpmnt", "apologized", "asked", "hours", "hr", "item",
		"note", "amcst", "num", "rgs", "said", "ask", "cnne", "every", "frm", "non", "opoa", "pa", "rvsa", "nt",
		"pr", "jxxxxxx", "nwr", "thinks", "vjah", "iyka", "kh", "plz", "upd", "irq", "trk", "twfrc", "jh", "pull",
		"sdrrc", "try", "yzra", "name", "pzl", "yyzrc", "dxxxxxxxxxx", "sdq", "yet", "ah", "anything", "date",
		"help", "ct", "tnx", "ymxa", "yvrrc", "doesnt", "done", "eta", "jm", "say", "day", "insisted", "noted",
		"put", "receive", "removed", "didnt", "hi", "xxxxxxxxxxxx", "xxxxxxxxxxxxxxxx", "kxxxxxx", "xxfrd",
		"xxxcom", "xxxxxconducted", "xxxxxxxxh", "xxxxxxxxxxxxxxxxxxxx", "xxxxxxxxxxxxxxxxxxxxxx", "ybna", "ybza",
		"yegb", "yfha", "ykarc", "ymxc", "yycb", "yyz", "zdba", "zqca", "zrhrc", "mailto", "zlem", "",
		"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "touch", "able", "according",
		"accordingly", "across", "actually", "afterwards", "aint", "allow", "allows", "almost", "alone", "along",
		"already", "although", "always", "among", "amongst", "another", "anybody", "anyhow", "anyone", "anyway",
		"anyways", "anywhere", "apart", "appear", "appreciate", "appropriate", "arent", "aside", "asking",
		"associated", "available", "away", "awfully", "became", "become", "becomes", "becoming", "beforehand",
		"behind", "believe", "beside", "besides", "best", "better", "beyond", "brief", "cmon", "cs", "came", "cant",
		"cause", "causes", "certain", "certainly", "changes", "clearly", "co", "come", "comes", "concerning",
		"consequently", "consider", "considering", "contain", "containing", "contains", "corresponding", "couldnt",
		"course", "currently", "definitely", "described", "despite", "different", "dont", "downwards", "edu", "eg",
		"eight", "either", "else", "elsewhere", "enough", "entirely", "especially", "et", "etc", "even", "ever",
		"everybody", "everyone", "everything", "everywhere", "ex", "exactly", "example", "except", "far", "ff",
		"fifth", "first", "five", "followed", "following", "follows", "former", "formerly", "forth", "four",
		"furthermore", "gets", "getting", "given", "gives", "go", "goes", "gone", "got", "gotten", "greetings",
		"hadnt", "happens", "hardly", "hasnt", "havent", "hes", "hello", "hence", "heres", "hereafter", "hereby",
		"herein", "hereupon", "hither", "hopefully", "howbeit", "however", "ill", "im", "ive", "ie", "ignored",
		"immediate", "inasmuch", "inc", "indeed", "indicate", "indicated", "indicates", "inner", "insofar",
		"instead", "inward", "isnt", "itd", "itll", "just", "keep", "keeps", "kept", "knows", "known", "last",
		"lately", "later", "latter", "latterly", "least", "less", "lest", "lets", "liked", "likely", "little",
		"look", "looking", "looks", "ltd", "mainly", "many", "may", "maybe", "mean", "meanwhile", "merely", "might",
		"moreover", "mostly", "much", "must", "namely", "nd", "near", "nearly", "necessary", "needs", "neither",
		"never", "nevertheless", "new", "next", "nine", "nobody", "none", "noone", "normally", "nothing", "novel",
		"now", "nowhere", "obviously", "often", "oh", "ok", "okay", "old", "one", "ones", "onto", "otherwise",
		"outside", "overall", "particular", "particularly", "perhaps", "placed", "plus", "possible", "presumably",
		"probably", "provides", "que", "quite", "qv", "rather", "rd", "re", "really", "reasonably", "regarding",
		"regardless", "regards", "relatively", "respectively", "right", "saw", "saying", "says", "second",
		"secondly", "seeing", "seem", "seemed", "seeming", "seems", "seen", "self", "selves", "sensible", "serious",
		"seriously", "seven", "several", "shall", "shouldnt", "since", "six", "somebody", "somehow", "someone",
		"something", "sometime", "sometimes", "somewhat", "somewhere", "soon", "sorry", "specified", "specify",
		"specifying", "still", "sub", "sup", "sure", "ts", "taken", "tell", "tends", "th", "than", "thanx", "thats",
		"thence", "theres", "thereafter", "thereby", "therefore", "therein", "thereupon", "theyd", "theyll",
		"theyre", "theyve", "think", "third", "thorough", "thoroughly", "though", "three", "throughout", "thru",
		"thus", "together", "took", "toward", "towards", "tried", "tries", "truly", "trying", "twice", "two", "un",
		"unfortunately", "unless", "unlikely", "unto", "upon", "use", "used", "useful", "uses", "using", "usually",
		"value", "various", "via", "viz", "vs", "want", "wasnt", "way", "wed", "weve", "welcome", "went", "werent",
		"whats", "whatever", "whence", "whenever", "wheres", "whereafter", "whereas", "whereby", "wherein",
		"whereupon", "wherever", "whether", "whither", "whos", "whoever", "whole", "whose", "willing", "wish",
		"without", "wont", "wonder", "wouldnt", "yes", "youd", "youll", "youre", "youve", "zero", "fresh", "dried",
		"chilled", "frozen", "products", "included", "acids", "acid", "preparations", "industry", "substitutes",
		"properties", "concentrated", "forms", "containers", "mixtures", "provisionally", "unsuitable", "state",
		"consumption", "produce", "produeced", "including", "origin", "gluten", "saps", "extracts", "materials",
		"material", "plaiting", "fats", "waxes", "invertebrates", "confectionery", "parts", "feed", "food",
		"substances", "substance", "matter", "goods", "essential", "modified", "manufactures", "manufacture",
		"plup", "fabrics", "fibers", "coverings", "suitable", "accessories", "sets", "artices", "similar", "base",
		"appliances", "locomotives", "fixtures", "equipment", "structures", "instruments", "resulting",
		"extracting", "works", "preserved", "consisting", "shelled", "unshelled", "peel", "peeled", "roast",
		"roasted", "break", "broken", "cooks", "cooked", "purposes", "primarily", "flavored", "residues", "feeding",
		"stock", "pure", "specially", "cuts", "cut", "piece", "pieces", "content", "solid", "grated", "powdered",
		"formation", "powder", "attached", "syrup", "sliced", "flavouring", "flavoured", "flavour", "weight",
		"weighing", "solids", "processed", "wholly", "partly", "refuse", "components", "compounds", "purity",
		"imported", "grade", "accelerators", "accelerator", "plasticizers", "plasticizer", "subheading",
		"solutions", "printed", "xi", "form", "semimanufactured", "superstructured", "revolving", "heading",
		"headings", "chapter", "fitted", "box", "boxes", "control", "operated", "winding", "exceeding", "years",
		"kind", "retail", "coloring", "reduced", "size", "entered", "synthesized", "packed" };

	vector<string> words = StringUtils::tokenize(rcsUtilityRequest.getSearchText(), ' ');
	for (int i = 0; i<words.size(); ++i) {
		for (int j = 0; j<stopWords.size(); ++j) {
			if (words[i] == stopWords[j]) {

				words[i] = "";
			}
		}
	}
	string temp = "";
	for (int i = 0; i<words.size(); ++i) {
		if (words[i].length()) {
			temp += words[i] + " ";
		}
	}
	rcsUtilityRequest.setSearchText(temp);
	return rcsUtilityRequest;

}

RcsUtilityReply RcsUtility::populateRcsReply(RcsUtilityReply rcsUtilityReply, vector<RcsUtilityData> filteredRcsUtilityDatas) {
	Constants constants;
	RcsUtil rcsUtil;
	if (filteredRcsUtilityDatas.size() == 0) {
		Notification notification;
		vector<Notification> notificationList;
		notification.setSeverity(constants.STATUS_CODE_SUCCESS);
		notification.setSource(constants.TRADE_TOOLS);
		notification.setMessage(constants.NO_MATCH_FOUND);
		notificationList.push_back(notification);
		// cout<<"Notification List size: "<<notificationList.size()<<endl;
		rcsUtilityReply.setNotifications(notificationList);

	}
	else if (filteredRcsUtilityDatas.size() == 1) {

		Notification notification;
		vector<Notification> notificationList;
		notification.setSeverity(constants.STATUS_CODE_ERROR);
		notification.setSource(constants.TRADE_TOOLS);
		notification.setCode(constants.MATCHED_RESTRICTED_COMMODITY_ERROR_CODE);
		notification.setMessage(constants.MATCHED_RESTRICTED_COMMODITY_ERROR_MESSAGE);
		notificationList.push_back(notification);
		rcsUtilityReply.setNotifications(notificationList);

		rcsUtilityReply.setHsCode(filteredRcsUtilityDatas[0].getHsCode());
		rcsUtilityReply.setHsLevel(rcsUtil.getHSLevel(filteredRcsUtilityDatas[0].getHsCode()));
		rcsUtilityReply.setId(filteredRcsUtilityDatas[0].getKeywordId());
		/*
		vector<Message> userMessage;
		vector<MessageParameter> parameterList;
		for(int i=0;i<filteredRcsUtilityDatas.size();++i){
		MessageParameter messageParameter;
		messageParameter.setId(filteredRcsUtilityDatas[i].getKeywordId());
		messageParameter.setValue(filteredRcsUtilityDatas[i].getKeyword());
		parameterList.push_back(messageParameter);

		}
		Message msg;
		userMessage.push_back(msg);

		userMessage[0].setParameters(parameterList);

		rcsUtilityReply.setUserMessages(userMessage);
		*/


	}
	else {

		Notification notification;
		vector<Notification> notificationList;
		notification.setSeverity(constants.STATUS_CODE_WARNING);
		notification.setSource(constants.TRADE_TOOLS);
		notification.setCode(constants.VAGUE_COMMODITY_ERROR_CODE);
		notification.setMessage(constants.VAGUE_COMMODITY_ERROR_MESSAGE);
		notificationList.push_back(notification);
		rcsUtilityReply.setNotifications(notificationList);

		Message message;
		vector<Message> userMessages;
		userMessages.push_back(message);
		userMessages[0].setCode("1001");
		userMessages[0].setText("Please provide additional details for what you're trying to ship: ");
		userMessages[0].setLocalizedText("");

		vector<MessageParameter> parameterList;
		for (int i = 0; i<filteredRcsUtilityDatas.size(); ++i) {
			MessageParameter messageParameter;
			messageParameter.setId(filteredRcsUtilityDatas[i].getKeywordId());
			messageParameter.setValue(filteredRcsUtilityDatas[i].getKeyword());
			messageParameter.setHsCode(filteredRcsUtilityDatas[i].getHsCode());
			messageParameter.setHsLevel(filteredRcsUtilityDatas[i].getHsLevel());
			parameterList.push_back(messageParameter);
		}

		userMessages[0].setParameters(parameterList);

		rcsUtilityReply.setUserMessages(userMessages);

	}

	return rcsUtilityReply;

}
/*
static string getHSLevel(string hsCode){
if(hsCode.length()==1 || hsCode.length()==2){
return HS2;
}else if(hsCode.length()==3 || hsCode.length()==4){
return HS4;
}else{
return HS6;
}
}
*/
