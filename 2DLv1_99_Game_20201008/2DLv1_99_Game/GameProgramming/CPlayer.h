#ifndef CPLAYER_H
#define CPLAYER_H

#include "CRectangle.h"

class CPlayer : public CRectangle {
public:
	static int mFx, mFy;
	int FireCount;
	int mJump; //�W�����v�t���O
	float  mVj;  //�W�����v�p���x
	int mAniCnt;	//�A�j���[�V�����p�J�E���^
	static int Gameover;
	static int Gameclear;
	static CPlayer* spInstance;
	CPlayer();
	void Update();
	void Render();
	void Collision(CRectangle *i, CRectangle *y);
};

#endif
