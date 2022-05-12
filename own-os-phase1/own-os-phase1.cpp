#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
using namespace std;

//Global Declarations ********
ifstream fin;
ofstream fout;
int rfcount=0;
char mem[100][4], buff[60], ir[5], r[4];
string str;
int wfcount=0;
int ic, si=0, num;
bool c;
int flag=0;
int buffsize=0;
void load();
//*********initialsize*********************
void init()
{
  for(int i=0; i<100; i++)
  {
      for(int j=0; j<4; j++)
          mem[i][j]=' ';
  }
  for(int k=0; k<60; k++)
      buff[k]=' ';

  for(int l=0; l<4; l++)
      ir[l]=' ';

    ic=0;
}

//*****************GET DATA*******************
void readFun()
{ string s;
	cout<<"**********Inside readFUN**********:"<<endl;
	ir[3]=0;
	if(rfcount==0)
	{
	getline(fin,str);
	rfcount++;
	}
        else
         {  getline(fin,s);
             if(s[0]!='$')
               {
                 int a;
                   for(a=0;s[a]!='\0';a++)
                       { str[a]=s[a];}
               str[a]='\0';
               }
         }
	cout<<str<<endl;
	int k=0;
	int i,j;
	cout<<"NUM:"<<num;
	for(i=0;str[i]!='\0';i++,k++)
	{
		buff[k]=str[i];
	}
	buff[k]='\0';
 	cout<<endl;
	k=0;
	j=num;
	cout<<"j:"<<j<<endl;
	for(int i=0; buff[i]!='\0'; i++)
	{
	    mem[j][k++]=buff[i];
		if(k==4)
		{
			j++;
			k=0;
		}
	}
}

//****************** PUT DATA*******************************
void writeFun()
{ 
	ir[3]='0';
	cout<<"Inside write function"<<endl;
	if(wfcount!=0)
		{ fout.open("output.txt", ios::app); }
	else
	{       cout<<"Opening for first time"<<endl;
		fout.open("output.txt",ios::out);
		wfcount++;
	}

	int j;char Tbuff[40];
	int count=1;  int k=0;
	for(int i=0; i<40; i++)
	{	Tbuff[i]=' ';
	}
       cout<<"tbuff: "<<endl;
	for(int i=num; k<40; i++,k++)
	{
		for(j=0; j<4;j++,k++)
		{
			Tbuff[k]=mem[i][j];
		}
	}

	int pos=0;
	for(int i=39;i>=0;i--)
	{
		if(Tbuff[i]!=' ')
		{       pos=i;
			break;
		}
	}
	k=0;
        cout<<" writing: ";
	for(int i=num; k<=pos;i++,k++)
	{

		for(j=0;j<4;j++,k++)
		{
			fout<<mem[i][j];
		}

	}
	        fout<<endl;
		fout.close();
}

//********************TERMINATE PROGRAM**********************
void terminateFun()
{ fout.open("output.txt", ios::app);
   fout<<endl;
   fout<<endl;
  cout<<"Terminated"<<endl;
   fout.close();
}

//***********************MOS**************************
void mos()
{
	switch(si)
	{
		case 1:
			readFun();
			break;
		case 2:
			writeFun();
			break;
		case 3: flag=1;
			//terminateFun();
			break;
		default:
			break;
	}
}

void exeUserProgram()
{    for(int i=0;i<=buffsize;i++)
       {  if(flag==0)
    	{for(int j=0; j<4; j++)
        	ir[j]=mem[ic][j];

    	ic++;
    	si=0;
    	num=ir[2]-'0';
    	num=num*10+(ir[3]-'0');
    	if(ir[0]=='G' && ir[1]=='D')
    	{
    	    si=1;
	    mos();
    	}
    	else if(ir[0]=='P' && ir[1]=='D')
    	{
    	    si=2;
	    mos();
    	}
    	else if(ir[0]=='H')
    	{
    	    si=3;
	       mos();
	    }
	else if(ir[0]=='L' && ir[1]=='R')
    	{
		for(int i=0;i<4;i++)
		{
			r[i]=mem[num][i];

		}
		cout<<"\n Content of r: "<<r<<endl;
	}
	else if(ir[0]=='S' && ir[1]=='R')
    	{
		for(int i=0;i<4;i++)
		{
			mem[num][i]=r[i];

		}
		cout<<"\n Memory content after storing instruction"<<endl;
	}
	else if(ir[0]=='C' && ir[1]=='R')
    {
		for(int i=0;i<4;i++)
		{
			if(r[i]==mem[num][i])
				c=true;
			else
				c=false;
		}
	}
	else if(ir[0]=='B' && ir[1]=='T')
    {
		if(c==true)
			ic=num;
		cout<<endl<<"Contents of ic: "<<ic<<endl;
	}
        si=0;
    }
    else
        break;
       }
}

void stexe()
{
    cout<<"In Start Execution Program"<<endl;
    ic=0;
    exeUserProgram();
}

//*******************************load

void load()
{ 
while(!fin.eof())
{
  si=0;
  int k=0;
getline(fin,str);  cout<<str<<endl;
for(int i=0; str[i]!='\0'; i++)
    {  buff[k]=str[i]; k++;  }
    buff[k]='\0';
if(buff[0]=='$' && buff[1] == 'A' && buff[2] == 'M' && buff[3] == 'J')
{       buffsize=0; flag=0;
	init();
	getline(fin,str);
	k = 0; cout<<"Read str ="<<str<<endl;
    for(int i=0; str[i]!='\0'; i++)
 	buff[k++]=str[i];//It stores GD10PD10H
        buff[k]='\0';
       cout<<endl;
       cout<<"Bufer=  "<<buff<<endl;
    for(int i=0;buff[i]!='\0';i++)
        {cout<<buff[i];}

   int j=0;
   k=0;
for(int i=0; buff[i]!='\0'; i++)
{
	mem[j][k++]=buff[i];
        if(mem[j][k-1]=='H')
        { k=0;j++;}
	if(k==4)
	{
		j++;
		k=0;
	}
}

  buffsize=j-1;
//   cout<<"  BUFFSIZE: "<<buffsize;
//     cout<<"\n Memory content after storing instruction"<<endl;
//   cout<<"mem[20]="<<mem[20][0]<<mem[20][1]<<mem[20][2]<<mem[20][2]<<endl;
}
else if(buff[0]=='$' && buff[1] == 'D' && buff[2] == 'T' && buff[3] == 'A')
	stexe();
else if(buff[0]=='$'&&buff[1]=='E'&&buff[2]=='N'&&buff[3]=='D')
{ cout<<"exiting the program"<<endl; //exit(0);
   terminateFun();
}
}
//cout<<buff<<endl;
fin.close();

}


int main()
{ fin.open("OS.txt");
  load();

return 0;
}

