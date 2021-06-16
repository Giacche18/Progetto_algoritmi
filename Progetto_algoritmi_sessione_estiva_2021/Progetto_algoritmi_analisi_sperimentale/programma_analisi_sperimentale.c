/**********************************************************/
/* Progetto d'esame sessione estiva 2020/2021, ************/
/* corso: Algoritmi e Strutture dati. *********************/
/**********************************************************/

/*****************************************************************************************************/
/* Programma che gestisce una serie di operazioni su veicoli che vengono acquisiti in input da file  */
/*****************************************************************************************************/

/**************************************/
/* Inclusione delle librerie standard */
/**************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

/************************/
/* DEFINIZIONE DEI TIPI */
/************************/

/* Creazione di un dato strutturato che rappresenta un veicolo */
typedef struct
{
	char codice_veicolo[7];			/* stringa che rappresenta il codice con cui viene identificato il veicolo 									*/
	char codice_proprietario[7];	/* stringa che rappresenta il codice con cui viene identificato il proprietario 							*/
	char nome_veicolo[21];			/* stringa che mi rappresenta il nome del veicolo che viene acquisito input da file o inserito dall'utente  */
	int anno_immatricolazione;		/* dato intero che rappresenta l'anno in cui il veicolo è stato immatricolato								*/
} veicolo;							/* nome con cui identifichiamo il dato strutturato che rappresenta un veicolo				 				*/

/* funzione che permette di leggere il file passato in input, inizializzare dinamicamente la memoria e riempire le celle dell'array con le informazioni del file */
veicolo* Leggi_su_File(char*, 								/* Argomento 1 funzione: stringa che rappresenta il nome del file da cui acquisire le informazioni inziali		     									   */
					   int*);								/* Argomento 2 funzione: valore intero che rappresenta il numero di veicoli e che viene passato come puntatore perche' voglio tenere conto delle modifiche */

/* funzione che permette di scrivere su file ogni volta che il programma modifica le informazioni riguardanti i veicoli (aggiungendone di nuovi o elinandone altri) */ 	
void Scrivi_su_file(veicolo *array_veicoli, 				/* Argomento 1 funzione: array che mi contiene i veicoli		     															  						   */
					int, 									/* Argomento 2 funzione: valore intero che rappresenta il numero di veicoli		     															  		   */
					char*);									/* Argomento 3 funzione: stringa che rappresenta il nome del file su cui andare a scrivere le informazioni aggiornate		     						   */

/* funzione che permette di inserire un nuovo veicolo */
veicolo* Inserisci_veicolo(veicolo *array_veicoli, 			/* Argomento 1 funzione: array che mi conterra' i veicoli		     										  											   */	
						   int*, 							/* Argomento 2 funzione: valore intero che rappresenta il numero di veicoli e che viene passato come puntatore perche' voglio tenere conto delle modifiche */
						   int);							/* Argomento 3 funzione: valore intero che rappresenta il numero di nuovi veicoli che l'utente vuole inserire											   */
						   
/* funzione che permette di ricercare uno specifico veicolo in memoria */
int Ricerca_veicolo(veicolo *array_veicoli, 				/* Argomento 1 funzione: array che mi contiene i veicoli		     										  											   */
					int, 									/* Argomento 2 funzione: valore intero che rappresenta il numero di veicoli		     															  		   */
					int);									/* Argomento 3 funzione: valore intero che rappresenta la posizione dell'elemento centrale dell'array	     									   		   */

/* funzione che permette di rimuovere uno specifico veicolo dalla memoria */
void Rimozione_veicolo(veicolo *array_veicoli, 				/* Argomento 1 funzione: array che mi contiene i veicoli		     										  											   */	
					   int*, 								/* Argomento 2 funzione: valore intero che rappresenta il numero di veicoli e che viene passato come puntatore perche' voglio tenere conto delle modifiche */
					   int);								/* Argomento 3 funzione: valore intero che rappresenta la posizione dell'elemento centrale dell'array	     									   		   */

/* copia della funzione che permette di ricercare uno specifico veicolo dalla memoria 													  */
/* questa copia viene utilizzata all'interno della funzione "Rimozione_veicolo" per poter contare i passi dell'algoritmo 				  */
/* questa scelta e' stata fatta per essere sicuri di non avere errori nel conteggio del numero dei passi dell'algoritmo "Ricerca_veicolo" */					   
int Ricerca_veicolo_rimuovere(veicolo *array_veicoli, 		/* Argomento 1 funzione: array che mi contiene i veicoli		     										  											   */
							  int, 							/* Argomento 2 funzione: valore intero che rappresenta il numero di veicoli 																			   */
							  int, 							/* Argomento 3 funzione: valore intero che rappresenta la posizione dell'elemento centrale dell'array	     									   		   */
							  int*);						/* Argomento 4 funzione: valore intero che rappresenta il numero di passi momentaneo dell'algoritmo di rimozione 	     								   */

