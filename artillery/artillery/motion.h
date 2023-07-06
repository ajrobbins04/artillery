/***********************************************************************
 * Header File:
 *    Motion : The representation of a derived position
 *    object in x, y coordinates. These coordinates
 *    change with each new callback loop, giving
 *    them movement.
 * Summary:
 *    Everything we need to know about the movement
 *    of objects on the screen.
 ************************************************************************/

#ifndef motion_h
#define motion_h

#include "position.h"
#include "angle.h"
#include <math.h>

class Motion : public Position
{
public:
	Motion()
	{
	   setMetersX(0);
	   setMetersY(0);
	}

	// non-default constructor
	Motion(const double x, const double y)
	{
		setMetersX(x);
		setMetersY(y);
	}
 
	// adds the force of resistance into motion object's travel path
	void add(const Motion resistance)
	{
		setMetersX(resistance.getMetersX() + getMetersX());
		setMetersY(resistance.getMetersY() + getMetersY());
	}
   
	 
	// will help calculate velocity and acceleration
	double getRateOfChange() const { return sqrt(pow(getMetersX(), 2) + pow(getMetersY(), 2)); }
 
	
	// adjusts the movement of a Motion object
	void setMovement(const double rate, const Angle angle)
	{
		setMetersX(cos(angle.getRadians()) * rate);
		setMetersY(sin(angle.getRadians()) * rate);
	}
	
   Angle getDirection() const;
   
};

/***********************************************************
 * MOTION :: GET DIRECTION
 * Returns the angle that helps determine
 * the direction that a Motion object is traveling
**********************************************************/
Angle Motion::getDirection() const {

  Angle angle;
  angle.setRadians(atan2(getMetersY(), getMetersX()));

  return angle;
}
 
#endif /* motion_h */

#endif /* motion_h */
