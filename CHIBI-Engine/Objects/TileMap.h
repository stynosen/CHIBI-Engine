#pragma once
#include "MainData.h"

#include "GameObject.h"
#include <vector>

#include "Managers/ImageManager.h"
#include "Managers/CollisionManager.h"

#include "Components/HitRegion.h"
#include "Components/Scene.h"

#include "Materials/TileMaterial.h"


struct Tile
{
	Tile() 
	{
		posId			= 0;
		layer			= 0;
		pos				= Vector2();
		textureTag		= _T("");
		drawRect		= Rect();
		collData[0]		= -1;
		collData[1]		= -1;
		collData[2]		= -1;
		collData[3]		= -1;
	};

	Vector2	GetTilePos(int tileSize);
	void	BakeCollision();

	int				posId; //unique int that contain the X pos, Y pos and layer information
	Vector2			pos;   //the drawing position in pixels
	int				layer;
	tstring			textureTag;
	Rect			drawRect;
	int				collData[4];
};

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

	tstring		tileSet;
	int			layer;
	int			instanceId;
};

class TileMap : public GameObject
{
public:
	static const int	INITIAL_BUFFER_SIZE = 10000;
	static const int	MAX_LAYERS = 5;

	TileMap(int tileSize);
	virtual			~TileMap(void);
	
	virtual bool	Initialise();

	virtual void	Paint();
	void			Paint(const int layer, const float alpha = 1.0f);
	void			Paint(const tstring& tileset, const int layer, const float alpha = 1.0f);

	void			AddTile(const int drawPriority, const Tile& newTile);
	void			RemoveTile(const int posId);
	
	void			UpdateInstanceBuffer(const tstring& tileSet,const int layer);
	void			UpdateInstanceBuffers();

	TileMaterial*	GetMaterial(const tstring& tileSettag);

private:
	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------

	ID3D10Buffer										*m_VertexBufferPtr;
	vector<VertexPosTex>								m_VecVertices;
	ID3D10Buffer										*m_IndexBufferPtr;
	vector<DWORD>										m_VecIndices;

	//A material for each texture
	map<tstring,TileMaterial*>							m_MaterialPtr;

	//texturetag(tstring) )-> vector of layers -> instance buffer of the layer
	map<tstring,vector<ID3D10Buffer*>>					m_InstanceBufferPtr;

	//textureTag(tstring)-> vector of layers -> vector of instance data
	map<tstring,vector<vector<VertexTileInstanceData>>>	m_TileInstanceData;
	
	//posId (int) -> textureTag(tstring),layer(int),instanceId(int)
	map<int,InstanceData>								m_TilePosToIndex;

	//textureTag(tstring) -> vector of layers -> nr of tiles on that layer
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