#define _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <signal.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <time.h>
#include <sys/wait.h>
#include <stdatomic.h>
#include <semaphore.h>
#include <sys/shm.h>
#include <sys/types.h>


int *br_sobova;
int *br_patuljaka;
int id;
sem_t *djedbozicnjak, *konzultacije, *sobovi, *K;


void patuljak() {
	sem_wait(K);
	(*br_patuljaka)++;
	printf("Pred vratima je %d patuljaka\n", *br_patuljaka);
	if (*br_patuljaka == 3) {//ovaj je treći
		printf("Grupa od 3 patuljka je pred vratima!\n");
		sem_post(djedbozicnjak);
	} 
	sem_post(K);
	sem_wait(konzultacije);
}

void sob(){
	sem_wait(K);
	(*br_sobova)++;
	printf("Pred vratima je %d sobova\n", *br_sobova);
	if (*br_sobova == 10){
		printf("Svih 10 sobova je pred vratima!\n");
		sem_post(djedbozicnjak);
	}
	sem_post(K);
	sem_wait(sobovi);
}

void SjeverniPol(){
	while(1) {
		sleep(rand() % 3 + 1);//od 1 do 3 sekunde
		if ((rand() % 101) > 50 && *br_sobova < 10) {
			switch(fork()){
				case -1:
					printf("Ne mogu stvoriti novi proces!\n");
					exit(1);
				case 0:
					sob();
					exit(0);
			}
		}
		if ((rand() % 101) > 50){
			switch(fork()){
				case -1:
					printf("Ne mogu stvoriti novi proces!\n");
					exit(1);
				case 0:
					patuljak();
					exit(0);
			}
		}
	}
}

void DjedBozicnjak() {
	while(1) {
		sem_wait(djedbozicnjak);
		sem_wait(K);
		if (*br_sobova == 10 && *br_patuljaka > 0) {
			printf("DJED JE PROBUĐEN: Svi sobovi su pred vratima i nekoliko patuljaka!\n");
			sem_post(K);
			printf("DJEDOV ZADATAK: Djed mora raznositi poklone\n");
			sleep(0.5); //raznosi poklone
			sem_wait(K);
			for(int i = 0; i < 10; i++) sem_post(sobovi); //povećaj semafor za 10
			*br_sobova = 0;
		}
		if (*br_sobova == 10) {
			printf("DJED JE PROBUĐEN: Svi sobovi su pred vratima bez patuljaka!\n");
			sem_post(K);
			printf("DJEDOV ZADATAK: Djed mora nahraniti sobove\n");
			sleep(0.5); //hrani sobove
			sem_wait(K);
		}
		//ako je samo_tri_patuljka_pred_vratima
		if (*br_patuljaka >= 3) {
			printf("DJED JE PROBUĐEN: Pred vratima je grupa od 3 patuljka i nema svih sobova!\n");
			sem_post(K);
			printf("DJEDOV ZADATAK: Djed mora riješiti problem koji imaju patuljci\n");
			sleep(0.5); //riješi_njihov_problem 
			sem_wait(K);
			for(int i = 0; i < 3; i++) sem_post(konzultacije); //povećaj semafor za 3
			*br_patuljaka -= 3;
		}
		sem_post(K);
	}
}

int main(void){
	id = shmget(IPC_PRIVATE, 2*sizeof(int)+4*sizeof(sem_t), 0600);
	br_patuljaka = shmat(id, NULL, 0);
	br_sobova = (int *) (br_patuljaka + 1);
	K = (sem_t *) (br_sobova + 1);
	djedbozicnjak = (sem_t *) (K + 1);
	konzultacije = (sem_t *) (djedbozicnjak + 1);
	sobovi = (sem_t *) (konzultacije + 1);
	sem_init(K, 1, 1);
	sem_init(djedbozicnjak, 1, 0);
	sem_init(konzultacije, 1, 0);
	sem_init(sobovi, 1, 0);
	switch(fork()){
		case -1:
			printf("Ne mogu stvoriti novi proces!\n");
			exit(1);
		case 0:
			DjedBozicnjak();
			exit(0);
	}
	switch(fork()){
		case -1:
			printf("Ne mogu stvoriti novi proces!\n");
			exit(1);
		case 0:
			SjeverniPol();
			exit(0);
	}
	for (int i = 0; i < 2; i++)
		wait(NULL);
	shmctl(id, IPC_RMID, NULL); 
	return 0;
}

