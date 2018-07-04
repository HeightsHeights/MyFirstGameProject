//モデルデータ保存
//

#include "../header/graphics.h"
#include <fstream>
#include <string.h>
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

OBJVEC3::OBJVEC3() : Vector3f()
{
}
OBJVEC3::OBJVEC3(float nx, float ny, float nz) : Vector3f(nx, ny, nz)
{
}

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
OBJVEC2::OBJVEC2() : Vector2f()
{
}
OBJVEC2::OBJVEC2(float nx, float ny) : Vector2f(nx, ny)
{
  x = nx;
  y = ny;
}
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
//　頂点情報
////////////////////////////////////////////////////////////////
class OBJVERTEX
{
public:
  OBJVEC3 normal;
  OBJVEC3 position;
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
  bool LoadMTLFile(const char *filename);
  bool LoadOBJFile(const char *filename);

public:
  bool LoadFile(const char *filename);
  void Release();
  void Draw();
};
////////////////////////////////////////////////////////////////

bool OBJMESH::LoadFile(const char *filename)
{
  std::ifstream file;

  char buf[OBJ_BUFFER_LENGTH] = {0};
  std::vector<OBJVEC3> positions;
  std::vector<OBJVEC3> normals;
  std::vector<OBJVEC2> texcoords;
  std::vector<OBJVERTEX> t_vertices;
  std::vector<OBJSUBSET> t_subsets;

  std::vector<unsigned int> t_indices;

  unsigned long total = 0;

  file.open(filename, std::fstream::in);

  if (!file.is_open())
  {
    printf("error file_open\n");
    return false;
  }

  while (1)
  {
    file >> buf;
    if (!file)
    {
      printf("a\n");
      break;
    }
    if (0 == strcmp(buf, "#"))
    {
      //コメント
    }
    else if (0 == strcmp(buf, "v"))
    {
      //頂点座標
      float x, y, z;
      file >> x >> y >> z;
      printf("x:%fy:%fz:%f\n", x, y, z);
      OBJVEC3 v(x, y, z);
      positions.push_back(v);
    }
    else if (0 == strcmp(buf, "vt"))
    {
      //テクスチャ座標
      float u, v;
      file >> u >> v;
      texcoords.push_back(OBJVEC2(u, v));
    }
    else if (0 == strcmp(buf, "vn"))
    {
      //法線ベクトル
      float x, y, z;
      file >> x >> y >> z;
      normals.push_back(OBJVEC3(x, y, z));
    }
    else if (0 == strcmp(buf, "f"))
    {
    }
  }
}

int main()
{
  OBJMESH mesh;
  mesh.LoadFile("data/data_3d/test.obj");
  return 0;
}