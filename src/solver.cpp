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

int ManhattanNorm(const coord &a, const coord &b)
{
	return (abs(a.first - b.first) + abs(a.second - b.second));
}

std::ostream &operator<<(std::ostream &o, const std::pair<int, coord> &p)
{
	o << p.first << "->" << p.second;
	return o;
}

class Node
{

	Node() : _value(0), _cost(0), _parent(0)
	{}

public :

	coord				_pos;
	int					_value;
	int 				_cost;
	Node				*_parent;

	Node(coord pos, Node *parent, coord goal) : _pos(pos), _parent(parent)
	{
		if (parent)
			_cost = parent->_cost + 1;
		else
			_cost = 0;
		_value = _cost + ManhattanNorm(_pos, goal);
	}
	Node(coord pos, Node *parent, int heuristicValue) : _pos(pos), _parent(parent)
	{
		if (parent)
			_cost = parent->_cost + 1;
		else
			_cost = 0;
		_value = _cost + heuristicValue;
	}
	Node(const Node &other) : _pos(other._pos), _value(other._value), _cost(other._cost), _parent(other._parent)
	{}
	~Node() {}
	Node &operator=(const Node &other)
	{
		_pos = other._pos;
		_value = other._value;
		_cost = other._cost;
		_parent = other._parent;
		return (*this);
	}
};

typedef std::multimap<int, Node*>				openType;
typedef std::map<std::pair<int, int>, Node*>	closeType;


class AStar
{
	//Coplien not to use
	AStar() {}
	AStar(const AStar &other) {(void) other;}
	AStar &operator&(const AStar &other) {(void) other; return *this;}
	//End of Coplien not to use

	//Member's data
	openType								_open;
	closeType 								_close;
	std::set<coord>							_secureFreeTool;
	std::set<coord>                         _zone;
	coord									_start;
	coord									_end;
	bool									_endReached;
	Node									*_startNode;
	Node									*_current;

	//Private tool functions

	void _checkSide(const coord &move)
	{
		coord	newCoord = _current->_pos + move;
		std::set<coord>::const_iterator  zoneIt = _zone.find(newCoord);
		int newVal = ManhattanNorm(_end, newCoord);
		if (zoneIt != _zone.end()) // check if I'm out of border
		{
			closeType::iterator	found = _close.find(_current->_pos);
			if (found != _close.end())
			{
				if (found->second->_value > newVal + 1 + _current->_cost)
				{
					Node	*newNode = new Node(newCoord, _current, newVal);
					_open.insert(std::make_pair(newNode->_value, newNode));
					_close.erase(found);
				}
			}
			else
			{
				Node	*newNode = new Node(_current->_pos + move, _current, newVal);
				_open.insert(std::make_pair(newNode->_value, newNode));
			}
		}
	}

public :

	AStar(const std::set<coord> &zone, const coord &start, const coord &end) :	_zone(zone), _start(start), _end(end),
																				_endReached(false)
	{
		_startNode = new Node(_start, NULL, end);
		_open.insert(std::make_pair(_startNode->_value, _startNode));
		_current = _open.begin()->second;
		while (!_open.empty() && !_endReached)
		{
			_checkSide(std::make_pair(-1, 0));	//LEFT
			_checkSide(std::make_pair(0, -1));	//UP
			_checkSide(std::make_pair(0, 1));	//DOWN
			_checkSide(std::make_pair(1, 0));	//RIGHT
			std::pair<closeType::iterator, bool> res = _close.insert(std::make_pair(_open.begin()->second->_pos, _open.begin()->second));
			(void) res;
			_open.erase(_open.begin());
			if (!ManhattanNorm(_current->_pos, end))
				_endReached = true;
			if (!_open.empty() && !_endReached)
				_current = _open.begin()->second;
		}
	}

	~AStar ()
	{
		for (openType::iterator it = _open.begin(); it != _open.end(); ++it)
		{
			_secureFreeTool.insert(it->second->_pos);
			delete (it->second);
		}
		for (closeType::iterator it = _close.begin(); it != _close.end(); ++it)
		{
			if (_secureFreeTool.find(it->first) == _secureFreeTool.end())
				delete (it->second);
		}
	}

	std::pair<int, coord> stepCount()	const
	{
		int 	stepCount = 0;
		Node	*idx = _current;
		Node    *nextMove;
		if (!_endReached)
			return std::make_pair(-1, coord(0, 0));
		while (idx->_parent)
		{
			nextMove = idx;
			idx = idx->_parent;
			++stepCount;
		}
		return std::make_pair(stepCount, nextMove->_pos);
	}

	std::deque<coord>	getPath()	const
	{
		if (!_endReached)
			return std::deque<coord>();
		std::deque<coord>	path;
		Node	*idx = _current;
		while (idx != _startNode)
		{
			path.push_front(idx->_pos);
			idx = idx->_parent;
		}
		return path;
	}

};

class solver {

	int					_width;
	int					_high;
	grid				_grid;
	coord				_pos;
	coord				_start;
	coord				_goal;
	bool				_goalReached;
	int					_timer;
	std::set<coord>		_AStarData;
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
														   _goalReached(false), _timer(timer) {}

	solver(const solver &o) : _width(o._width), _high(o._high), _grid(o._grid), _pos(o._pos), _start(o._start),
							  _goal(o._goal), _goalReached(o._goalReached), _timer(o._timer), _AStarData(o._AStarData),
							  _path(o._path) {}

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
		for (std::string::size_type i = 0; i < 5; ++i) {
			getline(std::cin, line);
			for (std::string::size_type idx = 0; idx < 5; ++idx) {
				if (_pos.first + static_cast<int>(idx) - 2 >= 0 && _pos.first + idx - 2 < _grid[0].size() && _pos.second + static_cast<int>(i) - 2 >= 0 && _pos.second + i - 2 < _grid.size()) {
					if (_grid[_pos.second + i - 2][_pos.first + idx - 2].first == '?') {
						discovered = true;
						if (line[idx] != '#')
							_AStarData.insert(coord(_pos.first + idx - 2, _pos.second + i - 2));
						if (line[idx] == 'P')
							_grid[_pos.second + i - 2][_pos.first + idx - 2].first = '.';
						else
						{
							if (line[idx] == 'O')
								_goal = coord(_pos.first + idx - 2, _pos.second + i - 2);
							_grid[_pos.second + i - 2][_pos.first + idx - 2].first = line[idx];
						}
					}
				}
			}
		}
		return discovered;
	}

	void	setNewPath()
	{
		if (_goalReached)
		{
			AStar	aStart(_AStarData, _pos, _start);
			_path = aStart.getPath();
			return;
		}
		_path.clear();
		std::set<coord>	visited;
		changeScoreBfs();
		coord	step = _pos;
		while (_nextStep(step, visited))
			;
		if (_path.empty())
		{
			AStar	aStart(_AStarData, _pos, _goal);
			_path = aStart.getPath();
			_goalReached = true;
		}
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
	getline(std::cin, line);
	std::cout << "y\n";

	line.clear();
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

	line.clear();
	//Third input tells me the max movement I can do when I reached the O (goal) to bring it to the beginning posision
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