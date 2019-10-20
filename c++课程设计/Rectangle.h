#ifndef RECTANGLE_H
#define RECTANGLE_H
#include"Shape.h"
#include"Point.h"
class Rect:public Shape{
    Point lp;
    Point rp;
    float or_area;
    static int count_j;
public:
    Rect(int ob,float lp_x,float lp_y,float rp_x,float rp_y,float area,std::string D):or_area(area),Shape(ob,D){
     lp.put_in_data(1,lp_x,lp_y,"  "); rp.put_in_data(1,rp_x,rp_y," ");  count_j++; };
    Rect(const Rect& in):lp(in.lp),rp(in.rp),or_area(in.or_area),Shape(in){};
    float get_lpx(){return lp.getX();}
    float get_lpy(){return lp.getY();}
    float get_rpx(){return rp.getX();}
    float get_rpy(){return rp.getY();}
    float get_arae(){return or_area;}
    static int Get_count(){return count_j;}
    virtual float Area(){
            float lpx = lp.getX();
            float lpy = lp.getY();
            float rpx = rp.getX();
            float rpy = rp.getY();
           return (lpx - rpx)*(lpy -rpy);
    };
    virtual void WriteToFile(std::ofstream& o);
    float Distance(Rect &in);
};
int Rect::count_j = 0;
#endif // RECTANGLE_H
