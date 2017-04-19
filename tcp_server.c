#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <ctype.h>
#define BILLION 1E9;

char countries[201][35]={"Afghanistan","Albania","Algeria","Andorra","Angola","Antigua and Barbuda","Argentina","Armenia","Aruba","Australia","Austria",
    "Azerbaijan","The Bahamas","Bahrain","Bangladesh","Barbados","Belarus","Belgium","Belize","Benin","Bhutan","Bolivia","Bosnia and Herzegovina",
    "Botswana","Brazil","Brunei","Bulgaria","Burkina Faso","Burma","Burundi","Cambodia","Cameroon","Canada","Cabo Verde","Central African Republic","Chad","Chile",
    "China","Colombia","Comoros","Democratic Republic of the Congo","Republic of the Congo","Costa Rica","Cote d'Ivoire","Croatia","Cuba","Curacao","Cypru",
    "Czechia","Denmark","Djibouti","Dominica","Dominican Republic","East Timor","Ecuador","Egypt","El Salvador","Equatorial Guinea","Eritrea","Estonia","Ethiopia","Fiji","Finland",
    "France","Gabon","The Gambia","Georgia","Germany","Ghana","Greece","Grenada","Guatemala","Guinea","Guyana","Haiti","Honduras","Hong Kong","Hungary","Iceland",
    "India","Indonesia","Iran","Iraq","Ireland","Israel","Italy","Jamaica","Japan","Jordan","Kazakhstan","Kenya","Kiribati","North Korea ","South Korea","Kosovo","Kuwait",
    "Kyrgyzstan","Laos","Latvia","Lebanon","Lesotho","Liberia","Libya","Liechtenstein","Lithuania","Luxembourg","Macau","Macedonia","Madagascar","Malawi","Malaysia","Maldives","Mali"
    ,"Malta","Marshall Islands","Mauritania","Mauritius","Mexico","Micronesia","Moldova","Monaco","Mongolia","Montenegra","Morocco","Mozambique"
    ,"Namibia","Nauru","Nepal","Netherlands","New Zealand","Nicaragua","Niger","Nigeria","North Korea","Norway","Oman","Pakistan","Palau"
    ,"Panama","Papua New Guinea","Paraguay","Peru","Philippines","Poland","Portugal","Qatar","Romania","Russia","Rwanda","Saint Kitts and Nevis","Saint Lucia",
    "Saint Vincent and the Grenadines","Samoa","San Marino","Saudi Arabia","Senegal","Serbia","Seychelles","Sierra Leone","Singapore","Sint Maarten",
    "Slovakia","Slovenia","Solomon Islands","Somalia","South Africa","South Korea","South Sudan","Spain","Sri Lanka","Sudan","Suriname","Swaziland","Sweden",
    "Switzerland","Syria","Taiwan","Tajikistan","Tanzania","Thailand","Timor-Leste","Togo","Tonga","Trinidad and Tobago","Tunisia","Turkey","Turkmenistan",
    "Tuvalu","Uganda","Ukraine","United Arab Emirates","United Kingdom","Uruguay","Uzbekistan","Vanuatu",
    "Venezuela","Vietnam","Yemen","Zambia","Zimbabwe", "Vatican City"};

char cities[69][15] = {"Shanghai","Karachi","Beijing","Lahore","Dhaka","Delhi","Istanbul","Tokyo",
    "Moscow","Sao Paulo","Shenzhen","Cairo","Jakarta","Seoul","Mexico City","London","New York",
    "Bengaluru","Bangkok","Tehran","Bogota","Hong Kong","Baghdad","Mumbai","Chennai","Hanoi",
    "Riyadh","Ahmedabad","Singapore","Ankara","Alexandria","Kolkata","Surat","Johannesburg","Giza",
    "Los Angeles","Cape Town","Berlin","Durban","Hyderabad","Kabul","Melbourne","Sydney","Islamabad",
    "Petra","Madrid","Barcelona","Toronto","Munich","Venice","Manchester","Rome","Turin","Belgrad",
    "Vienna","Colombo","Dublin","Paris","Lyon","Chicago","Osaka","Nagpur","Kuala Lumpur","Budapest",
    "Montreal","Philadelphia","Phoenix","Bhopal","Prague"
    };

