#pragma once

struct Location
{
	Location(int in_x, int in_y)
	{
		x = in_x;
		y = in_y;
	};
	int x;
	int y;
	Location operator+(const Location& rhs) const
	{
		return { x + rhs.x, y + rhs.y };
	}
	bool operator==(const Location& rhs) const
	{
		return ((x == rhs.x) && (y == rhs.y));
	}
};