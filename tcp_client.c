/*
Group 22

Team Members 

Aamod Kharb         2014A7PS063P
Harshit Jain        2014A7PS101P
Darshit Khajanchi   2014A7PS144P

*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>


int main()
{
    int clientSocket,i,j,iid,tu;
    char id[1]={'\0'}, turn[1]={'\0'}, z[1] = {'\0'}, o[1] = {'\0'},ans[1] = {'\0'}, rnd[1]={'\0'}, name[10], sc[2]={'\0'}, a;
    char *recvBuffer1,*recvBuffer2,*recvBuffer3,*buffer, *score;
    struct sockaddr_in serverAddr;
    socklen_t addr_size;
	int recvBytes = 0;
    char *userInput;

    userInput = (char *)malloc(sizeof(char)*35);
    buffer = (char *)malloc(sizeof(char)*10);
    recvBuffer1 = (char *)malloc(sizeof(char)*35);
    score = (char *)malloc(sizeof(char)*9);

    clientSocket = socket(PF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;

    serverAddr.sin_port = htons(9031);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    addr_size = sizeof serverAddr;

    // Connect with the client

    if (connect(clientSocket,(struct sockaddr *) &serverAddr, addr_size) < 0) {

        printf("[ERROR] Unable to connect to server.\n");
        close( clientSocket );
        exit(0);
    }

    // Receive Client ID

    if ((recvBytes =(recv(clientSocket, id, 1, 0) < 0)) == 1)
        printf("[ERROR] No input id received from client.\n");

    printf("Enter Nick (Max 10 Characters) : \n");
    scanf("%[^\n]s", name);

    while (strlen(name)>10) {

        printf("Please enter Nick again (Max 10 Characters) : \n");
        scanf("%c", &a);
        scanf("%[^\n]s", name);        
    }

    // Send Client Nick

    if (send(clientSocket, name, strlen(name), 0) != strlen(name))
        printf("[ERROR] Unable to send the data.\n");

    iid = atoi(id);

	printf("Your player ID is %d\n", iid);
    printf("\nThe game has 3 levels. \nIn Level 1 provide the answer to the mathematical expression.\nIn Level 2, fill in the blanks and provide the complete name of a Country.\nIn level 3, anagrams of names of famous cities of the world are given. Provide the origianl city name\n");
    printf("\n\t\t\tTHE GAME IS ABOUT TO BEGIN\n");
    scanf("%c", &a);
    
    while(1) {
        
        for (i=0;i<35;i++) {

            recvBuffer1[i]='\0';
        }

        turn[0]='\0';

        // Receive Scoreboard

        for (i=0;i<5;i++) {

            for (j=0;j<9;j++) {

                score[j]='\0';
            }

            sc[0]='\0';

            if ((recvBytes = (recv(clientSocket, score, 9, 0) < 0)) == 1)
                printf("[ERROR] No input received from client.\n");

            if ((recvBytes = (recv(clientSocket, sc, 2, 0) < 0)) == 1)
                printf("[ERROR] No input received from client.\n");

            if (score[0]!=' ' || score[0]!='\0') {
                
                if(i==0){
                    printf("\t\t\t\tSCOREBOARD\n\n");
                }
                printf("\t\t\t%s\t", score);
                printf("%s\n", sc);                
            }

        }

        for (j=0;j<9;j++) {

            score[j]='\0';
        }

        // Receive the loser of each round

        if ((recvBytes = (recv(clientSocket, score, 9, 0) < 0)) == 1)
                printf("[ERROR] No input received from client.\n");

        if (score[0]!=' ') {
            printf("\t\tLoser of the Round is %s\n\n", score);
        }    

        for (j=0;j<9;j++) {

            score[j]='\0';
        }


        // Receive Question, ID and name of the player whose turn it is

        if ((recvBytes = (recv(clientSocket, score, 9, 0) < 0)) == -1)
                printf("[ERROR] No input received from client.\n");


        if ((recvBytes = (recv(clientSocket, turn, 1, 0) < 0)) == -1) {
            
            printf("[ERROR] No input received from client.\n");
            
        }

        if ((recvBytes = (recv(clientSocket, recvBuffer1, 35, 0) < 0)) == -1)
            printf("[ERROR] No input received from client.\n");

        if (recvBuffer1[1]=='\0')
            break;

        printf("Solve this question :  \"%s\"\n\n", recvBuffer1);

        tu = atoi(turn);

        printf("Current Turn : %s\n",score);
        
        if (iid==tu) {

            printf("It's your turn. Please answer the question : \n");
            fgets(userInput, 35, stdin);
            char *pos;
            if ((pos=strchr(userInput, '\n')) != NULL)
                *pos = '\0';
            
            // Send Answer

            if (send(clientSocket, userInput, strlen(userInput), 0) != strlen(userInput))
                printf("[ERROR] Unable to send the data.\n");
        }

 	}
    
    // Close Connection

    close(clientSocket);
    return 0;
}
