#include "stdafx.h"
#include "playerClass.h"

CPlayer::CPlayer()
{
	 m_offReb = 0;
	 m_defReb = 0;
	 m_asst = 0;
	 m_turnOver = 0;
	 m_steal = 0;
	 m_block = 0;
	 m_foul = 0;

	 m_number = 0;

	 m_minPlayed = 0.0;
	 m_points = 0;
	 m_shotAttempt = 0;
	 m_shotMade = 0;
	 m_freeThrowsAttempted = 0;
	 m_freeThrowsMade = 0;
	 m_and1 = 0;

	 inGame = false;
}
CPlayer::CPlayer(std::string n, char id)
{
	 m_offReb = 0;
	 m_defReb = 0;
	 m_asst = 0;
	 m_turnOver = 0;
	 m_steal = 0;
	 m_block = 0;
	 m_foul = 0;

	 m_number = 0;

	 m_minPlayed = 0.0;
	 m_points = 0;
	 m_shotAttempt = 0;
	 m_shotMade = 0;
	 inGame = false;
	 m_freeThrowsAttempted = 0;
	 m_freeThrowsMade = 0;
	 m_and1 = 0;

	 initPlayer(n,id);
}

CPlayer::~CPlayer()
{}

void CPlayer::initPlayer(std::string n, char id)
{
	name = n;
	m_number = id;
}

float CPlayer::calcShootingPercentage()
{
	if(m_shotAttempt == 0)
		return 0;

	float temp;
	// (m_shotMade / m_shotAttempt) * 100; /why doesnt this work?

	temp = m_shotMade;
	temp /= m_shotAttempt;
	temp *= 100;
	return temp;
}

void CPlayer::shoot(int x, int y, bool madeShot)
{
	m_shotAttempt++;
	
	shotPos pos;
	pos.x = x;
	pos.y = y;
	pos.madeShot = madeShot;

	if(madeShot)
		m_shotMade++;

	m_arrShots.push_back(pos);
}