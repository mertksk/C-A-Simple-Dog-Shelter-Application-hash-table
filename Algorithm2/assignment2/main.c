/**
*
*		Author of this code -> Mert Özçelik
*
*/



#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#include <string.h>

/*DEFINING TYPE TO HOLD ALL DETAILS IN AN ARRAY*/
typedef struct data{
	int k;
    char name[30];  
    float weight,height;
    char leave[30];
    char entry[30];
    
    
	   
 

}data; // VARIABLE NAME


void menu();
void del(int,data[],int,data deletedList[]);
void search(int,data[],int);

 
 
// Function to print an array 
void printArray(data arr[], int n) 
{ 	
	printf("ALL DOGS\n");
	printf("-------------------------------------------\n");
	for (int i = 0; i < n; i++)  
    { 	
    	if(arr[i].k==-1){
 			printf("\nSLOT %d",i+1);
    		printf("\nEmpty Slot\n");
    		
		}
    	else{
    		printf("\nSLOT %d",i+1);
       		printf("\nUnique Identifier: %d\nName: %s\nWeight: %.2f\nHeight: %.2f\nEntry Date:%s\n" ,arr[i].k,arr[i].name,arr[i].weight,arr[i].height,arr[i].entry   );
		
			printf("Leave Date: %s\n\n",arr[i].leave);
		
	}
    } 
} 
  
 //The function is for hashing in quadratic probing 
void hashing(data hash_table[], int size, data arr[]) //1)table 2)size 3)Value array 
{ 
    for (int i = 0; i < size; i++)  
    { 
        int value = arr[i].k % size; // initial key
  
        if (hash_table[value].k == -1)   // if -1 then empty
            hash_table[value] = arr[i];  //slot is available , put
        else 								//if not
        { 
            for (int j = 0; j < value; j++)  
            { 
                int t = (value + j * j) % value;  //second key until finds quadratic probation
                if (hash_table[t].k == -1)  
                { 
                    hash_table[t] = arr[i];  		//put it other appropirate slot
                    break; 
                } 
            } 
        } 
    } 
    printArray(hash_table, size); //sending hash table and size to print
} 
  
