/***********************************************************************
 * Header File:
 *    Drag
 * Author:
 *    Amber Robbins, Eddy Sosa Lora, and Mosiah Hazen
 * Summary:
 *    Contains the calculation of drag resistance incurred on
 *    the fired ammo. This calculation is based on a number
 *    of environmental factors plus the velocity and altitude
 *    of ammo. All these things continually change in value
 *    as the ammo advances.
 ************************************************************************/

#ifndef drag_h
#define drag_h

#include "ammunition.h"
#include "position.h"
#include "data/data.h"
#include <iostream>

class Drag
{
public:
  Drag(Ammunition* ammo)
   {
	 //  Sets pAmmo to an instance of Ammunition so
	 //  we can access its attributes to do calculations.
	 setAmmunition(ammo);
	 updateFactors();
   }
   
   void setAmmunition(Ammunition *ammunition) { pAmmo = ammunition; }
   Motion getAcceleration();
   double getDrag()
   {
	 updateFactors();
	 return drag;
   }
   
   void displayDrag();
   
   
private:
   void   computeDrag(const double coefficient, const double density);
   double computeDensity(     const double altitude    )  const;
   double computeSpeedOfSound(const double altitude    )  const;
   double computeCoefficient( const double velocity,
							  const double speedOfSound)  const;
   double computeMidValue(const double x, const double x1, const double y1,
						  const double x2, const double y2) const;
   void updateFactors();
  
   
   double drag;
   Ammunition *pAmmo;
	
};

/**********************************************
 * DRAG :: GET ACCELERATION
 * Returns an instance of point that
 * is acceleration.
  **********************************************/
Motion Drag::getAcceleration()
{
   double mass = pAmmo->getMass();
   assert(mass > 0); // ammo cannot be weightless
	
   double resistance = getDrag() / mass;

   Angle dragAngle(pAmmo->getVelocity().getDirection());
   dragAngle.addRadians(PI);

   Motion acceleration;
   acceleration.setMovement(resistance, dragAngle);
   return acceleration;
  
}

/*********************************************
 * DRAG :: COMPUTE DENSITY
 * Calculates density, which is
 * determined based on altitude.
 * *******************************************/
double Drag::computeDensity(const double altitude) const
{
   double density = densityData.back().output;

   for (int i = 0; i < densityData.size() - 1; i++)
   {
	  
	  if (altitude == densityData[i].input)
	  {
		 // every .input altitude has a .output density
		 density = densityData[i].output;
		 assert(density > 0.0000186 && density < 1.226);
		 break;
	  }
	  // try to find two values where altitude
	  // qualifies as their midpoint
	  else if (altitude > densityData[i].input &&
			   altitude < densityData[i + 1].input)
	  {
		 assert (altitude > 0 || altitude < 21);
		 
		 // an estimated density can be computed now that its
		 // corresponding altitude falls between two known values
		 density = computeMidValue(altitude, densityData[i].input, densityData[i].output,
								 densityData[i + 1].input, densityData[i + 1].output);
		 
		 assert(density < densityData[i].output && density > densityData[i+1].output);
		 std::cout << "density: " << density << std::endl;
		 break;
	  }
	  
   }
   return density;
}

/**************************************************
 * DRAG :: COMPUTE SPEED OF SOUND
 * Computes speed of sound, which is
 * determined based on the ammo's altitude
 * *************************************************/
double Drag::computeSpeedOfSound(const double altitude) const
{
   // as the altitude rises the speed of sound
   // decreases, and vice-versa
   double speedOfSound = soundData.back().output;

   for (int j = 0; j < soundData.size() - 1; j++)
   {
	  // every .input altitude has a .output speedOfSound
	  if (altitude == soundData[j].input)
	  {
		 speedOfSound = soundData[j].output;
		 assert(speedOfSound >= 324 && speedOfSound <= 340);
		 break;
	  }
	  // try to find two values where altitude
	  // qualifies as their midpoint
	  else if (altitude > soundData[j].input &&
				 altitude < soundData[j + 1].input)
	  {
		 assert(j > 0 || j < 15);
		 
		 // an estimated speedOfSound can be computed now that its
		 // corresponding altitude falls between two known values
		 speedOfSound = computeMidValue(altitude, soundData[j].input,
									  soundData[j].output,
									  soundData[j + 1].input,
									  soundData[j + 1].output);
		 // 11-13 share same output
		 if (j < 11 || j == 14)
			assert((speedOfSound > soundData[j].output && speedOfSound < soundData[j+1].output)
				   || (speedOfSound < soundData[j].output && speedOfSound > soundData[j+1].output));
		 else
			assert(speedOfSound == 295);
		 
		 std::cout << "speedOfSound: " << speedOfSound << std::endl;
		 break;
	  }
	  
   }
   return speedOfSound;
}