/* funzione che permette di calcolare il valore piu' grande (secondo l'ordine lessicografico) del codice alfanumerico rappresentante il veicolo */							  
veicolo Ricerca_valore_massimo(veicolo *array_veicoli,		/* Argomento 1 funzione: array che mi contiene i veicoli		     										  											   */ 
							   int);						/* Argomento 2 funzione: valore intero che rappresenta il numero di veicoli 																			   */

/* funzione che permette di calcolare il valore piu' piccolo (secondo l'ordine lessicografico) del codice alfanumerico rappresentante il veicolo */							   
veicolo Ricerca_valore_minimo(veicolo *array_veicoli, 		/* Argomento 1 funzione: array che mi contiene i veicoli		     										  											   */
							  int);							/* Argomento 2 funzione: valore intero che rappresenta il numero di veicoli 																			   */

/* funzione utilizzata dal programma per liberare il buffer */
void LiberaBuffer();

/* funzione utilizzata dal programma per creare le 4 informazioni riguardanti il veicolo */
veicolo Recupero_dati_veicolo(int*);						/* Argomento 1 funzione: valore intero che rappresenta il numero di passi momentaneo dell'algoritmo di inserimento 	     								   */

/* funzione utilizzata dal programma per stampare a schermo i veicoli contenuti nell'array con le rispettive informazioni*/
void Stampa_array(veicolo *array_veicoli, 					/* Argomento 1 funzione: array che mi contiene i veicoli		     										  											   */
				  int);										/* Argomento 2 funzione: valore intero che rappresenta il numero di veicoli 																			   */

int main(int argc, char *argv[]) 
{
	int posizione_valore_ricercato,		/* variabile intera che mi permette di tenere conto della posizione fisica (all'interno dell'array) in cui si trova il veicolo che l'utente vuole ricercare 			*/
	    numero_veicoli_inseriti,		/* variabile intera che mi permette di tenere conto del numero di veicoli che l'utente vuole inserire 																	*/
	    numero_veicoli,					/* variabile intera che mi permette di tenere conto del numero totale di veicoli	   																					*/
        posizione_centrale_array,		/* variabile intera che mi permette di tenere conto della posizione che rappresenta l'elemento centrale dell'array 														*/
	    valore_controllo_scanf = 0;		/* variabile intera che mi permette di controllare che il valore di ritorno della scanf riguardante l'input che rappresenta la scelta della voce del menu' sia corretto */
		
	veicolo *array_veicoli = NULL;		/* variabile che mi conterra' i veicoli con le rispettive informazioni 				    */
	veicolo valore_massimo;				/* variabile che mi conterra' il veicolo piu' grande (secondo l'ordine lessicografico)  */
	veicolo valore_minimo;				/* variabile che mi conterra' il veicolo piu' piccolo (secondo l'ordine lessicografico) */
	
	char nome_file[30];					/* stringa che mi conterra' il nome del file che contiene le informazioni iniziali necessarie al programma																*/

	srand (time(NULL));
	
	/* apro il file di input e acquisisco le informazioni riguardanti i veicoli presenti all'interno */
	array_veicoli = Leggi_su_File(nome_file, &numero_veicoli);
	
	/* prima di stampare l'eventuale contenuto del file vado a controllare che il file non fosse vuoto 																							*/
	/* anche se il file fosse vuoto la memoria veine inizializzata dinamicamente e quindi l'informazione "anno_immatricolazione" viene inizializzata a zero e la utilizzo per fare il controllo */
	if(array_veicoli->anno_immatricolazione == 0)
	{
		printf("\nFile vuoto!\n");
	}
	else
	{
		printf("\n\nLe informazioni sono memorizzate nel modo che segue... \n\n");	
		Stampa_array(array_veicoli, numero_veicoli);
	}
	
	/* a differenza del programma principale, questo programma deve essere utilizzato per l'analisi sperimentale delle funzioni implementatate,
	 * quindi non e' stata creata un'interfaccia utente. semplicemente viene chiesto il numero di veicoli e vengono eseguite una alla volta
	 * le operazioni richieste dalla specifica comunicando oltre al risultato il numero di passi necessari all'algorimto					   */
	/* acquisisco il numero di veicoli che l'utente vuole inserire e su cui vuole eseguire le 5 operazioni richieste dalla specifica 		   */
	printf("\nQuanti veicoli vuoi inserire? ");
	valore_controllo_scanf = scanf("%d", &numero_veicoli_inseriti);
	
	LiberaBuffer();
	
	/* controllo che l'utente abbia inserito un valore congruo a quelli che il programma si aspetta */
	if(numero_veicoli_inseriti <= 0 || valore_controllo_scanf == 0)
	{
		printf("\n\nErrore! Il numero di veicoli deve corrispondere ad un valore positivo e diverso da 0!\n\n");
	}
	else
	{
		/* viene invocata la funzione "Inserisci_veicolo" per permettere all'utente di inserire nuovi veicoli */
		array_veicoli = Inserisci_veicolo(array_veicoli, &numero_veicoli, numero_veicoli_inseriti);	
		
		/* calcolo la posizione centrale dell'array dopo che ho tutti i veicoli richiesti dall'utente */
		posizione_centrale_array = numero_veicoli / 2;
		
		/* viene invocata la funzione "Ricerca_veicolo" per permettere all'utente di ricercare uno specifico veicolo e salvo il valore di ritorno all'interno di "posizione_valore_ricercato" */	
		posizione_valore_ricercato = Ricerca_veicolo(array_veicoli, numero_veicoli, posizione_centrale_array);
		
		/* se il veicolo non viene trovato la funzione "Ricerca_veicolo" inizializza "posizione_valore_ricercato" a -1 in modo da poterlo comunicare all'utente */
		/* il valore centrale dovrebbe esistere sempre ma per sicurezza e' stato lasciato il controllo sul valore di ritorno									    */
		if(posizione_valore_ricercato == -1)
		{
			printf("\nVeicolo non trovato in memoria\n");
		} 
		
		/* viene invocata la funzione "Ricerca_veicolo" per permettere all'utente di rimuovere uno specifico veicolo */
		Rimozione_veicolo(array_veicoli, &numero_veicoli, posizione_centrale_array);
		
		/* viene invocata la funzione "Ricerca_valore_minimo" per calcolare il valore piu' piccolo (secondo l'ordine lessicografico) e salvo il valore di ritorno all'interno di "valore_minimo"  */
		valore_minimo = Ricerca_valore_minimo(array_veicoli, numero_veicoli);
		printf("Valore minimo: %s\n", valore_minimo.codice_veicolo);	
	
		/* viene invocata la funzione "Ricerca_valore_massimo" per calcolare il valore piu' grande (secondo l'ordine lessicografico) e salvo il valore di ritorno all'interno di "valore_massimo" */
		valore_massimo = Ricerca_valore_massimo(array_veicoli, numero_veicoli);
		printf("Valore massimo: %s\n", valore_massimo.codice_veicolo);
	}
				
	return 0;
}

