#include "stdafx.h"
#include "NotificationParameter.h"
#include<string>
using namespace std;

NotificationParameter::NotificationParameter()
{

	string id;
	string value;
	static const long serialVersionUID = 1L;
	static const string _GENERATION_ = "NotificationParameter (1.0) from Trade Tools (trdt 3.10) from ./loads/201801/DOM-Versions-1-29.xml 1.29.1.6";
	//ctor
}

NotificationParameter::~NotificationParameter()
{
	//dtor
}


string NotificationParameter::getId() {
	return id;
}

void NotificationParameter::setId(string _id) {
	id = _id;
}

string NotificationParameter::getValue() {
	return value;
}

void NotificationParameter::setValue(string _value) {
	value = _value;
}


string NotificationParameter::getHsCode() {
	return hsCode;
}

void NotificationParameter::setHsCode(string _hsCode) {
	hsCode = _hsCode;
}

void NotificationParameter::setHsLevel(string _hsLevel) {
	hsLevel = _hsLevel;
}
string NotificationParameter::getHsLevel() {
	if (hsCode.length() == 1 || hsCode.length() == 2) {
		return "HS2";
	}
	else if (hsCode.length() == 4) {
		return "HS4";
	}
	else if (hsCode.length() == 6) {
		return "HS6";
	}
	else if (hsCode.length() == 8) {
		return "HS8";
	}
	else if (hsCode.length() == 10) {
		return "HS10";
	}
	else if (hsCode.length() == 12) {
		return "HS12";
	}
}
