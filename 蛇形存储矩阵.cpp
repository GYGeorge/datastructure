#include<iostream>
#include<iomanip>
using namespace std;
struct circle{//iѭ������ boΪ0ÿ�ε��� boΪ1ÿ�εݼ� 
    int i;
    bool bo;
};
int main()
{
    int n;
    cin >> n;
    int Matrix[n][n];
    int row = 0, col = 0, i = 1 ,j;
    bool tag = 0;//�����0Ϊrow--��col++ 
    circle c;
    c.i = 2;
    c.bo = 0;
    Matrix[row][col] = i; i++;//��¼��һ�� 
 while(i<=n*n){//ѭ������Ϊn2 
    if(tag == 0){
        if(c.bo==1)//ѭ�������ݼ�ʱ��һ�β���rowֻ��col 
			col++;
        else 
			row++;
        tag = 1;
        Matrix[row][col] = i; i++;//ÿ��ѭ����һ�θ�ֵ 
        for(j=1;j<c.i;j++){//���ڸոո���һ��ֵ��ѭ������Ϊc.i-1 
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