veicolo* Leggi_su_File(char* nome_file, int* numero_veicoli)
{
	veicolo tmp_veicolo;				/* variabile che mi permette di salvare temporaneamente le informazioni riguardanti un veicolo presenti su una riga del file  	 */
	veicolo *array_veicoli;				/* array in cui salvare i veicoli con le rispettive informazioni														  	  	 */
	
	char* valore_ritorno_fgets;			/* variabile che mi conterra' il valore di ritorno delle fgets per eventuali controlli 									  	  	 */

	FILE *file;							/* variabile di tipo file per poter agire sul file di input in modalità lettura/scrittura									  	 */
	
	int count = 0,						/* variabile intera che mi permette di tenere conto del numero di righe contenenti informazioni sui veicoli all'interno del file */
	    valore_controllo_scanf = 0,		/* variabile intera che mi conterra' il valore di ritorno delle scanf per eventuali controlli 									 */	
	    valore_controllo_fscanf = 0;	/* variabile intera che mi conterra' il valore di ritorno delle fscanf per eventuali controlli 									 */
		
	/* il programma continua a chiedere il nome del file finche' l'utente non inserira' il nome (estensione compresa) corretto */	
	do	
	{
		printf("Digita il nome del file (con estensione) da cui estrappolare i dati: ");
		valore_controllo_scanf = scanf("%s", nome_file);
	     
		/* controllo il valore di ritorno della scanf per verificare che l'input dell'utente sia corretto */   
		if(valore_controllo_scanf == 0)
		{
			printf("\nErrore!\n");
		}
		else
		{
			/* il file viene aperto in modalità lettura 											   */
			/* la prima volta il file viene letto soltanto per contare il numero di righe che presenta */
			/* successivamente lo vado a rileggere dall'inizio per salavre le informazioni in memoria  */
			file = fopen(nome_file,
				         "r"); 
			
			/* controllo che il file esista */					 
			if(file != NULL)
			{	
				/* salto la prima riga del file perche' contiene informazioni che non sono utili al fine della corretta esecuzione del programma */
				while (fgetc(file) != '\n');
				
				/* il programma ripete determinate operazioni finche' non arriva alla fine del file di input */	
	 			while(!feof(file))
				{
					/* acquisisco momentaneamenete codice veicolo e codice proprietario di ogni riga ad ogni iterazione */
					valore_controllo_fscanf = fscanf(file,
			   		 			         		     "%s%s\t",
			  		  		  					     tmp_veicolo.codice_veicolo, tmp_veicolo.codice_proprietario);	
			  		  		  					     
			  		/* controllo il valore di ritorno della fscanf per verificare che cio' che e' stato letto da file sia corretto */
			  		if(valore_controllo_fscanf == 0)
			  		{
			  			printf("\nErrore!\n");
					}
					else
					{
						/* acquisisco momentaneamenete il nome del veicolo di ogni riga ad ogni iterazione */
						valore_ritorno_fgets = fgets(tmp_veicolo.nome_veicolo,
					     			     		 	 21,
				    	     			     	 	 file);	  
				    	     			     	 	 
				    	/* controllo il valore di ritorno della fgets per verificare che cio' che e' stato letto da file sia corretto */     			     	 	 
						if(valore_ritorno_fgets == NULL)
						{
							printf("\nErrore!!\n");
						}
						else
						{
							/* acquisisco momentaneamenete l'anno di immatricolazione di ogni riga ad ogni iterazione */
							valore_controllo_fscanf = fscanf(file,
						           					  "%d\n",
					   	   	       					  &tmp_veicolo.anno_immatricolazione);
					   	   	
					   	   	/* controllo il valore di ritorno della fscanf per verificare che cio' che e' stato letto da file sia corretto */
					   	   	if(valore_controllo_fscanf == 0)
					   	   	{
					   	   		printf("\nErrore!!\n");
							}
					    	else
					    	{
					    		/* conto il numero di righe che presenta il file esclusa la prima */
					    		count++;
							}			
						}
					}	
				}
				
				/* sposto il puntatore alla prima riga del file per poterlo rileggere (senza chiuderlo e riaprirlo) */
				rewind(file);
				
				/* inizializzo dinamicamente la memoria e utilizzo una struttura dati di tipo array */	
				array_veicoli = (veicolo*) malloc(sizeof(veicolo) * count);	
				
				/* vado a resettare il contenuto della variabile count per poterla ri-utilizzare successivamente per salvare le informazioni dei veicoli in specifiche celle di memoria */
				count = 0;
				
				/* salto la prima riga del file perche' contiene informazioni che non sono utili al fine della corretta esecuzione del programma */
				while (fgetc(file) != '\n');
				
				/* il programma ripete le stesse operazioni fatte precedentemente, sta volta per salvare le informazioni in memoria */
				/* ogni acquisizione viene controllata per essere validata 															*/			
				while(!feof(file))
				{
					valore_controllo_fscanf = fscanf(file,
		  			       					  		 "%s%s\t",
					       							 array_veicoli[count].codice_veicolo, array_veicoli[count].codice_proprietario);
					
					if(valore_controllo_fscanf == 0)
			  		{
			  			printf("\nErrore!\n");
					}
					else
					{
						valore_ritorno_fgets = fgets(array_veicoli[count].nome_veicolo,
				            	 				 	 21,
				             				     	 file);
				      		
						if(valore_ritorno_fgets == NULL)
						{
							printf("\nErrore!!\n");
						}
						else
						{
							valore_controllo_fscanf = fscanf(file,
					      	   	   					  "%d\n",
					     	       					  &array_veicoli[count].anno_immatricolazione);
					     	
					     	if(valore_controllo_fscanf == 0)
					     	{
					     		printf("\nErrore!!\n");
							}
							else
							{
								count++;	
							}				
						}			
					}
				}
				
				/* chiudo il file*/
				fclose(file);
				
				/* inizializzo numero_veicoli a count per tenere conto del numero di veicoli che ho acquisito per le successive operazioni */
				*numero_veicoli = count;
			}
			else
			{
				printf("\nErrore in apertura del file! Riprova!\n\n");
			}
		}	
	}while(file == NULL);
	
	return(array_veicoli);
}

