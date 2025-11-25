#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <syncstream>
#include <string>

using namespace std;

const int SLOW_TIME = 7;
const int QUICK_TIME = 1;

string run_timed_task(const string& name, int seconds) {
    this_thread::sleep_for(chrono::seconds(seconds));
    osyncstream(cout) << name << "\n";
    return name;
}

void work() {
    auto start_time = chrono::steady_clock::now();

    future<string> fA2 = async(launch::async, run_timed_task, "A2", SLOW_TIME);
    future<string> fB2 = async(launch::async, run_timed_task, "B2", SLOW_TIME);

    run_timed_task("A1", QUICK_TIME);
    run_timed_task("A3", QUICK_TIME);
    run_timed_task("A4", QUICK_TIME);
   
    fA2.get();
    run_timed_task("B1", QUICK_TIME);

    fB2.get();
    run_timed_task("C", QUICK_TIME); 

    auto end_time = chrono::steady_clock::now();
    chrono::duration<double> elapsed_seconds = end_time - start_time;
    osyncstream(cout) << "Total execution time: " << elapsed_seconds.count() << " seconds" << endl;
    osyncstream(cout) << "Work is done!" << endl;
  
}

int main() {
     work();
     return 0;
}