#include "../header/vector.h"
#include <vector>

////////////////////////////////////////////////////////////////
//　ベクトル3fからなるオブジェクト用のベクトル
////////////////////////////////////////////////////////////////
class OBJVEC3 : public Vector3f
{
public:
  OBJVEC3();
  OBJVEC3(float nx, float ny, float nz);

  operator float *();
  operator const float() const;
};

////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
//　ベクトル2fからなるオブジェクト用のベクトル
////////////////////////////////////////////////////////////////
class OBJVEC2 : public Vector2f
{
public:
  OBJVEC2();
  OBJVEC2(float nx, float ny);
  operator float *();
  operator const float() const;
};

////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
//　頂点情報
////////////////////////////////////////////////////////////////
class OBJVERTEX
{
public:
  OBJVEC3 position;
  OBJVEC3 normal;
  OBJVEC2 texcoord;

  OBJVERTEX() {}
};
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
//　サブセット情報
////////////////////////////////////////////////////////////////
class OBJSUBSET
{
public:
  unsigned int materialIndex;
  unsigned int faceStart;
  unsigned int faceCount;
  OBJSUBSET() {}
};
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//　メッシュ情報
////////////////////////////////////////////////////////////////
class OBJMESH
{
private:
  OBJVERTEX *m_Vertex;
  OBJSUBSET *m_Subset;
  unsigned int *m_Indices;

  bool LoadMTLFile(const char *filename);
  bool LoadOBJFile(const char *filename);

public:
  std::vector<OBJVERTEX> VERTICES;
  std::vector<unsigned int> P_INDICES;
  std::vector<unsigned int> N_INDICES;
  std::vector<unsigned int> T_INDICES;

  bool LoadFile(const char *filename);
  void Release();
  void Draw();
};
////////////////////////////////////////////////////////////////