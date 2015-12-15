#pragma once
#include "afx.h"
#include "PlanePlayer.h"
#include "PlaneEnyne.h"
#include "PlaneBoss.h"
#include "Bomb.h"
#include "Ball.h"
#include "Explosion.h"

#define TOTAL_ITEMS 10
#define ENEMY 0
#define BOSS 1
#define BALL 2
#define BOMB 3
#define EXPLOSION 4

class GameManager :
	public CObject
{
public:
	GameManager();
	void drawGameObjects(CDC *pDC, CRect clientArea);
	PlanePlayer * getPlayer();
	void create();
	void createBomb();
	void createUniqueSkill();
	~GameManager();
protected:
	CObList mGoLists[10];
	int mBossScore;
	int mScore;
	int data;
	PlanePlayer *m_pPlayer;
	PlaneBoss *m_pBoss;


protected:
	bool isCollesion(CRect *rectA, CRect *rectB);
	void createEnemyRand();
	void createBoss();
	void createEnemyBall();
	void createBossBall();
	void checkBallCollesion();
	void checkBombCollesionEnemy();
	void checkBombCollesionBoss();
	void checkPlayerCollesionEnemy();
	void checkPlayerCollesionBoss();

};

