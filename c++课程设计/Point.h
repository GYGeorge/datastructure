#ifndef POINT_H
#define POINT_H
#include"Shape.h"
class Point: public Shape{
        float x, y;
        static int count_n;
public:
        Point(int ob,float xx, float yy, std::string DD):x(xx),y(yy),Shape(ob,DD){count_n++;};
        Point(const Point& in):x(in.x),y(in.y),Shape(in){};
        Point(){};
        void put_in_data(int b,float m,float n,std::string F){x = m; y = n;  Shape::put_in(b,F);}
        float getX(){return x;}
        float getY(){return y;}
        void Change_shape(int ob,std::string str){Shape::put_in(ob,str);}
        static int Get_count(){return count_n;}
        virtual float Area(){return 0;}
        virtual void WriteToFile(std::ofstream& o);
        float Distance(Point &in);
        float Distance_R_L(Point &in,Point &im);
};
int Point::count_n = 0;
#endif // POINT_H
