#include <iostream>
#include <string>
#include <fstream>

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

	while (1)
	{
		for (int i = 0; i < 5; ++i)
			getline(std::cin, line);
		std::cout << "HAUT\n";
	}
	return 0;
}