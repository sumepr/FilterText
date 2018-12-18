#ifndef __MAIN_H__
#define __MAIN_H__

#include <windows.h>
#include<string>
#include<RcsUtilityReply.h>
using namespace std;

/*  To use this exported function of dll, include this header
 *  in your project.
 */

#define DLL_EXPORT __declspec(dllexport)



#ifdef __cplusplus
extern "C"
{
#endif


	RcsUtilityReply DLL_EXPORT QueryRCS(string a, string b, string c, string d, string e);


#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__