void Scrivi_su_file(veicolo *array_veicoli, int numero_veicoli, char* nome_file)
{
	int i;			/* variabile intera che verra' utilizzata come contatore per scorrere gli elementi dell'array */
	
	FILE *file;		/* variabile di tipo file per poter agire sul file di input in modalità lettura/scrittura	  */
	
	/* il file viene aperto in modalità scrittura per aggiornarlo con le nuove informazioni					  */
	file = fopen("dati.txt",
				 "w");
	
	/* controllo che il file esista */	
	if(file != NULL)
	{
		fprintf(file,
				"Veicolo\tProprietario\tModello             \tAnno\n");
				
		for(i = 0; i < numero_veicoli; i++)
		{
			fprintf(file,
				    "%s\t%s\t\t\t%s\t%d\n", 
					array_veicoli[i].codice_veicolo, array_veicoli[i].codice_proprietario, array_veicoli[i].nome_veicolo, array_veicoli[i].anno_immatricolazione);
		}
		
		/* chiudo il file per rendere le modifiche permanenti */
		fclose(file);	
	}
	else
	{
		printf("Errore in apertura del file!");
	}		 	
}

veicolo* Inserisci_veicolo(veicolo *array_veicoli, int* numero_veicoli, int numero_veicoli_inseriti)
{
	int dim = *numero_veicoli + numero_veicoli_inseriti,	/* variaible intera che mi rappresenta il numero di veicoli totali che avro' dopo l'inserimento   									*/
		i,													/* variabile intera che verra' utilizzata come contatore per scorrere gli elementi dell'array 										*/
		steps = 0;											/* variabile che mi conterra' il valore risultante dalla conta del numero dei passi che esegue l'algoritmo							*/
	
	array_veicoli = (veicolo*)realloc(array_veicoli, sizeof(veicolo) * dim);	/* ri-alloco dinamicamente la memoria per fare in modo che l'array possa contenere i nuovi veicoli 				*/
	steps++;
	
	/* controllo per verificare che la realloc vada a buon fine*/
	if (array_veicoli == NULL) 
	{
		steps++;
    	printf("errore!");

	}
	else
	{
		steps++;
		/* scorro gli elementi dell'array e ad ogni iterazione inserisco all'interno della i-esima cella di memoria il nuovo valore */ 
		for(i = *numero_veicoli; i < dim; i++)
		{
			steps++;
			/* invovo ad ogni iterazione la funzione "recupero_dati_veicolo" per acquisire in input le informazioni del nuovo veicolo */
			array_veicoli[i] = Recupero_dati_veicolo(&steps);
			steps++;	
		}	
		
		/* aggiorno "numero_veicoli" al numero di veicoli totali che si avra' dopo l'inserimento*/
		*numero_veicoli = dim;
		steps++;
	}
	
	printf("\nElenco dei veicoli aggiornato come segue...\n\n");
	
	/* stampo l'elelenco dei veicoli aggiornato */
	Stampa_array(array_veicoli, dim);
	steps++;
	
	printf("\nL'algoritmo ha impiegato %d passi per inserire %d veicoli\n", steps, dim - 1);

	return(array_veicoli);
}

