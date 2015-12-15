#include "stdafx.h"
#include "GameManager.h"
#include "PlaneEnyne.h"


GameManager::GameManager():mScore(0),mBossScore(0),data(0)
{
	m_pPlayer = new PlanePlayer(900, 500);
	srand((unsigned)time(NULL));
}

void GameManager::drawGameObjects(CDC * pDC, CRect clientArea)
{
	if (m_pPlayer)
	{
		m_pPlayer->Draw(pDC, clientArea);
	}
	for (int i = 0; i < TOTAL_ITEMS; i++)
	{
		POSITION pos1, pos2;
		for (pos1 = mGoLists[i].GetHeadPosition(); (pos2 = pos1) != NULL; )
		{
			GameObject* pObj = (GameObject*)mGoLists[i].GetNext(pos1);
			if (!pObj->Draw(pDC, clientArea))
			{
				mGoLists[i].RemoveAt(pos2);
				delete pObj;
			}
		}
	}
}

PlanePlayer * GameManager::getPlayer()
{
	return m_pPlayer;
}

void GameManager::create()
{
	if (m_pPlayer == nullptr)
	{
		return;
	}
	 createEnemyRand();
	 createBoss();
	 createEnemyBall();
	 createBossBall();
	 checkBallCollesion();
	 checkBombCollesionEnemy();
	 checkBombCollesionBoss();
	 checkPlayerCollesionEnemy();
	 checkPlayerCollesionBoss();
}


GameManager::~GameManager()
{
}

bool GameManager::isCollesion(CRect *rectA, CRect *rectB)
{
	CRect temRect;

	return temRect.IntersectRect(rectA, rectB);
}

void GameManager::createEnemyRand()
{
	static int nCreator = rand() % 15 + 10;
	if (nCreator <= 0)
	{
		nCreator = rand() % 15 + 10;
	    mGoLists[ENEMY].AddTail(new PlaneEnyne());
	}
	nCreator--;
}

void GameManager::createBoss()
{
	if (mBossScore >= PlaneBoss::level)
	{
		mBossScore -= PlaneBoss::level;

		mGoLists[BOSS].AddTail(new PlaneBoss);
	}
}

void GameManager::createBomb()
{
	if (m_pPlayer != NULL && m_pPlayer->isFirable())
	{
		CPoint pt = m_pPlayer->getPoint();
		mGoLists[BOMB].AddTail(new Bomb(pt.x + 0, pt.y + 10, -1, 0));
		mGoLists[BOMB].AddTail(new Bomb(pt.x + 20, pt.y + 10, -1, 0));
		mGoLists[BOMB].AddTail(new Bomb(pt.x + 40, pt.y + 10, -1, 0));
	}
}

void GameManager::createUniqueSkill()
{
	if (m_pPlayer != NULL && m_pPlayer->isFirable())
	{
		CPoint pt = m_pPlayer->getPoint();
		mGoLists[BOMB].AddTail(new Bomb(pt.x + 50, pt.y + 10, -1, 1));
		mGoLists[BOMB].AddTail(new Bomb(pt.x + 30, pt.y + 10, -1, 0));
		mGoLists[BOMB].AddTail(new Bomb(pt.x + 10, pt.y + 10, -1, -1));
		mGoLists[BOMB].AddTail(new Bomb(pt.x + 50, pt.y + 10, 1, 1));
		mGoLists[BOMB].AddTail(new Bomb(pt.x + 30, pt.y + 10, 1, 0));
		mGoLists[BOMB].AddTail(new Bomb(pt.x + 10, pt.y + 10, 1, -1));
	}
}

void GameManager::createEnemyBall()
{
	CPoint PlanePt = m_pPlayer->getPoint();
	for (POSITION ePos = mGoLists[ENEMY].GetHeadPosition(); ePos != NULL;)
	{
		PlaneEnyne* pEnemy = (PlaneEnyne*)mGoLists[ENEMY].GetNext(ePos);
		if (!pEnemy->isFirable())
			continue;
		CPoint  ePt = pEnemy->getPoint();
		if(ePt.x > PlanePt.x && ePt.x < PlanePt.x + m_pPlayer->getRect().Width())
		{ 
		mGoLists[BALL].AddTail(new Ball(ePt.x + 30, ePt.y + 30, 1, 0));
		}
	}
}

