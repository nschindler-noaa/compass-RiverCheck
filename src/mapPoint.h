#ifndef _mapPoint_h_
#define _mapPoint_h_

//#include <rw/stackcol.h>
#include <math.h>
//typedef RWSlistCollectablesStack Stack;

/** Define a point on a map. A geographical point with lattitude and longitude. */
class mapPoint 
{
  public:
	/** Constructor from two values. \param _lon longitude \param _lat lattitude */
    mapPoint(double _lon, double _lat) : latitude(_lat), longitude(_lon) { }
	/** Destructor */
    ~mapPoint() { }
	/** The lattitude. \return lattitude*/
    inline double lat() const {	return latitude; }
	/** The longitude. \return longitude*/
    inline double lon() const {	return longitude; }
	/** Set the lattitude. */
    inline void lat(const double new_lat){ latitude=new_lat; }
	/** Set the longitude. */
    inline void lon(const double new_lon){ longitude=new_lon; }
	/** Find the distance to another point. \param p Other point on the map \return Distance*/
	double distance(const mapPoint &p);
	/** Assignment operator. \param p Point to copy values from. \return This point.*/
	inline mapPoint &operator=(const mapPoint &p){
		if(this != &p){
			latitude = p.lat();
			longitude = p.lon();
		}
		return *this;

	}
	/** Is equal operator. \param p Point to compare. \return true if lattitudes and longitudes equal.*/
	inline bool operator==(const mapPoint& p) const {
		return ((latitude == p.lat()) && (longitude == p.lon()));
	}
	/** Not equal operator. \param p Point to compare. \return true is lattitudes or longitudes not equal.*/
	inline bool operator!=(const mapPoint& p) const {
		return !(*this == p);
	}
	/** Compare function similar to strcmp. \param p Pointer to mapPoint to compare.
	 * \return 0 if equal, 1 if magnitude p > this, -1 if magnitude p < this*/
    int compareTo(const mapPoint *p) const;
    
  private:
    
    double latitude, longitude;
    
};
/** A map coordinate set. Four values that determine the boundaries of the map. */
class mapCordset 
{
  public:
	/** Constructor from four double values. \param x1 First x value \param x2 Second x value
	 *  \param y1 First y value \param y2 Second y value */
    mapCordset(double x1, double y1, double x2, double y2) : _x1(x1),_x2(x2),_y1(y1),_y2(y2) {}
	/** Copy constructor. \param mp A map coordinate set to copy. */
    mapCordset(const mapCordset& mp) : _x1(mp.X1()),_x2(mp.X2()),_y1(mp.Y1()),_y2(mp.Y2()) {}
	/** Destructor. */
	~mapCordset() {}

	/** The first x value. \return X1 */
    inline double X1(void) const {return _x1;}
	/** The second x value. \return X2 */
    inline double X2(void) const {return _x2;}
	/** The first y value. \return Y1 */
    inline double Y1(void) const {return _y1;}
	/** The second y value. \return Y2 */
    inline double Y2(void) const {return _y2;}
    
  private:
    
    const double _x1, _x2, _y1, _y2;

};

#endif

