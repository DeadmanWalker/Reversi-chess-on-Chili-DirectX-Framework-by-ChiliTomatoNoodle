#include "Board.h"
#include "assert.h"

const int player1_id = 1;
const int player2_id = 2;
Location direction[8] =
{
	{ -1,1 },
	{ 0,1 },
	{ 1,1 },
	{ -1,0 },
	{ 1,0 },
	{ -1,-1 },
	{ 0,-1 },
	{ 1,-1 }
};

void Board::DrawBoard(Graphics & gfx) const
{
	gfx.DrawRectDim(pos_x, pos_y, width * cell_dim, height * cell_dim, bg_color);
	DrawCell(gfx);
	
	if (draw_ghost_piece)
	{
		DrawPiece(gfx, selected_cell, 2 - curr_turn % 2);
	}
	
	DrawValidMove(gfx);

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
	ResetBoard();
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

	curr_turn = 1;

	cell_hash.clear();

	PlacePiece({ width / 2,height / 2 }, player1_id);
	PlacePiece({ width / 2 - 1,height / 2 - 1 }, player1_id);
	PlacePiece({ width / 2 - 1,height / 2 }, player2_id);
	PlacePiece({ width / 2,height / 2 - 1 }, player2_id);

	updateValidMove(1);
}

void Board::Control(const Mouse & mouse)
{
	draw_ghost_piece = false;
	Location temp = { (mouse.GetPosX() - pos_x) / cell_dim, (mouse.GetPosY() - pos_y) / cell_dim };
	if (!valid_move_hash.empty())
	{
		if (checkValidSelect(temp))
		{
			draw_ghost_piece = true;
			int curr_player = 2 - curr_turn % 2;
			selected_cell = temp;
			if (pre_mouse_input && !mouse.LeftIsPressed() && cells[selected_cell.x][selected_cell.y] == 0)
			{
				PlacePiece(selected_cell, curr_player);
				++curr_turn;
				updateValidMove(2 - curr_turn % 2);
			}
		}
	}
	else
	{
		++curr_turn;
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

void Board::PlacePiece(Location loc, int id)
{
	cells[loc.x][loc.y] = id;
	cell_hash.push_back(HashFunc(loc));
}

int Board::HashFunc(Location loc) const
{
	return (width * loc.y + loc.x + 1);
}

Location Board::DeHashFunc(int hash) const
{
	return Location((hash - 1) % width, (hash - 1) / width);
}

void Board::checkForMove(Location loc, int id)
{
	for (int i = 0; i < 8; ++i)
	{
		Location temp = loc + direction[i];
		if (cells[temp.x][temp.y] != id && cells[temp.x][temp.y] != 0)
		{
			while(isInBound(temp))
			{

				if (cells[temp.x][temp.y] == 0)
				{
					valid_move_hash.push_back(HashFunc(temp));
					break;
				}
				else if (cells[temp.x][temp.y] == id)
				{
					break;
				}
				temp = temp + direction[i];
			}
		}
	}
}

bool Board::isInBound(Location loc)
{
	return loc.x >= 0 && loc.x < width && loc.y >= 0 && loc.y < height;
}

void Board::updateValidMove(int id)
{
	valid_move_hash.clear();
	for (int i = 0; i < cell_hash.size(); ++i)
	{
		Location temp = DeHashFunc(cell_hash[i]);
		if (cells[temp.x][temp.y] == id)
		{
			checkForMove(temp, id);
		}

	}
}

void Board::DrawValidMove(Graphics & gfx) const
{
	for (int i = 0; i < valid_move_hash.size(); ++i)
	{
		Location temp = DeHashFunc(valid_move_hash[i]);
		int offset_x = pos_x + cell_dim / 2;
		int offset_y = pos_y + cell_dim / 2;
		gfx.DrawCircle(offset_x + temp.x * cell_dim, offset_y + temp.y * cell_dim, 5, Colors::Green);
	}
}

bool Board::checkValidSelect(Location loc) const
{
	for (int i = 0; i < valid_move_hash.size(); ++i)
	{
		if (HashFunc(loc) == valid_move_hash[i])
		{
			return true;
		}
	}
	return false;
}
