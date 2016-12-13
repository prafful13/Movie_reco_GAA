#include<bits/stdc++.h>
#define rand rand()

using namespace std;

class user{
public:
	char name[30];
	char gender;
	int rating[50];

	void setData()	{
		cout<<"Enter name: ";
		gets(name);
		cout<<"Enter Gender: ";
		cin>>gender;
		getchar();

		for(int i=0;i<50;i++)	rating[i]=-1;
		int nop=rand%50+30;
		
		for(int i=0;i<nop;i++)	{
			int j=rand%50;
			rating[j]=rand%4;
			rating[j]++;
		}
	}
	void showData()	{
		cout<<"Name: "<<name;
		cout<<endl<<"Gender: "<<gender<<endl;
		cout<<"Ratings\n";
		for(int i=0;i<50;i++)	cout<<rating[i]<<",";
		cout<<endl;
	}
	char * getName()	{
		return name;
	}
};

int main()	{

	fstream fp;

	srand(time(NULL));
	while(1)	{

		fp.open("user.bin", ios::binary | ios::app);

		char ch='n';
		
		user obj;
		obj.setData();
		obj.showData();

		fp.write((char*)&obj, sizeof(user));

		fp.close();

		cout<<endl<<"Do you wish to exit(y/n)?"<<endl;
		cin>>ch;
		getchar();
		if(ch=='y')	exit(0);
	}
}