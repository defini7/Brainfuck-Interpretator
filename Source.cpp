#include <iostream>
#include <vector>

char rgStack[30000]{ 0 };

int main()
{
	uint32_t nStackPointer = 0;
	int brc = 0;

	std::vector<char> vecInput;

	std::cout << "DEFINIT BRAINFUCK v0.1\n";
	
	while (true)
	{
		if (nStackPointer > 29999 || nStackPointer < 0)
		{
			std::cout << "Error: Pointer out of range.\n";
			return -1;
		}
		
		std::string s;
		std::cin >> s;

		if (s == "exit")
			return 0;

		if (s != "run")
		{
			for (size_t i = 0; i < s.length(); i++)
				vecInput.push_back(s[i]);

			continue;
		}
		
		if (std::count(vecInput.begin(), vecInput.end(), '[') != std::count(vecInput.begin(), vecInput.end(), ']'))
		{
			std::cout << "Error: While loop started but not ended.\n";
			return -1;
		}

		for (size_t i = 0; i < vecInput.size(); i++)
		{
			switch (vecInput[i])
			{
			case ' ':
				break;

			case '+':
				rgStack[nStackPointer]++;
				break;

			case '-':
				rgStack[nStackPointer]--;
				break;

			case '>':
				nStackPointer++;
				break;

			case '<':
				nStackPointer--;
				break;

			case '.':
				std::cout << (char)rgStack[nStackPointer];
				break;

			case ',':
				std::cin >> rgStack[nStackPointer];
				break;

			case '[':
			{
				if (rgStack[nStackPointer] == 0)
				{
					++brc;
					while (brc)
					{
						++i;

						if (vecInput[i] == '[')
							++brc;
						if (vecInput[i] == ']')
							--brc;
					}
				}
				else
					break;
			}
			break;

			case ']':
			{
				if (rgStack[nStackPointer] == 0)
					break;
				else
				{
					if (vecInput[i] == ']')
						brc++;

					while (brc)
					{
						--i;
						if (vecInput[i] == '[')
							brc--;
						if (vecInput[i] == ']')
							brc++;
					}
					--i;
				}
			}
			break;

			default:
				std::cout << "Unexpected symbol!\n";
				return 1;

			}
		}

		vecInput.clear();

	}

	return 0;
}
