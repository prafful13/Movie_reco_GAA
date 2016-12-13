#include<bits/stdc++.h>
#define rand rand()
// #define M 5
// #define m 0
using namespace std;

char movies[50][100];

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

int compare( const void *aa, const void  *bb)
{
    int *a=(int *)aa;
    int *b=(int *)bb;
    if (a[25]<b[25])
     return -1;
    else if (a[25]==b[25]) 
    return 0;
    else  
     return 1;
}

int compare1( const void *aa, const void  *bb)
{
    int *a=(int *)aa;
    int *b=(int *)bb;
    if (a[0]<b[0])
     return -1;
    else if (a[0]==b[0]) 
    return 0;
    else  
     return 1;
}

void intobin(int n,int ans[])	{
	int j=4;
	for(int i=0;i<5;i++)	ans[i]=0;
	while(n>0)	{
		ans[j]=n%2;
		n/=2;
		j--;
	}
}

void randompop(float arr[][26])	{
	for(int i=0;i<20;i++)	for(int j=0;j<25;j++)	arr[i][j]=1;

	for(int j=0;j<20;j++)	for(int i=0;i<rand%25+15;i++)	arr[j][rand%25]=0;
}

void popadd(float w[5], float arr[][26], int pos)	{
	int value,col=0,k,j;
	for(int i=0;i<5;i++)	{
		value = (w[i]+1)*15.5;
		// cout<<"value: "<<value<<"\t";
		int binr[5];
		intobin(value,binr);
		// for(int l=0;l<5;l++)	cout<<binr[l];
		for(j=col,k=0;k<5;j++,k++)	arr[pos][j]=binr[k];
		col=j;
		// cout<<endl;
	}
	// cout<<endl;
}

