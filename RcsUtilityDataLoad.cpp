#include "pch.h"
#include "stdafx.h"
#include "RcsUtilityDataLoad.h"
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <stdexcept>
#include <sys/types.h>
#include <sys/stat.h>
#include <chrono>
#include<limits>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <fstream>
#ifndef WIN32
#include <unistd.h>x
#endif

#ifdef WIN32
#define stat _stat
#endif
using namespace std;
RcsUtilityDataLoad::RcsUtilityDataLoad()
{
	//ctor
	vector<RcsUtilityData> rcsUtilityDataList;
	RcsUtilityData data;
	dataLoadStartTime = 0;
	fileLoadDate = 0;
	daysLapsed = 1;


}

RcsUtilityDataLoad::~RcsUtilityDataLoad()
{
	//dtor
}

RcsUtilityDataLoad* RcsUtilityDataLoad::instance = 0;
RcsUtilityDataLoad* RcsUtilityDataLoad::getInstance()
{
	if (instance == 0)
	{
		instance = new RcsUtilityDataLoad();
	}

	return instance;
}

vector<RcsUtilityData> RcsUtilityDataLoad::getRcsUtilityDataList() {
	return rcsUtilityDataList;
}

void RcsUtilityDataLoad::setRcsUtilityDataList(vector<RcsUtilityData> _rcsUtilityDataList) {

	rcsUtilityDataList = _rcsUtilityDataList;
}

vector<string> tokenizeLine(string line) {
	vector<string> ret;
	string temp = "";
	//|asc|csc
	for (int i = 0; i<line.length(); ++i) {

		if (line[i] == '|') {
			ret.push_back(temp);
			temp = "";
		}
		else {
			temp += line[i];
		}
	}
	ret.push_back(temp);
	return ret;
}

vector<RcsUtilityData> RcsUtilityDataLoad::readDataFromFlatFile(string path) {


	vector<RcsUtilityData> ret;
	try {


		string line;
		time_t my_time = time(NULL);
		const long double sysTime = time(0);
		const long double currentSystemTime = sysTime;

		string  filename = path;

		double SECONDSINADAY = 86400.0;



			
		string temp = "";
		//DAY 1
		double timeDistance;
		if (fileLoadDate) {
			timeDistance = currentSystemTime - fileLoadDate;
			//daysLapsed = (timeDistance/SECONDSINADAY )+2;
			//cout<<"TIME DISTANCE "<<timeDistance<<endl;
			//cout<<"Current DAy "<<daysLapsed<<endl;
		}
		else {
			daysLapsed = 1;

		}

		//cout<<( daysLapsed-1) * SECONDSINADAY<<" "<<daysLapsed*SECONDSINADAY<<endl;
		//CHECKS IF WE ARE IN DAY 1 OR A NEW DAY
		if ((int)fileLoadDate == 0 || ((((daysLapsed - 1) * SECONDSINADAY) <= timeDistance) && ((timeDistance) <= (daysLapsed*SECONDSINADAY)))) {



			//cout<<"TRIGGERRREDD"<<endl;
			if ((int)fileLoadDate == 0) {

				fileLoadDate = currentSystemTime;


			}



			daysLapsed++;

			int x = 0;
			//if(rcsUtilityDataList.size()==0){

			ifstream myfile(path);
			while (myfile.good())
			{

				getline(myfile, line);

				/*
				for(int i=0;i<line.length();++i){
				if( (line[i]>='a'&&line[i]<='z') || (line[i]>='A' && line[i]<='Z') || isdigit(line[i]) || line[i]==' '
				|| line[i]=='.' || line[i]=='%' || line[i]=='-' || line[i]=='|'){

				temp+= line[i];

				}
				line = temp;
				}*/
				vector<string> tokens = tokenizeLine(line);

				data.setHsCode(tokens[0]);
				data.setKeywordId(tokens[1]);
				data.setKeyword(tokens[2]);
				data.setCountryCode(tokens[3]);
				data.setIeFlag(tokens[4]);
				data.setCleanedDescription(tokens[5]);
				data.setSubjectDescription(tokens[6]);
				rcsUtilityDataList.push_back(data);

				line = "";


			}

			//}else{

			//setRcsUtilityDataList(rcsUtilityDataList);
			//return rcsUtilityDataList;


			// }

		}
		else {
			//cout<<"I AM NOT RELOADING FILE"<<endl;
			setRcsUtilityDataList(rcsUtilityDataList);
			return rcsUtilityDataList;

		}





	}
	catch (std::exception const& e) {
		//cout<<"error happenned"<<e.what()<<endl;
	}

	setRcsUtilityDataList(rcsUtilityDataList);
	return rcsUtilityDataList;
}
