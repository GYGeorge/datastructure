#include<iostream>
#include"Shape.h"
#include"Line.h"
#include"Rectangle.h"
#include"Point.h"
#include<string>
#include<fstream>
#include<vector>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include<algorithm>
#define M 20
#define S 10
using namespace std;
ostream& operator<<(ostream &o, Point m)//重载point的<<
{
    o<<m.get_OB()<<" "<<m.getX()<<" "<<m.getY()<<" "<<m.get_des()<<endl;
}
ostream& operator<<(ostream &o, Line in)//重载line的<<
{
    o<<in.get_OB()<<" "<<in.get_p1x()<<" "<<in.get_p1y()<<" "<<in.get_p2x()<<" "<<in.get_p2y()<<" "<<in.get_len()<<endl;
}
ostream& operator<<(ostream& o,Rect q)//重载rect的<<
{
    o<<q.get_OB()<<" "<<q.get_lpx()<<" "<<q.get_lpy()<<" "<<q.get_rpx()<<" "<<q.get_rpy()<<" "<<q.get_arae()<<" "<<q.get_des()<<endl;
}
bool operator<(Point& a, Point& b)//重载point的<
{
    if(a.getX()<b.getX())
        return true;
    else if(a.getX() == b.getX() ){
        if(a.getY() < b.getY())
                return true;
    }
    else
        return false;
}
bool operator<(Line& a, Line& b)//重载line的<
{
    if(a.get_len()<b.get_len())
        return true;
    else
        return false;
}
bool operator<(Rect& a, Rect& b)//重载rect的<
{
    if(a.get_des()<b.get_des())
        return true;
    else
        return false;
}
Point operator+(Point& a, Point& b)//重载point的+
{
    Point temp(0,(a.getX()+b.getX()),(a.getY()+b.getY())," sum ");
    return temp;
}
Rect operator+(Rect& a,Rect& b)//重载rect的+
{
   float lp1 = (a.get_lpx()*a.get_lpx())+(a.get_lpy()*a.get_lpy());
   float lp2 = (b.get_lpx()*b.get_lpx())+(b.get_lpy()*b.get_lpy());
   float rp1 = (a.get_rpx()*a.get_rpx())+(a.get_rpy()*a.get_rpy());
   float rp2 = (b.get_rpx()*b.get_rpx())+(b.get_rpy()*b.get_rpy());
   float lp_x,lp_y,rp_x,rp_y;
   if((lp1 - lp2) > 0.0001){
        lp_x = b.get_lpx();
        lp_y = b.get_lpy();
   }else if((lp2 - lp1) > 0.0001){
        lp_x = a.get_lpx();
        lp_y = a.get_lpy();
   }else if(lp2 == lp1){
        lp_x = a.get_lpx();
        lp_y = a.get_lpy();
   }
   if((rp1 - rp2) > 0.0001){
        rp_x = b.get_rpx();
        rp_y = b.get_rpy();
   }else if((rp2 - rp1) > 0.0001){
        rp_x = a.get_rpx();
        rp_y = a.get_rpy();
   }else if(rp2 == rp1){
        rp_x = a.get_rpx();
        rp_y = a.get_rpy();
   }
   Rect temp(0,lp_x,lp_y,rp_x,rp_y,0," sum ");
   return temp;

}
float Point::Distance(Point &in)
{
    return sqrt((x-in.x)*(x-in.x)+(y-in.y)*(y-in.y));
}
float Line::Distance(Line &in)
{
    int i;
    float a[4],mi;
    a[0] = p1.Distance(in.p1);
    a[1] = p1.Distance(in.p2);
    a[2] = p2.Distance(in.p1);
    a[3] = p2.Distance(in.p2);
    mi = a[0];
   for(i = 0; i < 4 ; i++){
        if(a[i] < mi)
            mi = a[i];
   }
   return mi;
}
float Rect::Distance(Rect &in)
{
     int i;
    float a[4],mi;
    a[0] = lp.Distance(in.lp);
    a[1] = lp.Distance(in.rp);
    a[2] = rp.Distance(in.lp);
    a[3] = rp.Distance(in.rp);
    mi = a[0];
   for(i = 0; i < 4 ; i++){
        if(a[i] < mi)
            mi = a[i];
   }
   return mi;
}
float Point::Distance_R_L(Point &in,Point &im)
{
    float in_x = in.x,in_y = in.y;
    float im_x = im.x,im_y = im.y;
    float a,b;
    a = (in_x - x)*(in_x - x) + (in_y - y)*(in_y - y);
    b = (im_x - x)*(im_x - x) + (im_y - y)*(im_y - y);

    if(a < b) return sqrt(a);
    else return sqrt(b);
}
void Point::WriteToFile(ofstream& o)
{
    o<<Point::get_OB()<<" "<<x<<" "<<y<<" "<<Point::get_des()<<endl;
}
void Rect::WriteToFile(ofstream& o)
{
    o<<Rect::get_OB()<<" "<<Rect::get_lpx()<<" "<<Rect::get_lpy()<<" "<<Rect::get_rpx()<<" "<<Rect::get_rpy()<<" "<<Rect::get_des()<<endl;
}
void Line::WriteToFile(ofstream& o)
{
    o<<Line::get_OB()<<" "<<Line::get_p1x()<<" "<<Line::get_p1y()<<" "<<Line::get_p2x()<<" "<<Line::get_p2y()<<" "<<Line::get_des()<<" "<<Line::get_len()<<endl;
}
void WriteData(Shape* s, ofstream& out_file)
{
        s->WriteToFile(out_file);
}
bool compare(int a,int b)
{
    return a > b;
}
int main()
{
    vector<Point> point_list;
    ifstream q_point;
    q_point.open("point.txt",ios::in);
    char x_point[M],y_point[M],useless[M];
    char id[S],de_s[M];
    while(!q_point.eof()){
            q_point.getline(id,S,' ');
            q_point.getline(x_point,M,' ');
            q_point.getline(y_point,M,' ');
            q_point.getline(useless,M,' ');
            q_point.getline(de_s,M);
            int id_pi = atof(id);
            float x_pi = atof(x_point);
            float y_pi = atof(y_point);
            string desi = de_s;
            Point temp(id_pi,x_pi,y_pi,desi);
            point_list.push_back(temp);
    }
    int count_point = Point::Get_count()-1;
    cout<<count_point<<endl;
    q_point.close();

    vector<Line> line_list;
    ifstream q_Line;
    q_Line.open("line.txt",ios::in);
    char a_x_p[M],a_y_p[M];
    char b_x_p[M],b_y_p[M];
    char Leng[M];
    while(!q_Line.eof()){
        q_Line.getline(id,S,' ');
        q_Line.getline(a_x_p,M,' ');
        q_Line.getline(a_y_p,M,' ');
        q_Line.getline(b_x_p,M,' ');
        q_Line.getline(b_y_p,M,' ');
        q_Line.getline(Leng,M);
        int id_li = atof(id);
        float a_x_pi = atof(a_x_p);
        float a_y_pi = atof(a_y_p);
        float b_x_pi = atof(b_x_p);
        float b_y_pi = atof(b_y_p);
        double leni = atof(Leng);
        Line temp(id_li,a_x_pi,a_y_pi,b_x_pi,b_y_pi,leni,"  ");
        line_list.push_back(temp);
    }
    int count_line = Line::Get_count()-1;
    cout<<count_line<<endl;
    q_Line.close();


    vector<Rect> rect_list;
    ifstream q_rect;
    q_rect.open("rect.txt",ios::in);
    while(!q_rect.eof()){
        q_rect.getline(id,S,' ');
        q_rect.getline(a_x_p,M,' ');
        q_rect.getline(a_y_p,M,' ');
        q_rect.getline(b_x_p,M,' ');
        q_rect.getline(b_y_p,M,' ');
        q_rect.getline(Leng,M,' ');
        q_rect.getline(de_s,M);
        int id_li = atof(id);
        float a_x_pi = atof(a_x_p);
        float a_y_pi = atof(a_y_p);
        float b_x_pi = atof(b_x_p);
        float b_y_pi = atof(b_y_p);
        double leni = atof(Leng);
        string dese = de_s;
        Rect temp(id_li,a_x_pi,a_y_pi,b_x_pi,b_y_pi,leni,dese);
        rect_list.push_back(temp);
    }
    int count_rect = Rect::Get_count()-1;
    cout<<count_rect<<endl;
    q_rect.close();

    int num;
    string to_find;
    cout<<"输入Point序号：";
    cin>>num;
    vector<Point>::iterator iter_point = point_list.begin();
    vector<Rect>::iterator iter_rect = rect_list.begin();
    for(;iter_point != point_list.end(); iter_point++ )
    {
        Point temp_in = *iter_point;
        if(num == temp_in.get_OB())
        {
            to_find = temp_in.get_des();
                break;
        }
    }
    if(iter_point == point_list.end())  cout<<"未找到"<<endl;
    else
    {
        for(;iter_rect != rect_list.end(); iter_rect++ )
        {
            Rect Temp = *iter_rect;
            if(to_find == Temp.get_des())
            {
             cout<<Temp;
            }
        }
    }
    cout<<"输入Rect序号：";
    cin>>num;
    iter_point = point_list.begin();
    iter_rect = rect_list.begin();
    for(;iter_rect != rect_list.end(); iter_rect++ )
    {
        Rect temp_in = *iter_rect;
        if(num == temp_in.get_OB())
        {
            to_find = temp_in.get_des();
                break;
        }
    }
    if(iter_rect == rect_list.end())  cout<<"未找到"<<endl;
    else
    {
        for(;iter_point != point_list.end(); iter_point++ )
        {
            Point Temp = *iter_point;
            if(to_find == Temp.get_des())
            {
                cout<<Temp;
            }
        }
    }
    iter_rect = rect_list.begin();
    Rect in_temp = *iter_rect;
    float AREA_max = in_temp.get_arae() ;
    float AREA_min = in_temp.get_arae() ;
    Rect area_max = *iter_rect;
    Rect area_min = *iter_rect;
    for(;iter_rect != rect_list.end()-1; iter_rect++)
    {
        Rect temp = *iter_rect;
        if(temp.get_arae() > AREA_max)
        {
            AREA_max = temp.get_arae();
            area_max = *iter_rect;
        }
        else if(temp.get_arae() < AREA_min)
        {
            AREA_min = temp.get_arae();
            area_min = *iter_rect;
        }
    }
    string N = area_max.get_des();
    ofstream rect_data;
    rect_data.open("Rect_data.txt",ios::out);
    area_max.WriteToFile(rect_data);
    area_min.WriteToFile(rect_data);

    vector<Line>::iterator iter_line = line_list.begin();
    Line l_temp_max = *iter_line;
    Line l_temp_min = *iter_line;
    float line_area_min = l_temp_min.Area();
    float line_area_max = l_temp_max.Area();
    for(;iter_line != line_list.end()-1; iter_line++ )
    {
        Line temp = *iter_line;
        if(line_area_max < temp.Area())
        {
            l_temp_max = *iter_line;
            line_area_max = temp.Area();
        }
        else if(line_area_min > temp.Area())
        {
            l_temp_min = *iter_line;
            line_area_min = temp.Area();
        }
    }
    ofstream line_data;
    line_data.open("Line_data.txt",ios::out);
    l_temp_max.WriteToFile(line_data);
    l_temp_min.WriteToFile(line_data);

    Point show1(1,5,6," ");
    Point show2(2,9,10," ");
    Point end_of_show = show1 + show2;//任务4演示
    cout<<end_of_show;
    Rect new_show1(1,8,9,1,2,56," ");
    Rect new_show2(1,18,19,4,5,55," ");
    Rect end_of_new_show = new_show1 + new_show2;//任务4演示
    cout<<end_of_new_show;
    Line Sh(1,6,3,8,5,88," ");
    Line Ch(1,19,18,16,13,99," ");
    float st = show1.Distance(show2);
    cout<<st<<endl; //任务5.1演示
    st = new_show1.Distance(new_show2);
    cout<<st<<endl; //任务5.2演示
    st = Sh.Distance(Ch);
    cout<<st<<endl; //任务5.3演示
    Point new_show1_a(1,new_show1.get_lpx(),new_show1.get_lpy()," ");
    Point new_show1_b(1,new_show1.get_rpx(),new_show1.get_rpy()," ");
    st = show1.Distance_R_L(new_show1_a,new_show1_b);
    cout<<st<<endl; //任务5.4演示
    Point Sh_a(1,Sh.get_p1x(),Sh.get_p1y()," ");
    Point Sh_b(1,Sh.get_p2x(),Sh.get_p2y()," ");
    st = show1.Distance_R_L(Sh_a,Sh_b);
    cout<<st<<endl; //任务5.4演示


    iter_point = point_list.begin();
    for(;iter_point != point_list.end(); iter_point++){
        Point chan_temp = *iter_point;
        int ob = chan_temp.get_OB();
        string change;
        change = chan_temp.get_des();
        transform(change.begin(),change.end(),change.begin(),::tolower);
        chan_temp.Change_shape(ob,change);
        *iter_point = chan_temp;
    }
     sort(point_list.begin(),point_list.end()-1);
     ofstream write_to_point;
     write_to_point.open("Point2.txt");
     for(iter_point = point_list.begin();iter_point != point_list.end()-1; iter_point++)
     {
         Point temp = *iter_point;
         WriteData(&temp,write_to_point);
     }
     sort(line_list.begin(),line_list.end()-1);
     ofstream write_to_line;
     write_to_line.open("Line2.txt");
     for(iter_line = line_list.begin();iter_line != line_list.end()-1; iter_line++)
     {
         Line temp = *iter_line;
         WriteData(&temp,write_to_line);
     }
     sort(rect_list.begin(),rect_list.end()-1);
     ofstream write_to_rect;
     write_to_rect.open("Rect2.txt");
     for(iter_rect = rect_list.begin();iter_rect != rect_list.end()-1; iter_rect++)
     {
         Rect temp = *iter_rect;
         WriteData(&temp,write_to_rect);
     }


}
