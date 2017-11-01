// #include<iostream>
// #include<stdlib.h>
// #include<stdio.h>
#include<bits/stdc++.h>

using namespace std;

			
		/* ********************************************************* */
								/*Node Class*/

class Node
{
	private:
		int nodeNumber;
		int weight;
		Node* next;
	public:
		void setData(int value,int weight,Node* address);
		int getData();
		int getWeight();
		void setNextAddress(Node* address);
		Node* getNextNodeAddress();
		Node* getNodeAddress();
};

void Node :: setData(int value,int weight,Node* address)
{
	this->nodeNumber = value;
	this->weight = weight;
	this->next = address;
}

int Node :: getData()
{
	return this->nodeNumber;
}

int Node :: getWeight()
{
	return this->weight;
}

void Node :: setNextAddress(Node* address)
{
	this->next = address;
}

Node* Node :: getNextNodeAddress()
{
	return this->next;
}

Node* Node :: getNodeAddress()
{
	return this;
}

			/* ********************************************************* */
								/*LinkedList Class*/
class LinkedList
{
	
	private:
		Node* head,currentNode;
	public:
		LinkedList();
		void insertNode(int v,int weight);
		void deleteNode(int v);
		void traverseList();
		Node* getHead();
};

LinkedList :: LinkedList()
{
	head = NULL;
}

Node* LinkedList :: getHead()
{
	return this->head;
}

void LinkedList :: insertNode(int v,int weight)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	Node* temp;

	if(!newNode)
	{
		cout<<"\n\tMemory Full!";
		return;
	}

	temp = this->head;
	while(temp!=NULL)
	{
		if(temp->getData() == v)
		{
			cout<<"\n\tEdge Already Exists!";
			return;
		}
		temp = temp->getNextNodeAddress();
	}

	if(this->head == NULL)
	{
		newNode->setData(v,weight,NULL);
		this->head = newNode;
		return;
	}

	newNode->setData(v,weight,NULL);

	temp = this->head;
	while(temp->getNextNodeAddress() != NULL)
	{
		temp = temp->getNextNodeAddress();
	}
	temp->setNextAddress(newNode);
}

void LinkedList :: deleteNode(int v)
{
	Node* temp = this->head;
	Node* previous = NULL;


	while(temp->getData() != v)
	{
		previous = temp;
		temp = temp->getNextNodeAddress();
	}

	if(previous == NULL)
	{
		this->head = this->head->getNextNodeAddress();
		return;
	}
	previous->setNextAddress(temp->getNextNodeAddress());
	free(temp);
}

void LinkedList :: traverseList()
{
	Node* temp;
	temp = this->head;
	if(temp == NULL)
		return;
	while(temp!=NULL)
	{
		cout<<temp->getData()<<" ";
		temp = temp->getNextNodeAddress();
	}
}


class Queue
{	
	private:
		Node* *queue;
		int front,rear,size;
	public:
		Queue(){}
		Queue(int);
		void enqueue(Node*);
		Node* dequeue();
		bool isEmpty();
		bool isFull();
		int getrear()
		{
			return rear;
		}
		int getfront()
		{
			return front;
		}
		int print(int index)
		{
			cout<<queue[index];
		}
};

Queue :: Queue(int size)
{
	this->size = size;
	queue = (Node**)calloc(size,sizeof(Node*));
	front=-1;rear=-1;
	// cout<<"\n\tQueue Created!\n\tSize: "<<size;
	// cout<<"\n\t";
	// for(int counter=0;counter<size;counter++)
	// {
	// 	cout<<queue[counter];
	// }
}

bool Queue :: isFull()
{
	if(front == (rear+1)%size)
		return true;
	return false;
}

bool Queue :: isEmpty()
{
	if(rear == front && rear == -1)
		return true;
	return false;
}

void Queue :: enqueue(Node* address)
{
	if(isFull())
	{
		cout<<"Overflow Condition!";
		return;
	}
	if(isEmpty())
		front = rear = 0;
	else
		rear = (rear+1)%size;
	queue[rear] = address;
}

