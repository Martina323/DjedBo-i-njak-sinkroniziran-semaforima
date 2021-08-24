#include <signal.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <time.h>
#include <sys/wait.h>
#include <pthread.h>

pthread_mutex_t monitor;
pthread_cond_t redCekanja[5];
char filozof[5] = {'0', '0', '0', '0', '0'};
int stapici[5] = {1, 1, 1, 1, 1};

void misliti(){
	sleep(3);
}

void jesti(int n){
   	/* n - redni broj filozofa */
   	pthread_mutex_lock(&monitor);
   	filozof[n] = 'o';
      	while (stapici[n] == 0 || stapici[(n + 1) % 5] == 0) pthread_cond_wait(&redCekanja[n], &monitor);
	stapici[n] = 0;
	stapici[(n + 1) % 5] = 0;
	filozof[n] = 'X';
	printf("%c %c %c %c %c (%d)\n", filozof[0], filozof[1], filozof[2], filozof[3], filozof[4], n + 1);
	pthread_mutex_unlock(&monitor);

   	sleep(2); //njam_njam

  	pthread_mutex_lock(&monitor);
	filozof[n] = 'O';
	stapici[n] = 1;
	stapici[(n + 1) % 5] = 1;
	pthread_cond_signal(&redCekanja[(n - 1) % 5]);
	pthread_cond_signal(&redCekanja[(n + 1) % 5]);
	printf("%c %c %c %c %c (%d)\n", filozof[0], filozof[1], filozof[2], filozof[3], filozof[4], n + 1);
   	pthread_mutex_unlock(&monitor);
}

void aktivnostiFilozofa(void *s){
	int *p = s;
    	while (1){
        	misliti();
        	jesti(*p);
    	}
}

int main(void){
	pthread_t dretve[5];
	pthread_mutex_init(&monitor, NULL);
	pthread_cond_init(redCekanja, NULL);
	int *pomocno = malloc(5 * sizeof(int));
	for (int j = 0; j < 5; j++) pomocno[j] = j;
	for (int i = 0; i < 5; i++){
		if (pthread_create(&dretve[i], NULL, (void *) aktivnostiFilozofa, &pomocno[i]) != 0){
			printf("Ne mogu stvoriti novog filozofa!\n");
			exit(1);
		}
	}
	for (int i = 0 ; i < 5 ; i++) pthread_join(dretve[i], NULL);
	pthread_mutex_destroy(&monitor);
	return 0;
}
