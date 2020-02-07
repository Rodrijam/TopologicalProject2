#include<iostream>
#include<list>
#include<queue>
#include<vector>
#include<bits/stdc++.h> 

using namespace std;

struct vertex{
	
	int clientNum = 0;
	int StartDate = 0;
	int EndDate = 0;
	int Rent = 0;
	int InEdge = 0;
	vertex* next = NULL;
};

void addEdge(list<vertex>  Adjlist[], int Index, vertex v);
vector<int> topoSort(list<vertex>  Adjlist[], int DataSize);
int F(list<vertex> Adjlist[], vertex vi);

vector<vertex> opt;	// vector of optimal path

int main(){
	
	string filename;
	cout << "Enter the file to read data: ";
	cin >> filename;
	
	ofstream fileOut("out" + filename);
	
	ifstream fileIn(filename);

	    if (!fileIn)                            // checks for file errors
	    {
		cout << "File does not exist" << endl;
		exit(1);
	    }

	string clientData;

	vector<vertex> temp;
	vertex S;
	temp.push_back(S);

	int clientCount = 0;

	while (getline(fileIn, clientData))
	{
		clientCount++;
		vector<int> perVal;
		stringstream ss(clientData);
		string tempS;
		
		while (ss >> tempS)
			perVal.push_back(stoi(tempS));
		
		vertex tempV;
		tempV.StartDate = perVal[0];
		tempV.EndDate = perVal[1];
		tempV.Rent = perVal[2];
		tempV.clientNum = clientCount;
		temp.push_back(tempV);
	}
	
	cout << "\nThere are " << clientCount << " clients in this file\n" << endl;
	fileOut << "\nThere are " << clientCount << " clients in this file\n" << endl;
	
	vertex E;
	E.clientNum = clientCount + 1;
	temp.push_back(E);
	list<vertex> Adjlist[temp.size()+2];

	for(int i = 1; i < temp.size()-1; i++)
	{
		for(int j = i+1; j < temp.size()-1; j++)
		{
			if(temp[i].EndDate <= temp[j].StartDate)
			{
				addEdge(Adjlist, i, temp[j]); 
				temp[j].InEdge++;
			}
			if(temp[j].EndDate <= temp[i].StartDate)
			{
				addEdge(Adjlist, j, temp[i]);
				temp[i].InEdge++;

			}
		}		
	}
	for(int i = 1; i < temp.size()-1; i++)
	{
		if(Adjlist[i].size() == 0)
			addEdge(Adjlist, i, E);
		if(temp[i].InEdge == 0)
			addEdge(Adjlist, 0, temp[i]);
	
	}

	int DataSize = temp.size();
	vector<int> tpd_order = topoSort(Adjlist, DataSize);
	
	vector<vertex> tpd;	// make a list of the vertexes from the tpd_order
	
	for (int i=0; i<tpd_order.size(); i++) 
		tpd.push_back(temp[tpd_order[i]-1]);

	int max = 0;
	
	opt.push_back(S);
	
	for (int i = 0; i < tpd.size(); i++)
	{
		int newVal = F(Adjlist, temp[i+1]);
		cout << "-------------------------------" << endl;
		if (newVal > max)
		{
			max = newVal;
			opt[0] = temp[i+1];
		}
	}
	
	cout << "\nOptimal revenue earned is: " << max << endl;
	cout << "Clients contributing to this optimal revenue: ";

	fileOut << "\nOptimal revenue earned is: " << max << endl;
	fileOut << "Clients contributing to this optimal revenue: ";

	reverse(opt.begin()+1, opt.end());


	for (int i=0; i < opt.size(); i++) 
	{
		cout << opt[i].clientNum;
		fileOut << opt[i].clientNum;
		if (i != opt.size()-1)
		{
			cout << ", "; 
			fileOut << ", "; 
		}
	}
	cout << endl;
	fileOut << endl;
	
	fileOut.close();
	
	return 0;
}

void addEdge(list<vertex> Adjlist[], int Index, vertex v)
{
	Adjlist[Index].push_back(v);
//	Adjlist[Index].next = v;	
}

vector<int> topoSort(list<vertex>  Adjlist[], int DataSize)
{
	vector<int> in_degree(DataSize, 0);

	for(int u = 0; u < DataSize; u++)
	{
		list<vertex>::iterator itr;
		int listIndex = 0;
		for (itr = Adjlist[u].begin(); itr != Adjlist[u].end(); itr++)
		{ 
         	in_degree[listIndex]++; 
		    listIndex++;
		}
	} 
  
	queue<int> q; 
	for (int i = 0; i < DataSize; i++) 
		if (in_degree[i] == 0) 
			q.push(i); 

	int cnt = 0; 
  
	vector <int> top_order; 
  
	while (!q.empty()) 
	{ 
		int u = q.front(); 
		q.pop(); 
		top_order.push_back(u); 
		int listIndex = 0;
		list<vertex>::iterator itr; 
		for (itr = Adjlist[u].begin(); itr != Adjlist[u].end(); itr++) 
		{
			if (--in_degree[listIndex] == 0) 
			q.push(listIndex); 
			listIndex++;
		}
		cnt++; 
	} 
	
	//top_order.insert(top_order.begin(),2);
	
	return top_order;

} 
		
int F(list<vertex> Adjlist[], vertex vi)
{	
	int max = 0;
	int ccount = 0;

	for (list<vertex>::iterator it = Adjlist[vi.clientNum].begin(); it != Adjlist[vi.clientNum].end(); ++it)
	{
		vertex inV = *it;
		int newVal = F(Adjlist, inV) + vi.Rent;
		
		// DEBUG for optimal path below
		cout << "Sub New Value: " << newVal << " from Object " << vi.clientNum << " to " << inV.clientNum << endl;
		
		if (newVal > max)
		{
			ccount++;
			if (opt.size() <= ccount)
				opt.push_back(vi);
			else
				opt[ccount] = vi;
			max = newVal;
		}
	}
	
	return max;
}

