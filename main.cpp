#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <tuple>
#include <algorithm>
#include <iomanip>
using namespace std; 
using namespace std::chrono;

tuple<int, int, int> runReading();
tuple<int, int, int> runSorting();
tuple<int, int, int> runInserting();
tuple<int, int, int> runDeleting();

int main() {
    // first row of each array is for storing the latest race results
    // second row of each array stores cummulative results
    int reading[2][3];
    int sorting[2][3];
    int inserting[2][3];
    int deleting[2][3];

    //set initial sums to 0
    reading[1][0] = 0;
    reading[1][1] = 0;
    reading[1][2] = 0;
    sorting[1][0] = 0;
    sorting[1][1] = 0;
    sorting[1][2] = 0;
    inserting[1][0] = 0;
    inserting[1][1] = 0;
    inserting[1][2] = 0;
    deleting[1][0] = 0;
    deleting[1][1] = 0;
    deleting[1][2] = 0;

    // run tests
    for(int i = 0; i < 15; i++) {
        // run reading
        auto [temp1, temp2, temp3] = runReading();
        reading[0][0] = temp1;
        reading[1][0] += reading[0][0];
        reading[0][1] = temp2;
        reading[1][1] += reading[0][1];
        reading[0][2] = temp3;
        reading[1][2] += reading[0][2];
        
        // run sorting
        auto [temp1b, temp2b, temp3b] = runSorting();
        sorting[0][0] = temp1b;
        sorting[1][0] += sorting[0][0];
        sorting[0][1] = temp2b;
        sorting[1][1] += sorting[0][1];
        sorting[0][2] = temp3b;
        sorting[1][2] += sorting[0][2];
        
        // run inserting
        auto [temp1c, temp2c, temp3c] = runInserting();
        inserting[0][0] = temp1c;
        inserting[1][0] += inserting[0][0];
        inserting[0][1] = temp2c;
        inserting[1][1] += inserting[0][1];
        inserting[0][2] = temp3c;
        inserting[1][2] += inserting[0][2];

        // run deleting
        auto [temp1d, temp2d, temp3d] = runDeleting();
        deleting[0][0] = temp1d;
        deleting[1][0] += deleting[0][0];
        deleting[0][1] = temp2d;
        deleting[1][1] += deleting[0][1];
        deleting[0][2] = temp3d;
        deleting[1][2] += deleting[0][2];
    }

    //output
    cout << "Operation Vector   List    Set" << endl;
    cout << setw(9) << "Read" << setw(7) << reading[1][1] / 15 << setw(7)  << reading[1][2] / 15 << setw(7)  << reading[1][0] / 15 << endl;
    cout << setw(9)  << "Sort" << setw(7)  << sorting[1][1] / 15 << setw(7)  << sorting[1][2] / 15 << setw(7)  << sorting[1][0] / 15 << endl;
    cout << setw(9)  << "Insert" << setw(7)  << inserting[1][1] / 15 << setw(7)  << inserting[1][2] / 15 << setw(7)  << inserting[1][0] / 15 << endl;
    cout << setw(9)  << "Delete" << setw(7)  << deleting[1][1] / 15 << setw(7)  << deleting[1][2] / 15 << setw(7)  << deleting[1][0] / 15 << endl;
    return 0;
}

//function runs race to see how long each type takes to read a set of codes
tuple<int, int, int> runReading() {
    
    string code_lst[20000];
    string curr_code;
    ifstream file("codes.txt");

    int reading[3];
    set<string> set1;
    vector<string> vec1;
    list<string> lst1;

    for(int i = 0; file >> curr_code; i++) {
        code_lst[i] = curr_code;
    }

    // reading  test
    // set reading
    auto start = high_resolution_clock::now();
    for(int i = 0; i < 20000; i++) {
        set1.insert(code_lst[i]);
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    reading[0] = duration.count();

    // vector reading
    start = high_resolution_clock::now();
    for(int i = 0; i < 20000; i++) {
        vec1.push_back(code_lst[i]);
    }
    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start);
    reading[1] = duration.count();

    // list reading
    start = high_resolution_clock::now();
    for(int i = 0; i < 20000; i++) {
        lst1.push_back(code_lst[i]);
    }
    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start);
    reading[2] = duration.count();
    tuple<int, int, int> tup = {reading[0], reading[1], reading[2]};
    return tup;
}

