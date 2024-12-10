#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
using namespace std;

ifstream fin("input.txt");

struct Doctor
{
	string Name;
	vector<string>Specialties;
	int liber_de_la=8;
	vector<pair<string, int>>Answer; // .first=specialty .second=when they arrive
};

struct Problem
{
	string Name;
	string SpecialtyNeeded;
	int arrival_time;
	int duration_of_treatment;
	int priority;

	bool operator<(const Problem& other) const 
	{
		// logic here
		if (arrival_time != other.arrival_time)
			return arrival_time > other.arrival_time;
		return priority < other.priority;
	}
};

int main()
{
	int HowManyProblems;
	priority_queue<Problem>Problems;
	int HowManyDoctors;
	vector<Doctor>Doctors;

	fin >> HowManyProblems;
	for (int i = 1; i <= HowManyProblems; i++)
	{
		Problem p;
		fin >> p.Name >> p.SpecialtyNeeded >> p.arrival_time >> p.duration_of_treatment >> p.priority;
		Problems.push(p);
	}

	fin >> HowManyDoctors;
	for (int i = 1; i <= HowManyDoctors; i++)
	{
		int HowManySpecialties;
		Doctor d;
		fin >> d.Name;
		fin >> HowManySpecialties;
		for (int j = 1; j <= HowManySpecialties; j++)
		{
			string spec;
			fin >> spec;
			d.Specialties.push_back(spec);
		}
		d.liber_de_la = 8;

		Doctors.push_back(d);
	}

	//Afisare probleme sortate in pq
	cout << "Afisare pq:\n";
	cout << Problems.size() << "\n";
	while (!Problems.empty())
	{
		Problem p = Problems.top();
		cout << p.Name << " " << p.SpecialtyNeeded << " " << p.arrival_time << " " << p.duration_of_treatment << " " << p.priority << "\n";
		Problems.pop();
	}

	//Rezolvarea problemei...
	
	//se mai putea si cu map de specializari 

	return 0;
}