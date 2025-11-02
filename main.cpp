#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
using namespace std; 
using namespace std::chrono;

int main() {
    string code_lst[20000];
    string curr_code;
    ifstream file("codes.txt");

    int reading[3];
    int sorting[3];
    int inserting[3];
    int deleting[3];
    set<string> set1;
    vector<string> vec1;
    list<string> lst1;

    for(int i = 0; getline(file, curr_code); i++) {
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

    // sorting test
    // set sorting
    sorting[0] = -1;

    // vector sorting
    start = high_resolution_clock::now();
    sort(vec1.begin(), vec1.end());
    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start);
    sorting[1] = duration.count();

    // list sorting
    start = high_resolution_clock::now();
    lst1.sort();
    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start);
    sorting[2] = duration.count();

    // insertion
    // set insert
    start = high_resolution_clock::now();
    set1.insert("TESTCODE");
    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start);
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
    
    // delete race
    // set delete
    start = high_resolution_clock::now();
    cnt = 1;
    for(auto i = set1.begin(); i != set1.end(); i++) {
        if (cnt == 10001) {
            set1.erase(i);
            break;
        }
        cnt += 1;
    }
    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start);
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

    //output
    cout << "Operation    Vector    List    Set" << endl;
    cout << "Read         " << reading[1] << "      " << reading[2] << "    " << reading[0] << endl;
    cout << "Sort         " << sorting[1] << "      " << sorting[2] << "    " << sorting[0] << endl;
    cout << "Insert       " << inserting[1] << "        " << inserting[2] << "     " << inserting[0] << endl;
    cout << "Delete       " << deleting[1] << "        " << deleting[2] << "     " << deleting[0] << endl;
    return 0;
}