#include "stdafx.h"
#include "Notification.h"

Notification::Notification()
{
	//ctor
	static const long serialVersionUID = 1L;
	static const string _GENERATION_ = "Notification (2.2) from Trade Tools (trdt 3.10) from ./loads/201801/DOM-Versions-1-29.xml 1.29.1.6";

	string severity;
	string source;
	string code;
	string message;
	string localizedMessage;
	vector<NotificationParameter> MessageParameter;


}

Notification::~Notification()
{
	//dtor
}


void Notification::setSeverity(string _severity) {
	severity = _severity;
}

string Notification::getSeverity() {
	return severity;
}

string Notification::getSource() {
	return source;
}

void Notification::setSource(string _source) {
	source = _source;
}


string Notification::getCode() {
	return code;
}

void Notification::setCode(string _code) {
	code = _code;
}


string Notification::getMessage() {
	return message;
}
void Notification::setMessage(string _message) {
	message = _message;
}

string Notification::getLocalizedMessage() {
	return localizedMessage;
}
void Notification::setLocalizedMessage(string _localizedMessage) {
	localizedMessage = _localizedMessage;
}

vector<NotificationParameter> Notification::getMessageParameters() {
	return MessageParameter;
}

void Notification::setMessageParameters(vector<NotificationParameter> _messageParameters) {
	MessageParameter = _messageParameters;
}
