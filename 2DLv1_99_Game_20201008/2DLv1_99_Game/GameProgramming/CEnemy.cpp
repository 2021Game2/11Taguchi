#include "CEnemy.h"
#include "CTexture.h"
//extern�F���̃\�[�X�t�@�C���̊O���ϐ��ɃA�N�Z�X����錾
extern CTexture Texture;

CEnemy::CEnemy()
: mFx(1.0f), mFy(0.0f)
{
	mTag = EENEMY;
	w = 25;
	h = 25;
	mEnabled = true;
}


void CEnemy::Update() {
	x += mFx;
	y += mFy;
}

/*
�e��Collision���I�[�o�[���C�h����
�Փ˂���ƈړ������𔽑΂ɂ���
*/
bool CEnemy::Collision(const CRectangle &r) {
	
	//�e��Collision���\�b�h���Ăяo��
	if (CRectangle::Collision(r)) {
		switch (r.mTag) {
		case EBLOCK:
			//�Փ˂��Ă���Δ��]
			mFx *= -1;
			mFy *= -1;
			break;
		}
		return true;
	}
	/*return false;*/
}

void CEnemy::Render() {
	if (mEnabled) {
		CRectangle::Render(Texture, 146 - 16, 146 + 16, 178 + 16, 178 - 16);
	}
}

void CEnemy::Collision(CRectangle *i, CRectangle *y) {
	Collision(*y);
}
