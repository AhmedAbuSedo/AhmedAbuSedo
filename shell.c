//Ahmed Abu Sedo 
//my gmail : abosedoahmed@gmail.com
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
void handler (int sig){
}
int main (int argc , char *argv[]){
	signal(SIGINT,&handler); // handle signal send by ctrl+c to kill process .
	signal(SIGTSTP,&handler);// handle signal send by ctrl+z to stop process .
	size_t size = 100;
	char currentPath [size];
	char currentpath_env [size];
	getcwd(currentpath_env,size);// get current path
	strcat (currentpath_env ,argv[0]); // concat current path with path of exceute file 
	setenv("SHELL",currentpath_env,1);//set the excecute path in env
	int count = 0;
	while(1){
		int f_d =0;
		int fileopen;
		int save_stdout = dup(1);
		int back_ground =0;
		if (count ==0){    //to clear screen in the first
		     char * argv[2];
		     argv[0]="clear";
		     argv[1]=NULL;
		     count =1;
		     int pid1 =fork();
		     if (pid1 !=0){
		         wait(NULL);
		        
		    }else{
		         execvp(argv[0],argv); 
		           exit(0);
		   }
		   }
		 getcwd(currentPath,size); // get current path
		 
		 
		printf("\e[1m\e[32mahmed@ahmed-VirtualBox:\e[21m\e[0m");
	         printf("\e[1m\e[38;5;25m~%s\e[21m\e[0m\e[38;5;116m$ " , currentPath); //print current path in prompt
		char command[100] ;
		char command2[100];
		memset(command,0,100); //after write command to reset command
		scanf ("%[^\n]99s", command);// scan command 
		strcpy(command2,command);
		getchar();
		char* args[11];
		char* command_token = strtok (command, " "); //to divide command to args
		int argscounter = 0;
        while (command_token != NULL && argscounter < 10) {
            args[argscounter] = command_token;
            command_token =strtok (NULL, " ");
            argscounter ++;
            if (command_token== NULL || argscounter==10){
               args[argscounter]=NULL;
            }
            }
            char ch ='&';
            char * found_ch ;
            found_ch = strchr(command2 ,ch);
            if (found_ch!=NULL){ // if comment have & run it in backgruond
            	int j= 0;
            	while(j<11){
            	if (!strcmp(args[j],"&")){
            		break;
            	}
            	j++;
            	}
            	if (args[j+1]==NULL){
            		args [j]=NULL;
            
            	     back_ground = 1;  // to run this command in child with out wait in pearent .
		  	
            
            }
            }
            	if (args[0]==NULL){ //in the first prompt if you enter enter with out args
            		continue;
            	}
            	//after you enter command if you enter enter with out args in prompt 
            	if(command[0]==0){ 
            	continue;
            	}
            char ch2 ='>';
            char * found_ch2 ;
            found_ch2 = strchr(command2 ,ch2);
             if (found_ch2!=NULL){ //if you have > in your command
            	int j= 0;
            	int i =0;
            	int k =0;
            	while(j<11){
            	if (!strcmp(args[j],">")){ // faund the index of > or >>
            		i=j;
            		break;
            	}else if(!strcmp(args[j],">>")){
            		k=j;
            		break;
            	}
            	else{
            	j++;
            	}
            	}
            	if(i!=0){ //overwrite to file
            	fileopen = open(args[j+1]  , O_WRONLY | O_CREAT |O_TRUNC,0777);
            		if (fileopen == -1){
            			continue;
            		}
            		
            		while (j<11){
            		args [j]=NULL;
            		j++;
 			}
 			}
 			
 			if(k!=0){ //append the open file
            	fileopen = open(args[j+1]  ,O_WRONLY | O_APPEND| O_CREAT,0777);
            		if (fileopen == -1){
            			continue;
            		}
            		
            		while (j<11){ //after open file set it and > null
            		args [j]=NULL;
            		j++;
 			}
 			}
 			
 			
            			dup2(fileopen ,1); // to swap the strout
            			f_d=1; //helper to return strout
           }
           
           
           
            
           
           
           
           
             char ch3 ='<';
            char * found_ch3 ;
            found_ch3 = strchr(command2 ,ch3);
             if (found_ch3!=NULL){
            	int j= 0;
            	int i =0;
            	int k =0;
            	
            	if (!strcmp(args[1],"<")){
            		i=1;
            		
            	}else if(!strcmp(args[1],"<<")){
            		k=1;
            		
            	}
            		
            	if (i!=0){
            	fileopen = open(args[0]  , O_WRONLY | O_CREAT |O_TRUNC,0777);
            		if (fileopen == -1){
            			continue;
            		}
            		while (j+2<11){
            		args [j]=args [j+2];
            		j++;
 			}
            		}
            		if (k!=0){
            	fileopen = open(args[0]  , O_WRONLY | O_APPEND| O_CREAT,0777);
            		if (fileopen == -1){
            			continue;
            		}
            		while (j+2<11){
            		args [j]=args[j+2];
            		j++;
 			}
            		}
            		
 			
 			
 			
            			dup2(fileopen ,1);
            			f_d=1;
            			
            			
            			
           }
           
           
           
            if (!strcmp(args[0],"myShell")){ // to read and exce command from file
            
           
             
             
             if (args[1]==NULL){ //you have to write the file of command
            		printf("\e[31m%s : THIS COMMAND MUST HAS ARGUMENT\e[0m\e[38;5;116m\n",args[0]); 
            		continue;
            		}else{
            	    FILE * inp;
           	   char str[1000] ;
            	   char str2[1000] ;
           inp = fopen(args[1],"r");
            	  
            while(fgets(str,1000,inp)!=NULL){ //read line line from file to the end of file 
            strcpy(str2,str);
            int f_d =0;
		int fileopen;
		int save_stdout = dup(1);
		int back_ground =0;
           
            	char s = '\n';
            	char * found ;
            	found = strchr(str ,s); 
            	* found =' ';
            	 printf("\e[38;5;63m\e[1mEXECUTION COMMAND : %s \e[21m\e[0m\e[38;5;116m\n",str);
            	char* args[11];
		char* command_token = strtok (str, " ");
		int argscounter = 0;
            	 while (command_token != NULL && argscounter < 10) {
                   args[argscounter] = command_token;
                   command_token =strtok (NULL, " ");
                   argscounter ++;
                   if (command_token== NULL || argscounter==10){
                   args[argscounter]=NULL;
            }
            }	
            char ch ='&';
            char * found_ch ;
            found_ch = strchr(str2 ,ch);
            if (found_ch!=NULL){
            	int j= 0;
            	while(j<11){
            	if (!strcmp(args[j],"&")){
            		break;
            	}
            	j++;
            	}
            	if (args[j+1]==NULL){
            		args [j]=NULL;
            
            	     back_ground = 1;
		  	
            
            }
            }
            	if (args[0]==NULL){
            		continue;
            	}
            	if(command[0]==0){
            	continue;
            	}
            char ch2 ='>';
            char * found_ch2 ;
            found_ch2 = strchr(str2 ,ch2);
             if (found_ch2!=NULL){
            	int j= 0;
            	int i =0;
            	int k =0;
            	while(j<11){
            	if (!strcmp(args[j],">")){
            		i=j;
            		break;
            	}else if(!strcmp(args[j],">>")){
            		k=j;
            		break;
            	}
            	else{
            	j++;
            	}
            	}
            	if(i!=0){
            	fileopen = open(args[j+1]  , O_WRONLY | O_CREAT |O_TRUNC,0777);
            		if (fileopen == -1){
            			continue;
            		}
            		
            		while (j<11){
            		args [j]=NULL;
            		j++;
 			}
 			}
 			
 			if(k!=0){
            	fileopen = open(args[j+1]  ,O_WRONLY | O_APPEND| O_CREAT,0777);
            		if (fileopen == -1){
            			continue;
            		}
            		
            		while (j<11){
            		args [j]=NULL;
            		j++;
 			}
 			}
 			
 			
            			dup2(fileopen ,1);
            			f_d=1;
           }
           
           
           
            
           
           
           
           
             char ch3 ='<';
            char * found_ch3 ;
            found_ch3 = strchr(str2 ,ch3);
             if (found_ch3!=NULL){
            	int j= 0;
            	int i =0;
            	int k =0;
            	
            	if (!strcmp(args[1],"<")){
            		i=1;
            		
            	}else if(!strcmp(args[1],"<<")){
            		k=1;
            		
            	}
            		
            	if (i!=0){
            	fileopen = open(args[0]  , O_WRONLY | O_CREAT |O_TRUNC,0777);
            		if (fileopen == -1){
            			continue;
            		}
            		while (j+2<11){
            		args [j]=args [j+2];
            		j++;
 			}
            		}
            		if (k!=0){
            	fileopen = open(args[0]  , O_WRONLY | O_APPEND| O_CREAT,0777);
            		if (fileopen == -1){
            			continue;
            		}
            		while (j+2<11){
            		args [j]=args[j+2];
            		j++;
 			}
            		}
            		
 			
 			
 			
            			dup2(fileopen ,1);
            			f_d=1;
            			
            			
            			
           }
           
            	  if (!strcmp(args[0],"clear")){
            printf("\e[31m%s : COMMAND NOT FOUND\e[0m\e[38;5;116m\n",args[0]);
            continue;
            }
             
            if (!strcmp(args[0],"cd")){
            	if (args[1]==NULL){
            		printf("\e[38;5;42mThe Current Path Is: \e[95m\e[4m%s\e[24m\e[0m\e[38;5;116m\n",currentPath);
            	}else {
            	   chdir(args[1]);
            	   }
            }else if (!strcmp(args[0],"quit")){
            		if (args[1]!=NULL){
            		printf("\e[31m%s : THIS COMMAND HAS NO ARGUMENT\e[0m\e[38;5;116m\n",args[0]); 
            		continue;
            		}else {
            		args[0]="clear";
            		
            		int pid =fork();
		    int check_success ;
		    if (pid !=0){
		        waitpid(pid,NULL,0);
		   }else{
		   	
		       check_success = execvp(args[0],args);
	printf("\e[31m%s : COMMAND NOT FOUND\e[0m\e[38;5;116m\n",args[0]);   
			if (check_success==-1){
				exit(0);
			}
		   }
                      exit(0);
                      }
                   }else if (!strcmp(args[0],"pause")){
            			if (args[1]!=NULL){
            		printf("\e[31m%s : THIS COMMAND HAS NO ARGUMENT\e[0m\e[38;5;116m\n",args[0]); 
            		continue;
            		}else {
            		while(1){
            		char c;
			scanf("%c",&c);
            		if(c=='\n'){
            		break;
            		}
            		}
            		}
            	
            }else {
		if (!strcmp(args[0],"ls") || !strcmp(args[0],"dir")){
			int pointer1 = 0;
			while (pointer1+1<11){
				if(args[pointer1]==NULL){
					args[pointer1] = "--color=auto";
					args[pointer1+1]=NULL;
					break;				
				}
				pointer1++;
			}
		
		}


            else if (!strcmp(args[0],"environ")){
            	
            	args[0]="env";
            	
            	
            }else if (!strcmp(args[0],"env")){
            		printf("\e[31m%s : COMMAND NOT FOUND\e[0m\e[38;5;116m\n",args[0]);
            		continue;
            
            
            }
            else if (!strcmp(args[0],"help")||!strcmp(args[0],"Help")){
            	 	if (args[1]!=NULL){
            		printf("\e[31m%s : THIS COMMAND HAS NO ARGUMENT\e[0m\e[38;5;116m\n",args[0]); 
            		continue;
            		}else {
            	 	printf("\e[38;5;35m\n");
            	     args[0] ="more";
            	     args[1] = "/home/ahmed/Desktop/Shellproject/help.txt";
            	     args[2]=NULL;
            	     }
            	   }
                   else if (!strcmp(args[0],"clr")){
                   	if (args[1]!=NULL){
            		printf("\e[31m%s : THIS COMMAND HAS NO ARGUMENT\e[0m\e[38;5;116m\n",args[0]); 
            		continue;
            		}else {
                      args[0]="clear";
                      }
                   }
                   
                   
		    int pid =fork();
		    int check_success ;
		    if (pid !=0){
		    	if (back_ground==1){
		    	printf("%d\n",pid);
		    	}else{
		        waitpid(pid,NULL,0);
		        }
		        
		   }else{
		   	
		       check_success = execvp(args[0],args);
	printf("\e[31m%s : COMMAND NOT FOUND\e[0m\e[38;5;116m\n",args[0]);   
			if (check_success==-1){
				exit(0);
			}
		   }
		   if(f_d==1){
		    dup2(save_stdout,1);
		   close(fileopen);	
	         }
	    }
	               
            }  	
                     fclose(inp);
                   }  	   	   	
            	   		
            	   }  else {
            	   
            	    if (!strcmp(args[0],"clear")){ //command clr to clear  
            printf("\e[31mclr : COMMAND TO CLEAR SCREEN\e[0m\e[38;5;116m\n");
            continue;
            }
             
            if (!strcmp(args[0],"cd")){  
            	if (args[1]==NULL){//to print current path
            		printf("\e[38;5;42mThe Current Path Is: \e[95m\e[4m%s\e[24m\e[0m\e[38;5;116m\n",currentPath);
            	}else {//to change cwd 
            	   chdir(args[1]);
            	   }
            }else if (!strcmp(args[0],"quit")){ //to exit my Shell
            		if (args[1]!=NULL){
            		printf("\e[31m%s : THIS COMMAND HAS NO ARGUMENT\e[0m\e[38;5;116m\n",args[0]); 
            		continue;
            		}else {
            		args[0]="clear"; //to clear my shell befor exit 
            		
            		int pid =fork();
		    int check_success ;
		    if (pid !=0){
		        waitpid(pid,NULL,0);
		   }else{
		   	
		       check_success = execvp(args[0],args);
	printf("\e[31m%s : COMMAND NOT FOUND\e[0m\e[38;5;116m\n",args[0]);   
			if (check_success==-1){
				exit(0);
			}
		   }
                      exit(0);
                      }
                   }else if (!strcmp(args[0],"pause")){
            			if (args[1]!=NULL){
            		printf("\e[31m%s : THIS COMMAND HAS NO ARGUMENT\e[0m\e[38;5;116m\n",args[0]); 
            		continue;
            		}else {
            		while(1){
            		char c;
			scanf("%c",&c);
            		if(c=='\n'){
            		break;
            		}
            		}
            		}
            	
            }else {
		if (!strcmp(args[0],"ls") || !strcmp(args[0],"dir")){
			int pointer1 = 0;
			while (pointer1+1<11){
				if(args[pointer1]==NULL){
					args[pointer1] = "--color=auto";
					args[pointer1+1]=NULL;
					break;				
				}
				pointer1++;
			}
		
		}


            else if (!strcmp(args[0],"environ")){
            	
            	args[0]="env";
            	
            	
            }else if (!strcmp(args[0],"env")){
            		printf("\e[31m%s : COMMAND NOT FOUND\e[0m\e[38;5;116m\n",args[0]);
            		continue;
            
            
            }
            
            else if (!strcmp(args[0],"help")||!strcmp(args[0],"Help")){
            	 	if (args[1]!=NULL){
            		printf("\e[31m%s : THIS COMMAND HAS NO ARGUMENT\e[0m\e[38;5;116m\n",args[0]); 
            		continue;
            		}else {
            	 	printf("\e[38;5;35m\n");
            	     args[0] ="more";
            	     args[1] = "/home/ahmed/Desktop/Shellproject/help.txt";
            	     args[2]=NULL;
            	     }
            	   }
                   else if (!strcmp(args[0],"clr")){
                   	if (args[1]!=NULL){
            		printf("\e[31m%s : THIS COMMAND HAS NO ARGUMENT\e[0m\e[38;5;116m\n",args[0]); 
            		continue;
            		}else {
                      args[0]="clear";
                      }
                   }
		    int pid =fork();
		   
		    if (pid !=0){
		    	if (back_ground==1){ //if command have & run in background
		    	printf("%d\n",pid);
		    	}else{
		        waitpid(pid,NULL,0); //wait your child
		        }
		        
		   }else{
		   	
		      execvp(args[0],args);
	printf("\e[31m%s : COMMAND NOT FOUND\e[0m\e[38;5;116m\n",args[0]);   
			
				exit(0);
			
		   }
	    }
	    
	}
		
		
	if(f_d==1){ //if change stdout return to stdout (screen) 
		    dup2(save_stdout,1);
		   close(fileopen);	
	         }
		
	}
	return 0;
}