//Main block  
int main() 
{ 	
	/*Initial */
	int counter=0,select=0,old=0;
	int N = 11; // initial size of Dog Table
	data *arr,*temp;  //variables for swap process
	data *deletedList;// to hold Adopted Variables
	
	bool activeHigh=false;  //control mechanism
	arr=(data*)malloc(N * sizeof(data));   // -1 load
	for(int i=0;i<N;i++){
		arr[i].k=-1;
	}
	deletedList=(data*)malloc(N * sizeof(data)); 
	for(int i=0;i<N;i++){
			deletedList[i].k=-1;
		}
	 /*Initial ends*/
	L1: 	//go to;
	counter++;	
	old=N;
	if(counter>=N){		//if true Lambda is less then 0.5 double the table
		N=N*2;	
		activeHigh=true;
	}
	
	// Load new Nulls
	temp=arr;
    arr=(data*)malloc(N * sizeof(data));
	for(int i=0;i<old;i++){
		arr[i]=temp[i];
	} 
 
    if(activeHigh==true){
		for(int i=(N/2);i<N;i++){
			arr[i].k=-1;
		} 
  		activeHigh=false;
	}
	//Data enter
	while(true){
		L2:
		if(counter==1){
			 printf("ENTER INITIAL VALUES\n");
			 printf("--------------------------------------------------------------------\n");
		 }
		printf("\nEnter unique identifier for %dth Dog (-1 to exit):",counter);
		scanf("%d",&select);
	
	/*Input taking*/
		if(select==-1) break;
		arr[counter-1].k=select;
		printf("Enter Name: ");
		scanf("%s",arr[counter-1].name);
		printf("Enter Weight: ");
		scanf("%f",&(arr[counter-1].weight));
		printf("Enter Height: ");
		scanf("%f",&(arr[counter-1].height));
		printf("Enter Entry Date:");
		scanf("%s",arr[counter-1].entry);
		strcpy(arr[counter-1].leave,"none");
		if(counter>=N) goto L1;
		counter++;
		 
		}

  
    data *hash_table;
    hash_table=(data*)malloc(N * sizeof(data)); 
    // Initializing the hash table 
    for (int i = 0; i < N; i++)  
    { 
        hash_table[i].k = -1; 
    } 
    
	//sending to hashing with quadratic probing  
    hashing(hash_table, N, arr); 
    
    int op=0;
    while(true){
    	
    	menu();
    	printf("Enter Your Selection\n");
    	scanf("%d",&op);
    	switch (op)
{
		     case 1:
		     	goto L2; //To adding
		    	break;	
		     
		     //Adopt Dog
		     case 2:
			    
		     	printf("Enter the Unique Identifier to Adopt: ");    
				scanf("%d",&select);
				del(select,hash_table,N,deletedList);
				
				//Preperation of Rehashing 
			    arr=(data*)malloc(N * sizeof(data)); 
			    for(int i=0;i<N;i++){
			    	arr[i].k=-1;
				}
				for(int i=0;i<N;i++){
				    arr[i]=hash_table[i];
					}
				for(int i=0;i<N;i++){
					hash_table[i].k=-1;
				}
				
				//Rehashing after removing variable
				hashing(hash_table, N, arr); 
		    	break; 	
		     
		    
		     //search a dog
		     case 3:
		     	printf("Enter unique identifier: ");
		     	scanf("%d",&select);
		     	search(select,hash_table,N);
		     	break;	
		     	
		     	//exit
		     case 4:
		     	printf("Thank You For Coming Our Shelter\n");
		     	printf("Hope to see you again!\n");
			     exit(0);	
		     
		     default:
		     	printf("\nUndefined Value!\n");
		     	break;
}
    	
	}

    return 0; 
} 
//search function
void search(int value,data hash_table[],int size){
	

	 int key = value % size;		// key finding
    
     for (int i = 0; i < size; i++)  
    	{
		if(hash_table[key].k==-1){			// if slot is -1
			printf("The value could not be found \n");
			break;
		} 
		else if(hash_table[key].k!=value){   //if slot is not equal our value then change the key according to quadratic probing
			key=(key+value*value) % size;
		}
		else{ // if none of above happens 
			
			printf("\n--------------------------------------------------\n");
			printf("Value Found\n");
			printf("Details:\n");
			printf("Unique Value: %d\n",hash_table[key].k);
			printf("Name: %d\n",hash_table[key].k);
			printf("Weight: %d\n",hash_table[key].k);
			printf("Entry Date: %d\n",hash_table[key].k);
			printf("Leave Date: %d\n",hash_table[key].k);

			break;
			
		}	}
}

//adopt function
void del(int value,data hash_table[],int size,data deletedList[])
{
	data *temp;	//Temporary pointer
	if(size>=11){
		temp=deletedList;						
		deletedList=(data*)malloc(size * sizeof(data));   //re evaluate our Adopted Dog List according to possibility
		for(int i=0;i<size/2;i++){
			
			deletedList[i]=temp[i]; 
		}
		for(int i=size/2;i<size;i++){
			deletedList[i].k=-1;
		}
	}
	
	
	int key = value % size; // key finding
	
	for (int i = 0; i < size; i++)  
	    	{
		if(hash_table[key].k==-1){			// if -1 then no value
			printf("\nThe value could not be found \n");
			break;
			} 
		else if(hash_table[key].k!=value){ // next flag
			key=(key+value*value) % size;	// new key in case the slot it looks for is full 
			}	
		else{			//if value in the slot is equal to ,then delete
				
			printf("The Dog Has Been Adopted ,and Deleted From The System!\n ");
			/*Adding New Dop Adopted to the Table*/
			temp[0]=hash_table[key];
			for(int a=0;a<size;a++){
				if(deletedList[a].k==-1){		
					deletedList[a]=temp[0];
					break;
				}
				else{
					continue;
				}
				
			}
			
			hash_table[key].k=-1; //Remove index in Hash_Table
			
			break;			}								}
			/*Preparing  Adopted Dog for Re-Hashing*/					
			temp=(data*)malloc(size * sizeof(data)); 
			for(int i=0;i<size;i++){
				temp[i]=deletedList[i];
			}
			for(int i=0;i<size;i++){
				deletedList[i].k=-1;
			}
			printf("\nADOPTED DOGS\n");
			/*Sending Adopted Dogs Table to Hashing*/
	   		hashing(deletedList, size, temp); 
			
		}
//function for menu
void menu(){
	
	printf("\n1)ADD New Dog\n");
	printf("2)ADOPT a Dog\n");
	printf("3)SEARCH For a Dog\n");
	printf("4)EXIT\n");
}

