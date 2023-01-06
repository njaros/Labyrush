#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <set>

typedef	std::vector<char>	raw;
typedef	std::vector<raw>	grid;
typedef	std::pair<int, int>	coord;

coord	&operator+=(coord &lhs, const coord &rhs)
{
	lhs.first += rhs.first;
	lhs.second += rhs.second;
	return lhs;
}

coord	operator+(const coord &lhs, const coord &rhs)
{
	coord	toReturn(lhs);
	return coord(toReturn += rhs);
}

coord	&operator-=(coord &lhs, const coord &rhs)
{
	lhs.first -= rhs.first;
	lhs.second -= rhs.second;
	return lhs;
}

coord	operator-(const coord &lhs, const coord &rhs)
{
	coord	toReturn(lhs);
	return coord(toReturn -= rhs);
}

std::ostream &operator<<(std::ostream &o, const coord &c)
{
	o << c.first << '|' << c.second;
	return o;
}

std::ostream &operator<<(std::ostream &o, const raw &r)
{
	for (raw::const_iterator cit = r.begin(); cit != r.end(); ++cit)
		o << *cit;
	return o;
}

std::ostream &operator<<(std::ostream &o, const grid &g)
{
	for (grid::const_iterator cit = g.begin(); cit != g.end(); ++cit)
		o << *cit;
	return o;
}
// This is a C++ exemple solver

class solver
{

	int 	_width;
	int 	_high;
	grid	_grid;
	coord	_pos;
	coord	_start;
	coord	_goal;
	int		_timer;

	public :

	solver() {}
	solver(int width, int high, int x, int y, int timer) :	_width(width), _high(high), _grid(high, raw(width, '?')),
															_pos(coord(x, y)), _start(_pos), _goal(coord(-1, -1)), _timer(timer)
	{}
	solver(const solver &o) :	_width(o._width), _high(o._high), _grid(o._grid), _pos(o._pos), _start(o._start),
								_goal(o._goal), _timer(o._timer)
	{}
	~solver() {}

	solver &operator=(const solver &o)
	{
		_high = o._high;
		_width = o._width;
		_grid = o._grid;
		_pos = o._pos;
		_start = o._start;
		_goal = o._goal;
		_timer = o._timer;
		return *this;
	}

	void	getView()
	{
		std::string					line;
		for (int i = 0; i < 5; ++i)
		{
			getline(std::cin, line);
			for (std::string::size_type idx = 0; idx < 5; ++idx)
			{
				if (_pos.first - )
			}
		}

	}

};

int	main(void)
{
	std::string	line;
	int	width;
	int	high;
	int	timer;
	int	beginX;
	int	beginY;

	//First input asks if I'm a program or not (to define a timer or not)
	getline(std::cin, line);
	std::cout << "y\n";

	//Second input tells me the map size, and the coordinate of the beginning position
	getline(std::cin, line);
	std::string::size_type	idx = line.find('=') + 1;
	width = atoi(&line[idx]);
	idx = line.find('=', idx) + 1;
	high = atoi(&line[idx]);
	idx = line.find('=', idx) + 1;
	beginX = atoi(&line[idx]);
	idx = line.find('=', idx) + 1;
	beginY = atoi(&line[idx]);

	//Third input tells me the max movement I can do when I reached the O (goal) to bring it to the beginning posision
	getline(std::cin, line);
	idx = line.find('=') + 1;
	timer = atoi(&line[idx]);

	solver	solv(width, high, beginX, beginY, timer);
	while (1)
	{
		solv.getView();
		std::cout << "HAUT\n";
	}
	return 0;
}