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
	void Control(const Mouse& mouse);
private:
	void DrawCell(Graphics& gfx) const;
	void DrawPiece(Graphics& gfx, Location loc, int id) const;
	void PlacePiece(Location loc, int id);
	int HashFunc(Location loc, int id);
	Location DeHashFunc(int hash);
private:
	static constexpr int height = 8;
	static constexpr int width = 8;
	static constexpr int cell_dim = 50;
	static constexpr int cell_offset = 2;
	static constexpr int pos_x = 200;
	static constexpr int pos_y = 100;
	static constexpr Color bg_color = Color(182, 125, 34);
	static constexpr Color cell_color = Color(116, 71, 0);
	static constexpr Color player_color[2] = { Colors::White, Colors::Black };

	int cells[width][height];
	std::vector<int> cell_hash;
	Location selected_cell;
	int curr_turn = 1;
	bool pre_mouse_input = false;
	bool draw_ghost_piece = true;
};