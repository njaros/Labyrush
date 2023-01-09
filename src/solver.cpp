#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <map>
#include <set>
#include <deque>

typedef	std::vector<std::pair<char, int> >	raw;
typedef	std::vector<raw>					grid;
typedef	std::pair<int, int>					coord;

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

std::ostream &operator<<(std::ostream &o, const std::pair<char, int> &c)
{
	o << c.first << '|' << c.second;
	return o;
}

std::ostream &operator<<(std::ostream &o, const coord &c)
{
	o << c.first << '|' << c.second;
	return o;
}

std::ostream &operator<<(std::ostream &o, const raw &r)
{
	for (raw::const_iterator cit = r.begin(); cit != r.end(); ++cit)
		o << cit->first;
	o << "  ";
	for (raw::const_iterator cit = r.begin(); cit != r.end(); ++cit)
		if (cit->second <= 9)
			o << cit->second;
		else
			o << '9';
	return o;
}

std::ostream &operator<<(std::ostream &o, const grid &g)
{
	for (grid::const_iterator cit = g.begin(); cit != g.end(); ++cit)
		o << *cit << '\n';
	return o;
}
// This is a C++ exemple solver

class solver {

	int _width;
	int _high;
	grid _grid;
	coord _pos;
	coord _start;
	coord _goal;
	int _timer;

	int _dfsScore(coord c, std::set <coord> &visited) {
		if (c.first < 0 || static_cast<unsigned int>(c.first) >= _grid[0].size() || c.second < 0 ||
			static_cast<unsigned int>(c.second) >= _grid.size()
			|| _grid[c.second][c.first].first == '#')
			return 0;
		std::pair<std::set<coord>::iterator, bool> insertResult = visited.insert(c);
		if (!insertResult.second)
			return 0;
		if (_grid[c.second][c.first].first == '?')
			return 1;
		_grid[c.second][c.first].second = _dfsScore(c + coord(1, 0), visited) + _dfsScore(c + coord(0, 1), visited) +
										  _dfsScore(c + coord(-1, 0), visited) + _dfsScore(c + coord(0, -1), visited);
		return (_grid[c.second][c.first].second);
	}

	int _beamScore(std::deque<coord> &lifo, std::set<coord> &visited)
	{
		while (!lifo.empty())
		{
			coord	tmp = lifo.front();
			std::pair<std::set<coord>::iterator, bool>	insertResult;
			if ((tmp + coord(1, 0)).first < _grid[0].size() - 1)
		}
	}

public :

	solver() {}

	solver(int width, int high, int x, int y, int timer) : _width(width), _high(high),
														   _grid(high, raw(width, std::make_pair('?', 0))),
														   _pos(coord(x, y)), _start(_pos), _goal(coord(-1, -1)),
														   _timer(timer) {}

	solver(const solver &o) : _width(o._width), _high(o._high), _grid(o._grid), _pos(o._pos), _start(o._start),
							  _goal(o._goal), _timer(o._timer) {}

	~solver() {}

	solver &operator=(const solver &o) {
		_high = o._high;
		_width = o._width;
		_grid = o._grid;
		_pos = o._pos;
		_start = o._start;
		_goal = o._goal;
		_timer = o._timer;
		return *this;
	}

	void moveUp() {
		_pos.second -= 1;
		std::cout << "UP\n";
	}

	bool getView() {
		std::string line;
		bool discovered = false;
		for (int i = 0; i < 5; ++i) {
			getline(std::cin, line);
			for (std::string::size_type idx = 0; idx < 5; ++idx) {
				if (_pos.first + idx - 2 >= 0 && _pos.first + idx - 2 < _grid[0].size()) {
					if (_grid[_pos.second + i - 2][_pos.first + idx - 2].first == '?') {
						discovered = true;
						if (line[idx] == 'P')
							_grid[_pos.second + i - 2][_pos.first + idx - 2].first = '.';
						else
							_grid[_pos.second + i - 2][_pos.first + idx - 2].first = line[idx];
					}
				}
			}
		}
		return discovered;
	}

	void	changeScoreBeam()
	{
		std::deque<coord>	lifo;
		std::set<coord>		visited;
		lifo.push_back(_pos);
		_beamScore(lifo, visited);
	}

	void	changeScoreDfs()
	{
		std::set<coord>	visited;
		_dfsScore(_pos, visited);
	}

	void	debugMap()
	{
		_grid[_pos.second][_pos.first].first = 'P';
		std::cerr << _grid << '\n';
		_grid[_pos.second][_pos.first].first = '.';
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
		if (solv.getView())
			solv.changeScoreDfs();
		solv.debugMap();
		solv.moveUp();
	}
	return 0;
}