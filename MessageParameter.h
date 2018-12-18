#ifndef MESSAGEPARAMETER_H
#define MESSAGEPARAMETER_H
#include<string>

#define DLL_EXPORT __declspec(dllexport)


using namespace std;
class DLL_EXPORT MessageParameter
{
    public:
        MessageParameter();
        virtual ~MessageParameter();

        void setId(string id);
        string getId();

        void setValue(string value);
        string getValue();

        void setHsCode(string hsCode);
        string getHsCode();

        void setHsLevel(string hsLevel);
        string getHsLevel();


    protected:

    private:
        string id;
        string value;
        string hsCode;
        string hsLevel;

};

#endif // MESSAGEPARAMETER_H
