#include "mapPoint.h"

int mapPoint::compareTo(const mapPoint * p1) const 
{
    if((p1->latitude == latitude) && (p1->longitude == longitude)) return 0;
    else if((p1->latitude+p1->longitude) > (longitude+latitude)) return 1;
    else return -1;
}
double mapPoint::distance(const mapPoint &p)
{
	double p1,p2;
	p1 = p.lat()-latitude;
	if(p1 < 0.0) p1 = -p1;
	p2 = p.lon()-longitude;
	if(p2 < 0.0) p2 = -p2;
	return (p1+p2);
}