/* A differenza del programma principale dove questa funzione e' stata creata per acquisire una alla volta da input utente le informazioni riguardanti un veincolo,
 * in questo programma destinato all'analisi sperimentale le informazioni vengono create dal programma in maniera pseudo-casuale senza che l'utente tocchi la tastiera */
veicolo Recupero_dati_veicolo(int* steps)
{
	veicolo nuovo_veicolo;		/* variabile che mi conterra' il nuovo veicolo ritornato dalla funzione e salvato all'interno dell'iesima cella dell'array 						   */
	
	char tmp_string[7];			/* stringa che mi conterra' temporneamente codice veicolo e codice proprietario											   						   */
	
	int anno_immatricolazione,	/* variabile intera che mi conterra' temporneamente l'anno di immatricolazione del veicolo 								  						   */
	    lunghezza_stringa = 0,	/* variabile intera utilizzata per tenere conto della lunghezza della stringa per successive modifiche 					  						   */
	    i,						/* variabile contatore per scorrere i caratteri che formano le stringhe riguardanti le informazioni di un veicolo							 	   */
		j;						/* variabile contatore per scorrere gli elementi di un array statico che mi contiene 10 veicoli predefiniti									 	   */
		
	/* array statico di stringhe che mi contiene 10 nomi di veicoli che saranno utilizzati in maniera continua e pseudo-casuale dal programma									   */	
	char nomi_veicoli[10][20] = {"Fiat Panda",
							 	 "Fiat Uno",
							 	 "Renault Clio",
							 	 "Ford Fiesta",
							 	 "Fiat 500",
							 	 "Dacia Duster",
							 	 "Opel Meriva",
							 	 "Ford Mustang",
							 	 "Lancia Y",
							 	 "Lancia Delta",
								};
	
	/* creo in maniera pseudo-casuale i primi 4 caratteri della stringa, riguardante il codice veicolo, che corrispondono lettere maiuscole */
	for (i=0; i<4; i++)
	{	
		(*steps)++;
		tmp_string[i] = 65 + rand() % (91 - 65);
		(*steps)++;
	}
	
	/* creo in maniera pseudo-casuale gli ultimi 2 caratteri della stringa, riguardante il codice veicolo, che corrispondono a numeri */
	for (i=4; i<6; i++)
	{	
		(*steps)++;
		tmp_string[i] = 48 + rand() % (58 - 48);
		(*steps)++;
	}
	
	/* utilizzo la "strcmp" per copiare il contenuto della stringa temporanea all'interno della variabile stringa della struttura "veicolo" */
	strcpy(nuovo_veicolo.codice_veicolo, tmp_string);
	(*steps)++;
	
	/* creo in maniera pseudo-casuale i primi 3 caratteri della stringa, riguardante il codice proprietario, che corrispondono lettere maiuscole */
	for (i=0; i<3; i++)
	{
		(*steps)++;
		tmp_string[i] = 65 + rand() % (91 - 65);
		(*steps)++;
	}
	
	/* creo in maniera pseudo-casuale gli ultimi 3 caratteri della stringa, riguardante il codice proprietario, che corrispondono a numeri */
	for (i=3; i<6; i++)
	{
		(*steps)++;
		tmp_string[i] = 48 + rand() % (58 - 48);
		(*steps)++;
	}
	
	/* utilizzo la "strcmp" per copiare il contenuto della stringa temporanea all'interno della variabile stringa della struttura "veicolo" */
	strcpy(nuovo_veicolo.codice_proprietario, tmp_string);
	(*steps)++;
	
	/* creo in maniera pseudo-casuale un valore compreso tra 0 e 10 e che mi rappresentera' un veicolo di quelli elencati sopra */
	j = rand()%11;
	(*steps)++;
	
	/* verifico la lunghezzza della stringa */	
	lunghezza_stringa = strlen(nomi_veicoli[j]);
	(*steps)++;
	
	/* se la stringa acquisita ha meno di 20 caratteri vado a riempire gli elementi vuoti con degli spazi  */
	/* questo viene fatto per poter mantenere, durante la stampa, l'indentazione comunicata dalla specifica*/
	for(i = lunghezza_stringa; i < 20; i++)
	{
		(*steps)++;
		nomi_veicoli[j][i] = ' ';
		(*steps)++;
	}
	
	/* viene inizializzato l'ultimo elemento della stringa al carattere di terminazione della stringa */	
	nomi_veicoli[j][20] = '\0';
	(*steps)++;
	
	/* controllo di sicurezza per verificare che la stringa non sia più grande del dovuto */	
	if(strlen(nomi_veicoli[j]) != 20)
	{
		(*steps)++;
		printf("\nValore inserito errato! Valore con un formato diverso da quello atteso! Riprovare! Riprovare!\n\n");
		(*steps)++;
	}

	/* utilizzo la "strcmp" per copiare il contenuto della stringa temporanea all'interno della variabile stringa della struttura "veicolo" */
	strcpy(nuovo_veicolo.nome_veicolo, nomi_veicoli[j]);
	(*steps)++;
	
	/* creo in maniera pseudo-casuale un valore compreso tra 1900 e 2021 e che mi rappresentera' l'anno di immatricolazione di un veicolo */
	anno_immatricolazione = rand()%121 + 1900;
	(*steps)++;
	
	/* inizializzo la variabile intera della struttura "veicolo" al contenuto della variabile intera temporanea */
	nuovo_veicolo.anno_immatricolazione = anno_immatricolazione;	
	(*steps)++;
	
	return(nuovo_veicolo);
}

