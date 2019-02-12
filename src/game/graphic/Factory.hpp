#ifndef __GRAPHIC__FACTORY__
#define __GRAPHIC__FACTORY__

#include <vector>
#include "./Graphic.hpp"
// #include "./Object.hpp"
// #include "./Actor.hpp"
// #include "./Player.hpp"

enum E_Graphics {GRAPHIC_TERRAIN, GRAPHIC_OBJECT, GRAPHIC_ACTOR, GRAPHIC_PLAYER};

class Graphic;

class GraphicFactory {
	private:
	std::vector<Graphic*> m_vGraphics = {};
	Graphic *_getGraphic(E_Graphics graphic);

	public:
	GraphicFactory();
	~GraphicFactory();
	// GraphicTerrain *getGraphicTerrain();
	// GraphicObject *getGraphicObject();
	// GraphicActor *getGraphicActor();
	// GraphicPlayer *getGraphicPlayer();

};

#endif
