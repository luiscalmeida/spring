/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */

#ifndef _I_TREE_DRAWER_H_
#define _I_TREE_DRAWER_H_

#include <vector>

#include "Rendering/GL/myGL.h"
#include "System/EventClient.h"
#include "System/float3.h"

const int TREE_SQUARE_SIZE = 64;

class CFeature;
class ITreeDrawer : public CEventClient
{
public:
	ITreeDrawer();
	virtual ~ITreeDrawer();

	static ITreeDrawer* GetTreeDrawer();

	void SetupState() const;
	void ResetState() const;
	void Draw();
	void DrawShadow();
	void DrawTree(const CFeature* f, bool setupState, bool resetState);

	virtual void DrawPass() = 0;
	virtual void DrawShadowPass() = 0;
	virtual void Update() {}

	virtual void ResetPos(const float3& pos) {}
	virtual void AddTree(int treeID, int treeType, const float3& pos, float size);
	virtual void DeleteTree(int treeID, const float3& pos);
	virtual void AddFallingTree(int treeID, int treeType, const float3& pos, const float3& dir) {}

	bool WantsEvent(const std::string& eventName) {
		return
			(eventName == "RenderFeatureCreated") ||
			(eventName == "FeatureMoved") ||
			(eventName == "RenderFeatureDestroyed");
	}

	float GetBaseDistance() const { return baseTreeDistance; }
	float GetDrawDistance() const { return drawTreeDistance; }
	float IncrDrawDistance();
	float DecrDrawDistance();

	int NumTreesX() const { return treesX; }
	int NumTreesY() const { return treesY; }

	bool& DefDrawTreesRef() { return defDrawTrees; }
	bool& LuaDrawTreesRef() { return luaDrawTrees; }
	bool& WireFrameModeRef() { return wireFrameMode; }

	void RenderFeatureCreated(const CFeature* feature);
	void FeatureMoved(const CFeature* feature, const float3& oldpos);
	void RenderFeatureDestroyed(const CFeature* feature);

public:
	struct TreeStruct {
	public:
		bool operator == (const TreeStruct& ts) const { return (id == ts.id); }
	public:
		int id;
		int type;

		float3 pos;
	};

	struct TreeSquareStruct {
		// all trees within this tree-square
		std::vector<TreeStruct> trees;
	};

	std::vector<TreeSquareStruct> treeSquares;

private:
	void AddTrees();

protected:
	float baseTreeDistance;
	float drawTreeDistance;

	int treesX;
	int treesY;
	int nTrees;

	bool defDrawTrees;
	bool luaDrawTrees;
	bool wireFrameMode;

};

extern ITreeDrawer* treeDrawer;

#endif // _I_TREE_DRAWER_H_

