#include <iostream>
#include <string>
using namespace std;

#include "olcConsoleGameEngine.h"

class FlappyBird : public olcConsoleGameEngine
{
public:
	FlappyBird()
	{
		m_sAppName = L"FlappyBird";
	}

private:
	float birdVelocity     = 0.0f;
	float birdAcceleration = 0.0f;
	float birdPosition     = 0.0f;
	float gravity = 100.0f;
	float objectPosition = 80;
	float objectHeight = 40;
	float h;
	int maxScore = 0;
	int currentScore = 0;
	int colorRand;
	bool dead = false;
	bool reset = false;
	bool up = true;

protected:

	virtual bool OnUserCreate() 
	{
		return true;
	}

	virtual bool OnUserUpdate(float fElapsedTime) 
	{
		if (reset) {
			birdPosition = ScreenHeight() / 3.0f;
			currentScore = 0;
			birdVelocity = 0.0f;
			birdAcceleration = 0.0f;
			objectPosition = 85;
			reset = false;
			dead = false;
		}
		if (dead) {
			if (m_keys[VK_SPACE].bReleased) {
				reset = true;
			}
		}
		else {
			if (m_keys[VK_SPACE].bPressed && birdVelocity >= 10.0f) {
				birdAcceleration = 0.0f;
				birdVelocity = -gravity / 4.0f;
				currentScore++;
				if (currentScore >= maxScore) {
					maxScore = currentScore;
				}
			}
			else {
				birdAcceleration += gravity * fElapsedTime;
			}
			birdVelocity += birdAcceleration * fElapsedTime;
			birdPosition += birdVelocity * fElapsedTime;

			int birdXPos = (int)(ScreenWidth() / 3.0f);
			Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');
			if (birdVelocity > 0) {
				DrawString(birdXPos, birdPosition + 0, L"\\\\\\\\");
				DrawString(birdXPos, birdPosition + 1, L"<\\\\\\\\=Q");
			}
			else {
				DrawString(birdXPos, birdPosition + 0, L"<////=Q");
				DrawString(birdXPos, birdPosition + 1, L"////");
			}
				Fill(objectPosition, objectHeight, objectPosition + 6, ScreenHeight(), PIXEL_SOLID, FG_CYAN);
				Fill(objectPosition, 0, objectPosition + 6, objectHeight - 16, PIXEL_SOLID, FG_CYAN);
			objectPosition -= 12 * fElapsedTime;
			if (objectPosition < -6) {
				objectPosition = ScreenWidth();
				objectHeight = rand() % (ScreenHeight());
				h = objectHeight;
				while (objectHeight - 16 < 0 || objectHeight > 20) {
					objectHeight = rand() % (ScreenHeight());
				}
			}
			if (objectHeight >= 20 && up) {
				objectHeight -= 10 * fElapsedTime;
			}
			else {
				objectHeight += 10 * fElapsedTime;
				up = false;
				if (objectHeight >= 30) up = true;
			}
			if (birdXPos >= objectPosition - 6 && birdXPos <= objectPosition + 6) {
				if (birdPosition >= objectHeight) dead = true;
				if (birdPosition <= objectHeight - 16) dead = true;
			}

			if (birdPosition > ScreenHeight())
				dead = true;
			if (birdPosition < 0)
				dead = true;
		
		DrawString(2, 0, L"Score: " + to_wstring(currentScore));
		DrawString(12, 0, L"High Score: " + to_wstring(maxScore));
		}
		return true;
	}

};

int main()
{
	FlappyBird game;
	game.ConstructConsole(80, 45, 14, 14);
	game.Start();
	return 0;
}
