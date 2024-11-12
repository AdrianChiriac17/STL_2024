#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Doctor
{
    string drId;
    string speciality;
};

struct Patient
{
    string problem;
    string speciality;
};


int main()
{
    ifstream inFile("input.txt");

    int no_problems, no_doctors;
    string name, speciality;
    vector<Patient>injuries;
    vector<Doctor>doctors;


    inFile >> no_problems;

    for (int i = 0; i < no_problems; i++)
    {
        inFile >> name;
        inFile >> speciality;
        injuries.push_back({name, speciality});
        //cout << injuries[i].problem << " " << injuries[i].speciality << " " << i << "\n";
    }

    inFile >> no_doctors;
    //cout << "\n";
    for (int i = 0; i < no_doctors; i++)
    {
        inFile >> name;
        inFile >> speciality;
        doctors.push_back({name, speciality});
        //cout << doctors[i].drId<< " " << doctors[i].speciality << " " << i << "\n";
    }
    

    for (int i = 0; i < no_problems; i++)
    {
        string curr_problem = injuries[i].problem;
        string curr_target = injuries[i].speciality;

        auto it = find_if(doctors.begin(), doctors.end(), [&curr_target](const Doctor& d) {
            return d.speciality == curr_target;
            });

        if (it != doctors.end())
        {
            cout << curr_problem << " Acceptat\n";
        }
        else
        {
            cout << curr_problem << " Respins\n";
        }
    }

    return 0;
}