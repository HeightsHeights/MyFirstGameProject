class Vector3f
{
public:
  //フィールド
  float x;
  float y;
  float z;

  //演算子のオーバーロード
  Vector3f operator+(Vector3f obj);
  Vector3f operator-(Vector3f obj);
  Vector3f operator*(float scalar);
  Vector3f operator/(float scalar);
  Vector3f operator=(Vector3f obj);
  Vector3f operator+();
  Vector3f operator-();

  //コンストラクタ
  Vector3f();
  Vector3f(float a, float b, float c);

  //メソッド
  float magnitude_second_power();
  float magnitude();
  Vector3f normalize();
  static float dot(Vector3f a, Vector3f b);
  static Vector3f cross(Vector3f a, Vector3f b);
  Vector3f Matrix_multiplication(float matrix[3][3]);
  Vector3f Rotate(Vector3f v, float angle);
};