Node* Queue :: dequeue()
{
	if(isEmpty())
	{
		cout<<"Underflow Condition!";
		return NULL;
	}
	Node* temp = queue[front];
	if(front == rear)
	{
		front = rear = -1;
		return temp;
	}
	front = (front+1)%size;
	return temp;
}


			/* ********************************************************* */
								/*Graph Class*/


class Graph
{
	private:
		LinkedList *adjlist;
		Queue Q;
		int vertices,totalIncludedVertices,totalEdges;
		int *child,*minWeight;
		int edges;
		bool *visited,*inqueuestate,*included,*finished;
		bool backedge;
		typedef struct 
		{	
			int from,to,weight;
		}KruskalWeights;
		void DFStraversal(int);
		void DFIDtraversal(int,int);
		void BFStraversal(int);
		void Cycle(int);
		void prims();
		void kruskal();
		static int compare(KruskalWeights,KruskalWeights);
	public:
		Graph();
		void createGraph(int);
		void insertEgde(int,int,int);
		void deleteEdge(int,int);
		void traverseGraph();
		void DFS(int);
		void DFID(int,int);
		void BFS(int);
		bool detectCycle(int);
		void MSTprim(int);
		void MSTkruskal();
		void dijkstras(int v);
};

Graph :: Graph() {}

void Graph :: createGraph(int vertices)
{
	this->vertices = vertices;
	totalIncludedVertices = 0;
	totalEdges = 0;
	adjlist = (LinkedList*)calloc(vertices,sizeof(LinkedList));
	visited = (bool*)calloc(vertices,sizeof(bool));
	finished = (bool*)calloc(vertices,sizeof(bool));
	included = (bool*)calloc(vertices,sizeof(bool));
	child = (int*)calloc(vertices,sizeof(int));
	minWeight = (int*)calloc(vertices,sizeof(int));
	inqueuestate = (bool*)calloc(vertices,sizeof(bool));
	Q = vertices; //Setting The Length Of The Queue
}

void Graph :: insertEgde(int u,int v,int weight) //Ordered Pair (u,v)
{
	if(u > vertices-1 && v > vertices-1 )
	{
		cout<<"\n\t"<<u<<" and "<<v<<" Vertices Not Available";
		return;
	}

	else if(u > vertices-1 )
	{
		cout<<"\n\t"<<u<<" Vertice Not Available";
		return;
	}

	else if(v > vertices-1)
	{
		cout<<"\n\t"<<v<<" Vertice Not Available";
		return;
	}

	adjlist[u].insertNode(v,weight);
	totalEdges++;
	 adjlist[v].insertNode(u,weight);	
	 totalEdges++;
}


void Graph :: deleteEdge(int u,int v)
{

	Node* temp;
	if(u > vertices-1 && v > vertices-1 )
	{
		cout<<"\n\t"<<u<<" and "<<v<<" Vertices Not Available";
		return;
	}

	else if(u > vertices-1 )
	{
		cout<<"\n\t"<<u<<" Vertice Not Available";
		return;
	}

	else if(v > vertices-1)
	{
		cout<<"\n\t"<<v<<" Vertice Not Available";
		return;
	}

	temp = adjlist[u].getHead();

	if(temp == NULL)
	{
		cout<<"\n\tThere Is No Outgoing Edge From "<<u;
		return;
	}

	while(temp->getData() != v)
	{
		temp = temp->getNextNodeAddress();
		if(temp == NULL) break;
	}

	if(temp == NULL)
	{
		cout<<"\n\tNo Egde From "<<u<<" to "<<v<<".";
		return;
	}

	adjlist[u].deleteNode(v);	
	totalEdges--;
}

