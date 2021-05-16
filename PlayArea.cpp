#include "PlayArea.h"


PlayArea::PlayArea() : hasBegun(false), isPlay(false), hasPlayerWon(false), gameOver(false)
{
	setImmediateDrawMode(false);	
}
PlayArea::~PlayArea() {
	delete startButton;
	delete hitButton;
	delete standButton;
}

void PlayArea::onDraw()
{
	if (!gameOver) {
		clearScreen(DARK_GREEN);
		setPenColour(BLACK, 1);
		setTextColour(BLACK);
		setBackColour(WHITE);
		startButton->draw(this);

		drawBitmap(L"Assets/pack.bmp", 300, 100, 44 * 3, CARD_HEIGHT * 3, 0x00FF00FF);

		if (isPlay) {//after the start button has been pressed isplay=true
			midGameSequence();
		}
		else if (hasBegun)
		{
			(&deck)->playCard(2);//plays cards for casino and player 2 times
			midGameSequence();
		}
	}
	EasyGraphics::onDraw();
}
void PlayArea::midGameSequence()
{
	clearScreen(DARK_GREEN);
	drawBitmap(L"Assets/pack.bmp", 300, 100, 44 * 3, 47 * 3, 0x00FF00FF);
	(&deck)->drawCards(this);//draw cards for casino and player
	hitButton->draw(this);//draw buttons
	standButton->draw(this);
}

void PlayArea::hitGameSequence() 
{
	(&deck)->playCard(true);//true=player, false=casino

	onDraw();
	int playerTotal = (&deck)->cardsTotal((&deck)->playersCards);
	int casinoTotal = (&deck)->cardsTotal((&deck)->casinosCards);
	if (playerTotal == 21) {
		//check casino
		if (casinoTotal == 21){
			//casino wins
			hasPlayerWon = false;
		}
		else if(casinoTotal < 21){
			//player wins
			hasPlayerWon = true;
		}
		gameOver = true;
		endGameSequence();
	}
	else if (playerTotal > 21)
	{
		hasPlayerWon = false;
		gameOver = true;
		endGameSequence();
	}
}
void PlayArea::standGameSequence() {
	int casinoTotal = (&deck)->cardsTotal((&deck)->casinosCards);
	int playerTotal = (&deck)->cardsTotal((&deck)->playersCards);
	if (playerTotal == 21) {
		//check casino
		if (casinoTotal == 21) {
			//casino wins
			hasPlayerWon = false;
		}
		else {
			//player wins
			hasPlayerWon = true;
		}
		gameOver = true;
		endGameSequence();
	}
	else {
		while (casinoTotal < playerTotal)
		{
			(&deck)->playCard(false);
			casinoTotal = (&deck)->cardsTotal((&deck)->casinosCards);
			Sleep(1000);//slight delay just to make it look more natural
			onDraw();
		}
		if (casinoTotal > 21)
		{
			hasPlayerWon = true;
			gameOver = true;
		}
		else {
			hasPlayerWon = false;
			gameOver = true;
		}
		endGameSequence();
	}
}
void PlayArea::endGameSequence()
{
	clearScreen(DARK_GREEN);
	if (hasPlayerWon)
	{
		drawBitmap(L"Assets/win.bmp", 200, 200, 660, 480, 0x00FF00FF);// /2-66 is for centering the image
	}
	else
	{
		drawBitmap(L"Assets/lose.bmp", 200, 200, 720, 600, 0x00FF00FF);
	}
	Sleep(2000);
	onDraw();
}

void PlayArea::onLButtonDown(UINT nFlags, int x, int y)//dynamic polymorphism
{
	if (hasBegun) {
		if (hitButton->hitTest(x, y)) 
		{
			isPlay = true;
			hitGameSequence();
			onDraw();
		}
		if(standButton->hitTest(x,y))
		{
			isPlay = true;
			standGameSequence();
			onDraw();
		}
	
	}
	else {
		if (startButton->hitTest(x, y))
		{
			hasBegun = true;
			onDraw();
		}
	}
	
}
