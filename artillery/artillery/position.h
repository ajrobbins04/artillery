/***********************************************************************
 * Header File:
 *    Position : The representation of a position in x, y
 *    coordinates
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a location on the screen
 *    or the location on the field.
 ************************************************************************/

#ifndef position_h
#define position_h

#include <iomanip>
#include <iostream>
#include <cmath>

class TestPosition;
class Acceleration;
class Velocity;

/*********************************************
 * Position
 * A single position on the field in Meters
 *********************************************/
class Position
{
public:
   friend TestPosition;
   
   // constructors
   Position()            : x(0.0), y(0.0)  {}
   Position(double x, double y);
   Position(const Position & pt) : x(pt.x), y(pt.y) {}
   Position& operator = (const Position& pt);

   // getters
   double getMetersX()       const { return x;                    }
   double getMetersY()       const { return y;                    }
   double getPixelsX()       const { return x / metersFromPixels; }
   double getPixelsY()       const { return y / metersFromPixels; }

   // setters
   void setMetersX(const double xMeters)       { x = xMeters;           }
   void setMetersY(const double yMeters)       { y = yMeters;           }
   void setMetersXY(const double xMeters, const double yMeters) {
	  x = xMeters;
	  y = yMeters;
   }
   void setPixelsX(const double xPixels)       { x = xPixels * metersFromPixels;          }
   void setPixelsY(const double yPixels)       { y = yPixels * metersFromPixels;          }
   
   // addition
   void addMetersX(const double dxMeters)      { setMetersX(getMetersX() + dxMeters);     }
   void addMetersY(const double dyMeters)      { setMetersY(getMetersY() + dyMeters);     }
   void addPixelsX(const double dxPixels)      { setPixelsX(getPixelsX() + dxPixels);     }
   void addPixelsY(const double dyPixels)      { setPixelsY(getPixelsY() + dyPixels);     }
 


   // deal with the ratio of meters to pixels
   void setZoom(const double metersFromPixels) { this->metersFromPixels = metersFromPixels; }
   
   double getZoom() const { return metersFromPixels; }


   // display
   void displayPosition(const char* name) const {
	   std::cout.precision(2);
	   std::cout << std::fixed;
	   std::cout << name << ": (" << getMetersX() << ", " << getMetersY() << ")\n";
	   std::cout.clear();
   }

protected:
   double x;                 // horizontal position
   double y;                 // vertical position
	
private:
   static double metersFromPixels;
};

/*********************************************
 * COMPUTE DISTANCE
 * Find the distance between two positions
 *********************************************/
inline double computeDistance(const Position& pos1, const Position& pos2)
{
   return sqrt((pos1.getMetersX() - pos2.getMetersX()) * (pos1.getMetersX() - pos2.getMetersX()) +
			   (pos1.getMetersY() - pos2.getMetersY()) * (pos1.getMetersY() - pos2.getMetersY()));
}

// stream I/O useful for debugging
std::ostream & operator << (std::ostream & out, const Position& pt);
std::istream & operator >> (std::istream & in,        Position& pt);


/*********************************************
 * PT
 * Trivial point
 *********************************************/
struct PT
{
   double x;
   double y;
};



#endif /* position_h */
