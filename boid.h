// boid.h

#ifndef BOID_H
#define BOID_H

#include <fstream>

// pre-declaration of class Flock to avoid compiling errors
class Flock;

class Boid{
private:
    double x_;      
    double y_;
    double vx_;
    double vy_;

public:
    Boid();
    Boid(double, double, double, double);
    Boid(const Boid&);
    double x() const;
    double y() const;
    double vx() const;
    double vy() const;
    double v() const;
    void update();
    void separation();
    void alignement();
    void cohesion();
    void edges();
    double distance(Boid&) const;
    void write_in_file(std::ofstream&);
};

#endif