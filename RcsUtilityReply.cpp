#include "pch.h"
#include "stdafx.h"


#include "RcsUtilityReply.h"
#include <algorithm>
#include <iterator>
#include<string>
#include<vector>
#include<iostream>
#include<ostream>
using namespace std;
#define DLL_EXPORT __declspec(dllexport)


 RcsUtilityReply::RcsUtilityReply()
{
	//ctor
	 cout << "construct RcsUtilityReply" << endl;

}

 RcsUtilityReply::~RcsUtilityReply()
{
	//dtor
}
/**
* @param hsCode the hsCode to set
*/
void RcsUtilityReply::setHsCode(string _hsCode)
{

	if (_hsCode.length() == 5) {
		_hsCode = "0" + _hsCode;
	}
	hsCode = _hsCode;
}


/**
* @return the hsCode
*/
string RcsUtilityReply::getHsCode()
{
	return hsCode;
}


/**
* @param hsLevel the hsLevel to set
*/
void RcsUtilityReply::setHsLevel(string _hsLevel)
{
	hsLevel = _hsLevel;
}


/**
* @return the hsLevel
*/
string RcsUtilityReply::getHsLevel()
{
	return hsLevel;
}


/**
* @return the highestSeverity
*/
string RcsUtilityReply::getHighestSeverity()
{
	return highestSeverity;
}

/**
* @param highestSeverity the highestSeverity to set
*/
void RcsUtilityReply::setHighestSeverity(string _highestSeverity)
{
	highestSeverity = _highestSeverity;
}




/**
* @return the notifications
*/
vector<Notification> RcsUtilityReply::getNotifications()
{
	//cout<<"size getting"<<notifications.size()<<endl;
	return notifications;
}

/**
* @param notifications the notifications to set
*/
void RcsUtilityReply::setNotifications(vector<Notification> _notifications)
{
	notifications = _notifications;
}

/**
* @return the messages[]
*/
vector<Message> RcsUtilityReply::getUserMessages()
{
	return userMessages;
}

/**
* @param messages the messages to set
*/
void RcsUtilityReply::setUserMessages(vector<Message> _userMessages)
{
	//we need to go element by element
	userMessages = _userMessages;
}
string RcsUtilityReply::getId() {
	return id;
}

void RcsUtilityReply::setId(string _id) {
	id = _id;
}

string RcsUtilityReply::toString() {
	if (hsCode == "") {
		hsCode = "NULL";
	}
	if (hsLevel == "") {
		hsLevel = "NULL";
	}
	if (id == "") {
		id = "NULL";

	}

	string ret = "{hsCode: " + hsCode + ", hsLevel: " + hsLevel + ", id: " + id;
	if (notifications.size() == 0) {
		ret += ", notifications=null }";
	}
	else {
		ret += ", notifications: [ \n {";

		for (int i = 0; i < notifications.size(); ++i) {

			ret += " \n Severity: " + notifications[i].getSeverity() + "\n";
			ret += " Source: " + notifications[i].getSource() + "\n";
			ret += " Code: " + notifications[i].getCode() + "\n";
			ret += " Message: " + notifications[i].getMessage() + "\n";

			if (notifications[i].getLocalizedMessage().length()) {
				ret += " LocalizedMessage: " + notifications[i].getLocalizedMessage() + "\n";

			}
			else {
				ret += " LocalizedMessage: NULL \n";

			}

			if (!notifications[0].getMessageParameters().size()) {

				ret += " MessageParameters: NULL\n";

			}
			else {

				for (int j = 0; j < notifications[i].getMessageParameters().size(); ++j) {

					vector<NotificationParameter>params = notifications[0].getMessageParameters();
					ret += " Parameters(" + to_string(params.size()) + ")[";

					for (int j = 0; j < params.size(); ++j) {
						ret += "{";

						ret += "ID: " + params[j].getId() + "/n";
						ret += "VALUE: " + params[j].getValue() + "/n";

						ret += "}";

					}
					ret += "}";
				}
			}
			ret += "}";
			ret += "]";


		}


	}

	if (userMessages.size()) {


		ret += ",\n userMessages{";
		ret += "Code: " + userMessages[0].getCode();
		ret += ", Text:  " + userMessages[0].getText();
		ret += ", Localized Text: " + userMessages[0].getLocalizedText();
		ret += "parameters: [ \n";
		vector<MessageParameter> messageParams = userMessages[0].getParameters();
		for (int i = 0; i < messageParams.size(); ++i) {

			ret += "ID: " + messageParams[i].getId() + "\n";
			ret += "Value: " + messageParams[i].getValue() + "\n";
			ret += "hsCode: " + messageParams[i].getHsCode() + "\n";
			ret += "hsLevel: " + messageParams[i].getHsLevel() + "\n";
		}
		ret += "]";
		ret += "}";
	}
	else {

		ret += ", userMessages: NULL }";

	}


	return ret;
}



