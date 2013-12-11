#ifndef _TILE_LOADER_
#define _TILE_LOADER_

#include <SFML/Graphics/VertexArray.hpp>
#include <string>

struct MapData
{
    std::string texture_name;
    u_int32_t mapx, mapy;
    MapData( void )
        :mapx( 0 ),
         mapy( 0 )
    { }
};
class TileLoader //this is the class you must derieve from and complete following 2 tasks :
{
protected:
	MapData m_mapdata; //1.fill this struct with name of texture and map dimensions(in tiles)
public:
	virtual ~TileLoader( void ) { };
	virtual void append_tile( u_int32_t gx, u_int32_t gy,sf::VertexArray& garr ) = 0;
	/*
	2.implement this method to append(or skip appending) tiles(4 vertices) to given vertex array,
	you may assume tiles will be requested in row major order:((0,0),(1,0),..,(map_x-1,0),(0,1),..,(map_x-1,map_y-1)),
	this method will be called exactly MapX*MapY times,
	for correct displaying and culling it's assumed your appended tile will be square with side equal to tilesize
	and have it's top left point at (tilesize*gx,tilesize*gy),
	*/
	const MapData& getdata( void ) const { return m_mapdata; }
};

#endif // _TILE_LOADER_
