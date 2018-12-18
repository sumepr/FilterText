#include "stdafx.h"
#include "Message.h"
#include<vector>
#include<cstring>
#include<MessageParameter.h>

using namespace std;

Message::Message()
{
	string code;
	string text;
	string localizedText;
	vector<MessageParameter> parameters;
	//ctor
}

Message::~Message()
{
	//dtor
}
string Message::getCode() {

	return code;

}
void Message::setCode(string _code) {

	code = _code;

}


string Message::getText() {

	return text;

}

void Message::setText(string _text) {

	text = _text;

}


string Message::getLocalizedText() {
	return localizedText;
}
void Message::setLocalizedText(string _localizedText) {
	localizedText = _localizedText;
}


vector<MessageParameter> Message::getParameters() {
	return parameters;
}

void Message::setParameters(vector<MessageParameter> _parameters) {
	parameters = _parameters;
}

