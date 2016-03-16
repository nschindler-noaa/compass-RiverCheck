/** \file mapConstants.h 
 * Defines for map items */
#ifndef _mapConstants_h_
#define _mapConstants_h_

//const int REACH = 10;
//const int COASTLINE = 20;
//const int RIVER = 30;
//const int RELEASE = 40; 
//const int DAM = 50; 
//const int BOUNDARY = 60;
//const int HEADWATER = 100; 
//const int POWERHOUSE = 150; 

/** Type of segment or other item on map. This enum replaces const int 
 * that are used to identify what we show (and how we show it) on the map. */
enum ItemType{
	DAM = 100, /**< Dam map item. */
	POWERHOUSE,/**< Powerhouse map item */
	REACH,     /**< Reach map item. */
	HEADWATER, /**< Headwater map item. */
	RELEASE,   /**< Release map item. */
	TRANSPORT, /**< Transport map item. */
	COASTLINE, /**< Coastline map item */
	RIVER,     /**< River map item */
	BOUNDARY   /**< Political boundary map item */
};

#endif

