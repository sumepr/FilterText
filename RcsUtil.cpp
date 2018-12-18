#include "stdafx.h"
#include "RcsUtil.h"
#include<iostream>
#include<vector>
#include<StringUtils.h>
#include<Lemmantization.h>
#include <algorithm>
#include<string>
using namespace std;

RcsUtil::RcsUtil()
{
    //ctor
    static const string HS6 =  "HS6";
    static const string HS4 =  "HS4";
    static const string HS2 =  "HS2";

}

RcsUtil::~RcsUtil()
{
    //dtor
}

vector<string> tokenize(string searchText){
    vector<string> searchTextTokenList;
    string temp="";
    for(int i=0;i<searchText.length();++i){

        if(searchText[i]==' '){
            searchTextTokenList.push_back(temp);
            temp="";
        }else{
            temp += searchText[i];
        }

    }
    if(temp.length()){
        searchTextTokenList.push_back(temp);
    }
    return searchTextTokenList;

}
Lemmantization * lemmantization = Lemmantization::getInstance();
//cahnge signature, we no longer matching against keyword


 bool RcsUtil::getFuzzinessEnabled(){
    return isFuzzinessEnabled;
 }


void RcsUtil::setFuzinessEnabled(bool fuzinessEnabled){
    isFuzzinessEnabled = fuzinessEnabled;
}

float RcsUtil::getScore(string searchText, string keyword, RcsUtilityData rcsUtilityData){


    vector<string> searchTextTokenList=tokenize(searchText);
    vector<string> keywordTokenList = tokenize(keyword);


    int counter=0;
    string searchTextToken="";
    string keywordToken="";

    string searchTextTokenTemp="";
    string keywordTokenTemp="";
    int searchTokenListSize = searchTextTokenList.size();

     //banana fresh  (2 /2)
    //banana, grapefrut, including pomelos, fresh or dried, fresh or dried
    for(int i=0;i<searchTextTokenList.size();++i){
        for(int j=0;j<keywordTokenList.size();++j){
            keywordToken = keywordTokenList[j];
            searchTextToken = searchTextTokenList[i];

            searchTextTokenTemp = searchTextToken;
            keywordTokenTemp = keywordToken;

            string keywordSubstr = ""+ keywordToken[0] + keywordToken[1];
            string searchTextsubstr ="" + searchTextToken[0] + searchTextToken[1];

            //cout<<keywordToken<<" "<<searchTextToken<<endl;
            searchTextTokenTemp = lemmantization->getRoot(searchTextTokenTemp);
            if( searchTextTokenTemp == keywordToken && searchTextToken.length()){
                //cout<<"STEMMER "<<searchTextTokenTemp<<" "<<keywordToken<<endl;
                if(counter<=searchTokenListSize){
                    counter++;
                    break;
                }
                //searchTextToken.length()>2 &&  keywordSubstr==searchTextsubstr && StringUtils::getLevenshteinDistance(keywordToken, searchTextToken)<=2
            /*}else if( 5==7 ){//REMOVING LEVENSHTEIN
                //cout<<"LEVENSHTEIN "<<searchTextToken<<" "<<keywordToken;
                if(counter<=searchTokenListSize){
                    counter++;
                }
                */
            }else if(compareRootForms(keywordToken, searchTextToken)){
                //cout<<"ROOTS "<<keywordToken<<" "<<searchTextToken<<endl;
                if(counter<=searchTokenListSize){
                    counter++;
                    break;
                }
             //CHECK FOR A BUG
             //cout<<RcsUtil::isFuzzinessEnabled<<endl;
				
            }else if(RcsUtil::isFuzzinessEnabled && searchTextToken.length()>2 && keywordToken.length()>1 && tolower(searchTextToken[0])== tolower(keywordToken[0] ) ) {
                if (searchTextToken.length() <= 5
								&& StringUtils::getLevenshteinDistance(searchTextToken, keywordToken) <= 1
								&& (counter <= searchTokenListSize)) {
							counter++;
							break;
						} else {
							if (searchTextToken.length() > 5
									&& StringUtils::getLevenshteinDistance(searchTextToken, keywordToken) <= 2
									&& (counter <= searchTokenListSize)) {
								counter++;
								break;
							}
						}
            }


        }
    }
    //cout<<counter<<" "<<searchTokenListSize<<endl;

    float matchedPercentage = (float ) (counter * 100 )/searchTokenListSize ;
    rcsUtilityData.setScore(matchedPercentage);
    return matchedPercentage;

}
string RcsUtil::getHSLevel(string hsCode){
    if(hsCode.length()==1 || hsCode.length()==2){
        return "HS2";
    }else if(hsCode.length()==3 || hsCode.length()==4){
        return "HS4";
    }else{
        return "HS6";
    }
}
bool RcsUtil::compareRootForms(string keywordToken, string searchTextToken){

    if(StringUtils::isNotEmpty(keywordToken) && StringUtils::isNotEmpty(searchTextToken) && searchTextToken.length()>2 ){
        string temp = ""+searchTextToken[0] + searchTextToken[1];
        string temp2 = ""+keywordToken[0] + keywordToken[1];

        if(temp==temp2){

            keywordToken = lemmantization->getRoot(keywordToken);
            searchTextToken= lemmantization->getRoot(searchTextToken);

        }

        if(keywordToken==searchTextToken){
            return true;
        }

    }
    return false;
}
RcsUtilityRequest RcsUtil::updateSearchTextToSingular(RcsUtilityRequest rcsUtilityRequest){


    string ret="";
    string searchText = rcsUtilityRequest.getSearchText();
    vector<string> tokens = tokenize(searchText);
    for(int i=0;i<tokens.size();++i){
        tokens[i] = lemmantization->getRoot(tokens[i]);
        //extra space
        if(i==tokens.size()-1){
            ret+= tokens[i];
        }else{
            ret+= tokens[i]+" ";
        }

    }
    rcsUtilityRequest.setSearchText(ret);
    return rcsUtilityRequest;
}

