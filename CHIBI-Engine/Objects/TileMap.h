#pragma once
#include "MainData.h"

#include "GameObject.h"
#include <vector>

#include "Managers/ImageManager.h"
#include "Managers/CollisionManager.h"

#include "Components/HitRegion.h"
#include "Components/Scene.h"

#include "Materials/TileMaterial.h"

//!This struct contains all data of a tile
struct Tile
{
	Tile() 
	{
		posId			= 0;
		layer			= 0;
		pos				= Vector2();
		textureTag		= _T("");
		drawRect		= Rect();
	};

	//!Retrieve the position of the tile in world-space
	Vector2	GetTilePos(int tileSize);

	//!Unique int that contain the X position, Y position and layer information
	int				posId;
	//!The drawing position in wold-space in pixels
	Vector2			pos; 
	//!The layer where the tile is drawn upon
	int				layer;
	//!The tag of the texture that will be used to draw the tile
	tstring			textureTag;
	//!The part of the texture is is drawn on the tile
	Rect			drawRect;
};

//!The data that is used to draw the tiles instanced
struct InstanceData
{
	InstanceData(const tstring& tileset, const int layerId, const int instId)
	{
		tileSet = tileset;
		layer = layerId;
		instanceId = instId;
	}

	InstanceData()
	{
		tileSet=_T("");
		layer=-1;
		instanceId = -1;
	}

	//!The tag of the tileset that is used in this instance buffer
	tstring		tileSet;
	//!The layer of the instance buffer
	int			layer;
	//!The if of the instance buffer
	int			instanceId;
};

//!The GameObject that is responsible for drawing all the tiles instanced
/*!Pretty advanced, not for the faint of heart!*/
class TileMap : public GameObject
{
public:
	//!How big should a buffer be at initialization (width*height of a map)
	static const int	INITIAL_BUFFER_SIZE = 10000;
	//!Maximum number of layers
	static const int	MAX_LAYERS = 5;

	TileMap(int tileSize);
	virtual			~TileMap(void);
	
	virtual bool	Initialize();

	virtual void	Paint();
	//!Paint all buffers on a certain layer, with a certain opacity
	void			Paint(const int layer, const float alpha = 1.0f);
	//!Paint the buffer with a certain tileset on a certain layer, with a certain opacity
	void			Paint(const tstring& tileset, const int layer, const float alpha = 1.0f);

	//!Add a tile to the map
	void			AddTile(const int drawPriority, const Tile& newTile);
	//!Remove a tile from the map
	void			RemoveTile(const int posId);
	
	//!Update the buffer with given tileset and layer
	void			UpdateInstanceBuffer(const tstring& tileSet,const int layer);
	//!Update all instance buffers
	void			UpdateInstanceBuffers();

	//!Get the material that is used to draw all tiles with a certain tileset
	TileMaterial*	GetMaterial(const tstring& tileSettag);

private:
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

	ID3D10Buffer										*m_VertexBufferPtr;
	vector<VertexPosTex>								m_VecVertices;
	ID3D10Buffer										*m_IndexBufferPtr;
	vector<DWORD>										m_VecIndices;

	//!A material for each texture
	map<tstring,TileMaterial*>							m_MaterialPtr;

	//!texturetag(tstring) )-> vector of layers -> instance buffer of the layer
	map<tstring,vector<ID3D10Buffer*>>					m_InstanceBufferPtr;

	//!textureTag(tstring)-> vector of layers -> vector of instance data
	map<tstring,vector<vector<VertexTileInstanceData>>>	m_TileInstanceData;
	
	//!posId (int) -> textureTag(tstring),layer(int),instanceId(int)
	map<int,InstanceData>								m_TilePosToIndex;

	//!textureTag(tstring) -> vector of layers -> number of tiles on that layer
	map<tstring,vector<int>>							m_NrOfTiles;

	int													m_TileSize;

	void												BuildShape();
	void												AddTriangle (unsigned int a, unsigned int b, unsigned c);
	void												BuildVertexBuffer();
	void												BuildIndexBuffer();

	void												CreateInstanceBuffer(const tstring& tileSet,const int layer);
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	TileMap(TileMap& t);
	TileMap& operator=(TileMap& t);
};