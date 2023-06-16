#pragma once

#include "Graphics.h"

class SpriteCodex
{
public:
	static void DrawGameOver(Graphics& gfx );
	static void DrawTitle(Graphics& gfx );
	static void DrawBoost_Off(Graphics& gfx);
	static void DrawBoost_On(Graphics& gfx);
	static void DrawReady(Graphics& gfx);
	static void DrawGG(Graphics& gfx);
	static void DrawLife(Graphics& gfx, int x, int y);
	static void DrawRespawn(Graphics& gfx);
	static void DrawPaused(Graphics& gfx);
};