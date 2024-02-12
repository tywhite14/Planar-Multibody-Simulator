#pragma once

#include "Vect2d.h"

Vect2d rot(Vect2d vecIn, double angle);
Vect2d local2global(Vect2d vecIn, double angle);
Vect2d global2local(Vect2d vecIn, double angle);
