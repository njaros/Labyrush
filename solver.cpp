#include <iostream>
#include <string>
#include <fstream>


int	main(void)
{
	std::string	pouet;
	getline(std::cin, pouet);
	getline(std::cin, pouet);
	while (1)
	{
		for (int i = 0; i < 5; ++i)
			getline(std::cin, pouet);
		std::cout << "HAUT\n";
		std::cerr << pouet;
	}
	return 0;
}