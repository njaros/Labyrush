#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <map>
#include <set>
#include <deque>

typedef	std::vector<std::pair<char, int> >	row;
typedef	std::vector<row>					grid;
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

std::ostream &operator<<(std::ostream &o, const row &r)
{
	for (row::const_iterator cit = r.begin(); cit != r.end(); ++cit)
		o << cit->first;
	o << "  ";
	for (row::const_iterator cit = r.begin(); cit != r.end(); ++cit)
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

	int					_width;
	int					_high;
	grid				_grid;
	coord				_pos;
	coord				_start;
	coord				_goal;
	int					_timer;
	std::deque<coord>	_path;

	void	_resetScore()
	{
		for (grid::iterator idx = _grid.begin(); idx != _grid.end(); ++idx)
		{
			for (row::iterator idxR = idx->begin(); idxR != idx->end(); ++idxR)
				idxR->second = 0;
		}
	}

	int _dfsScore(coord c, std::set <coord> &visited)
	{
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

	void	_upScoreUntilRoot(const coord &f, std::map<coord, coord> &nodes)
	{
		std::map<coord, coord>::iterator it = nodes.find(f);
		++_grid[f.second][f.first].second;
		while (it->first != it->second)
		{
			++_grid[it->second.second][it->second.first].second;
			it = nodes.find(it->second);
			if (it == nodes.end())
				throw (std::invalid_argument("_upScoreUntilRoot: bad implementation of nodes\n"));
		}
	}

	void	_checkSide(const coord &c, const coord &f, std::deque<coord> &lifo, std::map<coord, coord> &nodes)
	{
		if (c.first <= 0 || static_cast<unsigned int>(c.first) >= _grid[0].size() - 1 || c.second <= 0 || static_cast<unsigned int>(c.second) >= _grid.size() - 1)
			return ;
		char	abia = _grid[c.second][c.first].first;
		switch (abia)
		{
			case '#':
				break ;
			case '?':
				_upScoreUntilRoot(f, nodes);
				break ;
			case 'O':
				break ;
			case '.': {
				std::pair<std::map<coord, coord>::iterator, bool> insertResult = nodes.insert(std::make_pair(c, f));
				if (insertResult.second)
					lifo.push_back(c);
				break;
			}
			default:
				throw (std::invalid_argument("_checkSide::_bfsScore : unexpected character\n"));
		}
	}

	void	_bfsScore()
	{
		std::deque<coord>		lifo;
		std::map<coord, coord>	nodes;
		lifo.push_back(_pos);
		nodes.insert(std::make_pair(_pos, _pos));
		while (!lifo.empty())
		{
			coord	tmp = lifo.front();
			lifo.pop_front();
			coord right = tmp + coord(1, 0);
			coord down = tmp + coord(0, 1);
			coord left = tmp + coord(-1, 0);
			coord up = tmp + coord(0, -1);
			_checkSide(right, tmp, lifo, nodes);
			_checkSide(down, tmp, lifo, nodes);
			_checkSide(left, tmp, lifo, nodes);
			_checkSide(up, tmp, lifo, nodes);
		}
	}

	bool	_nextStep(coord &step, std::set<coord> &visited)
	{
		visited.insert(step);
		coord	right = step + coord(1, 0);
		coord	down = step + coord(0, 1);
		coord	left = step + coord(-1, 0);
		coord	up = step + coord(0, -1);
		int 	rightScore = 0;
		int		downScore = 0;
		int		leftScore = 0;
		int		upScore = 0;

		if (visited.find(right) == visited.end())
			rightScore = _grid[right.second][right.first].second;
		if (visited.find(down) == visited.end())
			downScore = _grid[down.second][down.first].second;
		if (visited.find(left) == visited.end())
			leftScore = _grid[left.second][left.first].second;
		if (visited.find(up) == visited.end())
			upScore = _grid[up.second][up.first].second;
		if (rightScore == 0 && downScore == 0 && leftScore == 0 && upScore == 0)
			return false;
		if (rightScore && (!downScore || rightScore < downScore) && (!leftScore || rightScore < leftScore) && (!upScore || rightScore < upScore))
		{
			step = right;
			_path.push_back(right);
		}
		else if (downScore && (!leftScore || downScore < leftScore) && (!upScore || downScore < upScore))
		{
			step = down;
			_path.push_back(down);
		}
		else if (leftScore && (!upScore || leftScore < upScore))
		{
			step = left;
			_path.push_back(left);
		}
		else
		{
			step = up;
			_path.push_back(up);
		}
		return true;
	}

public :

	solver() {}

	solver(int width, int high, int x, int y, int timer) : _width(width), _high(high),
														   _grid(high, row(width, std::make_pair('?', 0))),
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

	void moveDown() {
		_pos.second += 1;
		std::cout << "DOWN\n";
	}

	void moveRight() {
		_pos.first += 1;
		std::cout << "RIGHT\n";
	}

	void moveLeft() {
		_pos.first -= 1;
		std::cout << "LEFT\n";
	}

	bool getView() {
		std::string line;
		bool discovered = false;
		for (int i = 0; i < 5; ++i) {
			getline(std::cin, line);
			std::cerr << "solver" << line << '\n';
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
		std::cerr << '\n';
		return discovered;
	}

	void	setNewPath()
	{
		_path.clear();
		std::set<coord>	visited;
		changeScoreBfs();
		coord	step = _pos;
		while (_nextStep(step, visited))
			;
	}

	void	followPath()
	{
		if (_path.empty())
		{
			std::cout << "fini\n";
			return ;
		}
		if (_path.front() - _pos == coord(1, 0))
			moveRight();
		else if (_path.front() - _pos == coord(0, 1))
			moveDown();
		else if (_path.front() - _pos == coord(-1, 0))
			moveLeft();
		else
			moveUp();
		_path.pop_front();
	}

	bool	pathEmpty()	const
	{
		return (_path.empty());
	}

	void	changeScoreBfs()
	{
		_resetScore();
		_bfsScore();
	}

	void	changeScoreDfs()
	{
		_resetScore();
		std::set<coord>	visited;
		_dfsScore(_pos, visited);
	}

	void	debugMap(std::ostream &out)
	{
		_grid[_pos.second][_pos.first].first = 'P';
		out << _grid << '\n';
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
	std::filebuf fb;

	fb.open("output.log", std::ios::out);
	std::ostream out(&fb);

	//First input asks if I'm a program or not (to define a timer or not)
	while (line.empty())
		getline(std::cin, line);
	std::cout << "y\n";

	line.clear();
	//Second input tells me the map size, and the coordinate of the beginning position
	while (line.empty())
		getline(std::cin, line);
	std::string::size_type	idx = line.find('=') + 1;
	width = atoi(&line[idx]);
	idx = line.find('=', idx) + 1;
	high = atoi(&line[idx]);
	idx = line.find('=', idx) + 1;
	beginX = atoi(&line[idx]);
	idx = line.find('=', idx) + 1;
	beginY = atoi(&line[idx]);

	line.clear();
	//Third input tells me the max movement I can do when I reached the O (goal) to bring it to the beginning posision
	while (line.empty())
		getline(std::cin, line);
	idx = line.find('=') + 1;
	timer = atoi(&line[idx]);

	solver	solv(width, high, beginX, beginY, timer);
	while (1)
	{
		solv.getView();
		if (solv.pathEmpty())
		{
			out << "setting up a new path\n";
			solv.setNewPath();
			out << "new path set up\n";
		}
		solv.debugMap(out);
		solv.followPath();
	}
	return 0;
}