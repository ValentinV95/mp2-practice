#include "stdlib.h"
#include "stdio.h"
#include <regex>
#include <fstream>
#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	regex rx_war("\\b[Ww][Aa][Rr]\\b");
	ifstream fin("WarAndPeace.txt");
	string warAndPeace;
	string buff;
	smatch mat;

	string replace("peace");
	regex rx_peace("[Pp]eace");

	while (!fin.eof())
	{
		getline(fin, buff);
		warAndPeace += buff + "\n";
	}
	int count = 0;
	string s = warAndPeace;
	while (regex_search(s, mat, rx_war))
	{
		count++;
		s = mat.suffix().str();
	}
	cout << "Количество слов \"War\": " << count << endl;
	
	count = 0;
	s = warAndPeace;
	while (regex_search(s, mat, rx_peace))
	{
		count++;
		s = mat.suffix().str();
	}
	cout << "Количество буквосочетаний \"peace\" в исходном тексте: " << count << endl;

	string s1 = regex_replace(warAndPeace, rx_war, replace);

	count = 0;
	s = s1;
	while (regex_search(s, mat, rx_peace))
	{
		count++;
		s = mat.suffix().str();
	}
	cout << "Количество буквосочетаний \"peace\" в измененом тексте: " << count << endl;

    return 0;
}

