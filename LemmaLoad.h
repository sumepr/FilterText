#ifndef LEMMALOAD_H
#define LEMMALOAD_H
#include<map>
#define DLL_EXPORT __declspec(dllexport)

using namespace std;
class DLL_EXPORT LemmaLoad
{
public:
	LemmaLoad();
	virtual ~LemmaLoad();

	//char * path="";
	static map<string, string> readDataFromFile();
protected:

private:

};

#endif // LEMMALOAD_H
