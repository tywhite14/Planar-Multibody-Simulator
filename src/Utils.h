#pragma once

#include "Vect2d.h"

constexpr double PI = 3.1415926;

Vect2d rot(Vect2d vecIn, double angle);
Vect2d local2global(Vect2d vecIn, double angle);
Vect2d global2local(Vect2d vecIn, double angle);
