#ifndef CPLAYER_H
#define CPLAYER_H

#include "CRectangle.h"

class CPlayer : public CRectangle {
public:
	static int mFx, mFy;
	int FireCount;
	int mJump; //ジャンプフラグ
	float  mVj;  //ジャンプ用速度
	int mAniCnt;	//アニメーション用カウンタ
	static int Gameover;
	static int Gameclear;
	static CPlayer* spInstance;
	CPlayer();
	void Update();
	void Render();
	void Collision(CRectangle *i, CRectangle *y);
};

#endif
