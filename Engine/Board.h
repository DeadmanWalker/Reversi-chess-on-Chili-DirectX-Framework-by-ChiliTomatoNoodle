#pragma once
#include"Location.h"
#include"Graphics.h"


class Board
{
public:
	void DrawBoard(Graphics& gfx) const;
private:
	void DrawCell(Graphics& gfx) const;

	static constexpr int height = 8;
	static constexpr int width = 8;
	static constexpr int cell_dim = 50;
	static constexpr int pos_x = 200;
	static constexpr int pos_y = 100;
	static constexpr Color bg_color = Color(182, 125, 34);
	static constexpr Color cell_color = Color(116, 71, 0);
};