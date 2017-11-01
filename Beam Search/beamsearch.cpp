#include<iostream>
#include<stdio.h>
using namespace std;
//test case
/*
0 1 1 0 1 0 0
1 0 0 1 0 1 0
1 0 0 0 0 0 1
0 1 0 0 0 0 0
1 0 0 0 0 1 0
0 1 0 0 1 0 0
0 0 1 0 0 0 0

*/
int main()
{

 int graph[10][10],rear=0,front=0;
 int q[] = { 0,0,0,0,0,0,0,0,0,0 }; 

   int sv,i,j,w,n;
   printf("Enter No of Vertex: ");
	cin>>n;
	int visited[n];
	printf("Enter Adjacency Matrix\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			cin>>graph[i][j];
                }
	}
	printf("Enter the Source Vertex\n");
	cin>>sv;
        
      printf("Enter the width.");
        cin>>w;
 for(i=0;i<n;i++)
	{
		visited[i]=0;
	}
   
       visited[sv] = 1;
   q[rear] = sv; 
    rear++; 
    while (rear != front) 
    {
        int u = q[front];
        printf("%d ",u);
        front++;
        int i = 0;
        int temp=0;
        for (i = 0; i < n; i++) 
		{
	         if (visited[i]!=1 && graph[u][i]==1 && temp<w ) 
			 {
	            q[rear] = i;
	            temp++;
	            rear++;
	            visited[i] = 1;
            }
        }
    }
cout<<"";
return 0; 
}
 


