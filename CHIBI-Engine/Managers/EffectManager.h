#pragma once
#include "Manager.h"

#include "MainData.h"
#include <map>
#include <vector>

using namespace std;

//!A struct that contains shader information
struct Effect
{
	Effect(const tstring& effectTag)
	{
		effectPtr = nullptr;
		tag = effectTag;
		path = _T("");
	}

	//!The address of the shader effect
	ID3D10Effect* effectPtr;
	//!The file path to the shader file
	tstring path;
	//!The tag of the shader
	tstring tag;
	//!The techniques in the shader
	vector<tstring> techniques;
};

//!The manager that stores and manages all the effects
class EffectManager final : public Manager
{
public:
	EffectManager(void);
	~EffectManager(void);

	//!Add a shader to the manager
	void AddEffect(const tstring& filePath, const tstring& tag);
	//!Remove a shader from the manager
	void RemoveEffect(const tstring& tag);
	//!Remove all effects from the manager
	void RemoveAllEffects();
	//!Check if a shader is present in the manager
	bool IsEffectPresent(const tstring& tag)const;
	//!Retrieve an effect from the manager
	Effect GetEffect(const tstring& tag);

private:
	//!load the shader file and create the effect
	ID3D10Effect* CreateEffect(const tstring& filepath);
	//!Map that stores all the loaded effects
	map<tstring, Effect> m_EffectMap;

private:
	EffectManager(EffectManager& t);
	EffectManager& operator=(EffectManager& t);
};