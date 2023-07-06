/***********************************************************************
 * Header File:
 *    Angle
 * Author:
 *    Amber Robbins
 * Summary:
 *    A class to encompass the needs of angles in the program.
 ************************************************************************/

#ifndef angle_h
#define angle_h

#include "constants.h"
#include <cmath>
#include <iostream>

class Angle
{
public:
	// default constructor
	Angle() { setRadians(0); }

	// non-default constructor
	Angle(const double radians) { setRadians(radians); }

	// copy constructor
	Angle(const Angle &angle) { setRadians(angle.getRadians()); }

	// getters
	double getDegrees() const { return radians * 180 / PI; }
	double getRadians() const { return radians; }

	// setters
	void setDegrees(const double degrees) { setRadians(degrees * PI / 180); }
	void setRadians(const double radians)
	{
		if (compare(radians, 0))
			this->radians = 0;
		else if (compare(radians, PI / 6))
			this->radians = (PI / 6);
		else if (compare(radians, PI / 4))
			this->radians = (PI / 4);
		else if (compare(radians, PI / 3))
			this->radians = (PI / 3);
		else if (compare(radians, PI / 2))
			this->radians = (PI / 2);
		else
			this->radians = radians;
	}

	void addRadians(const double radians) { setRadians(getRadians() + radians); }
	void display() const;
	
private:
	bool compare(const double firstRad, const double secondRad) const;
 
protected:
	double radians;
	
};

/**********************************************
 * ANGLE :: COMPARE
 * Compares two radian values to
 * see if they are the same
  **********************************************/
bool Angle::compare(const double firstRad, const double secondRad) const
{
	const double PRECISION = 0.001;
	
	if (fabs(firstRad - secondRad) < PRECISION)
		return true; // they are the same
	
	return false;  // they are not same
}

/**********************************************
 * ANGLE :: DISPLAY
 * Displays Angle object in degrees
 * and radians.
  **********************************************/
void Angle::display() const
{
  std::cout.precision(2);
  std::cout << std::fixed;
  std::cout << "Degrees: " << getDegrees() << "deg, Radians: " << getRadians()
			<< "rad\n";
  std::cout.clear();
}


#endif /* angle_h */
