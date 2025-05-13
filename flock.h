// flock.h
#ifndef FLOCK_H
#define FLOCK_H

#include "boid.h"
#include <vector>

class Flock{
private:
    int boidsNum_;
    std::vector<Boid> flock_;

public:
    Flock();
    Flock(int);
    void write_in_file(std::ofstream&);
    void update();
    int boidsNumber() const;
    Boid& get_boid(int);
};

#endif