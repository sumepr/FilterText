#ifndef LEMMANTIZATION_H
#define LEMMANTIZATION_H
#include<string>
#include<map>
#define DLL_EXPORT __declspec(dllexport)
using namespace std;

class DLL_EXPORT Lemmantization
{
public:
	Lemmantization();
	virtual ~Lemmantization();
	string getRoot(string word);
	static Lemmantization * getInstance();
protected:

private:
	map<string, string> myMap;
	static Lemmantization* instance;
};

#endif // LEMMANTIZATION_H
