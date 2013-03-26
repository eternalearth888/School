#include <cstdlib>
#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <deque>
#include <stack>
#include <algorithm>
#include <time.h>

using namespace std;

/***************************************************************/

void nearestNeighbor();
void exhaustiveSearch();

/***************************************************************/

int n;//number of points
int x = 0; //x coordinate
int y = 0; //y coordinate
double xArray[100]; //array that will store x values
double yArray[100]; //array that will store y values

/***************************************************************/

int main(){
     //bringing in the file
    ifstream myData("input2copy.txt");
   
    //Error Check for input file
    if(!myData)
    {
        cout << "Error! The file either needs to be renamed or it cannot be opened." << endl;
        system("PAUSE");
        return 1;
    }

    while(!myData.eof())
    {
        myData >>n;
        cout << "THERE ARE " << n << " TOTAL POINTS." << endl; //Checking number of points vs text file
        
        //reading the x and y values into their respective arrays
        for(int i = 0; i <= n; i++)
        {
            //x values
            myData >> x;
            xArray[i]=x;
            //y values
            myData >> y;
            yArray[i]=y;
        }  
    }

    myData.close();

   // // Allows for generating of points for questsions 3 and 4 without constantly having to change the txt file
   //  n = 10;
   //  cout << n << endl;
   //  for(int i=0; i < n; i++)
   //  {
   //      xArray[i]=(rand() % 100);
   //      yArray[i]=(rand() % 100);
  		
   // 	//cout << xArray[i] << "," << yArray[i] << "\n";
   //  }  	 

    //Checking to make sure that the points read in match the file
    for(int j=0; j < n; j++)
    {
        cout << "X: " << xArray[j] << " " << "Y: " << yArray[j] << endl;
    }

    //Nearest Neighbor Implementation
    cout << endl;
    cout << "NEAREST NEIGHBOR: " << endl;

    nearestNeighbor();


    //Exhaustive Search Implementation
    cout << endl;
    cout << "OPTIMAL TSP PATH: " << endl;

    exhaustiveSearch();

    // End Program
    cout << endl;
 
    return 0;
}

/***************************************************************/

void nearestNeighbor(){
   
    clock_t startClock, finishClock;
    double timeCount;

    bool *seen = new bool[n];
    for(int i = 0; i < n; i++) {
        seen[i] = 0;
    }

    //Distance vars
    double tempx,tempy;//points to be compared
    double * finalX = new double[n];
    double * finalY = new double[n];
    double distance = 100000.0;//distance
    double d = 0.0;
    double totalDistance = 0.0;

    //Getting points to compare to eachother
    double next;
    finalX[0] = xArray[0];
    finalY[0] = yArray[0];
    seen[0] = 1;

    startClock=clock();
    for(int k = 0; k < n; k++)
    {   
        int index = 0;
        tempx = finalX[k];
        tempy = finalY[k];

        for(int j = 0; j < n; j++)
        {   
            d = sqrt(pow(tempx - xArray[j],2) + (pow(tempy - yArray[j],2)));

            if( d < distance && seen[j] != 1)
            {
                distance = d;
                index = j;
            }   
        //	cout << "tempx: " << tempx << " xArray: " << xArray[j] << " tempy: " << tempy << " yArray: " << yArray[j] << endl;
        }

        totalDistance += d;
        //cout << "d " << d << " " << " td " << totalDistance << endl;

        seen[index] = 1;
        finalX[k+1] = xArray[index];
        finalY[k+1] = yArray[index];
    }   
    finishClock = clock();
   
    timeCount = finishClock-startClock;
    timeCount = timeCount/1000;

    for(int i = 0; i < n; i++) {
        cout <<" ("<< finalX[i]<<","<< finalY[i] <<") ";
    }
    cout << "\n";
    cout << "Time: " << timeCount << " microseconds" << endl;
    cout << "Total distance: " << totalDistance << endl;
}

/***************************************************************/

void exhaustiveSearch(){
    clock_t startClock,finishClock;
    double timeCount;

    //array for permutation
    int permIndex[10];
   
    //populating the array permIndex
    for(int pop=0; pop < 10; pop++)
    {
        permIndex[pop]=pop;
    }

    //array to store shortestRoute
    int shortestRoute[10];

    double distance = 0.0;
    double d = 0.0;
    double totalDistance = 0.0;

    startClock=clock();

    do{
	
        for(int i=0; i < (n-1); i++)
        {
            distance += sqrt( pow(xArray[permIndex[i+1]]-xArray[permIndex[i]], 2) + pow(yArray[permIndex[i+1]] - yArray[permIndex[i]], 2)) ;
        }

        if( distance < d || d == 0.0)
        {
            d = distance;
            
            for(int saveShort = 0; saveShort < n; saveShort++)
            {
                shortestRoute[saveShort]=permIndex[saveShort];
            }
        }
        //distance = 0.0;
        totalDistance += d;
     // cout << "d " << d << " " << " td " << totalDistance << endl;
        
    }while(next_permutation(permIndex,permIndex+n));

    finishClock=clock();

    timeCount=finishClock-startClock;
    timeCount = timeCount/1000;

    for(int result = 0; result < n; result++) {
        cout  << " (" <<  xArray[shortestRoute[result]] << "," << yArray[shortestRoute[result]] <<") ";
    }
    cout << "\n";
    cout << "Time: " << timeCount << " microseconds" << endl;
    cout << "Total distance: "  << totalDistance << endl;
}

