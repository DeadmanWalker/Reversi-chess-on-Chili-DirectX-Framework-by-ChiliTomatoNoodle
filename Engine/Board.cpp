#include "Board.h"
#include "assert.h"

void Board::DrawBoard(Graphics & gfx) const
{
	gfx.DrawRectDim(pos_x, pos_y, width * cell_dim, height * cell_dim, bg_color);
	DrawCell(gfx);
	DrawPiece(gfx);
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
	cells[width / 2][height / 2] = 1;
	cells[width / 2 - 1][height / 2 - 1] = 1;
	cells[width / 2 - 1][height / 2] = 2;
	cells[width / 2][height / 2 - 1] = 2;
}

void Board::DrawCell(Graphics & gfx) const
{
	const int cell_offset = 2;
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			gfx.DrawRectDim(pos_x + i * cell_dim + cell_offset, pos_y + j * cell_dim + cell_offset,
				cell_dim - 2 * cell_offset, cell_dim - 2 * cell_offset, cell_color);
		}
	}
}

void Board::DrawPiece(Graphics & gfx) const
{
	int offset_x = pos_x + cell_dim / 2;
	int offset_y = pos_y + cell_dim / 2;
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			if (cells[i][j] == 1)
			{
				gfx.DrawCircle(offset_x + i * cell_dim, offset_y + j * cell_dim, cell_dim / 2 - 5, Colors::White);
			}
			if (cells[i][j] == 2)
			{
				gfx.DrawCircle(offset_x + i * cell_dim, offset_y + j * cell_dim, cell_dim / 2 - 5, Colors::Black);
			}
		}
	}
}

int Board::HashFunc(Location loc, int id)
{
	return (1 - 2 * (id == 2)) * (width * loc.y + loc.x + 1);
}

Location Board::DeHashFunc(int hash)
{
	return Location((abs(hash) - 1) % 8, (abs(hash) - 1) / 8);
}
