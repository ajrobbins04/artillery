/***********************************************************************
 * Header File:
 *    Ammunition
 * Author:
 *    Amber Robbins
 * Summary:
 *    Contains the logic that governs the bullets.
 ************************************************************************/

#ifndef ammunition_h
#define ammunition_h

#include "position.h"
#include "motion.h"
#include <deque>
#include <iostream>

class Ammunition
{
public:
   Ammunition(const double area, const double mass, Position &pos)
   {
	  this->area = area;  // equals TRIPLE7_AREA
	  this->mass = mass;  // equals TRIPLE7_MASS
	  
	  // equals the current position of ptHowitzer
	  this->position.setMetersXY(pos.getMetersX(), pos.getMetersY());
	  
	  this->alive = true; // ammo is alive when it is initially fired

	  resetAcceleration();
	  
   }
	  
   // getters
   double         getArea()         const { return area;         }
   double         getMass()         const { return mass;         }
   Motion         getVelocity()     const { return velocity;     }
   Motion         getAcceleration() const { return acceleration; }
   Position       getPosition()     const
   {
	  return Position(position.getMetersX(), position.getMetersY());
   }
	
   bool isAlive() const { return alive; }
   void setIsAlive(const bool alive) { this->alive = alive; }
   
	
   void applyDrag(Motion resistance)
   {
	  resetAcceleration();
	  acceleration.add(resistance);
   }
   
   void fire(const double initialVelocity, const Angle angle);
   void advance();
   void displayAmmunition() const;
   void draw(ogstream& gout) const;
   
private:
   Position position;
   Position projectilePath[20];  // path of the projectile
   
   Motion velocity;
   Motion acceleration;

   double area;
   double mass;
   bool alive;
   
   // Sets acceleration values to zero and the force
   // of gravity so they can be computed fresh again.
   void resetAcceleration() { acceleration.setMetersXY(0, -1 * GRAVITY); }
};

/*******************************************
 * AMMUNITION :: FIRE
 * Sets up the initial position and
 * trajectory of the fired ammo.
 * *****************************************/
void Ammunition::fire(const double initialVelocity, const Angle angle)
{
   std::cout << "\nProjectile fired at: " << std::endl;
   angle.display();

   velocity.setMovement(initialVelocity, angle);
   std::cout << std::endl;

   // ammo originates at the position of the ptHowitzer
   projectilePath[0].setMetersX(position.getMetersX());
   projectilePath[0].setMetersY(position.getMetersY());
}

/*******************************************
 * AMMUNITION :: ADVANCE
 * Moves the bullet to a new position
 * and saves a trail of position values.
 * *****************************************/
void Ammunition::advance()
{
   // update position based on velocity
   position.addMetersX(velocity.getMetersX());
   position.addMetersY(velocity.getMetersY());

   for (int i = 19; i >= 1; --i)
   {
	  projectilePath[i] = projectilePath[i - 1];
   }

   // update projectile path
   projectilePath[0].setMetersX(position.getMetersX());
   projectilePath[0].setMetersY(position.getMetersY());

   // apply acceleration to velocity
   velocity.addMetersX(acceleration.getMetersX());
   velocity.addMetersY(acceleration.getMetersY());

}
 
/*******************************************
 * AMMUNITION :: DISPLAY AMMUNITION
 * A debugging function that allows us
 * to moniter the member variables of
 * ammuntion.
 * ******************************************/
void Ammunition::displayAmmunition() const
{
   position.displayPosition("Position");
   velocity.displayPosition("Velocity");
   acceleration.displayPosition("Acceleration");
}

/*******************************************
 * AMMUNITON :: DRAW
 * Draws the bullet and trail onto
 * the screen.
 * *****************************************/
void Ammunition::draw(ogstream& gout) const
{
   for (int i = 0; i < 20; i++)
   {
	  gout.drawProjectile(projectilePath[i], 0.5 * (double)i);
   }
}

#endif /* ammunition_h */
