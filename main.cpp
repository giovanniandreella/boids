// main.cpp
#include "boid.h"
#include "flock.h"
#include "globals.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <condition_variable>
using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::ofstream;
using std::thread;
using std::mutex;
using std::condition_variable;
using std::unique_lock;

// global variables
Flock f(300);
int count_moves{0};
int boids_assigned{0};
bool writing_finished{false};
std::mutex mtx;
std::condition_variable canWrite;
std::condition_variable canMove;
std::condition_variable startSimulation;

// functions executed by threads
void move(int);
void write();

int main(){
    // boid simulation threads
    vector<thread> threads;
    
    int n{f.boidsNumber()};
    for(int i{0}; i < n; ++i){
        threads.push_back(thread{move, i});
    }
    
    // write thread
    thread writer(write);
    
    for(vector<thread>::iterator pos = threads.begin(); pos != threads.end(); ++pos){
		pos -> join();
    }
    writer.join();

    return 0;
}

void move(int index){
    // waiting for every thread to have a boid assigned
    {
        unique_lock<mutex> mlock(mtx);
        ++boids_assigned;
        if(boids_assigned < f.boidsNumber())
            startSimulation.wait(mlock);
        else
            startSimulation.notify_all();
    }

    // simulation of the boid
    while(!writing_finished){
        f.get_boid(index).separation();
        f.get_boid(index).alignement();
        f.get_boid(index).cohesion();
        // critical section that updates the coordinates and signal whether to proceed with the file writing
        {
            unique_lock<mutex> mlock(mtx);    
            f.get_boid(index).update();
            ++count_moves;

            if(count_moves >= f.boidsNumber())
                canWrite.notify_one();

            // every boid waits for the writing to be done, since they are going to have similar execution times
            canMove.wait(mlock);
        }
    }
    return;
}

void write(){
    // creation of a local variable ofstream in order to write in a file
    std::ofstream file("coordinates.txt");
    if(!file.is_open()){
        cerr << "ERROR - Cannot open file." << endl;
        exit(EXIT_FAILURE);
    }

    // screen edges written on the first line of the file
    file << MIN_X << " " << MAX_X << " " << MIN_Y << " " << MAX_Y << endl;

    for(int i{0}; i < iterations; ++i){
        // critical section that writes coordinates in the file
        {
            unique_lock<mutex> mlock(mtx);
            // waiting for every boid to update at least once their own coordinates
            while(count_moves < f.boidsNumber())
                canWrite.wait(mlock);
                
            f.write_in_file(file);
            count_moves = 0;
            canMove.notify_all();
        }
    }
    writing_finished = true;
    file.close();
    return;
}