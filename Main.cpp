#include "pch.h"
#include "stdafx.h"
#include "main.h"

#include<iostream>
#include<RcsUtility.h>
#include<RcsUtilityReply.h>
#include<RcsUtilityRequest.h>
#include<RcsService.h>
#include<string>
using namespace std;

// a sample exported function
RcsUtilityReply DLL_EXPORT QueryRCS(string searchText, string originCountryCode, string destCountrCode, string carrierCode, string path)
{	
		
	RcsService rcs;
	cout << "DLL function" << "Search str " << searchText << endl;

	RcsUtilityReply reply = rcs.getDetails(searchText, originCountryCode, destCountrCode, carrierCode, path);
	cout<<reply.toString();
	return reply;

}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		// attach to process
		// return FALSE to fail DLL load
		break;

	case DLL_PROCESS_DETACH:
		// detach from process
		break;

	case DLL_THREAD_ATTACH:
		// attach to thread
		break;

	case DLL_THREAD_DETACH:
		// detach from thread
		break;
	}
	return TRUE; // succesful
}
