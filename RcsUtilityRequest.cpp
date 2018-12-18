#include "pch.h"
#include "stdafx.h"
#include "RcsUtilityRequest.h"
#include<string>
#include<algorithm>
using namespace std;

RcsUtilityRequest::RcsUtilityRequest()
{
	//ctor
}

RcsUtilityRequest::~RcsUtilityRequest()
{
	//dtor
}

/**
 * @return the searchText
 */
string RcsUtilityRequest::getSearchText() {
	return searchText;
}

/**
 * @param String to set
 */
void RcsUtilityRequest::setSearchText(string _searchText) {
	transform(_searchText.begin(), _searchText.end(), _searchText.begin(), ::tolower);
	searchText = _searchText;
}


/**
 * @return the originCountryCode
 */
string RcsUtilityRequest::getOriginCountryCode() {
	return originCountryCode;
}

/**
 * @param String to set
 */
void RcsUtilityRequest::setOriginCountryCode(string _originCountryCode) {
	originCountryCode = _originCountryCode;
}


/**
 * @return the originCountryCode
 */
string RcsUtilityRequest::getDestinationCountryCode() {
	return destinationCountryCode;
}


/**
 * @param String to set
 */
void RcsUtilityRequest::setDestinationCountryCode(string _destinationCountryCode) {
	destinationCountryCode = _destinationCountryCode;
}

/**
 * @return the carrierCode
 */
string RcsUtilityRequest::getCarrierCode() {
	return carrierCode;
}


/**
 * @param String to set
 */
void RcsUtilityRequest::setCarrierCode(string _carrierCode) {
	carrierCode = _carrierCode;
}