// Initial scores of all players    
int score[5] = {90,90,90,90,90};

// Initially as no players are connected, all values are 0 (Value is 1, if connected)    
int isPlaying[5] = {0,0,0,0,0};

int maxPlayer=5;

char * GenerateQnAType3(int ran) {
    
    char a;
    srand(time(NULL));

    char * temp=(char *)malloc(35*sizeof(char));
    char * temp1=(char *)malloc(70*sizeof(char));
    int i,i1,i2;

    for(i=0;cities[ran][i]!='\0';i++){

        temp[i]=tolower(cities[ran][i]);
        temp1[i]=tolower(temp[i]);
    }
        
    temp[i]='\0';
    temp1[i]='\0';
    int size=i;
    
    for(i=0;i<11;i++){
        
        i1=rand()%size;
        i2=rand()%size;
        if((temp1[i2]!=' ')&&(temp1[i1]!=' ')){
            a=temp1[i1];
            temp1[i1]=temp1[i2];
            temp1[i2]=a;
        }        
    }

    temp1[size]='/';
    temp1[size+1]='\0';
    strcat(temp1,temp);
    return temp1;  
}

char * GenerateQnAType2(int ran) {
    
    srand(time(NULL));

    char * temp=(char *)malloc(35*sizeof(char));
    char * temp1=(char *)malloc(70*sizeof(char));
    int i,i1,i2;

    for(i=0;countries[ran][i]!='\0';i++){
        temp[i]=countries[ran][i];
        temp1[i]=temp[i];
    }
    
    temp[i]='\0';
    temp1[i]='\0';
    int size=i;
    
    for(i=0;i<size;i=i+5){
    
        i1=rand()%5;
        i2=rand()%5;

        if(i+i1<size)
            if(temp1[i+i1]!=' ')
                temp1[i+i1]='-';
        
        if(i+i2<size)
            if(temp1[i+i2]!=' ')
                temp1[i+i2]='-';
        
    }

    temp1[size]='/';
    temp1[size+1]='\0';
    strcat(temp1,temp);
    return temp1;  
}

void updateview(char user[][10], int count) {
    int i=0;
    printf("\t\t\tScoreboard\n");
    printf("\n");
    while(i<count){
        printf("%d\t%s\n", score[i], user[i]);  
        i++;
    }
    printf("\n\n\n");
}

void updateScoreBoard(int id, char user[][10], int val, int count) {

    int i=0;

    switch (val){
        case 1:
            {break;}
        case -1:
            {score[id]=score[id] - 10;
            break;}
        case 0:
            {score[id]=score[id] - 20;
            break;}

        default: break;    
    }

    i=0;

    while(i<count){
    
        if(score[i] <= 0){
            
            isPlaying[i]=0;
            printf("\t\t\t\t%s Loser\n",user[i]);
        }

        i++;
    }
    updateview(user, count);
}

