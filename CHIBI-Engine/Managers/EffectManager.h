#pragma once
#include "MainData.h"
#include <map>
#include <vector>

using namespace std;

struct Effect
{
	Effect(const tstring& effectTag)
	{
		effectPtr = nullptr;
		tag = effectTag;
		path = _T("");
	}

	ID3D10Effect* effectPtr;
	tstring path;
	tstring tag;
	vector<tstring> techniques;
};

class EffectManager final
{
public:
	EffectManager(void);
	~EffectManager(void);

	void AddEffect(const tstring& filePath, const tstring& tag);
	void RemoveEffect(const tstring& tag);
	void RemoveAllEffects();
	bool IsEffectPresent(const tstring& tag)const;
	Effect GetEffect(const tstring& tag);

private:
	ID3D10Effect* CreateEffect(const tstring& filepath);
	map<tstring, Effect> m_EffectMap;

private:
	EffectManager(EffectManager& t);
	EffectManager& operator=(EffectManager& t);
};