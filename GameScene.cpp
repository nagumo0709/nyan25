//===================================================================================
//!	@file	:	GameScene.cpp
//!	@brief	:	GameSceneクラスのメンバ化数宣言
//!	@author	:	宮澤 渉太
//!	@date	:	2014/11/07
//!	@par	:	example
//!	@note	:	example
//===================================================================================
#include "GameScene.h"

USING_NS_CC;


//===================================================================================
//		Constants Definitions
//===================================================================================


//===================================================================================
//		public method
//===================================================================================

//-----------------------------------------------------------------------------------
//!	@brief		: シーン作成関数
//-----------------------------------------------------------------------------------
Scene* GameScene::scene()
{
	Scene* scene = Scene::create();
	GameScene* layer = GameScene::create();
	scene->addChild(layer);

	return scene;
}

//-----------------------------------------------------------------------------------
//!	@brief		: 初期化関数
//-----------------------------------------------------------------------------------
//初期化処理はここ
bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	////////////////////////
	//ここに記述していく
	
	//<! 変数を初期化する
	srand((unsigned)time(NULL));
	_nextNumber = 1;

	initListener();		//<! タッチイベントリスナ初期化
	setBackGround();	//<! 背景描画関数
	MakeCards();		//<! カード配置関数

	return true;
}

//-----------------------------------------------------------------------------------
//!	@brief		: タッチした瞬間に呼ばれる関数
//!	@param[in]	: タッチ (Touch)
//!	@param[in]	: イベント (Event)
//-----------------------------------------------------------------------------------
bool GameScene::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	return true;
}

//-----------------------------------------------------------------------------------
//!	@brief		: ドラッグした時に呼ばれる関数
//!	@param[in]	: タッチ (Touch)
//!	@param[in]	: イベント (Event)
//-----------------------------------------------------------------------------------
void GameScene::onTouchMoved(Touch* pTouch, Event* pEvent)
{
}

//-----------------------------------------------------------------------------------
//!	@brief		: タッチ終了後に呼ばれる関数
//!	@param[in]	: タッチ (Touch)
//!	@param[in]	: イベント (Event)
//-----------------------------------------------------------------------------------
void GameScene::onTouchEnded(Touch* pTouch, Event* pEvent)
{
	//<! タップポイント取得
	Director* pDirector = Director::sharedDirector();
	//<! 座標基準点を現在のデバイスの向きをとる
	Point touchPoint = pDirector->convertToGL(pTouch->getLocationInView());

	log("x:%f, y:%f", touchPoint.x, touchPoint.y);
	
	//<! タグを指定してカードのインスタンスを取得
	Node* pCard = this->getChildByTag(_nextNumber);
	if (!pCard)
	{
		return;
	}

	Rect cardRect = pCard->boundingBox();
	//<! 引数の位置にカードがあるか判定 trueが返ってくればタップされている
	if (cardRect.containsPoint(touchPoint))
	{
		//<! 裏カードを作成する
		Sprite* pNewCard = Sprite::create("image/card_backside.png");
		//<! 既に配置されているカード座標に新しいカードを配置
		pNewCard->setPosition(pCard->getPosition());
		this->addChild(pNewCard);

		//<! 表カードを削除する
		pCard->removeFromParentAndCleanup(true);
		if (_nextNumber >= 25)
		{
			return;
		}

		_nextNumber++;
	}
}

//===================================================================================
//		private method
//===================================================================================
#pragma region private_methods

//-----------------------------------------------------------------------------------
//!	@brief		: イベントリスナの初期化関数
//-----------------------------------------------------------------------------------
void GameScene::initListener()
{
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(_swallowsTouches);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

//-----------------------------------------------------------------------------------
//!	@brief		: 背景描画関数
//-----------------------------------------------------------------------------------
void GameScene::setBackGround()
{
	//背景を生成
	Sprite* pBG = Sprite::create("image/background.png");	//画像の読み込み
	pBG->setPosition(ccp(WINSIZE.width / 2, WINSIZE.height / 2));	//座標の設定
	this->addChild(pBG);
}

//-----------------------------------------------------------------------------------
//!	@brief		: カード配置関数
//! @param[in]	: ウィンドウサイズ ( Size )
//-----------------------------------------------------------------------------------
void GameScene::MakeCards()
{
	//<! 数値配列を初期化する
	Array* numbers = Array::create();
	for (int i = 1; i <= 25; i++)
	{
		//<! numbersをint型扱いにする
		numbers->addObject(Integer::create(i));
	}

	//<! 5 * 5 配置にする
	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			//<! ランダムで1つの値を取得する
			int index = rand() % numbers->count();
			int number = ((Integer*)numbers->objectAtIndex(index))->getValue();

			//<! カードを生成する(白紙のカード)
			Sprite* pCard = Sprite::create("image/card_frontside.png");
			//<! 白紙のカードの上に数字カードを設定する
			Size cardSize = pCard->getContentSize();
			pCard->setPosition(ccp(WINSIZE.width / 2 + (x-2) * cardSize.width, 
				WINSIZE.height / 2 + (y-2) * cardSize.height));
			pCard->setTag(number);
			this->addChild(pCard);

			//<! カード番号を表示する
			String* filename = String::createWithFormat(
				"image/%d.png", number);
			//<! 番号に一致した画像を呼び込む
			Sprite* pNumber = Sprite::create(filename->getCString());
			pNumber->setPosition(ccp(cardSize.width / 2, cardSize.height / 2));
			pCard->addChild(pNumber);

			//<! 数値配列から値を削除する(使った数字を消していく)
			numbers->removeObjectAtIndex(index);
		}
	}
}

#pragma endregion	// private_methods
//===================================================================================
//		End Of File
//===================================================================================
