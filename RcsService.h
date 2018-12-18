#ifndef RCSSERVICE_H
#define RCSSERVICE_H

#include<RcsUtilityReply.h>
#include<string>
using namespace std;
#define DLL_EXPORT __declspec(dllexport)
class DLL_EXPORT RcsService
{
public:
	RcsService();
	virtual ~RcsService();
	RcsUtilityReply getDetails(string searchText, string originCountryCode, string destinationCountryCode, string carrierCode, string path);

protected:

private:
};

#endif // RCSSERVICE_H
