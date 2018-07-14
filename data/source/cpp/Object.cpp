//キャラ__オブジェクトデータ
//自機
//敵
//弾

#include "../header/object.h"
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
Object::Object()
{
}

Object::Object(const char *filename)
{
    Model.LoadFile(filename);
}

Object::Object(const char *filename, Vector3f p, Vector3f r, Vector3f s)
{
    Model.LoadFile(filename);
    position = p;
    rotation = r;
    scale    = s;
}
Object::Object(OBJMESH model)
{
    Model.Copy(model);
}
Object::Object(OBJMESH model, Vector3f p, Vector3f r, Vector3f s)
{
    Model.Copy(model);
    position = p;
    rotation = r;
    scale    = s;
}
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
void Object::Draw()
{
    Model.Draw();
}