void GameManager::createBossBall()
{
	for (POSITION sPos = mGoLists[BOSS].GetHeadPosition(); sPos != NULL;)
	{
		PlaneBoss* pBoss = (PlaneBoss*)mGoLists[BOSS].GetNext(sPos);
		if (!pBoss->isFirable())
			continue;
		CPoint  ePt = pBoss->getPoint();
		CPoint playerPos = m_pPlayer->getPoint();
		if (pBoss != NULL && pBoss->isFirable())
		{
			mGoLists[BALL].AddTail(new Ball(ePt.x + 30, ePt.y + 10, 1, -1));
			mGoLists[BALL].AddTail(new Ball(ePt.x + 70, ePt.y + 10, 1, 1));
			mGoLists[BALL].AddTail(new Ball(ePt.x + 50, ePt.y + 10, 1, 0));
			mGoLists[BALL].AddTail(new Ball(ePt.x + 30, ePt.y + 10, -1, -1));
			mGoLists[BALL].AddTail(new Ball(ePt.x + 70, ePt.y + 10, -1, 1));
			mGoLists[BALL].AddTail(new Ball(ePt.x + 50, ePt.y + 10, -1, 0));

		}
		BOOL isInFront = FALSE;

		//敌机在战机前面
		if (pBoss->getMotion() == 1 && ePt.y<playerPos.y)
			isInFront = TRUE;
		//敌机在战机后面
		if (pBoss->getMotion() == -1 && ePt.y>playerPos.y)
			isInFront = TRUE;

		if (isInFront && ePt.x >= playerPos.x && ePt.x < playerPos.x + (m_pPlayer->getRect()).Width())
		{
			mGoLists[BALL].AddTail(new Ball(ePt.x + 40, ePt.y + 20, pBoss->getMotion(), 0));
		}
	}
}

void GameManager::checkBallCollesion()
{
	POSITION bPos1 = NULL, bPos2 = NULL;

	if (m_pPlayer == nullptr)
	{
		return;
	}

	CRect mRect = m_pPlayer->getRect();
	CPoint PlanePt = m_pPlayer->getPoint();
	for (bPos1 = mGoLists[BALL].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		Ball* pBall = (Ball*)mGoLists[BALL].GetNext(bPos1);
		CRect bRect = pBall->getRect();
		CRect tmpRect;
		if (isCollesion(&bRect, &mRect))
		{
			m_pPlayer->mBlood -= 10;
				mGoLists[BALL].RemoveAt(bPos2);
			delete pBall;
			mGoLists[EXPLOSION].AddTail(
				new Explosion(mRect.left, mRect.top)
				);
			int playerBlood = m_pPlayer->mBlood;
			delete m_pPlayer;
			m_pPlayer = NULL;
			if (playerBlood >= 0)
			{
			m_pPlayer = new PlanePlayer(PlanePt.x, PlanePt.y);
			m_pPlayer->mBlood = playerBlood;
			}
		}
	}
}

