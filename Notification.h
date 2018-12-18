#ifndef NOTIFICATION_H
#define NOTIFICATION_H
#include<NotificationParameter.h>
#include<string>
#include<vector>
using namespace std;

#define DLL_EXPORT __declspec(dllexport)

class DLL_EXPORT Notification
{
    public:
        Notification();
        virtual ~Notification();
        static const string _GENERATION_;// = "Notification (2.2) from Trade Tools (trdt 3.10) from ./loads/201801/DOM-Versions-1-29.xml 1.29.1.6";

        string getSeverity();
        void setSeverity(string severity);

        string getSource();
        void setSource(string source);

        string getCode();
        void setCode(string code);

        string getMessage();
        void setMessage(string message);

        string getLocalizedMessage();
        void setLocalizedMessage(string localizedMessage);

        void setMessageParameters(vector<NotificationParameter> messageParameters);
        vector<NotificationParameter> getMessageParameters();

        static long getSerialversionuid();
        static string getGeneration();

    protected:

    private:
        //static const long serialVersionUID;// = 1L;
        string severity;
        string source;
        string code;
        string message;
        string localizedMessage;
        vector<NotificationParameter> MessageParameter;


};

#endif // NOTIFICATION_H