void Graph :: traverseGraph()
{
	Node* temp;
	int check=0;
	for(int counter=0;counter<vertices;counter++)
	{
		temp = adjlist[counter].getHead();
		if(temp==NULL)
		{
			check++;
		}
	}
	if(check == vertices)
	{
		cout<<"\n\tGraph Is Empty";
		return; 
	}
	cout<<"\n\tThere are Directed Edges from:";
	for(int counter=0;counter<vertices;counter++)
	{
		temp = adjlist[counter].getHead();
		if(temp!= NULL)
		{
			cout<<"\n\t"<<counter<<" to ";
			adjlist[counter].traverseList();
		}	
	}
}

void Graph :: DFS(int v)
{
	int counter;
	for(counter=0;counter<vertices;counter++)
	{
		visited[counter] = false;
	}
	cout<<"\n\tDepth First Traversal: ";
	DFStraversal(v);
}

void Graph :: DFStraversal(int v)
{
	visited[v] = true;
	cout<<v<<" ";
	Node* temp = adjlist[v].getHead();
	while(temp!=NULL)
	{
		if(visited[temp->getData()] == false)
		{
			DFStraversal(temp->getData());
		}
		temp = temp->getNextNodeAddress();
	}
} 


void Graph :: DFID(int v,int depth)
{
	int counter,offset;
	cout<<"\n\tDFID Traversal: ";
	for(counter=0;counter<=depth;counter++)
	{
//		cout<<"Inside Loop";
		for(offset=0;offset<vertices;offset++)
		{
			visited[offset] = false;
		}
		cout<<"\n\tDepth "<<counter<<": ";
		DFIDtraversal(v,counter);
		cout<<"\n\t";
	}
}

void Graph :: DFIDtraversal(int v,int currentDepth)
{
	if(visited[v] == false)
		cout<<v<<" ";
	visited[v] = true;
	if(currentDepth <= 0 )
		return;
	
	Node* temp = adjlist[v].getHead();
	while(temp!=NULL)
	{
		if(visited[temp->getData()] == false)
		{
			DFIDtraversal(temp->getData(),currentDepth-1);
		}
		temp = temp->getNextNodeAddress();
	}
}


void Graph :: BFS(int v)
{
	int counter;
	for(counter=0;counter<vertices;counter++)
	{
		visited[counter] = false;
		inqueuestate[counter]=false;
	}
	cout<<"\n\tBreadth First Traversal: ";
	BFStraversal(v);
}

void Graph :: BFStraversal(int v)
{
	cout<<v<<" ";
	visited[v] = true;
	Node* temp = adjlist[v].getHead();
	while(temp!=NULL)
	{
		if(inqueuestate[temp->getData()] == false && visited[temp->getData()] == false)
		{
			Q.enqueue(temp);
			inqueuestate[temp->getData()] = true;
		}
		temp = temp->getNextNodeAddress();
	}
	// cout<<"\n\tQueue Elements: ";
	// for(int counter=Q.getfront();counter<=Q.getrear();counter++)
	// {
	// 	cout<<Q.print(counter)<<" ";
	// }
	if(!Q.isEmpty())
	{
		temp = Q.dequeue();
		BFStraversal(temp->getData());
	}
}

	/* ******** Detection Of Cycle In A Graph Using Depth First Search ****** */

bool Graph :: detectCycle(int v)
{
	int counter;
	for(counter=0;counter<vertices;counter++)
	{
		visited[counter] = false;
		finished[counter] = false;
	}
	backedge = false;
	Cycle(v);
	return backedge;
}

void Graph :: Cycle(int v)
{
	visited[v] = true;
	//cout<<"\n\tTotal Calls: "<<totalTraversals;
	Node* temp = adjlist[v].getHead();
	while(temp!=NULL)
	{
		if(visited[temp->getData()] == true && finished[temp->getData()] == false)
		{
			backedge = true;
			return;
		}
		if(visited[temp->getData()] == false)
			Cycle(temp->getData());
		if(backedge == true)
			return;
		temp = temp->getNextNodeAddress();
	}
	finished[v] = true;
}

