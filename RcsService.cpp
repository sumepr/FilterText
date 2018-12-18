#include "pch.h"
#include "stdafx.h"
#include "RcsService.h"
#include<RcsUtility.h>
#include<RcsUtilityRequest.h>
#include<RcsUtilityReply.h>
#include<algorithm>
#include<string>
using namespace std;

RcsService::RcsService()
{
	//ctor
}

RcsService::~RcsService()
{
	//dtor
}
RcsUtilityReply RcsService::getDetails(string searchText, string originCountryCode, string destinationCountryCode, string carrierCode, string path) {


	std::transform(destinationCountryCode.begin(), destinationCountryCode.end(), destinationCountryCode.begin(), ::toupper);
	std::transform(originCountryCode.begin(), originCountryCode.end(), originCountryCode.begin(), ::toupper);
	std::transform(carrierCode.begin(), carrierCode.end(), carrierCode.begin(), ::toupper);



	RcsUtility rcsUtility;
	RcsUtilityRequest rcsUtilityRequest;
	rcsUtilityRequest.setOriginCountryCode(originCountryCode);
	rcsUtilityRequest.setDestinationCountryCode(destinationCountryCode);
	rcsUtilityRequest.setCarrierCode(carrierCode);
	rcsUtilityRequest.setSearchText(searchText);


	RcsUtilityReply rcsUtilityReply = rcsUtility.getDetails(rcsUtilityRequest, path);
	return rcsUtilityReply;
}
