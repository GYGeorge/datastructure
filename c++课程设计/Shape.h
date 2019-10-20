#ifndef SHAPE_H
#define SHAPE_H
class Shape
{
    int obj_id; //对象标识符
  std::string des; //描述对象特征
public:
    Shape(int ob = 1,std::string D = "  "):obj_id(ob),des(D){};
    Shape(const Shape& in):obj_id(in.obj_id),des(in.des){};
    void put_in(int k,std::string L){obj_id = k; des = L; }
    int get_OB(){return obj_id;};
    std::string get_des(){return des;};
    virtual float Area() = 0 ;//纯虚函数
    virtual void WriteToFile(std::ofstream& o) = 0;//纯虚函数
};
#endif // SHAPE_H
