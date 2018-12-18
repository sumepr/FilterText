#include<stdafx.h>


#include "LemmaLoad.h"
#include<vector>
#include<stdio.h>
#include<iostream>
#include<map>
#include<string>
#include<StringUtils.h>
#include<fstream>
#include<windows.h>
using namespace std;

LemmaLoad::LemmaLoad()
{
	//ctor

}

LemmaLoad::~LemmaLoad()
{
	//dtor
}
map<string, string> LemmaLoad::readDataFromFile() {


	string dictionary[85];
	dictionary[0] = {
#include "lemmantizationdata/lemmatization-part-0.txt"
	};

	dictionary[1] = {
#include "lemmantizationdata/lemmatization-part-1.txt"
	};
	dictionary[2] = {
#include "lemmantizationdata/lemmatization-part-2.txt"
	};
	dictionary[3] = {
#include "lemmantizationdata/lemmatization-part-3.txt"
	};
	dictionary[4] = {
#include "lemmantizationdata/lemmatization-part-4.txt"
	};
	dictionary[5] = {
#include "lemmantizationdata/lemmatization-part-5.txt"
	};
	dictionary[6] = {
#include "lemmantizationdata/lemmatization-part-6.txt"
	};
	dictionary[7] = {
#include "lemmantizationdata/lemmatization-part-7.txt"
	};
	dictionary[8] = {
#include "lemmantizationdata/lemmatization-part-8.txt"
	};
	dictionary[9] = {
#include "lemmantizationdata/lemmatization-part-9.txt"
	};
	dictionary[10] = {
#include "lemmantizationdata/lemmatization-part-10.txt"
	};
	dictionary[11] = {
#include "lemmantizationdata/lemmatization-part-11.txt"
	};
	dictionary[12] = {
#include "lemmantizationdata/lemmatization-part-12.txt"
	};
	dictionary[13] = {
#include "lemmantizationdata/lemmatization-part-13.txt"
	};
	dictionary[14] = {
#include "lemmantizationdata/lemmatization-part-14.txt"
	};
	dictionary[15] = {
#include "lemmantizationdata/lemmatization-part-15.txt"
	};
	dictionary[16] = {
#include "lemmantizationdata/lemmatization-part-16.txt"
	};
	dictionary[17] = {
#include "lemmantizationdata/lemmatization-part-17.txt"
	};
	dictionary[18] = {
#include "lemmantizationdata/lemmatization-part-18.txt"
	};
	dictionary[19] = {
#include "lemmantizationdata/lemmatization-part-19.txt"
	};
	dictionary[20] = {
#include "lemmantizationdata/lemmatization-part-20.txt"
	};
	dictionary[21] = {
#include "lemmantizationdata/lemmatization-part-21.txt"
	};
	dictionary[22] = {
#include "lemmantizationdata/lemmatization-part-22.txt"
	};
	dictionary[23] = {
#include "lemmantizationdata/lemmatization-part-23.txt"
	};
	dictionary[24] = {
#include "lemmantizationdata/lemmatization-part-24.txt"
	};
	dictionary[25] = {
#include "lemmantizationdata/lemmatization-part-25.txt"
	};
	dictionary[26] = {
#include "lemmantizationdata/lemmatization-part-26.txt"
	};
	dictionary[27] = {
#include "lemmantizationdata/lemmatization-part-27.txt"
	};
	dictionary[28] = {
#include "lemmantizationdata/lemmatization-part-28.txt"
	};
	dictionary[29] = {
#include "lemmantizationdata/lemmatization-part-29.txt"
	};
	dictionary[30] = {
#include "lemmantizationdata/lemmatization-part-30.txt"
	};
	dictionary[31] = {
#include "lemmantizationdata/lemmatization-part-31.txt"
	};
	dictionary[32] = {
#include "lemmantizationdata/lemmatization-part-32.txt"
	};
	dictionary[33] = {
#include "lemmantizationdata/lemmatization-part-33.txt"
	};
	dictionary[34] = {
#include "lemmantizationdata/lemmatization-part-34.txt"
	};
	dictionary[35] = {
#include "lemmantizationdata/lemmatization-part-35.txt"
	};
	dictionary[36] = {
#include "lemmantizationdata/lemmatization-part-36.txt"
	};
	dictionary[37] = {
#include "lemmantizationdata/lemmatization-part-37.txt"
	};
	dictionary[38] = {
#include "lemmantizationdata/lemmatization-part-38.txt"
	};
	dictionary[39] = {
#include "lemmantizationdata/lemmatization-part-39.txt"
	};
	dictionary[40] = {
#include "lemmantizationdata/lemmatization-part-40.txt"
	};
	dictionary[41] = {
#include "lemmantizationdata/lemmatization-part-41.txt"
	};
	dictionary[42] = {
#include "lemmantizationdata/lemmatization-part-42.txt"
	};
	dictionary[43] = {
#include "lemmantizationdata/lemmatization-part-43.txt"
	};
	dictionary[44] = {
#include "lemmantizationdata/lemmatization-part-44.txt"
	};
	dictionary[45] = {
#include "lemmantizationdata/lemmatization-part-45.txt"
	};
	dictionary[46] = {
#include "lemmantizationdata/lemmatization-part-46.txt"
	};
	dictionary[47] = {
#include "lemmantizationdata/lemmatization-part-47.txt"
	};
	dictionary[48] = {
#include "lemmantizationdata/lemmatization-part-48.txt"
	};
	dictionary[49] = {
#include "lemmantizationdata/lemmatization-part-49.txt"
	};
	dictionary[50] = {
#include "lemmantizationdata/lemmatization-part-50.txt"
	};
	dictionary[51] = {
#include "lemmantizationdata/lemmatization-part-51.txt"
	};
	dictionary[52] = {
#include "lemmantizationdata/lemmatization-part-52.txt"
	};
	dictionary[53] = {
#include "lemmantizationdata/lemmatization-part-53.txt"
	};
	dictionary[54] = {
#include "lemmantizationdata/lemmatization-part-54.txt"
	};
	dictionary[55] = {
#include "lemmantizationdata/lemmatization-part-55.txt"
	};
	dictionary[56] = {
#include "lemmantizationdata/lemmatization-part-56.txt"
	};
	dictionary[57] = {
#include "lemmantizationdata/lemmatization-part-57.txt"
	};
	dictionary[58] = {
#include "lemmantizationdata/lemmatization-part-58.txt"
	};
	dictionary[59] = {
#include "lemmantizationdata/lemmatization-part-59.txt"
	};
	dictionary[60] = {
#include "lemmantizationdata/lemmatization-part-60.txt"
	};
	dictionary[61] = {
#include "lemmantizationdata/lemmatization-part-61.txt"
	};
	dictionary[62] = {
#include "lemmantizationdata/lemmatization-part-62.txt"
	};
	dictionary[63] = {
#include "lemmantizationdata/lemmatization-part-63.txt"
	};
	dictionary[64] = {
#include "lemmantizationdata/lemmatization-part-64.txt"
	};
	dictionary[65] = {
#include "lemmantizationdata/lemmatization-part-65.txt"
	};
	dictionary[66] = {
#include "lemmantizationdata/lemmatization-part-66.txt"
	};
	dictionary[67] = {
#include "lemmantizationdata/lemmatization-part-67.txt"
	};
	dictionary[68] = {
#include "lemmantizationdata/lemmatization-part-68.txt"
	};
	dictionary[69] = {
#include "lemmantizationdata/lemmatization-part-69.txt"
	};
	dictionary[70] = {
#include "lemmantizationdata/lemmatization-part-70.txt"
	};
	dictionary[71] = {
#include "lemmantizationdata/lemmatization-part-71.txt"
	};
	dictionary[72] = {
#include "lemmantizationdata/lemmatization-part-72.txt"
	};
	dictionary[73] = {
#include "lemmantizationdata/lemmatization-part-73.txt"
	};
	dictionary[74] = {
#include "lemmantizationdata/lemmatization-part-74.txt"
	};
	dictionary[75] = {
#include "lemmantizationdata/lemmatization-part-75.txt"
	};
	dictionary[76] = {
#include "lemmantizationdata/lemmatization-part-76.txt"
	};
	dictionary[77] = {
#include "lemmantizationdata/lemmatization-part-77.txt"
	};
	dictionary[78] = {
#include "lemmantizationdata/lemmatization-part-78.txt"
	};
	dictionary[79] = {
#include "lemmantizationdata/lemmatization-part-79.txt"
	};
	dictionary[80] = {
#include "lemmantizationdata/lemmatization-part-80.txt"
	};
	dictionary[81] = {
#include "lemmantizationdata/lemmatization-part-81.txt"
	};
	dictionary[82] = {
#include "lemmantizationdata/lemmatization-part-82.txt"
	};
	dictionary[83] = {
#include "lemmantizationdata/lemmatization-part-83.txt"
	};
	map<string, string> lemmas;


	


	string tempDictionary;
	for (int i = 0; i <= 83; ++i) {

		tempDictionary = dictionary[i];
		string temp1 = ""; string temp2 = "";
		bool delimmiterFound = 0;


		for (int j = 0; j<tempDictionary.length(); ++j) {

			if (tempDictionary[j] == '\n') {
				lemmas[temp2] = temp1;
				temp1 = temp2 = "";
				delimmiterFound = 0;
			}
			else {
				if (tempDictionary[j] == '|') {
					delimmiterFound = 1;
					continue;
				}

				if (!delimmiterFound) {

					temp1 += tempDictionary[j];

				}
				else {

					temp2 += tempDictionary[j];

				}

			}



		}

	}



	return lemmas;
}

