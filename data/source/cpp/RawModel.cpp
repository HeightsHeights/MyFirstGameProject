//モデルデータ保存
//
#include "../header/rawmodel.h"
#include <fstream>
#include <string.h>
#define OBJ_NAME_LENGTH 128
#define OBJ_BUFFER_LENGTH 128
#define BUFFER_OFFSET(bytes) ((GLubyte *)NULL + (bytes))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// コンストラクタ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OBJVEC3::OBJVEC3()
    : Vector3f()
{
}

OBJVEC3::OBJVEC3(Vector3f v)
    : Vector3f(v.x, v.y, v.z)
{
}
OBJVEC3::OBJVEC3(float nx, float ny, float nz)
    : Vector3f(nx, ny, nz)
{
}

OBJVEC2::OBJVEC2()
    : Vector2f()
{
}
OBJVEC2::OBJVEC2(float nx, float ny)
    : Vector2f(nx, ny)
{
}

OBJCOLOR::OBJCOLOR()
{
}

OBJCOLOR::OBJCOLOR(GLubyte cr, GLubyte cg, GLubyte cb)
{
    r = cr;
    g = cg;
    b = cb;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// マテリアル
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool OBJMESH::LoadMTLFile(const char *filename)
{
    std::ifstream file;
    char buf[OBJ_BUFFER_LENGTH] = { 0 };

    //ファイルを開ける
    file.open(filename, std::fstream::in);
    if (!file.is_open()) {
        printf("error file_open\n");
        return false;
    }

    while (1) {
        file >> buf;

        if (0 == strcmp(buf, "newmtl")) {
        } else if (0 == strcmp(buf, "Ka")) {
        } else if (0 == strcmp(buf, "Kb")) {
        } else if (0 == strcmp(buf, "Ks")) {
        } else if (0 == strcmp(buf, "d")) {
        } else if (0 == strcmp(buf, "Ns")) {
        } else if (0 == strcmp(buf, "map_Ka")) {
        } else if (0 == strcmp(buf, "map_Kd")) {
        } else if (0 == strcmp(buf, "map_Ks")) {
        } else if (0 == strcmp(buf, "map_Bump")) {
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

    char buf[OBJ_BUFFER_LENGTH] = { 0 };
    std::vector<OBJVEC3> positions;
    std::vector<OBJVEC3> normals;
    std::vector<OBJVEC2> texcoords;

    std::vector<OBJVERTEX> t_vertices;
    std::vector<OBJSUBSET> t_subsets;

    //ファイルを開ける
    file.open(filename, std::fstream::in);
    if (!file.is_open()) {
        printf("error file_open\n");
        return false;
    }

    while (1) {
        //読み込み
        file >> buf;

        //閉じる
        if (!file) {
            break;
        }
        if (0 == strcmp(buf, "#")) {
            //コメント
        }

        //頂点情報
        else if (0 == strcmp(buf, "v")) {
            //頂点座標
            float x, y, z;
            file >> x >> y >> z;
            //printf("x:%fy:%fz:%f\n", x, y, z);
            OBJVEC3 v(x, y, z);
            positions.push_back(v);
        } else if (0 == strcmp(buf, "vt")) {
            //テクスチャ座標
            float u, v;
            file >> u >> v;
            texcoords.push_back(OBJVEC2(u, v));
        } else if (0 == strcmp(buf, "vn")) {
            //法線ベクトル
            float x, y, z;
            file >> x >> y >> z;
            normals.push_back(OBJVEC3(x, y, z));
        }

        //インデックス情報
        else if (0 == strcmp(buf, "f")) {
            unsigned int iPosition, iTexCoord, iNormal;

            unsigned int index = 0;
            for (int iFace = 0; iFace < 3; iFace++) {

                file >> iPosition;

                P_INDICES.push_back(iPosition - 1);

                if ('/' == file.peek()) {
                    file.ignore();

                    //テクスチャ情報があれば追加
                    if ('/' != file.peek()) {
                        file >> iTexCoord;
                        T_INDICES.push_back(iTexCoord - 1);
                    }

                    if ('/' == file.peek()) {
                        file.ignore();
                        file >> iNormal;
                        N_INDICES.push_back(iNormal - 1);
                    }
                }

                //改行
                if ('\n' == file.peek()) {
                    break;
                }
            }
        }
    }
    for (int i = 0; i < positions.size(); i++) {
        OBJVERTEX vertex;
        vertex.position = positions[i];
        vertex.normal   = normals[i];
        vertex.color    = *new OBJVEC3(255, 255, 0);
        //vertex.texcoord = texcoords[i];
        VERTICES.push_back(vertex);
    }
    for (int i = 0; i < N_INDICES.size(); i++) {
        NORMALS.push_back(normals[N_INDICES[i]]);
    }
    //https://stackoverflow.com/questions/19986570/interleaved-vbo-with-coords-normals-and-color
    //make vao
    glGenVertexArrays(1, &Vertex_Array_Object);
    glBindVertexArray(Vertex_Array_Object);

    //make vbo
    glGenBuffers(1, &Vertex_Buffer_Object);
    glBindBuffer(GL_ARRAY_BUFFER, Vertex_Buffer_Object);
    glBufferData(GL_ARRAY_BUFFER, VERTICES.size() * sizeof(OBJVERTEX), &VERTICES[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(OBJVERTEX), (void *)0); //send positions on pipe 0
    // glEnableVertexAttribArray(2);
    // glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(OBJVERTEX), (void *)(sizeof(OBJVEC3))); //send normals on pipe 1
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(OBJVERTEX), (void *)(sizeof(OBJVEC3) * 2));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &Normal_Buffer_Object);
    glBindBuffer(GL_ARRAY_BUFFER, Normal_Buffer_Object);
    glBufferData(GL_ARRAY_BUFFER, NORMALS.size() * sizeof(OBJVEC3), &NORMALS[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *)0); //send normals on pipe 1
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //make ib
    glGenBuffers(1, &Index_Buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Index_Buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, P_INDICES.size() * sizeof(unsigned int), &P_INDICES[0], GL_STATIC_DRAW);

    //http://www.opengl-tutorial.org/jp/beginners-tutorials/tutorial-8-basic-shading/

    glBindVertexArray(0);
    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// オブジェファイル
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool OBJMESH::LoadFile(const char *filename)
{
    if (!LoadOBJFile(filename)) {
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

    //http://marina.sys.wakayama-u.ac.jp/~tokoi/?date=20080830

    //http://marina.sys.wakayama-u.ac.jp/~tokoi/?date=20151125
    glBindVertexArray(Vertex_Array_Object);

    glBindBuffer(GL_ARRAY_BUFFER, Vertex_Buffer_Object);

    //glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
    //glNormalPointer(GL_FLOAT, sizeof(OBJVERTEX), (void *)(3 * sizeof(float)));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Index_Buffer);

    glDrawElements(GL_TRIANGLES, P_INDICES.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}