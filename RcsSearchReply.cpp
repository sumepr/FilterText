#include"pch.h"
#include "stdafx.h"
#include "RcsSearchReply.h"
#include <algorithm>
#include <iterator>
#include<string>
#include<vector>
#include<iostream>
#include<ostream>
using namespace std;

RcsSearchReply::RcsSearchReply()
{
	//ctor
	string highestSeverity;
	vector<Notification> notifications;
	string hsCode;
	string hsLevel;
	string id;
	vector<Message> userMessages;
	static const long serialVersionUID = 1L;

}

RcsSearchReply::~RcsSearchReply()
{
	//dtor
}
/**
* @param hsCode the hsCode to set
*/
void RcsSearchReply::setHsCode(string _hsCode)
{
	hsCode = _hsCode;
}


/**
* @return the hsCode
*/
string RcsSearchReply::getHsCode()
{
	return hsCode;
}


/**
* @param hsLevel the hsLevel to set
*/
void RcsSearchReply::setHsLevel(string _hsLevel)
{
	hsLevel = _hsLevel;
}


/**
* @return the hsLevel
*/
string RcsSearchReply::getHsLevel()
{
	return hsLevel;
}


/**
* @return the highestSeverity
*/
string RcsSearchReply::getHighestSeverity()
{
	return highestSeverity;
}

/**
* @param highestSeverity the highestSeverity to set
*/
void RcsSearchReply::setHighestSeverity(string _highestSeverity)
{
	highestSeverity = _highestSeverity;
}




/**
* @return the notifications
*/
vector<Notification> RcsSearchReply::getNotifications()
{
	//cout<<"size getting"<<notifications.size()<<endl;
	return notifications;
}

/**
* @param notifications the notifications to set
*/
void RcsSearchReply::setNotifications(vector<Notification> _notifications)
{
	notifications = _notifications;
}

/**
* @return the messages[]
*/
vector<Message> RcsSearchReply::getUserMessages()
{
	return userMessages;
}

/**
* @param messages the messages to set
*/
void RcsSearchReply::setUserMessages(vector<Message> _userMessages)
{
	//we need to go element by element
	userMessages = _userMessages;
}
string RcsSearchReply::getId() {
	return id;
}

void RcsSearchReply::setId(string _id) {
	id = _id;
}

string RcsSearchReply::toString() {
	if (hsCode == "") { hsCode = "NULL"; }
	if (hsLevel == "") { hsLevel = "NULL"; }
	if (id == "") { id = "NULL"; }
	string ret = "{hsCode:" + hsCode + ", hsLevel:" + hsLevel + ", id: " + id;
	if (notifications.size() == 0) {
		ret += ", notifications=null";
	}
	else {
		ret += ", notifications:[";

		for (int i = 0; i<notifications.size(); ++i) {
			ret += "[(" + to_string(i) + ")";
			ret += " Severity: " + notifications[i].getSeverity() + "/n";
			ret += " Message: " + notifications[i].getMessage() + "/n";
			ret += " Code: " + notifications[i].getCode();
			for (int j = 0; j<notifications[i].getMessageParameters().size(); ++j) {

				vector<NotificationParameter>params = notifications[0].getMessageParameters();
				ret += " Parameters(" + to_string(params.size()) + ")[";

				for (int j = 0; j<params.size(); ++j) {
					ret += "{";
					ret += "(" + to_string(j) + ")";
					ret += "ID: " + params[j].getId() + "/n";
					ret += "VALUE: " + params[j].getValue() + "/n";
					ret += "}";

				}
				ret += "]";
			}

			ret += "]";


		}


	}

	if (userMessages.size()) {


		ret += ",  userMessages{";
		ret += "Code: " + userMessages[0].getCode();
		ret += ", Text:  " + userMessages[0].getText();
		ret += ", Localized Text: " + userMessages[0].getLocalizedText();
		ret += "parameters(" + to_string(userMessages[0].getParameters().size()) + ")";
		vector<MessageParameter> messageParams = userMessages[0].getParameters();
		for (int i = 0; i<messageParams.size(); ++i) {
			ret += "(" + to_string(i) + ")";
			ret += "ID: " + messageParams[i].getId() + "\n";
			ret += "Value: " + messageParams[i].getValue() + "\n";

		}
		ret += "}";
	}


	return ret;
}

