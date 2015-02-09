//===================================================================================
//!	@file	:	GameScene.h
//!	@author	:	宮澤 渉太
//!	@date	:	2014/11/07
//===================================================================================

//インクルードガード
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

//「using namespace cocos2d」の省略マクロ
USING_NS_CC;

//画面サイズを取得
#define WINSIZE Director::getInstance()->getWinSize()


//===================================================================================
//!	@class	:	GameScene
//!	@brief	:	ゲームシーン
//!	@par	:	example
//!	@note	:	example
//===================================================================================
//Layerクラスはシーンとして使われる事がある
//タッチ入力を受け付ける場合も必要
//このクラスがプログラムのベースとなる
class GameScene : public Layer
{

private:
	int _nextNumber;

	void initListener();
	void setBackGround();	//<! 背景描画
	void MakeCards();		//<! カード配置

public:
	static const int TAG_CHARACTER = 1;

	virtual bool init();	//初期化関数　createされた後に勝手に呼ばれる
	static Scene* scene();	//シーンの作成
	CREATE_FUNC(GameScene);	//お決まりのCreate関数を作成する用のマクロ

	//<! タップ関数
	virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
	virtual void onTouchMoved(Touch* pTouch, Event* pEvent);
	virtual void onTouchEnded(Touch* pTouch, Event* pEvent);
};

#endif	//__GAME_SCENE_H__
//===================================================================================
//		End Of File
//===================================================================================
