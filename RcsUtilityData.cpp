#include "pch.h"
#include "stdafx.h"
#include "RcsUtilityData.h"
#include<vector>
#include<iostream>
#include<set>
#include<algorithm>
using namespace std;

RcsUtilityData::RcsUtilityData()
{
	//ctor
	string hsCode;
	string keywordId;
	string keyWord;
	string countryCode;
	string ieFlag;
	string cleanedDescription;
	string subjectDescription;
	string hsLevel;

	float score;
}

RcsUtilityData::~RcsUtilityData()
{
	//dtor
}


string RcsUtilityData::getHsCode() {

	return hsCode;

}

void RcsUtilityData::setCleanedDescription(string _cleanedDescription) {
	cleanedDescription = _cleanedDescription;
}
string RcsUtilityData::getCleanedDescription() {
	return cleanedDescription;
}

void RcsUtilityData::setSubjectDescription(string _subjectDescription) {
	subjectDescription = _subjectDescription;
}
string RcsUtilityData::getSubjectDescription() {
	return subjectDescription;
}


void RcsUtilityData::setHsCode(string _hsCode) {

	hsCode = _hsCode;

}




string RcsUtilityData::getHsLevel() {

	return hsLevel;

}

void RcsUtilityData::setHsLevel(string _hsLevel) {
	hsLevel = _hsLevel;
}

void RcsUtilityData::setKeywordId(string _keywordId) {

	keywordId = _keywordId;
}




string RcsUtilityData::getKeywordId() {

	return keywordId;

}



string RcsUtilityData::getCountryCode() {
	return countryCode;
}

void RcsUtilityData::setCountryCode(string _countryCode) {
	countryCode = _countryCode;
}


string RcsUtilityData::getIeFlag() {
	return ieFlag;
}
void RcsUtilityData::setIeFlag(string _ieFlag) {

	ieFlag = _ieFlag;

}

string RcsUtilityData::getKeyword() {
	transform(keyWord.begin(), keyWord.end(), keyWord.begin(), ::tolower);
	return keyWord;
}
void RcsUtilityData::setKeyword(string _keyWord) {
	//convert _keyword to unique string without duplicates

	/*string temp="";
	vector<string> tokens;


	for(int i=0;i<_keyWord.length();++i){
	if(_keyWord[i]==' '){
	tokens.push_back(temp);
	temp="";
	}else{
	temp+=_keyWord[i];
	}
	}
	tokens.push_back(temp);
	string ret = "";
	for(int i=0;i<tokens.size();++i) {

	for(int j=0;j<tokens.size();++j){
	if(i!=j){
	if(tokens[i]==tokens[j]){
	tokens.erase (tokens.begin()+j);
	}
	}
	}
	}
	for(int i=0;i<tokens.size();++i){
	ret+= tokens[i] + " ";
	}
	_keyWord = ret;
	*/
	keyWord = _keyWord;
}

float RcsUtilityData::getScore() {
	return score;
}
void RcsUtilityData::setScore(float _score) {
	score = _score;
}