void GameManager::checkBombCollesionEnemy()
{  
	POSITION mPos1 = NULL, mPos2 = NULL;
	for (mPos1 = mGoLists[BOMB].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
	{
		Bomb* pBomb = (Bomb*)mGoLists[BOMB].GetNext(mPos1);
		CRect bRect = pBomb->getRect();

		POSITION ePos1 = NULL, ePos2 = NULL;
		for (ePos1 = mGoLists[ENEMY].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
		{
			PlaneEnyne* pEnemy = (PlaneEnyne*)mGoLists[ENEMY].GetNext(ePos1);
			CRect mRect = pEnemy->getRect();
			CRect tmpRect;
			if (isCollesion(&bRect, &mRect))
			{
				//添加爆炸效果
				mGoLists[EXPLOSION].AddTail(
					new Explosion(mRect.left, mRect.top)
					);
				//删除导弹
				mGoLists[BOMB].RemoveAt(mPos2);
				delete pBomb;
				mScore += 10;
				mBossScore += 10;
				data += 1;
				//删除敌机
				mGoLists[ENEMY].RemoveAt(ePos2);
				delete pEnemy;
				break;
			}
		}
	}
}

void GameManager::checkBombCollesionBoss()
{
	POSITION mPos1 = NULL, mPos2 = NULL;
	for (mPos1 = mGoLists[BOMB].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
	{
		Bomb* pBomb = (Bomb*)mGoLists[BOMB].GetNext(mPos1);
		CRect bRect = pBomb->getRect();

		POSITION ePos1 = NULL, ePos2 = NULL;
		for (ePos1 = mGoLists[BOSS].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
		{
			PlaneBoss* pBoss = (PlaneBoss*)mGoLists[BOSS].GetNext(ePos1);
			CRect mRect = pBoss->getRect();
			CRect tmpRect;
			if (isCollesion(&bRect, &mRect))
			{
				//添加爆炸效果
				mGoLists[EXPLOSION].AddTail(new Explosion(bRect.left, bRect.bottom - 100));
				//mGoLists[EXPLOSION].AddTail(new Explosion(mRect.right,mRect.bottom));
				//删除导弹
				mGoLists[BOMB].RemoveAt(mPos2);
				delete pBomb;
				mScore += 10;
				mBossScore += 10;
				data += 1;
				pBoss->mBlood--;
				//删除敌机
				if (pBoss->mBlood == 0)
				{
					mGoLists[BOSS].RemoveAt(ePos2);
					delete pBoss;
					//boss.blood = 30;
					mBossScore = 0;
					break;
				}

			}
		}
	}
}

void GameManager::checkPlayerCollesionEnemy()
{
	POSITION bPos1 = NULL, bPos2 = NULL;
	if (!m_pPlayer)
	{
		return;
	}
	CPoint  PlanePt = m_pPlayer->getPoint();
	for (bPos1 = mGoLists[ENEMY].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		PlaneEnyne* pEnemy = (PlaneEnyne*)mGoLists[ENEMY].GetNext(bPos1);
		CRect bRect = pEnemy->getRect();
		CRect mRect = m_pPlayer->getRect();
		CRect tmpRect;
		if (isCollesion(&bRect, &mRect))
		{
			mScore += 10;
			mBossScore += 10;
			data += 1;
			m_pPlayer->mBlood -= 10;
			mGoLists[EXPLOSION].AddTail(
				new Explosion(mRect.left, mRect.top));
			mGoLists[ENEMY].RemoveAt(bPos2);
			delete pEnemy;
			int playerBlood = m_pPlayer->mBlood;
			delete m_pPlayer;
			m_pPlayer = NULL;
			if (playerBlood >= 0)
			{
				m_pPlayer = new PlanePlayer(PlanePt.x, PlanePt.y);
				m_pPlayer->mBlood = playerBlood;
			}
		}
	}
}

void GameManager::checkPlayerCollesionBoss()
{
	if (!m_pPlayer)
	{
		return;
	}
		CRect bRect = m_pPlayer->getRect();
		POSITION ePos1 = NULL, ePos2 = NULL;
		for (ePos1 = mGoLists[BOSS].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
		{
			PlaneBoss* pBoss = (PlaneBoss*)mGoLists[BOSS].GetNext(ePos1);
			CRect mRect = pBoss->getRect();
			CRect tmpRect;
			if (isCollesion(&bRect, &mRect))
			{
				//添加爆炸效果
				mGoLists[EXPLOSION].AddTail(new Explosion(bRect.left, bRect.bottom - 100));
				//删除导弹
				mScore += 10;
				mBossScore += 10;
				data += 1;
				pBoss->mBlood--;
				//删除战机
				delete m_pPlayer;
				m_pPlayer = NULL;
			}
		}
	
}
