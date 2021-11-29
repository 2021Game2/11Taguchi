#include "CSceneGame.h"
#include "CTexture.h"
#include "CMap.h"
#include "CKey.h"
#include "CRectangle.h"
#include "CBullet.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CText.h"
#include "CSlidingfloor.h"
#include "CGoalflag.h"

int Time = 60 * 45;

void CSceneGame::Init() {
	//シーンの設定
	mScene = EGAME;

	Texture.Load("Image.tga");
	//文字画像の読み込み
	CText::mFont.Load("font.tga");

	//クラスのメンバ変数への代入
	CPlayer *Player = new CPlayer();
	Player->x = 150;
	Player->y = 150;
	Player->w = 25;
	Player->h = 25;
	Player->mEnabled = true;

	int map[6][50] =
	{
		{ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
		{ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
		{ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
		{ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
		{ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,4 ,1, 1, 1, 1},
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 3, 3, 3, 3, 3, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	};

	for (int j = 0; j < 6; j++) {
		for (int i = 0; i < 50; i++) {
			//mapの要素が1の時、四角形配置
			if (map[j][i] == 1) {
				CMap* Map = new CMap();
				//四角形に値を設定
				Map->mEnabled = true;
				Map->x = i * 100 - 350;
				Map->y = j * -100 + 250;
				Map->w = 50;
				Map->h = 50;
			}
		
			else if (map[j][i] == 2) {
				CEnemy* Enemy = new CEnemy();
				Enemy->x = i * 100 - 350;
				Enemy->y = j * -100 + 250;
				//右へ移動
				Enemy->mFx = 1;
				
			}
			else if (map[j][i] == 3) {
				CSlidingfloor* Slidingfloor = new CSlidingfloor();
				Slidingfloor->mEnabled = true;
				Slidingfloor->x = i * 100 - 350;
				Slidingfloor->y = j * -100 + 250;
				Slidingfloor->w = 50;
				Slidingfloor->h = 50;

			}
			else if (map[j][i] == 4) {
				CGoalflag* Goalflag = new CGoalflag();
				Goalflag->mEnabled = true;
				Goalflag->x = i * 100 - 350;
				Goalflag->y = j * -100 + 250;
				Goalflag->w = 25;
				Goalflag->h = 25;
			   
			}
		}
	}
}

void CSceneGame::Update() {
	/*
	配列の要素分繰り返す
	配列名.size()
	配列の要素数を取得する
	*/
	for (size_t i = 0; i < VectorRect.size(); i++) {
		/*
		配列の参照
		配列名[添え字]
		通常の配列同様に添え字で要素にアクセスできる
		*/
		//更新処理
		VectorRect[i]->Update();
	}
	for (size_t i = 0; i < VectorRect.size() ; i++) {
		//衝突処理
		for (size_t j = i + 1; j < VectorRect.size(); j++) {
			VectorRect[i]->Collision(VectorRect[i], VectorRect[j]);
			VectorRect[j]->Collision(VectorRect[j], VectorRect[i]);
		}
	}

	//リストから削除する
	//イテレータの生成
	std::vector<CRectangle*>::iterator itr;
	//イテレータを先頭
	itr = VectorRect.begin();
	//最後まで繰り返し
	while (itr != VectorRect.end()) {
		if ((*itr)->mEnabled) {
			//次へ
			itr++;
		}
		else {
			//falseのインスタンスを削除
			delete *itr;
			//リストからも削除
			itr = VectorRect.erase(itr);
		}
	}

	//描画範囲変数の作成　範囲下：-300　範囲上：300　固定
	double mLeft, mRight, mBottom = -300.0, mTop = 300.0;
	//画面範囲左の設定
	mLeft = CPlayer::spInstance->x - 400.0;
	//画面範囲右の設定
	mRight = mLeft + 800.0f;
	//画面投影範囲の変更
	//行列をプロジェクションモードへ変更
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	//行列を初期化
	//2Dの画面を設定

	gluOrtho2D(mLeft, mRight, mBottom, mTop);
	//行列をモデルビューモードへ変更
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	//行列を初期化
	for (size_t i = 0; i < VectorRect.size(); i++) {
		//描画処理
		VectorRect[i]->Render();
	}

		for (int i = 0; i < VectorRect.size(); i++) {
			//	描画処理
			VectorRect[i]->Render();
		}

		//画面投影範囲の変更
		//行列をプロジェクションモードに変更
			glMatrixMode(GL_PROJECTION);
		glLoadIdentity();   ////行列を初期化
		//2Dの画面を設定
		gluOrtho2D(-600, 600, -300, 300);
		//行列をモデルビューモードへ変更
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();    ////行列を初期化

		

		char buf[10];
		sprintf(buf, "%d", Time / 60);
		CText::DrawString(buf, 470, 250, 16, 16);

		CText::DrawString("Time", 330, 250, 16, 16);
		if (Time > 0) {
			Time--;
		}

		if (Time == 0) {
			CPlayer::Gameover = +1;
		}
		
		if (CPlayer::Gameover == 1) {
			CText::DrawString("GAME OVER", -250, 0, 32, 32);
			CText::DrawString("Push ENTER Key", -250, -80, 20, 20);
			
			if (CKey::Once(VK_RETURN)) {
				//次のシーンはゲーム
			     mScene=ETITLE;
				 CPlayer::Gameover = 0;
				 Time = 60 * 45;
				 
			}
		}
		
		
	
}


//次のシーンの取得
CScene::EScene CSceneGame::GetNextScene() {
	return mScene;
}
//デストラクタ
CSceneGame::~CSceneGame() {
	//全てのインスタンスを削除します
	for (size_t i = 0; i < VectorRect.size(); i++) {
		//インスタンスの削除
		delete VectorRect[i];
	}
	//可変長配列のクリア
	VectorRect.clear();
}