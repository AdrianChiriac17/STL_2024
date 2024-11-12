///cerinta bonus
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


/*
	ne vin n probleme, care se pot rezolva numai cu o anumita specializare, fiecare problema are si o durata

*/

struct Problema
{
	string nume;
	string specializare;
	int durata;
};


/*
	avem si m doctori, fiecare cu numele lui, si o specializare anume, mai am nevoie de un vector cu stringuri
	cu ce va trata pe ziua de astazi si un nr de ore ocupate pana in acest moment
*/

struct Doctor
{
	string nume;
	string specializare;
	vector<string>pe_astazi;
	int ore_ocupate;
};

int main()
{
	//ifstream fin("input2");
	
	int nr_probleme;
	fin >> nr_probleme;
	vector<Problema>probleme(nr_probleme);
	for(int i=0; i<nr_probleme; i++)
	{
		fin >> probleme[i].nume >> probleme[i].specializare >> probleme[i].durata;
	}
	int nr_doctori;
	fin >> nr_doctori;
	vector<Doctor>doctori(nr_doctori);
	for (int i = 0; i < nr_doctori; i++)
	{
		fin >> doctori[i].nume >> doctori[i].specializare;
		doctori[i].ore_ocupate = 0;
	}

	for (int i = 0; i < nr_probleme; i++)
	{
		string curr_specializare = probleme[i].specializare;
		int curr_durata = probleme[i].durata;
		string curr_problem_name = probleme[i].nume;

		//caut curr_problem.specializare prin lista de medici

		auto it = find_if(doctori.begin(), doctori.end(), [curr_specializare, curr_durata](Doctor& d) 
			{  return (curr_specializare == d.specializare) && (curr_durata + d.ore_ocupate <= 8);});

		if (it != doctori.end())
		{
			//it va reprezenta doctorul pentru la care aceasta problema poate fi tratata
			//int iterator = it - doctori.begin();
			it->pe_astazi.push_back(curr_problem_name);
			it->ore_ocupate += curr_durata;
			/*
			doctori[iterator].pe_astazi.push_back(curr_problem_name);
			doctori[iterator].ore_ocupate += curr_durata;
			*/
		}
	}

	for (int i = 0; i < nr_doctori; i++)
	{
		cout << doctori[i].nume << " " << doctori[i].pe_astazi.size();
		if (doctori[i].pe_astazi.size() != 0)
		{
			cout << " ";
			for (string& prb : doctori[i].pe_astazi)
			{
				cout << prb << " ";
			}
		}
		cout << endl;
	}

	return 0;
}