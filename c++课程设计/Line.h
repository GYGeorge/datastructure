#ifndef LINE_H
#define LINE_H
#include"Shape.h"
#include"Point.h"
#include<math.h>
class Line: public Shape{
    Point p1;
    Point p2;
    double len;
    static int count_m;
public:
    Line(int ob,float p1_x,float p1_y,float p2_x,float p2_y,double LL,std::string D):len(LL),Shape(ob,D){
        p1.put_in_data(1,p1_x,p1_y," ");   p2.put_in_data(1,p2_x,p2_y," ");   count_m++; };
    Line(const Line& in):p1(in.p1),p2(in.p2),Shape(in),len(in.len){};
    float get_p1x(){return p1.getX();}
    float get_p1y(){return p1.getY();}
    float get_p2x(){return p2.getX();}
    float get_p2y(){return p2.getY();}
    double get_len(){return len;}
    static int Get_count(){return count_m;}
    virtual float Area(){
        float p1_x,p1_y;
        float p2_x,p2_y;
        p1_x = p1.getX();
        p1_y = p1.getY();
        p2_x = p2.getX();
        p2_y = p2.getY();
        float length;
        length = sqrt((p1_x-p2_x)*(p1_x-p2_x)+(p1_y-p2_y)*(p1_y-p2_y));
        return length;
    };
    virtual void WriteToFile(std::ofstream& o);
    float Distance(Line &in);
};
int Line::count_m = 0;
#endif // LINE_H

