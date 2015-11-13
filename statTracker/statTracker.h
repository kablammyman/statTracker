#ifndef __STATTRACKER_H
#define __STATTRACKER_H

#include "playerClass.h"

#include <list>



class CStatTracker
{
public:
	std::list<CPlayer> homeTeam;
	std::list<CPlayer> awayTeam; 

	std::list<CPlayer>::iterator teamItr;

	std::string homeTeamName;
	std::string awayTeamName;
	
	CPlayer *curPlayer;

	CStatTracker()
	{
		homeTeam.clear();
		awayTeam.clear();
		curPlayer = NULL;
		homeTeamName = "No Home Team loaded or created";
		awayTeamName = "No Away Team loaded or created";
	}
	~CStatTracker(){}

	void addNameToHomeTeam(std::string name, int id);
	void addNameToAwayTeam(std::string name, int id);

	bool loadHomeTeamFromFile(std::string fileName);
	bool saveHomeTeamToFile(std::string fileName);
	
	bool saveHomeTeamStats(std::string fileName);
	bool saveAwayTeamStats(std::string fileName);

	CPlayer *getHomeTeamPlayer(int id);
	CPlayer *CStatTracker::getHomeTeamPlayer(std::string name );


};

#endif