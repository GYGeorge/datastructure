#include<iostream>
using namespace std;
int swapo(int &a,int &b)
{
	int m = a;
	a =b;
	b =m;
}
int main()
{
    int n;
    cin >> n;
    int arr[n];
    int fron = 0;
	int  bac = n - 1;
    int cur = fron;
    int i;
    for(i = 0; i < n; i++){
        cin >> arr[i];
    }//for
    for(i = 0; i < n; i++){
        cout << arr[i]<<" ";
    }//for
    cout<<arr[bac];
    cout<<endl;
    while(cur<=bac){
        if(arr[cur] == -1){
            if(cur!=fron) swapo(arr[fron],arr[cur]);
            fron++;
            cur++;
        }
        else if(arr[cur] == 0){
        	cur++;
        }
        else if(arr[cur] == 1){
            if(cur!=bac) swapo(arr[cur],arr[bac]);
            bac--;
        }
        else break;
    }
    for(i = 0; i < n; i++){
        cout << arr[i]<<" ";
    }//for
    cout<<endl;

}
