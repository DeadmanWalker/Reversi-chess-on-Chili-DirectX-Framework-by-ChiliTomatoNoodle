#pragma once
#include "Location.h"
#include "Graphics.h"
#include "Mouse.h"
#include <vector>


class Board
{
public:
	void DrawBoard(Graphics& gfx) const;
	Board();
	void ResetBoard();
private:
	void DrawCell(Graphics& gfx) const;
	void DrawPiece(Graphics& gfx) const;
	int HashFunc(Location loc, int id);
	Location DeHashFunc(int hash);
private:
	static constexpr int height = 8;
	static constexpr int width = 8;
	static constexpr int cell_dim = 50;
	static constexpr int pos_x = 200;
	static constexpr int pos_y = 100;
	static constexpr Color bg_color = Color(182, 125, 34);
	static constexpr Color cell_color = Color(116, 71, 0);

	int cells[width][height];
	std::vector<int> cell_hash;
};