/*********************************************
 * DRAG :: COMPUTE COEFFICIENT
 * Calculates the drag coefficient,
 * which is determined based on
 * velocity and speed of sound.
 * *******************************************/
double Drag::computeCoefficient(const double velocity,
								const double speedOfSound) const
{
   double speed = velocity / speedOfSound;

   // the ammo's drag coefficient is determined
   // based on the speed the ammo travels
   double coefficient = coefficientData.back().output;

   for (int k = 0; k < coefficientData.size() - 1; k++)
   {
	  if (speed == coefficientData[k].input)
	  {
		 coefficient = coefficientData[k].output;
		 assert(coefficient > 0.1628 && coefficient < 0.2657);
		 break;
	  }
	  // try to find two values where speed
	  // qualifies as their midpoint
	  else if (speed > coefficientData[k].input &&
			   speed < coefficientData[k + 1].input)
	  {
		 assert(k > 0 || k < 17);
		 coefficient = computeMidValue(speed, coefficientData[k].input,
									   coefficientData[k].output,
									   coefficientData[k + 1].input,
									   coefficientData[k + 1].output);
		 
		 assert(coefficient > coefficientData[k].output && coefficient < coefficientData[k+1].output
				|| coefficient < coefficientData[k].output && coefficient > coefficientData[k+1].output);
		 
		 std::cout << "coefficient: " << coefficient << std::endl;
		 break;
	  }
	  
   }
   return coefficient;
}

/*********************************************
 * DRAG :: COMPUTE MID VALUE
 * Calculates an estimate of an unknown
 * value based on known values using
 * the physics process of interpolation
 * *******************************************/
double Drag::computeMidValue(const double x, const double x1, const double y1,
					 const double x2, const double y2) const
{
   assert(x1 >= 0 && y1 >= 0);
   assert((x > x1 && x < x2 ) || (x < x1 && x > x2));
   
   return y1 + (x - x1) * (y2 - y1) / (x2 - x1);
}

/*******************************************************
 * DRAG :: UPDATE FACTORS
 * Advances the drag class with new values
 * for the various environmental factors based
 * on the bullets current location and velocity.
 * *****************************************************/
void Drag::updateFactors()
{
   double altitude = pAmmo->getPosition().getMetersY();
   double velocity = pAmmo->getVelocity().getRateOfChange();

   double density = computeDensity(altitude);
   double speedOfSound = computeSpeedOfSound(altitude);
   double coefficient = computeCoefficient(velocity, speedOfSound);

   computeDrag(coefficient, density);
  }

/*********************************************
 * DRAG :: COMPUTE DRAG
 * Does calculations to determine
 * double value for drag.
 * ********************************************/
void Drag::computeDrag(const double coefficient, const double density)
{
   double velocity = pAmmo->getVelocity().getRateOfChange();
   double area = pAmmo->getArea();

   drag = 0.5 * area * coefficient * density * velocity * velocity;
}

/*********************************************
 * DRAG :: DISPLAY DRAG
 * Debugging tool to see what is
 * happening with drag values.
 * *******************************************/
void Drag::displayDrag()
{
  std::cout.precision(2);
  std::cout << std::fixed;
  std::cout << "Drag Force: " << drag << std::endl;
  getAcceleration().displayPosition("Drag Acceleration");
  std::cout << std::endl;

  std::cout.clear();
}
 


#endif /* drag_h */
