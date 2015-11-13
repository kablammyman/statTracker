#ifndef __PLAYER_H
#define __PLAYER_H

#include <vector>
#include <string>

class CPlayer
{

public:
	int m_offReb;
	int m_defReb;
	int m_asst;
	int m_turnOver;
	int m_steal;
	int m_block;
	int m_foul; //how many times did this player commit a foul

	int m_number; //the number on thier jersey!
	std::string name;
	float m_minPlayed;
	int m_points;
	int m_shotAttempt;
	int m_shotMade;
	int m_freeThrowsAttempted;
	int m_freeThrowsMade;
	int m_and1; //how many tiems ddi this player get fouled

	bool inGame; //is the player on the court, or ridin' the pine?
	
	struct shotPos
	{
		int x,y;
		bool madeShot;
	};
	
	std::vector<shotPos> m_arrShots;
	std::vector<shotPos>::iterator itr;

	CPlayer();
	CPlayer(std::string n, char id);

	~CPlayer();
	void initPlayer(std::string n, char id);
	float calcShootingPercentage();
	void shoot(int x, int y, bool madeShot);

};
#endif