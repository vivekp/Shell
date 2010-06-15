#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main()
{
  do
  {
    FILE* pipe=popen("pwd","r");
    char buffer[256];
    string result="[Terminal:";
    while(!feof(pipe))
    {
      if(fgets(buffer,256,pipe)!=NULL)
      {
         result+=buffer;
      }
    }
    pclose(pipe);
    int length=result.length();
    result=result.substr(0,(result.length()-1)); 
    result.append("]");
    cout<<result;

    char* str=new char;
    cin.getline(str,50);
    string command="";
    command.append(str);

    char* arr[10]	;
    char* token=new char;
    int i=0;
    token=strtok(str," ");
    arr[0]=new char;
    arr[0]=token;

    while(token!=NULL)
    {
       i++;
       token=strtok(NULL," ");
       arr[i]=new char;
       arr[i]=token;
    }
/*    for(int j=0;j<i;j++)
    {
        cout<<arr[j]<<endl;
    } */ 
       int x=0;
       int d=fork();
       if(d==0)
       {
            char cmd[20]="/bin/";
            strcat(cmd,arr[0]);	

         //   cout<<cmd<<"  "<<arr[0]<<"\n";
            char* arg[10];
	    arg[0]=new char;
	    arg[0]=cmd;

	    for(int j=1;j<i;j++)
	    {
	      arg[j]=new char;
	      arg[j]=arr[j];
	    }
            arg[i]=new char;
	    arg[i]=(char*)0;
            x=execv(cmd,arg);
	  //  cout<<x<<"in child."<<"\n";
	    if(x==-1){ 
	       char cmd1[20]="/usr/bin/";
	       strcat(cmd1,arr[0]);
	       arg[0]=cmd1;
	       x=execv(cmd1,arg);
	    }
	    cout<<x<<" in child.\n";
	    cout<<"\'"<<command<<"\' is an Invalid command.\n"; 
       }
       else 
       {
           wait(NULL);
	   cout<<"\n"<<x<<"in parent.";
           cout<<"\nCommand Executed.\n";
       }  
   }while(true);

   return 0;
}