int Ricerca_veicolo(veicolo *array_veicoli, int numero_veicoli, int posizione_centrale_array)
{
	int posizione_valore = -1,	/* variabile che mi conterra' il valore rappresentante la posizione fisica di dove si trova l'elemento da ricercare nell'array  				 	*/
	    						/* inizialmente inizializzato a -1 che rappresenta il valore di default se il veicolo da ricercare non e' presente in memoria 						*/
	    risultato_confronto,	/* variabile che mi conterra' il valore risultante dal confronto del valore da ricercare con uno alla volta quelli presenti all'interno dell'array  */
	    i,						/* variabile intera contatore per scorrere gli elementi dell'array																					*/
	    steps = 0;				/* variabile che mi conterra' il valore risultante dalla conta del numero dei passi che esegue l'algoritmo											*/
	
	/* scorro gli elementi dell'array */	
	for(i = 0; i < numero_veicoli; i++)
	{
		steps++;
		/* ad ogni iterazione confronto l'elemento i-esimo dell'array con il valore acquisito in input */
		/* essendo confronto tra stringhe utilizzo la "strcmp" 										   */
		risultato_confronto = strcmp(array_veicoli[i].codice_veicolo, array_veicoli[posizione_centrale_array].codice_veicolo);
		steps++;
		
		/* se "risultato_confronto" uguale 0, vuol dire che le due stringhe sono uguali																 */
		/* quindi comunico all'utente tutte le informazioni riguardanti il veicolo trovato e ne salvo la posizione nell'array per eventuali utilizzi */
		if(risultato_confronto == 0)
		{
			steps++;
			printf("\nVeicolo\tProprietario\tModello            \tAnno\n");
			printf("%-7s\t%-12s\t%s\t%d\n", array_veicoli[i].codice_veicolo, array_veicoli[i].codice_proprietario, array_veicoli[i].nome_veicolo, array_veicoli[i].anno_immatricolazione);
			posizione_valore = i;
			steps++;
		}
	}
	
	printf("\nL'algoritmo ha impiegato %d passi per ricercare il veicolo centrale tra %d veicoli\n", steps, numero_veicoli);
	
	return(posizione_valore);
}

