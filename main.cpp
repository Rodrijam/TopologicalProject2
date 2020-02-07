#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

int F(vector<vector<int> >, int vi/* given_list and desired vetex i */ );

int main ()
{
	string filename;
    cout << "Enter the file to read data: ";
    cin >> filename;
	
	ifstream fileIn(filename);
	
    if (!fileIn)                            // checks for file errors
    {
        cout << "File does not exist" << endl;
        exit(1);
    }	

	string clientData;
	int clientCount;
	
	vector<vector<int> > clientList;
	
	
	while (getline(fileIn, clientData))
	{
		vector<int> perVal;
		stringstream ss(clientData);
		string temp;
		while (ss >> temp)
			perVal.push_back(stoi(temp));
		clientCount++;
		clientList.push_back(perVal);
	}
		
	for (int i = 0; i < clientList.size(); i++)
	{
		cout << clientList[i][0] << " ";
		cout << clientList[i][1] << " ";
		cout << clientList[i][2] << endl;
	}
	
	/*
		Data 2
		v0 = Start
		v1 = cl
		v2 = c2
		v3 = c3
		v4 = c4 
		v5 = c5
		v6 = End
		F(v2)

	*/
	int max = 0;
	vector<int> opt;
	for (int i = 0; i < clientList.size(); i++)
	{
		int newVal = F(clientList, i);
		if (newVal > max)
		{
			max = newVal;
			opt = clientList[i];
		}
	}
	
	cout << "Max value: " << max << " from client: ";
	cout << opt[0] << " ";
	cout << opt[1] << " ";
	cout << opt[2] << endl;	
	
	fileIn.close();

	return 0;
}


int F(vector<vector<int> > clientList, int vi/* given_list and desired vetex i */ )
{
	/*
	int max = 0
	vertex * opt = new vertex;
	for (int i = 0; i < given_list.size(); i++)
	{
		// skip v0 and v6? or make i initialize at 1
		//newVal = max(F(v2->next) + v2->value)
		newVal = F(given_list, given_list[i]->next) + given_list[i]->value;
		if (newVal > max)
		{
			max = newVal
			opt = given_list[i];1;
		}
	}
	max(F(v2->next) + weight2, F(v2->next->next + weight2
	
	*/
	int max = 0;
	for (int i = vi; i < clientList.size(); i++)
	{
		// change 
		int newVal = F(clientList, i+1) + clientList[i][2];
		if (newVal > max)
		{
			max = newVal;
			//opt = clientList[i];
		}
	}
	
	return max;
}