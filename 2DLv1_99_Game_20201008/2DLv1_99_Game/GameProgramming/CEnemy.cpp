#include "CEnemy.h"
#include "CTexture.h"
//extern：他のソースファイルの外部変数にアクセスする宣言
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
親のCollisionをオーバーライドする
衝突すると移動方向を反対にする
*/
bool CEnemy::Collision(const CRectangle &r) {
	
	//親のCollisionメソッドを呼び出す
	if (CRectangle::Collision(r)) {
		switch (r.mTag) {
		case EBLOCK:
			//衝突していれば反転
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
