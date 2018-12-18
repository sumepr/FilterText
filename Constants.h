#ifndef CONSTANTS_H
#define CONSTANTS_H
#define DLL_EXPORT __declspec(dllexport)
#include<iostream>
using namespace std;

class DLL_EXPORT Constants
{
public:
	Constants();
	virtual ~Constants();
	//static const float THRESHOLD;// = 0.4;
	const string SPACE = " ";
	const string EMPTY = "";
	const string SPECIAL_CHAR_REGEX = "[^a-zA-Z0-9-.%]";
	const string SPL_CHAR_SPACE_REGEX = "[^a-zA-Z0-9-.%\\s]";
	const string SPACE_REGEX = "\\s+";

	const string ALPHAREGEX = "(^[a-zA-Z_]*$)";
	const string DIGITREGEX = ".*\\d+.*";
	const string INVALID_REQUEST_ERROR_CODE = "22001";
	const string STATUS_CODE_SUCCESS = "SUCCESS";
	const string STATUS_CODE_WARNING = "WARNING";
	const string STATUS_CODE_ERROR = "ERROR";

	const string TRADE_TOOLS = "Trade Tools";

	const string MATCHED_RESTRICTED_COMMODITY_ERROR_MESSAGE = "Matched to a restricted commodity description";
	const string MATCHED_RESTRICTED_COMMODITY_ERROR_CODE = "22008";

	const string VAGUE_COMMODITY_ERROR_MESSAGE = "The commodity description is vague";
	const string VAGUE_COMMODITY_ERROR_CODE = "22007";

	const string NO_MATCH_FOUND = "No match found";

	const string IMPORT_FLAG = "1";
	const string EXPORT_FLAG = "0";

	const int MATCHING_THRESHHOLD = 100;

	const string HS6 = "HS6";
	const string HS4 = "HS4";
	const string HS2 = "HS2";
protected:

private:




};

#endif // CONSTANTS_H