void Graph :: MSTprim(int v)
{
	int counter;
	for(counter=0;counter<vertices;counter++)
	{
		included[counter] = false;
	}
	for(counter=0;counter<vertices;counter++)
	{
		minWeight[counter] = 9999;
	}
	included[v] = true;
	totalIncludedVertices += 1;
	// cout<<"\n\tTotal Included Vertices: "<<totalIncludedVertices;
	prims();
}

void Graph :: prims()
{
	Node* temp;
	int counter,minindex,minWeightInList=9999,minNumberInList=9999,minimum=9999,mstWeight=0;
	Graph MST;
	MST.createGraph(vertices);
	while(totalIncludedVertices != vertices)
	{
		for(counter=0;counter<vertices;counter++)
		{
			if(included[counter] == true)
			{
				temp = adjlist[counter].getHead();
				while(temp!=NULL)
				{
					if(temp->getWeight() < minWeightInList && included[temp->getData()] == false)
					{
						minWeightInList = temp->getWeight(); //Gives Least Weight Value
						minNumberInList = temp->getData(); //Gives Node Number
					}
					temp = temp->getNextNodeAddress();
				}
				child[counter] = minNumberInList;
				minWeight[counter] = minWeightInList;
			}	
		}

		for(counter=0;counter<vertices;counter++)
		{
			if(minWeight[counter] < minimum)
			{
				minimum = minWeight[counter];
				minindex = counter;
			}
		}
		MST.insertEgde(minindex,child[minindex],minWeight[minindex]);
		included[child[minindex]] = true;
		totalIncludedVertices += 1;
		mstWeight += minWeight[minindex];
		minWeightInList=99999;minNumberInList=99999;minimum=99999;
	}
	MST.traverseGraph();
	cout<<"\n\tMinimum Weight of MST: "<<mstWeight;
}

int Graph :: compare(KruskalWeights object1,KruskalWeights object2)
{
	return(object1.weight < object2.weight);
}

void Graph :: MSTkruskal()
{
	// int counter;
	// for(counter=0;counter<vertices;counter++)
	// 	included[counter] = false;
	kruskal();
}

void Graph :: kruskal()
{
	KruskalWeights sortedWeights[totalEdges];
	Node* temp;
	Graph MST;
	int minWeight=0;
	bool cycle;
	MST.createGraph(vertices);
	int counter,offset=0;
	for(counter=0;counter<vertices;counter++)
	{	
		temp = adjlist[counter].getHead();
		while(temp!=NULL)
		{
			sortedWeights[offset].from = counter;
			sortedWeights[offset].to = temp->getData();
			sortedWeights[offset].weight = temp->getWeight();
			offset++;
			temp = temp->getNextNodeAddress();
		}	
	}
	//Sorting the edges in the non-decreasing order.
	sort(sortedWeights,sortedWeights+totalEdges,compare);
	// for(counter=0;counter<totalEdges;counter++)
	// {
	// 	cout<<"\n\tFrom: "<<sortedWeights[counter].from<<" To: "<<sortedWeights[counter].to;
	// }
	counter=0;
	while(counter<totalEdges && MST.totalEdges != vertices-1)
	{
		//if(included[sortedWeights[counter].from] == false && included[sortedWeights[counter].to] == false)
		{
			MST.insertEgde(sortedWeights[counter].from,sortedWeights[counter].to,sortedWeights[counter].weight);
			cycle = MST.detectCycle(sortedWeights[0].to);
			if(cycle == true)
				MST.deleteEdge(sortedWeights[counter].from,sortedWeights[counter].to);
			else
			{
				minWeight += sortedWeights[counter].weight;
				included[sortedWeights[counter].from] = true;
				included[sortedWeights[counter].to] = true;
			}
		}
		counter++;
	}
	if(MST.totalEdges == this->vertices-1)
	{
		cout<<"\n\tMST Created!";
		MST.traverseGraph();
		cout<<"\n\tMinimum Weight Of The MST is: "<<minWeight<<endl;
	}
	else
	{
		cout<<"\n\tMST Cannot be created!";
	}
}