int main()	{

	srand(time(NULL));

	user cuser;
	int cu;
	char cname[30];
	

	int n=0;

	fstream fp;
	fp.open("user.bin", ios::binary | ios::in);

	user obj;
	cout<<"Enter logged in user's name: ";
	gets(cname);

	while(fp.read((char*)&obj, sizeof(obj)))
    {
        obj.showData();
        if(strcmp(obj.getName(),cname)==0)	{
        	cuser=obj;
        	// cuser.showData();
        }
        n++;
    }
    fp.close();
	fp.open("user.bin", ios::binary | ios::in);

	/*
	*	important variables
	*/
	float v[n][5];
	int NumberOfOtherUsers;
	float px[40][50];
	int ratingsofallusers[n][51];
	for(int it=0;it<n;it++)	ratingsofallusers[it][50]=0;

	fp.seekg(0,ios::beg);

	int j=0,user=0,nor=0;
	while(fp.read((char*)&obj, sizeof(obj)))
    {
    	// obj.showData();
    	for(int rat=0;rat<50;rat++)	{
    		ratingsofallusers[user][rat]=obj.rating[rat];
    		if(obj.rating[rat]!=-1)	{
    			ratingsofallusers[user][50]+=obj.rating[rat];
    			nor++;
    		}
    		if(strcmp(obj.getName(),cname)==0)	cu=user;
    	}
    	ratingsofallusers[user][50]/=nor;
    	user++;

        if(strcmp(obj.getName(),cname)!=0)	{
        	int common=0;
        	v[j][0]=0;
        	v[j][1]=0;
        	v[j][2]=0;
        	v[j][3]=0;
        	v[j][4]=0;
        	for(int i=0;i<50;i++)	{
        		if(cuser.rating[i]!=-1 && obj.rating[i]!=-1)	{
        			common++;
        			int diff=abs(cuser.rating[i]-obj.rating[i]);
        			if(diff==0)	v[j][0]++;
        			else if(diff==1)	v[j][1]++;
        			else if(diff==2)	v[j][2]++;
        			else if(diff==3)	v[j][3]++;
        			else if(diff==4)	v[j][4]++;
        		}
			}
			v[j][0]/=common;
        	v[j][1]/=common;
        	v[j][2]/=common;
        	v[j][3]/=common;
        	v[j][4]/=common;
			j++;
		}
    }
	fp.close();
	NumberOfOtherUsers=j;

	//			GAA

	float population[40][26];
	for(int i=0;i<40;i++)	for(int j=0;j<25;j++)	population[i][j]=0;

	randompop(population);	

	for(int i=20;i<40;i++)	{
		float w[5];
		int ran[5];
		for(int j=0;j<5;j++)	{
			ran[j]=rand%5;
		}
		ran[0]+=16;
		ran[1]+=12;
		ran[2]+=8;
		ran[3]+=4;
		for(int j=0;j<5;j++)	ran[j]-=10;
		for(int j=0;j<5;j++)	w[j]=ran[j]/10.0;
		popadd(w,population,i);
	}

	int generations = 31;

	while(generations--)	{
		//					SELECTION

		//			Finding fitness values
		float fvalue[40];

		//			Weights in decimal
		float wpop[40][5];

		for(int i=0;i<40;i++)	{
			for(int j=0;j<5;j++){
				int sum=0;	
				for(int k=0,a=4;k<5;a--,k++)	{
					sum+=pow(2,a)*population[i][j*5+k];
				}

				wpop[i][j]=2*sum/31.0 - 1.0;
			}
		}

		//			Similarity values
		float sim[40][NumberOfOtherUsers];

		for(int i=0;i<40;i++)	{
			for(int j=0;j<NumberOfOtherUsers;j++)	{
				float sum=0.0;

				for(int k=0;k<5;k++)	sum+=wpop[i][k]*v[j][k]*1.0;
				sim[i][j]=(1.0/5.0)*sum;
			}
		}

		//		generated similarity values now find px and then mae which is fitness function

		//		Calculating Px Values

		for(int j=0;j<40;j++)	{
			for(int i=0;i<50;i++)	{
				float sum1=0,sum2=0;
				for(int it=0;it<=NumberOfOtherUsers;it++)	{
					if(it!=cu)	{
						sum1 += sim[j][it]*(ratingsofallusers[it][i]-ratingsofallusers[it][50]);
						sum2 += sim[j][it];
					}
				}
				px[j][i]=ratingsofallusers[cu][50] + sum1*1.0/sum2;
			}
		}

		float fitness[40];
		for(int it=0;it<40;it++)	{
			fvalue[it]=0;
			for(int i=0;i<6;i++)	{
				float sum=0;
				int noi=0;
				for(int j=0;j<50;j++)	{
					if(ratingsofallusers[i][j]!=-1)	{
						sum += abs(px[it][j]-ratingsofallusers[i][j]);
						noi++;
					}
				}
				sum/=noi*1.0;
				fvalue[it] += sum;
			}
		}

		for(int i=0;i<40;i++)	{
			population[i][25]=fvalue[i];
		}

		qsort(population,40,sizeof(population[0]),compare);

		if(generations>1)	{
			//		CROSSOVER	PC=1

			for(int i=0;i<40;i+=2)		{
				int pos=rand%25;
				for(;pos<25;pos++)	{
					int temp = population[i][pos];
					population[i][pos] = population[i+1][pos];
					population[i+1][pos] = temp;
				}
			}

			//		MUTATION PM=1

			for(int i=0;i<40;i++)	{
				for(int j=0;j<25;j++)	{
					if(population[i][j]==0)	population[i][j]=1;
					else	population[i][j]=0;
				}
			}
		}
	}

	int newrat[50][2];

	float weight[5];
	float simi[NumberOfOtherUsers];
	float predicted[50];
	for(int j=0;j<5;j++)	{
		int sum=0;	
		for(int k=0,a=4;k<5;a--,k++)	{
			sum+=pow(2,a)*population[0][j*5+k];
		}
		weight[j]=2*sum/31.0 - 1.0;
	}

	for(int j=0;j<NumberOfOtherUsers;j++)	{
		float sum=0.0;

		for(int k=0;k<5;k++)	sum+=weight[k]*v[j][k]*1.0;
		simi[j]=(1.0/5.0)*sum;
	}		

	for(int i=0;i<50;i++)	{
		float sum1=0,sum2=0;
		for(int it=0;it<=NumberOfOtherUsers;it++)	{
			if(it!=cu)	{
				sum1 += simi[it]*(ratingsofallusers[it][i]-ratingsofallusers[it][50]);
				sum2 += simi[it];
			}
		}
		predicted[i]=ratingsofallusers[cu][50] + sum1*1.0/sum2;
	}

	for(int i=0;i<50;i++)	{
		newrat[i][0]=predicted[i];
		newrat[i][1]=i+1;
	}

	qsort(newrat,50,sizeof(newrat[0]),compare1);

	cout<<endl;

	fp.open("movie.txt", ios::in);
	int i=0;
	while(fp.getline(movies[i],100))	{
		i++;
	}
	fp.close();

	for(int i=39;i<50;i++)	cout<<movies[newrat[i][1]]<<endl;
}