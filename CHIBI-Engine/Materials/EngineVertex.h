#pragma once
#include "MainData.h"

//!Struct to store vertex data for a shader that only uses position
struct VertexPos
{
	//default constructor
	VertexPos():
		pos(0.0, 0.0, 0.0)
	{

	}

	//overloaded constructor
	VertexPos(	float x, float y, float z):
		pos(x,y,z)
	{

	}

	//overloaded constructor
	VertexPos(const D3DXVECTOR3& p)
		:pos(p)
	{

	}

	D3DXVECTOR3 pos;
};


//!Struct to store vertex data for a shader that only uses position and texture coordinates
struct VertexPosTex
{
	//default constructor
	VertexPosTex():
		pos(0.0, 0.0, 0.0),
		tex(0.0, 0.0)
	{

	}

	//overloaded constructor
	VertexPosTex(	float x, float y, float z,
						float u, float v):
		pos(x,y,z),
		tex(u,v)
	{

	}

	//overloaded constructor
		VertexPosTex(const D3DXVECTOR3& p, const D3DXVECTOR2& t)
		:pos(p),tex(t)
	{

	}

	D3DXVECTOR3 pos;
	D3DXVECTOR2 tex;
};

//!Struct to store vertex data for the tile shader
struct VertexTileInstanceData
{
	//Default constructor
	VertexTileInstanceData()
	{		
		texInfo = D3DXVECTOR4(0,0,0,0);
		posSizePriority = D3DXVECTOR4(0,0,0,0);
	}
	
	D3DXVECTOR4 posSizePriority;
	D3DXVECTOR4 texInfo;
};

