#ifndef RCSSEARCHREPLY_H
#define RCSSEARCHREPLY_H

#include<Notification.h>
#include<Message.h>
#include<string>
#include<iostream>

using namespace std;
#define DLL_EXPORT __declspec(dllexport)
class DLL_EXPORT RcsSearchReply
{
public:
	RcsSearchReply();
	virtual ~RcsSearchReply();
	void setHsCode(string hsCode);
	string getHsCode();
	void setHsLevel(string hsLevel);
	string getHsLevel();
	string getHighestSeverity();
	void setHighestSeverity(string highestSeverity);
	vector<Notification> getNotifications();
	void setNotifications(vector<Notification> notifications);
	vector<Message> getUserMessages();
	void setUserMessages(vector<Message> userMessages);
	string toString();

	void setId(string id);
	string getId();

protected:

private:
	string highestSeverity;
	vector<Notification> notifications;
	string hsCode;
	string hsLevel;
	string id;
	vector<Message> userMessages;
	static const long serialVersionUID;// = 1L;
};

#endif // RCSSEARCHREPLY_H
