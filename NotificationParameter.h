#ifndef NOTIFICATIONPARAMETER_H
#define NOTIFICATIONPARAMETER_H

#include<string>
using namespace std;

#define DLL_EXPORT __declspec(dllexport)


class DLL_EXPORT NotificationParameter
{
    public:
        static const string _GENERATION_;// = "NotificationParameter (1.0) from Trade Tools (trdt 3.10) from ./loads/201801/DOM-Versions-1-29.xml 1.29.1.6";

        NotificationParameter();
        virtual ~NotificationParameter();

        string getId();
        void setId(string id);

        string getValue();
        void setValue(string value);

        long getSerialversionuid();
        static string getGeneration();

        string getHsLevel();
        void setHsLevel(string hsLevel);

        string getHsCode();
        void setHsCode(string hsCode);

    protected:

    private:
        string id;
        string value;
        static const long serialVersionUID;// = 1L;
        string hsCode;
        string hsLevel;




};

#endif // NOTIFICATIONPARAMETER_H
