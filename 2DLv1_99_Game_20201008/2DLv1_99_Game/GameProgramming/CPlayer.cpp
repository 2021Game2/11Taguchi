#include "CPlayer.h"
#include "CKey.h"
#include "CBullet.h"
#include "CGoalflag.h"

//extern�F���̃\�[�X�t�@�C���̊O���ϐ��ɃA�N�Z�X����錾
extern CTexture Texture;

CPlayer* CPlayer::spInstance;

int CPlayer::Gameclear = 0;
int CPlayer::Gameover = 0;
int CPlayer::mFx = 1;
int CPlayer::mFy = 0;

#define G	0.5f    //�d��
#define VJ0	18	 //�W�����v��
#define ANICNT 40		//�A�j���[�V�����̐؂�ւ�

CPlayer::CPlayer() 
: FireCount(0) ,mVj(0) ,mJump(0) //0�̓W�����v�\
, mAniCnt(0)
{
	mTag = EPLAYER;
	spInstance = this;
}

void CPlayer::Update() {

	//static���\�b�h�͂ǂ�����ł��Ăׂ�
	if (CKey::Push('A')) {
		x -= 3;
		mFx = -1;
		mFy = 0;
		/*if (x - w < -400) {
			x = -400 + w;
		}*/
	}
	if (CKey::Push('D')) {
		x += 3;
		mFx = 1;
		mFy = 0;
		/*if (x + w > 400) {
			x = 400 - w;
		}*/
	}
	///*if (CKey::Push('W')) {
	//	y += 3;
	//	mFx = 0;
	//	mFy = 1;
	//	if (y + h > 300) {
	//		y = 300 - h;
	//	}
	//}
	//if (CKey::Push('S')) {
	//	y -= 3;
	//	mFx = 0;
	//	mFy = -1;
	//	if (y - h < -300) {
	//		y = -300 + h;
	//	}*/
	//}

	//�W�����v�\��
	if (mJump == 0 && CKey::Once(' ')) {
		//�W�����v�͂𑬓x�ɐݒ�
		mVj = VJ0;
		//�t���O��1���Z
		mJump++;
	}
	//���x�ɏd�͉����x���Z
	mVj -= G;
	//���x���ړ�
	y += mVj;

	if (y < -350) {
		Gameover = 1;
	}
}

void CPlayer::Render() {
	mAniCnt++;
	mAniCnt %= ANICNT;
	if (mAniCnt < ANICNT / 2)
	{
		if (mFx >= 0)
		{
			CRectangle::Render(Texture, 130, 162, 162, 130);
		}
		else
		{
			CRectangle::Render(Texture, 162, 130, 162, 130);
		}
	}
	else
	{
		if (mFx >= 0)
		{
			CRectangle::Render(Texture, 162, 194, 162, 130);
		}
		else
		{
			CRectangle::Render(Texture, 194, 162, 162, 130);
		}
	}
	
}

void CPlayer::Collision(CRectangle *ri, CRectangle *ry) {
	if (ry->mTag == EBLOCK) {
		int mx, my;
		if (CRectangle::Collision(ry, &mx, &my)) {
			//abs(x) x�̐�Βl�����߂�
			//�ړ��ʂ����Ȃ����������ړ�������
			if (abs(mx) < abs(my)) {
				//Rect��x�����ړ�����
				x += mx;
			}
			else {
				//Rect��y�����ړ�����
				y += my;
				//���n
				mVj = 0;	//�W�����v���x0
				if (my > 0)
				{
					//�W�����v�\
					mJump = 0;
				}

			}
		}
	}
	if (ry->mTag == EENEMY) {
		int mx, my;
		if (CRectangle::Collision(ry, &mx, &my)) {
			if (abs(mx) < abs(my)) {
				x += mx;
			}
			else {
				y += my;

			}
		}
	}
	
}