int main() {

    srand(time(NULL));

    int i=0,j=0,cnt=0,serverSocket = 0, newSocket[maxPlayer],trigger = 25, rnd=0,k=0,temp1=0,nor=0;
    int sendBytes = 0, sendNumber = 0, recvBytes = 0, recvNumber = 0,loser=0;
	int firstNum, secondNum, operationIndex, chance=0, nol1=3, nol2=6, nol3=9;
    char id[2], turn[2], name[10], sc[2];
    char names[maxPlayer][10];
    char *sendBuffer, *recvBuffer, *buffer,*recvBuffer2,*recvBuffer3,*recvBuffer4;
    char *firstChar,*secondChar,*qt2, *q2, *a2, *q3, *a3, *recva2;
    char *operation;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddress[maxPlayer];
    socklen_t addr_size;

    for (i=0;i<maxPlayer;i++) 
        newSocket[i]=0;

    firstChar =  (char *)malloc(sizeof(char)*3);
    secondChar =  (char *)malloc(sizeof(char)*3);
    operation =  (char *)malloc(sizeof(char)*4);

	operation[0] = '+';
	operation[1] = '-';
	operation[2] = '*';
	operation[3] = '/';
		
    sendBuffer = (char *)malloc(sizeof(char)*10);	
    recvBuffer = (char *)malloc(sizeof(char)*35);
    buffer = (char *)malloc(sizeof(char)*10);    
    recva2 = (char *)malloc(sizeof(char)*35);

    serverSocket = socket(PF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(9031);
    serverAddr.sin_addr.s_addr = inet_addr ("127.0.0.1");
    fcntl(serverSocket, F_SETFL, O_NONBLOCK);  

    memset(serverAddr.sin_zero, '\0', sizeof (serverAddr.sin_zero));
    memset(sendBuffer, 0, 10);
    memset(recvBuffer, 0, 35);
    memset(name, 0, 10);
    memset(buffer, 0, 10);
    memset(recva2, 0, 35);

    if (bind (serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr))  < 0)
        printf("[ERROR] Socket binding Failed. \n");

    if (listen (serverSocket, 5)==0)
        printf ( "Server Scocket Initiated. Listening to its clients : \n" );
    else
        printf("[ERROR] More than limit.\n");

    clock_t before = clock();
    clock_t end;
    i=0;

    struct timespec start, stop;
    double accum;

    // Starts Time for timer

    if(clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }

    // Acceps connections till a specified period of time (25 seconds) 

    do {

        temp1 = accept( serverSocket,(struct sockaddr *) &clientAddress[i], &addr_size);
	    
        if(temp1!=-1){
            newSocket[i]=temp1;

            sprintf(id, "%d", (i+1));
            printf("%s\t %d\n", id, (int) strlen(id));

            if ( send ( newSocket[i], id, strlen(id), 0) != strlen(id))
                printf("[ERROR] Unable to send the data.\n");

            for (k=0;k<10;k++) {

                names[i][k]='\0';
            }

            if ((recvBytes = recv(newSocket[i], names[i], 10, 0) == -1))
                printf("[ERROR] No input received from client.\n");

            printf("name=%s\n",names[i]);  
            isPlaying[i]=1;  
            i++;          
            cnt++;          // Variable cnt stores the total number of players
	   }
  
	    if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
            perror( "clock gettime" );
            exit( EXIT_FAILURE );
        }

        accum = ( stop.tv_sec - start.tv_sec )
              + ( stop.tv_nsec - start.tv_nsec )
                / BILLION;
    
    } while ( accum < trigger );

    // Minimum number of players should be 2

    if(cnt<2){
        
        printf("Insufficient players.\n");
        return 0;
    }

    for (i=0;i<cnt;i++) 
        printf("%s\n", names[i]);

    // Checks if all conncetions are properly Done
    for (i=0;i<cnt;i++) {
            
        addr_size = sizeof (clientAddress[i]);
            
        if (newSocket[i] < 0)
            printf("[ERROR] Failed to accept the input from client %d.\n",i);
   
    }

    for (i=0;i<cnt;i++) {

        k=0;
        while (k<9) {
            if (names[i][k]!='\0') {
                k++;
            }
            else 
                break;
        }

        while (k<9) {
            names[i][k]=' ';
            k++;
        }
        if (k==9)
            names[i][k]='\0';

        printf("%s\t%d\n",names[i],strlen(names[i]));
    }

    int temp=0;

    // This is the while loop for Level 1 type of questions. 

    while (nor < nol1) {

        if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
            perror( "clock gettime" );
            exit( EXIT_FAILURE );
        }

        before=clock();

        do {

            // Send Scoreboard to all clients

            for (i=0;i<cnt;i++) {
                
                for (k=0;k<cnt;k++) {

                    if (isPlaying[k]==1) {

                        if (send (newSocket[i], names[k], strlen(names[k]), 0) != strlen(names[k]))
                            printf("[ERROR] Unable to send the data.\n");

                        sprintf(sc, "%d", score[k]);

                        if (send (newSocket[i], sc, strlen(sc), 0) != strlen(sc))
                            printf("[ERROR] Unable to send the data.\n");

                    }

                    else {
                        
                        if (send (newSocket[i], "         ", 9, 0) != 9)
                            printf("[ERROR] Unable to send the data.\n");

                        if (send (newSocket[i], "  ", 2, 0) != 1)
                            printf("[ERROR] Unable to send the data.\n");
                    }                    
                }

                while (k<5) {

                    if (send (newSocket[i], "         ", 9, 0) != 9)
                        printf("[ERROR] Unable to send the data.\n");

                    if (send (newSocket[i], "  ", 2, 0) != 1)
                        printf("[ERROR] Unable to send the data.\n");

                    k++;
                }

                if (nor<=temp) {
                    if (send (newSocket[i], "         ", 9, 0) != 9)
                        printf("[ERROR] Unable to send the data.\n");

                }
                else {
                    if (send (newSocket[i], names[loser], 9, 0) != 9)
                        printf("[ERROR] Unable to send the data.\n");
                }
            }

            temp=nor;

            //  Generate Question of Level 1

            firstNum = rand()%100 + 1;
        	secondNum = rand()%100 + 1;
        	operationIndex = rand()%4;
        	
        	memset(firstChar, 0, 3);
        	memset(secondChar, 0, 3);
        	sprintf(firstChar, "%d", firstNum);
        	sprintf(secondChar, "%d", secondNum);
        	
        	char *operNum;
        	operNum = (char *) malloc(sizeof(char)*1);
        	operNum[0] = operation[operationIndex];

            char src[4], dest[4];

            strcpy(src,  firstChar);
            strcpy(dest, secondChar);
            strcat(src,operNum);
            strcat(src, dest);

            j = rand()%cnt;

            // Check if the players whose turn has been randomly chosen is still playing or not

            while (isPlaying[j]!=1) {
                j = rand()%cnt;
            }

            chance = j;

            printf("cnt = %d\n", cnt);

        	printf("Equation given to client %s : %s \n",names[j],src);
        	
            // Send the question, name and ID of the player whose turn it is
            
            for (i=0;i<cnt;i++) {

                if (isPlaying[i]==1) {

                    printf("%s\n", names[i]);

                    sprintf(turn, "%d", (j+1));

                    if (send (newSocket[i], names[j], strlen(names[j]), 0) != strlen(names[j]))
                            printf("[ERROR] Unable to send the data.\n");

                    if (send (newSocket[i], turn, strlen(turn), 0) != strlen(turn))
                        printf("[ERROR] Unable to send the data.\n");

                    if (send (newSocket[i], src, strlen(src), 0) != strlen(src))
                        printf("[ERROR] Unable to send the data.\n");
                }
        	}	
        
        	int answer = 0;

            // Calculate the Answer to each question

        	if(operation[operationIndex] == '+')
        	{	
        		answer = firstNum + secondNum;
        	}

        	else if(operation[operationIndex] == '-')
        	{	
        		answer = firstNum - secondNum;
        	}

        	else if(operation[operationIndex] == '*')
        	{	
        		answer = firstNum * secondNum;
        	}

        	else if(operation[operationIndex] == '/')
        	{	
        		answer = firstNum / secondNum;
        	}
        	
        	char *answerBuf =  (char *)malloc(sizeof(char)*4);
        	sprintf(answerBuf, "%d", answer);

            memset(recvBuffer, 0, 35);     

            // Receive the answer from the player   
                
            if ((recvBytes = recv(newSocket[j], recvBuffer, 35, 0) == -1))
                printf("[ERROR] No input received from client.\n");

            printf("Received Packet contains \"%s\"\n\n", recvBuffer);
    		
            // Check the answer and update the scoreboard accordingly

            if(strcmp(recvBuffer, answerBuf) == 0) {

                printf("Correct Answer : %s \n\n", answerBuf);
               
                updateScoreBoard(j, names, 1, cnt);
            }
        	else {

                printf("Wrong Answer, correct answer is : %s \n\n", answerBuf);
           
                updateScoreBoard(j, names, -1, cnt);	
        	}
            
            if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
              perror( "clock gettime" );
              exit( EXIT_FAILURE );
            }

            accum = ( stop.tv_sec - start.tv_sec )
                  + ( stop.tv_nsec - start.tv_nsec )
                    / BILLION;

            printf("time down: %f\n",accum);

        } while (accum < 30+(rand()%15));    // Check if the time is less than the random time

        printf("ROUND COMPLETE :Loser of this round is %s\n",names[chance]);
        updateScoreBoard(chance, names, 0, cnt);
        nor++;
        loser=chance;
    }

    // This is the while loop for Level 2 type of questions. 

    while(nor<nol2){
        
        if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
            perror( "clock gettime" );
            exit( EXIT_FAILURE );
        }

        before=clock();
        
        do {
            
            // Send Scoreboard to all clients

            for (i=0;i<cnt;i++) {

                for (k=0;k<cnt;k++) {

                    if (isPlaying[k]==1) {

                        if (send (newSocket[i], names[k], strlen(names[k]), 0) != strlen(names[k]))
                            printf("[ERROR] Unable to send the data.\n");

                        sprintf(sc, "%d", score[k]);

                        if (send (newSocket[i], sc, strlen(sc), 0) != strlen(sc))
                            printf("[ERROR] Unable to send the data.\n");

                    }

                    else {
                        
                        if (send (newSocket[i], "         ", 9, 0) != 9)
                            printf("[ERROR] Unable to send the data.\n");

                        if (send (newSocket[i], "  ", 2, 0) != 1)
                            printf("[ERROR] Unable to send the data.\n");
                    }
                }

                while (k<5) {

                    if (send (newSocket[i], "         ", 9, 0) != 9)
                        printf("[ERROR] Unable to send the data.\n");

                    if (send (newSocket[i], "  ", 2, 0) != 1)
                        printf("[ERROR] Unable to send the data.\n");

                    k++;
                }

                if (nor<=temp) {
                    if (send (newSocket[i], "         ", 9, 0) != 9)
                        printf("[ERROR] Unable to send the data.\n");

                }
                else {
                    if (send (newSocket[i], names[loser], 9, 0) != 9)
                        printf("[ERROR] Unable to send the data.\n");
                    
                }
            }
            temp=nor;

            int ran;
            ran = rand() % 195;
            printf("%d\n", ran);

            // This receives the question of Level 2, in the formal "Question/Answer"

            qt2 = GenerateQnAType2(ran);
            char * pch;
            pch = strtok(qt2,"/");  // Seperate the question from the answer and store seperately
            q2=pch;
            pch = strtok(NULL,"/");
            a2=pch;
            printf("q2=%s\n", q2);
            printf("a2=%s\n", a2);

            j = rand()%cnt;
            
            // Check if the players whose turn has been randomly chosen is still playing or not

            while (isPlaying[j]!=1) {
                j = rand()%cnt;
            }

            chance = j;
            printf("cnt = %d\n", cnt);

            printf("Question given to client %s : %s \n",names[j],q2);

            // Send the question, name and ID of the player whose turn it is
            
            for (i=0;i<cnt;i++) {

                if (isPlaying[i]==1) {

                    sprintf(turn, "%d", (j+1));

                    if (send (newSocket[i], names[j], strlen(names[j]), 0) != strlen(names[j]))
                            printf("[ERROR] Unable to send the data.\n");

                    if (send (newSocket[i], turn, strlen(turn), 0) != strlen(turn))
                        printf("[ERROR] Unable to send the data.\n");

                    if (send (newSocket[i], q2, strlen(q2), 0) != strlen(q2))
                        printf("[ERROR] Unable to send the data.\n");
                }                  
            }

            memset(recva2, 0, 35);  
          
    		// Receive the answer from the player

            if ((recvBytes = recv(newSocket[j], recva2, 35, 0) == -1))
           	     printf("[ERROR] No input received from client.\n");
    			 

            printf("Received Packet contains \"%s\"\n\n", recva2);
            
            // Check the answer and update the scores accordingly

            if(strcmp(recva2, a2) == 0) {
                printf("Correct Answer : %s \n\n", a2);
                updateScoreBoard(j, names, 1, cnt);
            }

            else {

              printf("Wrong Answer, Correct answer is : %s \n\n", a2);   
              updateScoreBoard(j, names, -1, cnt);
           
            }
    		

        	if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
              perror( "clock gettime" );
              exit( EXIT_FAILURE );
            }

            accum = ( stop.tv_sec - start.tv_sec )
                  + ( stop.tv_nsec - start.tv_nsec )
                    / BILLION;

            printf("time down: %f\n",accum);

        } while ( accum < 30+(rand()%15) );      // Check if the time is less than the random time

        printf("ROUND COMPLETE :Loser of this round is %s\n",names[chance]);
        updateScoreBoard(chance, names, 0, cnt);
        nor++;
        loser=chance;
    }

    // This is the while loop for Level 3 type of questions.

    while(nor<nol3){
        
        if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
            perror( "clock gettime" );
            exit( EXIT_FAILURE );
        }

        before=clock();
        
        do {

            // Send Scoreboard to all clients

            for (i=0;i<cnt;i++) {

                for (k=0;k<cnt;k++) {

                    if (isPlaying[k]==1) {

                        if (send (newSocket[i], names[k], strlen(names[k]), 0) != strlen(names[k]))
                            printf("[ERROR] Unable to send the data.\n");

                        sprintf(sc, "%d", score[k]);

                        if (send (newSocket[i], sc, strlen(sc), 0) != strlen(sc))
                            printf("[ERROR] Unable to send the data.\n");

                    }

                    else {
                        
                        if (send (newSocket[i], "         ", 9, 0) != 9)
                            printf("[ERROR] Unable to send the data.\n");

                        if (send (newSocket[i], "  ", 2, 0) != 1)
                            printf("[ERROR] Unable to send the data.\n");
                    }
                }

                while (k<5) {

                    if (send (newSocket[i], "         ", 9, 0) != 9)
                        printf("[ERROR] Unable to send the data.\n");

                    if (send (newSocket[i], "  ", 2, 0) != 1)
                        printf("[ERROR] Unable to send the data.\n");

                    k++;
                }

                if (nor<=temp) {
                    if (send (newSocket[i], "         ", 9, 0) != 9)
                        printf("[ERROR] Unable to send the data.\n");

                }
                else {

                    if (send (newSocket[i], names[loser], 9, 0) != 9)
                        printf("[ERROR] Unable to send the data.\n");
                    
                }
            }
            
            temp=nor;

            // This receives the question of Level 2, in the formal "Question/Answer"

            int ran;
            ran = rand() % 69;
            printf("%d\n", ran);
            qt2 = GenerateQnAType3(ran);
            char * pch;
            pch = strtok(qt2,"/"); // Seperate the question from the answer and store seperately
            q3=pch;
            pch = strtok(NULL,"/");
            a3=pch;
            printf("q3=%s\n", q3);
            printf("a3=%s\n", a3);

            j = rand()%cnt;

            // Check if the players whose turn has been randomly chosen is still playing or not

            while (isPlaying[j]!=1) {
                j = rand()%cnt;
            }

            chance = j;
            printf("cnt = %d\n", cnt);

            printf("Question given to client %s : %s \n",names[j],q3);

            // Send the question, name and ID of the player whose turn it is
            
            for (i=0;i<cnt;i++) {

                if (isPlaying[i]==1) {

                    sprintf(turn, "%d", (j+1));

                    if (send (newSocket[i], names[j], strlen(names[j]), 0) != strlen(names[j]))
                            printf("[ERROR] Unable to send the data.\n");
 
                    if (send (newSocket[i], turn, strlen(turn), 0) != strlen(turn))
                        printf("[ERROR] Unable to send the data.\n");

                    if (send (newSocket[i], q3, strlen(q3), 0) != strlen(q3))
                        printf("[ERROR] Unable to send the data.\n");
                }                  
            }

            memset(recva2, 0, 35);  
          
            
            if ((recvBytes = recv(newSocket[j], recva2, 35, 0) == -1))
                 printf("[ERROR] No input received from client.\n");
                 

            printf("Received Packet contains \"%s\"\n\n", recva2);

            // Check the answer and update the scores accordingly
            
            if(strcmp(recva2, a3) == 0) {
                printf("Correct Answer : %s \n\n", a3);
                updateScoreBoard(j, names, 1, cnt);
            }
            else {

              printf("Wrong Answer, Correct answer is : %s \n\n", a3);   
              updateScoreBoard(j, names, -1, cnt);
            
            }
            
            if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
              perror( "clock gettime" );
              exit( EXIT_FAILURE );
            }

            accum = ( stop.tv_sec - start.tv_sec )
                  + ( stop.tv_nsec - start.tv_nsec )
                    / BILLION;

            printf("time down: %f\n",accum);

        } while ( accum < 30+(rand()%15) );    // Check if the time is less than the random time

        printf("ROUND COMPLETE :Loser of this round is %s\n",names[chance]);
        updateScoreBoard(chance, names, 0, cnt);
        nor++;
        loser=chance;
    }

    for (i=0;i<cnt;i++) {
        close (newSocket[i]);
    }
    
    close (serverSocket);
    return 0;
}