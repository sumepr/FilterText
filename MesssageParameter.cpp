#include "stdafx.h"
#include "MessageParameter.h"
#include<string>
#include<iostream>
using namespace std;

MessageParameter::MessageParameter()
{
	//ctor
	id = "";
	value = "";

}

MessageParameter::~MessageParameter()
{
	//dtor
}

void MessageParameter::setId(string _id) {
	id = _id;
}

string MessageParameter::getId() {
	return id;
}

string MessageParameter::getValue() {

	return value;

}

void MessageParameter::setValue(string _value) {
	value = _value;
}
string MessageParameter::getHsCode() {
	return hsCode;
}

void MessageParameter::setHsCode(string _hsCode) {
	hsCode = _hsCode;
}

string MessageParameter::getHsLevel() {

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

void MessageParameter::setHsLevel(string _hsLevel) {
	if (hsCode.length() == 1 || hsCode.length() == 2) {
		hsLevel = "HS2";
	}
	else if (hsCode.length() == 4) {
		hsLevel = "HS4";
	}
	else if (hsCode.length() == 6) {
		hsLevel = "HS6";
	}
	else if (hsCode.length() == 8) {
		hsLevel = "HS8";
	}
	else if (hsCode.length() == 10) {
		hsLevel = "HS10";
	}
	else if (hsCode.length() == 12) {
		hsLevel = "HS12";
	}
}