void Rimozione_veicolo(veicolo *array_veicoli, int *numero_veicoli, int posizione_centrale_array)
{
	int posizione_veicolo_eliminare,	/* variabile che mi conterra' il valore rappresentante la posizione fisica di dove si trova l'elemento da eliminare nell'array */
		dim = (*numero_veicoli),		/* variaible intera che mi rappresenta il numero di veicoli totali che avro' dopo la rimozione   							   */
		i,								/* variabile intera contatore per scorrere gli elementi dell'array															   */
		steps = 0;						/* variabile che mi conterra' il valore risultante dalla conta del numero dei passi che esegue l'algoritmo					   */
	
	/* utilizzo la funzione "Ricerca_veicolo" per trovare in memoria la posizione fisica del veicolo che voglio eliminare */
	posizione_veicolo_eliminare = Ricerca_veicolo_rimuovere(array_veicoli, dim, posizione_centrale_array, &steps);
	steps++;
	
	/* stampo il veicolo che verra' eliminato */
	printf("\nVeicolo\tProprietario\tModello            \tAnno\n");
			printf("%-7s\t%-12s\t%s\t%d\n", array_veicoli[posizione_veicolo_eliminare].codice_veicolo, array_veicoli[posizione_veicolo_eliminare].codice_proprietario, array_veicoli[posizione_veicolo_eliminare].nome_veicolo, array_veicoli[posizione_veicolo_eliminare].anno_immatricolazione);
	
	/* se il valore di ritorno della funzione "Ricerca_veicolo" e' maggiore di -1 vuol dire che il veicolo e' stato trovato in memoria e proseguo con l'eliminazione */
	if(posizione_veicolo_eliminare > -1)
	{
		steps++;
		/* scorro gli elementi dell'array a partire dall'elemento che voglio eliminare 									     */
		/* ad ogni iterazione scambio l'elemento che voglio eliminare con il successivo fino a portarlo alla fine dell'array */
		for(i = posizione_veicolo_eliminare; i < dim; i++)
		{
			steps++;
			array_veicoli[i] = array_veicoli[i + 1];
			steps++;
		}
		
		/* diminuisco dim di 1 perche' dopo l'eliminazione avro' un veicolo in meno */
		dim -= 1;
		steps++;
		
		/* vado a ri-dimensionare il blocco di memoria in modo che mi contenga un elemento in meno in quanto voglio eliminare un veicolo 																		  */
		/* la realloc e' l'azione contemporanea di malloc e free, quindi taglia dalla fine dell'array un determinato numero di elementi se gli si fornisce una dimensione minore di quella che il blocco presenta */
		array_veicoli = (veicolo*)realloc(array_veicoli, sizeof(veicolo) * dim);
		steps++;
		
		/* aggiorno numero_veicoli */		
		*numero_veicoli = dim;
		steps++;
		
		printf("\nL'algoritmo ha impiegato %d passi per rimuovere il veicolo centrale tra %d veicoli\n", steps, dim + 1);
	}
}

int Ricerca_veicolo_rimuovere(veicolo *array_veicoli, int numero_veicoli, int posizione_centrale_array, int* steps)
{
	int posizione_valore = -1,	/* variabile che mi conterra' il valore rappresentante la posizione fisica di dove si trova l'elemento da ricercare nell'array  				 	*/
	    						/* inizialmente inizializzato a -1 che rappresenta il valore di default se il veicolo da ricercare non e' presente in memoria 						*/
	    risultato_confronto,	/* variabile che mi conterra' il valore risultante dal confronto del valore da ricercare con uno alla volta quelli presenti all'interno dell'array  */
	    i;						/* variabile intera contatore per scorrere gli elementi dell'array																					*/
	
	/* scorro gli elementi dell'array */	
	for(i = 0; i < numero_veicoli; i++)
	{
		(*steps)++;
		/* ad ogni iterazione confronto l'elemento i-esimo dell'array con il valore acquisito in input */
		/* essendo confronto tra stringhe utilizzo la "strcmp" 										   */
		risultato_confronto = strcmp(array_veicoli[i].codice_veicolo, array_veicoli[posizione_centrale_array].codice_veicolo);
		(*steps)++;
		
		/* se "risultato_confronto" uguale 0, vuol dire che le due stringhe sono uguali																 */
		/* quindi comunico all'utente tutte le informazioni riguardanti il veicolo trovato e ne salvo la posizione nell'array per eventuali utilizzi */
		if(risultato_confronto == 0)
		{
			(*steps)++;
			posizione_valore = i;
			(*steps)++;
		}
	}
	
	if(posizione_valore == -1)
	{
		(*steps)++;
		printf("\nVeicolo non trovato in memoria\n");
	} 
	
	return(posizione_valore);
}