void Graph :: dijkstras(int source)
{
	int counter,recentlyIncluded,totalIncluded=0,miniWeightVertex,miniWeight;
	int minimumWeight[vertices];
	Node* temp;
	for(counter=0;counter<vertices;counter++)
	{
		included[counter] = false;
		minimumWeight[counter] = 99999;
	}
	minimumWeight[source] = 0;
	included[source] = true;
	recentlyIncluded = source;
	while(totalIncluded != vertices)
	{
		temp = adjlist[recentlyIncluded].getHead();
		while(temp!=NULL)
		{
			if(minimumWeight[temp->getData()] > minimumWeight[recentlyIncluded] + temp->getWeight())
			{
				minimumWeight[temp->getData()] = minimumWeight[recentlyIncluded] + temp->getWeight();
			}
			temp = temp->getNextNodeAddress();
		}
		miniWeight = 100000;
		for(counter=0;counter<vertices;counter++)
		{
			if(miniWeight > minimumWeight[counter] && included[counter] == false)
			{
				miniWeight = minimumWeight[counter];
				miniWeightVertex = counter;
			}
		}
		recentlyIncluded = miniWeightVertex;
		included[recentlyIncluded] = true;
		totalIncluded++;
	}
	cout<<"\n\tThe Shortest Distance of Vertices From "<<source<<" are ";
	cout<<"\n\n\tSource\tDestination\tDistance";
	for(counter=0;counter<vertices;counter++)
	{
		cout<<"\n\t"<<source<<"\t"<<counter<<"\t\t"<<minimumWeight[counter];
	}
}

int main()
{
	int vertices,choice,u,v,weight;
	char sentinal='y';
	bool result;
	Graph G;
	cout<<"\n\tEnter The Number Of Vertices: ";
	cin>>vertices;
	G.createGraph(vertices);
	while(1)
	{
		cout<<"\n\t1.Insert An Edge\n\t2.Delete An Edge\n\t3.Traverse A Graph\n\t4.DFS\n\t5.BFS\n\t6.Detect Cycle\n\t7.Minimum Spanning Tree Using Prims\n\t8.Minimum Spanning Tree Using Kruskals\n\t9.Single Source Shortest Path(Dijkstras)\n\t10.DFID\n\t11.Exit\n\t";
		cin>>choice;
		switch(choice)
		{
			case 1:
				cout<<"\n\tEnter a vertex to insert an edge from: ";
				cin>>u;
				cout<<"\n\tEnter a vertex to insert an edge to: ";
				cin>>v;
//				cout<<"\n\tEnter the weight of an edge: ";
//				cin>>weight;
				G.insertEgde(u,v,0);
				break;
			case 2:
				cout<<"\n\tEnter a vertex to delete an edge from: ";
				cin>>u;
				cout<<"\n\tEnter a vertex to delete an edge to: ";
				cin>>v;
				G.deleteEdge(u,v);
				break;
			case 3:
				G.traverseGraph();
				break;
			case 4:
				cout<<"\n\tEnter The Source Node: ";
				cin>>v;
				G.DFS(v);
				break;
			case 5:
				cout<<"\n\tEnter The Source Node: ";
				cin>>v;
				G.BFS(v);
				break;
			case 6:
				cout<<"\n\tEnter The Source Node";
				cin>>v;
				result = G.detectCycle(v);
				if(result == true)
					cout<<"\n\tCycle Exists!";
				else
					cout<<"\n\tCycle Does Not Exists!";
				break;
			case 7:
				cout<<"\n\tEnter The Source Node";
				cin>>v;
				G.MSTprim(v);
				break;
			case 8:
				G.MSTkruskal();
				break;
			case 9:
				cout<<"\n\tEnter The Source Node";
				cin>>v;
				G.dijkstras(v);
				break;
			case 10:
				int depth;
				cout<<"\n\tEnter The Source Node: ";
				cin>>v;
				cout<<"\n\tEnter The Depth: ";
				cin>>depth;
				G.DFID(v,depth);
				break;
			case 11:
				exit(1);
		}
	}
}
