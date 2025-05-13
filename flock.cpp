// flock.cpp
#include "flock.h"
#include "globals.h"
#include <iostream>
#include <fstream>
using std::cerr;
using std::endl;
using std::cout;

// default constructor
Flock::Flock(){
    for(int i{0}; i < MAX_BOIDS; ++i)
        flock_.push_back(Boid());
}

// constructor
Flock::Flock(int n){
    if(n <= 0){
        cerr << "ERROR - Negative value in flock members number." << endl;
        exit(EXIT_FAILURE);
    }
    
    if(n > MAX_BOIDS){
        cerr << "WARNING - Too many boids in the flock. Set the number to maximum (" << MAX_BOIDS << ")." << endl;
        boidsNum_ = MAX_BOIDS;
    }
    else boidsNum_ = n;

    for(int i{0}; i < boidsNum_; ++i)
        flock_.push_back(Boid());
}

// writes every boid's coordinates in a file
void Flock::write_in_file(std::ofstream &tmp){
    if(!tmp.is_open()){
        cerr << "ERROR - Cannot open .txt file." << endl;
        exit(EXIT_FAILURE);
    }
    else{
        for(int i{0}; i < boidsNum_; ++i){
            flock_.at(i).write_in_file(tmp);
        }
        tmp << endl;
    }
    return;
}

// updates the position of every boid in the flock
void Flock::update(){
    for(int i{0}; i < boidsNum_; ++i)
        flock_.at(i).update();
    return;
}

// returns the number of boids in the flock
int Flock::boidsNumber() const{
    return boidsNum_;
}

// returns the i-th boid of the flock
Boid& Flock::get_boid(int n){
    return flock_.at(n);
}