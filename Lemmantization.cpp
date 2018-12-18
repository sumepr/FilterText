#include "pch.h"
#include "stdafx.h"
#include "Lemmantization.h"
#include<LemmaLoad.h>
#include<map>
#include<iostream>
#include<algorithm>

using namespace std;

Lemmantization::Lemmantization()
{
	//ctor


}

Lemmantization::~Lemmantization()
{
	//dtor
}

Lemmantization * Lemmantization::instance = 0;
Lemmantization * Lemmantization::getInstance() {

	if (instance == 0) {
		instance = new Lemmantization;
	}
	return instance;

}
string Lemmantization::getRoot(string word) {


	std::transform(word.begin(), word.end(), word.begin(), ::tolower);

	if (myMap.size() == 0) {

		//cout<<"empty;";
		myMap = LemmaLoad::readDataFromFile();
	}

	
	if (myMap[word] == "") {
		return word;
	}
	//cout<<":D"<<myMap[word]<<endl;
	return myMap[word];

	for (map<string, string>::iterator it = myMap.begin(); it != myMap.end(); ++it) {

		if (it != myMap.end()) {
			if (word == it->first) {

				return it->second;
			}
		}

	}
	return word;


}
