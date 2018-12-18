#ifndef RCSUTILITYVALIDATOR_H
#define RCSUTILITYVALIDATOR_H

#include<vector>
#include<Notification.h>
#include<string>
#include<RcsUtilityReply.h>
#include<RcsUtilityRequest.h>
#include<iostream>
using namespace std;
#define DLL_EXPORT __declspec(dllexport)
class DLL_EXPORT RcsUtilityValidator
{
public:
	RcsUtilityValidator();
	virtual ~RcsUtilityValidator();

	RcsUtilityReply validateRcsUtilityRequest(RcsUtilityRequest rcsUtilityRequest, RcsUtilityReply rcsUtilityReply);
	
	bool isAlphaNumeric(string arg);
protected:

private:
	const string INVALID_REQUEST_ERROR_CODE = "22001";
	vector<Notification> notifications;

};

#endif // RCSUTILITYVALIDATOR_H
