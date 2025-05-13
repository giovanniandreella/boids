// boid.cpp
#include "boid.h"
#include "flock.h"
#include "globals.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
using std::endl;
using std::cerr;
using std::cout;

// declaration of a global variable of type Flock
extern Flock f;

// default constructor
Boid::Boid(){
    // using uniform distributions to generate random values within given ranges
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<double> x_distribution(MIN_X, MAX_X);
    std::uniform_real_distribution<double> y_distribution(MIN_Y, MAX_Y);
    std::uniform_real_distribution<double> v_distribution(MIN_V, MAX_V);
    std::uniform_int_distribution<int> sign(-1, 1);
    x_ = x_distribution(rng);
    y_ = y_distribution(rng);
    vx_ = sign(rng) * v_distribution(rng);
    vy_ = sign(rng) * v_distribution(rng);
}

// constructor
Boid::Boid(double xx, double yy, double vvx, double vvy){
    x_ = xx;
    y_ = yy;
    vx_ = vvx;
    vy_ = vvy;
}

// copy constructor
Boid::Boid(const Boid &other){
    x_ = other.x_;
    y_ = other.y_;
    vx_ = other.vx_;
    vy_ = other.vy_;
}

// returns x coordinate
double Boid::x() const{
    return x_;
}

// returns y coordinate
double Boid::y() const{
    return y_;
}

// returns x speed
double Boid::vx() const{
    return vx_;
}

// returns y speed
double Boid::vy() const{
    return vy_;
}

// returns speed
double Boid::v() const{
    return sqrt(vx_ * vx_ + vy_ * vy_);
}

// writes the position of a boid in a file
void Boid::write_in_file(std::ofstream &tmp){
    tmp << x_ << " " << y_ << " ";
    return;
}

// updates the position with the current speed
void Boid::update(){
    x_ = x_ + vx_ * dt;
    y_ = y_ + vy_ * dt;
    return;
}

// returns the distance between the current boid and a given one
double Boid::distance(Boid &b) const{
    return sqrt(pow(x_ - b.x(), 2) + pow(y_ - b.y(), 2));
}

// separation rule
void Boid::separation(){
    double close_dx{0};
    double close_dy{0};

    for(int i{0}; i < f.boidsNumber(); ++i){
        if(distance(f.get_boid(i)) < d_sep){
            close_dx += x_ - f.get_boid(i).x();
            close_dy += y_ - f.get_boid(i).y();
        }
    }
    vx_ += close_dx * avoidfactor;
    vy_ += close_dy * avoidfactor;

    edges();
    return;
}

// alignement rule
void Boid::alignement(){
    double xvel_avg{0};
    double yvel_avg{0};
    double close_boids{0};

    for(int i{0}; i < f.boidsNumber(); ++i){
        if(distance(f.get_boid(i)) < d_ca){
            xvel_avg += f.get_boid(i).vx();
            yvel_avg += f.get_boid(i).vy();
            close_boids++;
        }
    }

    if(close_boids > 0){
        xvel_avg = xvel_avg / close_boids;
        yvel_avg = yvel_avg / close_boids;

        vx_ = vx_ + (xvel_avg - vx_) * alignfactor;
        vy_ = vy_ + (yvel_avg - vy_) * alignfactor;
    }

    edges();
    return;
}

// cohesion rule
void Boid::cohesion(){
    double xpos_avg{0};
    double ypos_avg{0};
    double neighboring_boids{0};

    for(int i{0}; i < f.boidsNumber(); ++i){
        if(distance(f.get_boid(i)) < d_ca){
            xpos_avg += f.get_boid(i).x();
            ypos_avg += f.get_boid(i).y();
            neighboring_boids++;
        }
    }

    if(neighboring_boids > 0){
        xpos_avg = xpos_avg / neighboring_boids;
        ypos_avg = ypos_avg / neighboring_boids;

        vx_ = vx_ + ((xpos_avg - x_) * centeringfactor) / dt;
        vy_ = vy_ + ((ypos_avg - y_) * centeringfactor) / dt;
    }

    edges();
    return;
}

// controls whether the boid is inside the edges of the screen and adjusts the speed within the range
void Boid::edges(){
    // edges controlling
    if (x_ < (MIN_X + d_ca))
        vx_ = vx_ + turnfactor;
    if (x_ > (MAX_X - d_ca))
        vx_ = vx_ - turnfactor;
    if (y_ < (MIN_Y + d_ca))
        vy_ = vy_ + turnfactor;
    if (y_ > (MAX_Y - d_ca))
        vy_ = vy_ - turnfactor;

    // speed adjusting
    if(v() >= MAX_V){
        vx_ = (vx_ / v()) * MAX_V;
        vy_ = (vy_ / v()) * MAX_V;
    }
    if(v() < MIN_V){
        vx_ = (vx_ / v()) * MIN_V;
        vy_ = (vy_ / v()) * MIN_V;
    }

    return;
}