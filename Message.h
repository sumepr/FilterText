#ifndef MESSAGE_H
#define MESSAGE_H
#include<MessageParameter.h>
#include<vector>
#include<string>

using namespace std;
#define DLL_EXPORT __declspec(dllexport)


class DLL_EXPORT Message
{
    public:
        Message();
        virtual ~Message();

        string getCode();
        void setCode(string code);

        string getText();
        void setText(string text);

        string getLocalizedText();
        void setLocalizedText(string localizedText);

        vector<MessageParameter> getParameters();
        void setParameters(vector<MessageParameter> parameters);


    protected:

    private:
        string code;
        string text;
        string localizedText;
        vector<MessageParameter> parameters;
};

#endif // MESSAGE_H