//function runs race to see how long each type takes to sort a set of codes
tuple<int, int, int> runSorting() {
    string code_lst[20000];
    string curr_code;
    ifstream file("codes.txt");

    int sorting[3];
    set<string> set1;
    vector<string> vec1;
    list<string> lst1;

    for(int i = 0; file >> curr_code; i++) {
        code_lst[i] = curr_code;
    }

    //fill set, vec, and list
    for(int i = 0; i < 20000; i++) {
        set1.insert(code_lst[i]);
    }
    for(int i = 0; i < 20000; i++) {
        vec1.push_back(code_lst[i]);
    }
    for(int i = 0; i < 20000; i++) {
        lst1.push_back(code_lst[i]);
    }

    // sorting test
    // set sorting
    sorting[0] = -1;

    // vector sorting
    auto start = high_resolution_clock::now();
    sort(vec1.begin(), vec1.end());
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    sorting[1] = duration.count();

    // list sorting
    start = high_resolution_clock::now();
    lst1.sort();
    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start);
    sorting[2] = duration.count();
    tuple<int, int, int> tup = {sorting[0], sorting[1], sorting[2]};
    return tup;
}

//function runs race to see how long each type takes to insert into a set of codes
tuple<int, int, int> runInserting() {
    
    string code_lst[20000];
    string curr_code;
    ifstream file("codes.txt");

    int inserting[3];
    set<string> set1;
    vector<string> vec1;
    list<string> lst1;

    //fill set, vec, and list
    for(int i = 0; i < 20000; i++) {
        set1.insert(code_lst[i]);
    }
    for(int i = 0; i < 20000; i++) {
        vec1.push_back(code_lst[i]);
    }
    for(int i = 0; i < 20000; i++) {
        lst1.push_back(code_lst[i]);
    }

    for(int i = 0; file >> curr_code; i++) {
        code_lst[i] = curr_code;
    }

    // insertion
    // set insert
    auto start = high_resolution_clock::now();
    set1.insert("TESTCODE");
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    inserting[0] = duration.count();

    // vector insert
    start = high_resolution_clock::now();
    vec1.insert(vec1.begin()+10000, "TESTCODE");
    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start);
    inserting[1] = duration.count();

    // list insert
    start = high_resolution_clock::now();
    int cnt = 1;
    for(auto i = lst1.begin(); i != lst1.end(); i++) {
        if (cnt == 10000) {
            lst1.insert(i, "TESTCODE");
            break;
        }
        cnt += 1;
    }
    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start);
    inserting[2] = duration.count();
    tuple<int, int, int> tup = {inserting[0], inserting[1], inserting[2]};
    return tup;
}

//function runs race to see how long each type takes to delete middle value of a set of codes
tuple<int, int, int> runDeleting() {
    
    string code_lst[20000];
    string curr_code;
    ifstream file("codes.txt");

    int deleting[3];
    set<string> set1;
    vector<string> vec1;
    list<string> lst1;

    for(int i = 0; file >> curr_code; i++) {
        code_lst[i] = curr_code;
    }
    
    //fill set, vec, and list
    for(int i = 0; i < 20000; i++) {
        set1.insert(code_lst[i]);
    }
    for(int i = 0; i < 20000; i++) {
        vec1.push_back(code_lst[i]);
    }
    for(int i = 0; i < 20000; i++) {
        lst1.push_back(code_lst[i]);
    }

    // delete race
    // set delete
    auto start = high_resolution_clock::now();
    int cnt = 1;
    auto i = set1.begin();
    advance(i, 10000);
    set1.erase(i);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    deleting[0] = duration.count();

    // vector delete
    start = high_resolution_clock::now();
    vec1.erase(vec1.begin()+10001);
    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start);
    deleting[1] = duration.count();

    // list delete
    start = high_resolution_clock::now();
    cnt = 1;
    for(auto i = lst1.begin(); i != lst1.end(); i++) {
        if (cnt == 10001) {
            lst1.erase(i);
            break;
        }
        cnt += 1;
    }
    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start);
    deleting[2] = duration.count();
    tuple<int, int, int> tup = {deleting[0], deleting[1], deleting[2]};
    return tup;
}