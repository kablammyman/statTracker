#include "stdafx.h"

#include <fstream>
#include <string>
#include <iomanip>
#include "statTracker.h"

using namespace std;
void CStatTracker::addNameToHomeTeam(std::string name, int id)
{
	CPlayer temp(name,id);
	homeTeam.push_back(temp);

	if(curPlayer == NULL)
		curPlayer = &homeTeam.back();
}

void CStatTracker::addNameToAwayTeam(std::string name, int id)
{
	CPlayer temp(name,id);
	awayTeam.push_back(temp);
	
}

bool CStatTracker::loadHomeTeamFromFile(std::string fileName)//add some serious error checking!
{
	std::fstream filestr;
	filestr.open (fileName.c_str(), std::fstream::in);

	if(!filestr.is_open())
		return false;

	std::string line;
	char tempString[256];

	filestr.getline (tempString,256); 
	homeTeamName = tempString;//first line is team name
	
	int counter = 0; //used to put first 5 names "in the game", the rest will be subs

	while(!filestr.eof())
	{
		filestr.getline (tempString,256);
		line = tempString;
		
		if(line.size() > 3)//dont process empty lines
		{
			char delim = line.find(",");

			if(line[delim+1] == ' ')
				delim++;
			int x = atoi ( line.substr(delim, line.size()).c_str() ); //get the char * from the delimeter to teh end of the string, and atoi it
			addNameToHomeTeam(line.substr(0, delim-1), x ); //delim - 1 makes sure the comma isnt in the name anymore

			if(counter < 5) 
			{
				counter++;
				homeTeam.back().inGame = true;
			}
		}

	}

	filestr.close();
	return true;

}
bool CStatTracker::saveHomeTeamToFile(std::string fileName)
{
	std::fstream filestr;
	filestr.open (fileName.c_str(), std::fstream::out);

	if(!filestr.is_open())
		return false;
	
	filestr << homeTeamName << endl;

	for(teamItr = homeTeam.begin(); teamItr != homeTeam.end();++teamItr) //is equivalent to std::advance fn()
	{
		CPlayer temp = *teamItr;
		filestr<< temp.name <<", " << temp.m_number <<endl;
	}

	filestr.close();
	return true;

}

bool CStatTracker::saveHomeTeamStats(std::string fileName)//add some serious error checking!
{
	std::fstream filestr;
	filestr.open (fileName.c_str(), std::fstream::out);

	if(!filestr.is_open())
		return false;
	int spacing = 6;
	
	filestr << homeTeamName << endl<<endl;

		filestr<< setw(spacing*5)<<left<< "name" <<"|";
		filestr<< setw(spacing)<<left<< "fg%"<<"|";
		filestr<< setw(spacing)<<left<< "offReb"<<"|";
		filestr<< setw(spacing)<<left<< "asst"<<"|"; 
		filestr<< setw(spacing)<<left<< "T.O."<<"|";
		filestr<< setw(spacing)<<left<< "FTA"<<"|";
		filestr<< setw(spacing)<<left<< "FT"<<"|";
		filestr<< setw(spacing)<<left<< "defReb" <<"|";
		filestr<< setw(spacing)<<left<< "steal"<<"|";
		filestr<< setw(spacing)<<left<< "foul"<< "|";
		filestr<< setw(spacing)<<left<< "and1" <<endl;

		filestr<<setfill('-')<<setw(100)<<"-"<<endl;

		filestr<<setfill(' '); //dont want lines after stats
	for(teamItr = homeTeam.begin(); teamItr != homeTeam.end();++teamItr) //is equivalent to std::advance fn()
	{
		CPlayer temp = *teamItr;
		filestr<< setw(spacing*5)<< temp.name <<"|";
		filestr<< setw(spacing)<<left<< setprecision(3)<<temp.calcShootingPercentage()<<"|";
		filestr<< setw(spacing)<<left<< temp.m_offReb<<"|";
		filestr<< setw(spacing)<<left<< temp.m_asst<<"|"; 
		filestr<< setw(spacing)<<left<< temp.m_turnOver<<"|";
		filestr<< setw(spacing)<<left<< temp.m_freeThrowsAttempted<<"|";
		filestr<< setw(spacing)<<left<< temp.m_freeThrowsMade<<"|";
		filestr<< setw(spacing)<<left<< temp.m_defReb <<"|";
		filestr<< setw(spacing)<<left<< temp.m_steal<<"|";
		filestr<< setw(spacing)<<left<< temp.m_foul<< "|";
		filestr<< setw(spacing)<<left<< temp.m_and1 <<endl;
	}

	filestr.close();
	return true;

}


CPlayer *CStatTracker::getHomeTeamPlayer(int id)
{
	if(homeTeam.empty())
		return NULL;

	for(teamItr = homeTeam.begin(); teamItr != homeTeam.end();++teamItr) //is equivalent to std::advance fn()
	{
		CPlayer temp = *teamItr;
		if(temp.m_number == id)
			return &*teamItr; //*teamItr returns normal, &* returns pointer to elemen t in list
	}
	
	return NULL;//we dopnt find the name, return null
}
CPlayer *CStatTracker::getHomeTeamPlayer(std::string name )
{

	if(homeTeam.empty())
		return NULL;

	for(teamItr = homeTeam.begin(); teamItr != homeTeam.end();++teamItr) //is equivalent to std::advance fn()
	{
		CPlayer temp = *teamItr;
		if(temp.name == name)
			return &*teamItr; //*teamItr returns normal, &* returns pointer to elemen t in list
	}
	
	return NULL;//we dopnt find the name, return null
}
