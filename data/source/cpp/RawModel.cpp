//モデルデータ保存
//
#include "../header/rawmodel.h"
#include <fstream>
#include <string.h>
#define OBJ_NAME_LENGTH 128
#define OBJ_BUFFER_LENGTH 128

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// コンストラクタ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// マテリアル
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool OBJMESH::LoadMTLFile(const char *filename)
{
  std::ifstream file;
  char buf[OBJ_BUFFER_LENGTH] = {0};

  //ファイルを開ける
  file.open(filename, std::fstream::in);
  if (!file.is_open())
  {
    printf("error file_open\n");
    return false;
  }

  while (1)
  {
    file >> buf;

    if (0 == strcmp(buf, "newmtl"))
    {
    }
    else if (0 == strcmp(buf, "Ka"))
    {
    }
    else if (0 == strcmp(buf, "Kb"))
    {
    }
    else if (0 == strcmp(buf, "Ks"))
    {
    }
    else if (0 == strcmp(buf, "d"))
    {
    }
    else if (0 == strcmp(buf, "Ns"))
    {
    }
    else if (0 == strcmp(buf, "map_Ka"))
    {
    }
    else if (0 == strcmp(buf, "map_Kd"))
    {
    }
    else if (0 == strcmp(buf, "map_Ks"))
    {
    }
    else if (0 == strcmp(buf, "map_Bump"))
    {
    }
  }

  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// オブジェファイル
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
  //https://stackoverflow.com/questions/19986570/interleaved-vbo-with-coords-normals-and-color
  //make vao
  glGenVertexArrays(1, &Vertex_Array_Object);
  glBindVertexArray(Vertex_Array_Object);

  //make vbo
  glGenBuffers(1, &Vertex_Buffer_Object);
  glBindBuffer(GL_ARRAY_BUFFER, Vertex_Buffer_Object);
  glBufferData(GL_ARRAY_BUFFER, VERTICES.size() * sizeof(OBJVERTEX), &VERTICES[0], GL_STATIC_DRAW);

  //make ib
  glGenBuffers(1, &Index_Buffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Index_Buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, P_INDICES.size() * sizeof(unsigned int), &P_INDICES[0], GL_STATIC_DRAW);

  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// オブジェファイル
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool OBJMESH::LoadFile(const char *filename)
{
  if (!LoadOBJFile(filename))
  {
    printf("error read file\n");
    return false;
  }

  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 描画
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void OBJMESH::Draw()
{

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(OBJVERTEX), (void *)0); //send positions on pipe 0

  glBindBuffer(GL_ARRAY_BUFFER, Vertex_Buffer_Object);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Index_Buffer);

  glDrawElements(GL_TRIANGLES, P_INDICES.size(), GL_UNSIGNED_INT, 0);
}