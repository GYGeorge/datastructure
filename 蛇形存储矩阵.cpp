#include<iostream>
#include<iomanip>
using namespace std;
struct circle{//i循环次数 bo为0每次递增 bo为1每次递减 
    int i;
    bool bo;
};
int main()
{
    int n;
    cin >> n;
    int Matrix[n][n];
    int row = 0, col = 0, i = 1 ,j;
    bool tag = 0;//标记域，0为row--，col++ 
    circle c;
    c.i = 2;
    c.bo = 0;
    Matrix[row][col] = i; i++;//记录第一个 
 while(i<=n*n){//循环次数为n2 
    if(tag == 0){
        if(c.bo==1)//循环次数递减时第一次不减row只加col 
			col++;
        else 
			row++;
        tag = 1;
        Matrix[row][col] = i; i++;//每次循环第一次赋值 
        for(j=1;j<c.i;j++){//由于刚刚赋过一次值，循环次数为c.i-1 
			row--; col++;
            Matrix[row][col] = i; i++;
        }
    }
    else if(tag == 1){
        if(c.bo==1) 
			row++;
        else 
			col++;
        tag = 0;
        Matrix[row][col] = i; i++;
        for(j=1;j<c.i;j++){
			col--;  row++;
            Matrix[row][col] = i; i++;
        }
    }
    if(c.i == n) c.bo = 1;
    if(c.bo == 1) c.i--;
    else c.i++;
 }
 	for(i=0;i<n;i++){
 
 	for(j=0;j<n;j++)
 	cout<<setw(3)<<Matrix[i][j]<<" ";
 	cout<<endl;
	}
}//main
