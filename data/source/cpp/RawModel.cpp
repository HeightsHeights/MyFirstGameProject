//モデルデータ保存
//
#include "../header/rawmodel.h"
#include "../header/graphics.h"
#include <fstream>
#include <string.h>

#include <GL/gl.h>
#include <GL/glut.h>

#include <GL/glext.h>
OBJVEC3::OBJVEC3() : Vector3f()
{
}
OBJVEC3::OBJVEC3(float nx, float ny, float nz) : Vector3f(nx, ny, nz)
{
}

OBJVEC2::OBJVEC2() : Vector2f()
{
}
OBJVEC2::OBJVEC2(float nx, float ny) : Vector2f(nx, ny)
{
}

bool OBJMESH::LoadMTLFile(const char *filename)
{
  return true;
}

bool OBJMESH::LoadOBJFile(const char *filename)
{
  std::ifstream file;

  char buf[OBJ_BUFFER_LENGTH] = {0};
  std::vector<OBJVEC3> positions;
  std::vector<OBJVEC3> normals;
  std::vector<OBJVEC2> texcoords;

  std::vector<OBJVERTEX> t_vertices;
  std::vector<OBJSUBSET> t_subsets;

  //ファイルを開ける
  file.open(filename, std::fstream::in);
  if (!file.is_open())
  {
    printf("error file_open\n");
    return false;
  }

  while (1)
  {
    //読み込み
    file >> buf;

    //閉じる
    if (!file)
    {
      printf("a\n");
      break;
    }
    if (0 == strcmp(buf, "#"))
    {
      //コメント
    }

    //頂点情報
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

    //インデックス情報
    else if (0 == strcmp(buf, "f"))
    {
      unsigned int iPosition, iTexCoord, iNormal;

      unsigned int index = 0;
      for (int iFace = 0; iFace < 3; iFace++)
      {

        file >> iPosition;

        P_INDICES.push_back(iPosition - 1);

        if ('/' == file.peek())
        {
          file.ignore();

          //テクスチャ情報があれば追加
          if ('/' != file.peek())
          {
            file >> iTexCoord;
            T_INDICES.push_back(iTexCoord - 1);
          }

          if ('/' == file.peek())
          {
            file.ignore();
            file >> iNormal;
            N_INDICES.push_back(iNormal - 1);
          }
        }

        //改行
        if ('\n' == file.peek())
        {
          break;
        }
      }
    }
  }
  for (int i = 0; i < positions.size(); i++)
  {
    OBJVERTEX vertex;
    vertex.position = positions[i];
    vertex.normal = normals[i];
    //vertex.texcoord = texcoords[i];
    VERTICES.push_back(vertex);
  }
  return true;
}

bool OBJMESH::LoadFile(const char *filename)
{
  if (!LoadOBJFile(filename))
  {
    printf("error read file\n");
    return false;
  }

  return true;
}

void OBJMESH::Draw()
{

  //glBufferData(GL_ARRAY_BUFFER, VERTICES.size() * sizeof(OBJVERTEX), &VERTICES[0], GL_STATIC_DRAW);
  /*
  for (unsigned int i = 0; i < 1; i++)
  {
    glInterleavedArrays(GL_T2F_N3F_V3F, 0, m_Vertex);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, &);
  }
  */
}

/*
int main()
{
  OBJMESH mesh;
  mesh.LoadFile("data/data_3d/test.obj");
  return 0;
}
*/