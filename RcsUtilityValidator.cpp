#include "pch.h"
#include "stdafx.h"

#include "RcsUtilityValidator.h"
#include<regex>
#include<Constants.h>
#include<StringUtils.h>
#include<algorithm>
#include<string>
RcsUtilityValidator::RcsUtilityValidator()
{
	//ctor
}

RcsUtilityValidator::~RcsUtilityValidator()
{
	//dtor
}

RcsUtilityReply RcsUtilityValidator::validateRcsUtilityRequest(RcsUtilityRequest rcsUtilityRequest, RcsUtilityReply rcsUtilityReply)
{

	// sp: this function can be broken into multiple functions for different type of validation.



	Constants constants;
	StringUtils stringUtils;
	if (rcsUtilityRequest.getSearchText() == "")
	{

		Notification notification;

		notification.setSeverity("ERROR");
		notification.setSource("Trade Tools");
		notification.setCode(INVALID_REQUEST_ERROR_CODE);
		notification.setMessage("Invalid request field[" + string("SearchText") + string("] value [") + string(rcsUtilityRequest.getSearchText()) + string("]."));

		notifications.push_back(notification);
		cout << notifications[0].getMessage();
		rcsUtilityReply.setNotifications(notifications);
	}
	regex alpharegex(constants.ALPHAREGEX);
	regex digitregex(constants.DIGITREGEX);

	if (stringUtils.isEmpty(rcsUtilityRequest.getDestinationCountryCode()) && stringUtils.isEmpty(rcsUtilityRequest.getOriginCountryCode())) {
		
		Notification notification;
		notification.setSeverity("ERROR");
		notification.setSource("Trade Tools");
		notification.setCode(INVALID_REQUEST_ERROR_CODE);
		notification.setMessage("Both Destination and source country code is empty");
		//notification.setMessage("Invalid request field[" + string("destinationCountry") + string("] value [") + string(rcsUtilityRequest.getDestinationCountryCode()) + string("]."));

		notifications.push_back(notification);

		
		
/*
		Notification notification_2;
		notification_2.setSeverity("ERROR");
		notification_2.setSource("Trade Tools");

		notification_2.setCode(INVALID_REQUEST_ERROR_CODE);
		notification_2.setMessage("Invalid request field[" + string("originCountry") + string("] value [") + string(rcsUtilityRequest.getOriginCountryCode()) + string("]."));

		notifications.push_back(notification_2);
*/

		rcsUtilityReply.setNotifications(notifications);



	}
	if (!stringUtils.isEmpty(rcsUtilityRequest.getDestinationCountryCode()) && !regex_match(rcsUtilityRequest.getDestinationCountryCode(), alpharegex))
	{

		Notification notification;
		notification.setSeverity("ERROR");
		notification.setSource("Trade Tools");
		notification.setCode(INVALID_REQUEST_ERROR_CODE);
		notification.setMessage("Invalid request field[" + string("destinationCountry") + string("] value [") + string(rcsUtilityRequest.getDestinationCountryCode()) + string("]."));

		notifications.push_back(notification);

		rcsUtilityReply.setNotifications(notifications);

	}

	if (!stringUtils.isEmpty(rcsUtilityRequest.getOriginCountryCode()) && !regex_match(rcsUtilityRequest.getOriginCountryCode(), alpharegex))
	{

		Notification notification;
		notification.setSeverity("ERROR");
		notification.setSource("Trade Tools");

		notification.setCode(INVALID_REQUEST_ERROR_CODE);
		notification.setMessage("Invalid request field[" + string("originCountry") + string("] value [") + string(rcsUtilityRequest.getOriginCountryCode()) + string("]."));

		notifications.push_back(notification);

		rcsUtilityReply.setNotifications(notifications);

	}

	if (stringUtils.isNotEmpty(rcsUtilityRequest.getCarrierCode()) && !regex_match(rcsUtilityRequest.getCarrierCode(), alpharegex))
	{

		Notification notification;
		notification.setSeverity("ERROR");
		notification.setSource("Trade Tools");

		notification.setCode(INVALID_REQUEST_ERROR_CODE);
		notification.setMessage("Invalid request field[" + string("carrierCode") + string("] value. [") + string(rcsUtilityRequest.getCarrierCode()) + string("]."));

		notifications.push_back(notification);

		rcsUtilityReply.setNotifications(notifications);

	}

	//sp: make singleton hashtable read from configurable file. Check the values are correct or not, FXF missing
	string arr[] = { "FDXC", "FDXG", "FDXE", "FXCC", "FXFR", "FXSP", "FXG", "FXE" }; 
	if (stringUtils.isNotEmpty(rcsUtilityRequest.getCarrierCode()))
	{
		bool found = 0;
		string carrierCode = rcsUtilityRequest.getCarrierCode();
		for (int i = 0; i<8; ++i) {
			if (arr[i] == carrierCode) {
				found = 1;
			}
		}
		if (!found) {
			Notification notification;
			notification.setSeverity("ERROR");
			notification.setSource("Trade Tools");

			notification.setCode(INVALID_REQUEST_ERROR_CODE);
			notification.setMessage("Invalid request field[" + string("carrierCode") + string("] value. [") + string(rcsUtilityRequest.getCarrierCode()) + string("]."));

			notifications.push_back(notification);

			rcsUtilityReply.setNotifications(notifications);
		}
	}



	return rcsUtilityReply;
}

bool RcsUtilityValidator::isAlphaNumeric(string arg)
{

	for (int i = 0; i<arg.length(); ++i)
	{
		if (isalnum(arg[i]) == false)
		{
			//cout<<arg[i]<<" false "<<endl;
			return false;

		}
	}
	return true;
}
