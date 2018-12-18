#ifndef RCSUTILITYREQUEST_H
#define RCSUTILITYREQUEST_H
#include<string>
using namespace std;
#define DLL_EXPORT __declspec(dllexport)
class DLL_EXPORT RcsUtilityRequest
{
public:
	RcsUtilityRequest();
	virtual ~RcsUtilityRequest();
	string getSearchText();
	void setSearchText(string searchText);
	string getOriginCountryCode();
	void setOriginCountryCode(string originCountryCode);
	string getDestinationCountryCode();
	void setDestinationCountryCode(string destinationCountryCode);
	string getCarrierCode();
	void setCarrierCode(string carrierCode);

protected:

private:
	static const long serialVersionUID;// = 1L;
	string searchText;
	string originCountryCode;
	string destinationCountryCode;
	string carrierCode;


};

#endif // RCSUTILITYREQUEST_H
