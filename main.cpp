#include <bits/stdc++.h>
#include <chrono> 
#include "sol.hpp"

using namespace std::chrono;
using namespace std;

/*
5 5 60
4
G1 150
G2 70
S1 60
S2 150
2
4 5
2
CSE_3 4 2 100 1
CSD1 f1 0 3 1 60 0
CSD2 f2 0 3 1 60 0
CSD3 f3 0 3 1 60 0
CSD4 f4 1 1 0 180 1 LAB_1
CSED_3 4 2 100 0
CSD1 f1 0 3 1 60 0
CSD2 f5 0 3 1 60 0
CSD3 f3 0 3 1 60 0
CSD4 f4 1 1 0 180 1 LAB_1
*/


int main(){

    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    auto start = high_resolution_clock::now();

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
     

    Solution* sol = new Solution();
    sol->setSlots();
    sol->setRooms();
    sol->setLunch();
    sol->setSubjects();

    bool success = false;
    int max_iter = 100;

    vector<int> successfullIterations;
    
    while(max_iter>0)
    {
        cout<<"\n\n---------------TRIES LEFT: "<<max_iter<<"--------------------\n\n";
        sol->resetData();
        sol->seed = time(NULL) + max_iter;
        success = sol->runBestFit();

        if(success)
            successfullIterations.push_back(max_iter);

        cout<<"\n\nGarbage: "<<sol->garbage.size();
        for(auto sub:sol->garbage)
        {
            sub->printDetails();
        }

        sol->T_WIDTH = 35;

        sol->printTable(max_iter);
        sol->makeFacultyView(max_iter);
        sol->makeClassView(max_iter);
        sol->makeRoomView(max_iter);

        max_iter--;
    }
    
    cout<<"\n"<<setw(50)<<setfill('x')<<""<<"\nSUCCESFULL ITERATIONS: ";
    for(auto s:successfullIterations)
        cout<<"( "<<s<<" ) ";

    auto stop = high_resolution_clock::now(); 
    double duration = duration_cast<nanoseconds>(stop - start).count(); 
    duration *= 1e-9;
    cout << "\nTime taken by program is : " << fixed  
         << duration << setprecision(9); 
    cout << " sec" << endl;

    return 0;
}
