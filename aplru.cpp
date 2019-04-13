#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <stack>

using namespace std;
using namespace std::chrono;


int secondChance(int frame, int pages[], int size){
	int frames[2][frame]; 
	/*defining a 2d array to store the page and bit*/ 
	int pointer = 0;
	int h, i, j;
	int x = 0, faults = 0, found = 0, load = 0;
	for (i=0;i<2;i++){
		for (j=0;j<frame;j++){
			frames[i][j] = 0;
		}
	}
	while(x < size){
		for (h=0;h<frame;h++){
			if(frames[0][h] == pages[x]){
				frames[1][h] = 1;
				found = 1;
			}
		}
		if (found == 0){
			do{
				if(frames[1][pointer] == 0){
					frames[0][pointer] = pages[x];
					frames[1][pointer] = 0;
					faults++;
					load = 1;
				}
				else{
					frames[1][pointer] = 0;
				}
				pointer++;
				if(pointer == frame){
					pointer = 0;
				}
			}

			while(load != 1);
		}

		found = 0;
		load = 0;
		x++;
	}
	return faults;
}

int main(){

    int sum = 0;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    for(int k=0;k<100;k++)
    {
       int q;
       cin>>q;
       int v[q];
    for(int j=0;j<q;j++)
    {
        cin>>v[j];
    }
    for(int i = 0;i<q;i++){
        
    }
        cout<<secondChance(25, v, 50)<<endl;
        sum+=secondChance(25, v, 50);
    }
    cout<<sum<<endl;
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>( t2 - t1 ).count();
    cout << duration;

    return 0;
}
