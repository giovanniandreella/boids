// globals.h
#ifndef GLOBALS_H
#define GLOBALS_H

const double MAX_V{4.0};                // maximum speed
const double MIN_V{0.0};                // minimum speed
const double MIN_X{-200.0};             // minimum x coordinate
const double MIN_Y{-200.0};             // minimum y coordinate
const double MAX_X{200.0};              // maximum x coordinate
const double MAX_Y{200.0};              // maximum y coordinate

const double turnfactor{0.5};
const double avoidfactor{0.2};
const double alignfactor{0.2};
const double centeringfactor{0.1};
const double dt{1.0};                   // time interval between two positions
const double d_sep{10.0};               // safety distance
const double d_ca{18.0};                // visibility distance
const int MAX_BOIDS{300};               // maximum number of boids
const int iterations{500};              // simulation iterations

#endif