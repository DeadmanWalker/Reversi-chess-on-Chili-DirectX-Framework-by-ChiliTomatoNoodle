#pragma once
#include "Location.h"
#include "Graphics.h"
#include "Mouse.h"
#include <vector>


class Board
{
public:
	Board();
	void DrawBoard(Graphics& gfx) const;
	void ResetBoard();
	void Control(const Mouse& mouse);
private:
	void DrawCell(Graphics& gfx) const;
	void DrawPiece(Graphics& gfx, Location loc, int id) const;
	void PlacePiece(Location loc, int id);
	int HashFunc(Location loc) const;
	Location DeHashFunc(int hash) const;
	void checkForMove(Location loc, int id);
	bool isInBound(Location loc);
	void updateValidMove(int id);
	void DrawValidMove(Graphics& gfx) const;
	bool checkValidSelect(Location loc) const;
	void takePieces(Location loc, int id);
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
	std::vector<int> valid_move_hash;
	Location selected_cell;
	int curr_turn = 1;
	bool pre_mouse_input = false;
	bool draw_ghost_piece = true;
	std::vector<int> move_direction[65];
};