veicolo Ricerca_valore_massimo(veicolo *array_veicoli, int numero_veicoli)
{
	int i,					/* variabile contatore utilizzata per scorrere uno alla volta gli elementi dell'array 											 	*/
		controllo,			/* variabile che mi conterra' il valore risultante dal confronto tra i valori presenti all'interno dell'array  					    */
		steps = 0;			/* variabile che mi conterra' il valore risultante dalla conta del numero dei passi che esegue l'algoritmo							*/
		
	veicolo tmp_veicolo;	/* variabile che mi conterra' il veicolo piu' piccolo (ottenuto confrontando i codici dei veicoli secondo l'ordine lessicografico)  */
	
	/* scorro gli elementi dell'array */
	for(i = 0; i < numero_veicoli; i++)
	{
		steps++;
		/* alla prima iterazione non faccio altro che prendere come elemento di riferimento il primo veicolo */
		if(i == 0)
		{
			steps++;
			tmp_veicolo = array_veicoli[i];
			steps++;
		}
		else
		{
			steps++;
			/* confronto tramite "strcmp" (che mi permette il confronto tramite ordine lessicografico) i codici dei veicoli */
			controllo = strcmp(tmp_veicolo.codice_veicolo, array_veicoli[i].codice_veicolo);
			steps++;
			
			/* se confronto e' maggiore di 0, vuol dire che il codice veicolo i-esimo confrontato con l'elemento di riferimento e' piu' piccolo 																	 */
			/* quindi mi diventa il mio nuovo elemento di riferimento e lo confrontero' con gli elementi successivi fino a quando non trovo un nuovo elemento piu' piccolo o finche' non arrivo alla fine dell'array */
			if(controllo < 0)
			{
				steps++;
				tmp_veicolo = array_veicoli[i];
			}
		}
	}
	
	printf("\nL'algoritmo ha impiegato %d passi per calcolare il veicolo piu' grande secondo l'ordine lessicografico tra %d veicoli\n", steps, numero_veicoli);
	
	return(tmp_veicolo);
}

veicolo Ricerca_valore_minimo(veicolo *array_veicoli, int numero_veicoli)
{
	int i,					/* variabile contatore utilizzata per scorrere uno alla volta gli elementi dell'array 											 	*/
		controllo,			/* variabile che mi conterra' il valore risultante dal confronto tra i valori presenti all'interno dell'array  					    */
		steps = 0;			/* variabile che mi conterra' il valore risultante dalla conta del numero dei passi che esegue l'algoritmo							*/
		
	veicolo tmp_veicolo;	/* variabile che mi conterra' il veicolo piu' piccolo (ottenuto confrontando i codici dei veicoli secondo l'ordine lessicografico) */
	
	/* scorro gli elementi dell'array */
	for(i = 0; i < numero_veicoli; i++)
	{
		steps++;
		/* alla prima iterazione non faccio altro che prendere come elemento di riferimento il primo veicolo */
		if(i == 0)
		{
			steps++;
			tmp_veicolo = array_veicoli[i];
			steps++;
		}
		else
		{
			steps++;
			/* confronto tramite "strcmp" (che mi permette il confronto tramite ordine lessicografico) i codici dei veicoli */
			controllo = strcmp(tmp_veicolo.codice_veicolo, array_veicoli[i].codice_veicolo);
			steps++;
			
			/* se confronto e' maggiore di 0, vuol dire che il codice veicolo i-esimo confrontato con l'elemento di riferimento e' piu' piccolo 																	 */
			/* quindi mi diventa il mio nuovo elemento di riferimento e lo confrontero' con gli elementi successivi fino a quando non trovo un nuovo elemento piu' piccolo o finche' non arrivo alla fine dell'array */
			if(controllo > 0)
			{
				steps++;
				tmp_veicolo = array_veicoli[i];
				steps++;
			}
		}
	}
	
	printf("\nL'algoritmo ha impiegato %d passi per calcolare il veicolo piu' piccolo secondo l'ordine lessicografico tra %d veicoli\n", steps, numero_veicoli);
	
	return(tmp_veicolo);
}

void Stampa_array(veicolo *array_veicoli, int numero_veicoli)
{
	int i;	/* variabile contatore utilizzata per scorrere uno alla volta gli elementi dell'array */
	
	printf("Veicolo\tProprietario\tModello            \tAnno\n");
	
	/* scorro gli elementi dell'array uno alla volta e ne stampo il contenuto mantenendo l'indentazione della specifica */
	for(i = 0; i < numero_veicoli ; i++)
	{
		printf("%-7s\t%-12s\t%s\t%d\n", array_veicoli[i].codice_veicolo, array_veicoli[i].codice_proprietario, array_veicoli[i].nome_veicolo, array_veicoli[i].anno_immatricolazione);
	}
}

/* Funzione che ripulisce il buffer */
void LiberaBuffer()
{
    while (getchar() != '\n');
}

