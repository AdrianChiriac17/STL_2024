#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include<set>

using namespace std;


struct problem
{
    string id, speciality;
    int arrivalTime, cureTime, priority;
};

struct doctor {
    string id;
    int nrSpecialities, freeAfter = 9;
    set<string> specialities;
    vector<pair<string, int>> cured;
};

int main()
{
    ifstream inFile("input2.txt");

    int noProblem, noDoctors;


    inFile >> noProblem;
    vector<problem> problemList;

    for (int i = 0; i < noProblem; i++)
    {
        struct problem prb;
        inFile >> prb.id;
        inFile >> prb.speciality;
        inFile >> prb.arrivalTime;
        inFile >> prb.cureTime;
        inFile >> prb.priority;
        //cout << prb.id << ' ' << prb.speciality << '\n';
        problemList.push_back(prb);
    }

    inFile >> noDoctors;

    vector<doctor> doctorList;

    for (int i = 0; i < noDoctors; i++)
    {
        doctor doc;
        inFile >> doc.id;
        inFile >> doc.nrSpecialities;

        for (int i = 0; i < doc.nrSpecialities; i++)
        {
            string speciality;
            inFile >> speciality;
            doc.specialities.insert(speciality);
        }
        // cout << doc.id << ' ' << doc.nr_specialities << '\n';
        doctorList.push_back(doc);
    }

    sort(problemList.begin(), problemList.end(), [](auto& prb1, auto& prb2)
        {
            if (prb1.arrivalTime == prb2.arrivalTime)
                return prb1.priority > prb2.priority;
            return prb1.arrivalTime < prb2.arrivalTime;
        });

    //DEBUG: problem list after sorting
    /*
    for (auto problem : prb_list)
    {
        cout << problem.arrivalTime << " " << problem.speciality << " si prioritate " << problem.priority << endl;
    }
    cout << endl;
    */

    for (auto& currProblem : problemList)
    {
        auto doctorWhoSolves = find_if(doctorList.begin(), doctorList.end(), [&](doctor doc) {
            return doc.specialities.contains(currProblem.speciality) && doc.freeAfter <= currProblem.arrivalTime && doc.freeAfter + currProblem.cureTime <=17;
            });
        if (doctorWhoSolves != doctorList.end())
        {
            ///DEBUG: affirmative finding of doctor who can solve the problem
            //cout << "s-a gasit doctorul" << doctor->id << "si rezolva problema " << prb.id << endl;
            doctorWhoSolves->freeAfter += currProblem.cureTime;
            doctorWhoSolves->cured.push_back( pair<string, int>(currProblem.id, currProblem.arrivalTime) );
        }
    }
    for (auto& doctor : doctorList)
    {
        if (!doctor.cured.empty())
        {
        cout << doctor.id << " ";
        for (auto& curedProblem : doctor.cured)
        {
            cout << curedProblem.first << " " << curedProblem.second << " ";
        }
        cout << endl;
        }
    }

    return 0;
}