#pragma once
#include "EasyGraphics.h"
#include "Button.h"
#include "CardDeck.h"

class PlayArea : public EasyGraphics
{
public:
	PlayArea();
	~PlayArea();
	virtual void onDraw();
	virtual void onLButtonDown(UINT nFlags, int x, int y);
private:
	void startGameSequence();
	void midGameSequence();
	void hitGameSequence();
	void endGameSequence();
	void standGameSequence();
	void drawCards(vector<int>* entitiesCards);
	bool hasBegun, isPlay, hasPlayerWon, gameOver;
	Button* startButton = new Button("Start", 100, 50, 550, 800);
	Button* hitButton = new Button("hit", 100, 50, 700, 800);
	Button* standButton = new Button("stand", 100, 50, 400, 800);
	CardDeck& deck = CardDeck::Get();
};

