#include "Board.h"
#include "assert.h"

void Board::DrawBoard(Graphics & gfx) const
{
	gfx.DrawRectDim(pos_x, pos_y, width * cell_dim, height * cell_dim, bg_color);
	DrawCell(gfx);
	
	if (draw_ghost_piece)
	{
		DrawPiece(gfx, selected_cell, 2 - curr_turn % 2);
	}
	
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			if (cells[i][j] != 0)
			{
				DrawPiece(gfx, { i, j }, cells[i][j]);
			}
		}
	}
}

Board::Board()
{
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			cells[i][j] = 0;
		}
	}
	cells[width / 2][height / 2] = 1;
	cells[width / 2 - 1][height / 2 - 1] = 1;
	cells[width / 2 - 1][height / 2] = 2;
	cells[width / 2][height / 2 - 1] = 2;

	cell_hash.push_back(HashFunc({ width / 2, height / 2 }, 1));
	cell_hash.push_back(HashFunc({ width / 2 - 1, height / 2 - 1 }, 1));
	cell_hash.push_back(HashFunc({ width / 2 - 1, height / 2 }, 2));
	cell_hash.push_back(HashFunc({ width / 2, height / 2 - 1 }, 2));
}

void Board::ResetBoard()
{
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			cells[i][j] = 0;
		}
	}

	cell_hash.clear();

	cells[width / 2][height / 2] = 1;
	cells[width / 2 - 1][height / 2 - 1] = 1;
	cells[width / 2 - 1][height / 2] = 2;
	cells[width / 2][height / 2 - 1] = 2;

	cell_hash.push_back(HashFunc({ width / 2, height / 2 }, 1));
	cell_hash.push_back(HashFunc({ width / 2 - 1, height / 2 - 1 }, 1));
	cell_hash.push_back(HashFunc({ width / 2 - 1, height / 2 }, 2));
	cell_hash.push_back(HashFunc({ width / 2, height / 2 - 1 }, 2));
}

void Board::PlacePiece(const Mouse & mouse)
{
	draw_ghost_piece = false;
	if (mouse.GetPosX() - pos_x >= 0 && (mouse.GetPosX() - pos_x) / cell_dim < width
		&& mouse.GetPosY() - pos_y >= 0 && (mouse.GetPosY() - pos_y) / cell_dim < height
		&& !(pre_mouse_input && mouse.LeftIsPressed()))
	{
		draw_ghost_piece = true;
		int curr_player = 2 - curr_turn % 2;
		selected_cell = { (mouse.GetPosX() - pos_x) / cell_dim, (mouse.GetPosY() - pos_y) / cell_dim };
		if (!pre_mouse_input && mouse.LeftIsPressed() && cells[selected_cell.x][selected_cell.y] == 0)
		{
			cells[selected_cell.x][selected_cell.y] = curr_player;
			cell_hash.push_back(HashFunc(selected_cell, curr_player));
			++curr_turn;
		}
	}

	pre_mouse_input = mouse.LeftIsPressed();
}

void Board::DrawCell(Graphics & gfx) const
{
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			gfx.DrawRectDim(pos_x + i * cell_dim + cell_offset, pos_y + j * cell_dim + cell_offset,
				cell_dim - 2 * cell_offset, cell_dim - 2 * cell_offset, cell_color);
		}
	}
}

void Board::DrawPiece(Graphics & gfx, Location loc, int id) const
{
	int offset_x = pos_x + cell_dim / 2;
	int offset_y = pos_y + cell_dim / 2;
	gfx.DrawCircle(offset_x + loc.x * cell_dim, offset_y + loc.y * cell_dim, cell_dim / 2 - 5, player_color[id - 1]);
}

int Board::HashFunc(Location loc, int id)
{
	return (1 - 2 * ((2 - curr_turn % 2) == 2)) * (width * loc.y + loc.x + 1);
}

Location Board::DeHashFunc(int hash)
{
	return Location((abs(hash) - 1) % width, (abs(hash) - 1) / width);
}
