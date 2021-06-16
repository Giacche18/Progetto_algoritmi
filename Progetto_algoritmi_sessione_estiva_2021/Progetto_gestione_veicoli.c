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
veicolo* Leggi_su_File(char* nome_file,								/* Argomento 1 funzione: stringa che rappresenta il nome del file da cui acquisire le informazioni inziali		     									   */
					   int*	 numero_veicoli);						/* Argomento 2 funzione: valore intero che rappresenta il numero di veicoli e che viene passato come puntatore perche' voglio tenere conto delle modifiche */
					   
/* funzione che permette di scrivere su file ogni volta che il programma modifica le informazioni riguardanti i veicoli (aggiungendone di nuovi o elinandone altri) */
void Scrivi_su_file(veicolo *array_veicoli, 						/* Argomento 1 funzione: array che mi contiene i veicoli		     															  						   */
					int numero_veicoli, 							/* Argomento 2 funzione: valore intero che rappresenta il numero di veicoli		     															  		   */
					char* nome_file);								/* Argomento 3 funzione: stringa che rappresenta il nome del file su cui andare a scrivere le informazioni aggiornate		     						   */
					
/* funzione che permette di inserire un nuovo veicolo */					   				
veicolo* Inserisci_veicolo(veicolo *array_veicoli, 					/* Argomento 1 funzione: array che mi conterra' i veicoli		     										  											   */
						   int* numero_veicoli, 					/* Argomento 2 funzione: valore intero che rappresenta il numero di veicoli e che viene passato come puntatore perche' voglio tenere conto delle modifiche */		     										  											  
						   int  numero_veicoli_inseriri);			/* Argomento 3 funzione: valore intero che rappresenta il numero di nuovi veicoli che l'utente vuole inserire											   */
						   
/* funzione che permette di ricercare uno specifico veicolo in memoria */					   
int Ricerca_veicolo(veicolo *array_veicoli, 						/* Argomento 1 funzione: array che mi contiene i veicoli		     										  											   */
				    int numero_veicoli);							/* Argomento 2 funzione: valore intero che rappresenta il numero di veicoli		     															  		   */

/* funzione che permette di rimuovere uno specifico veicolo dalla memoria */
void Rimozione_veicolo(veicolo *array_veicoli, 						/* Argomento 1 funzione: array che mi contiene i veicoli		     										  											   */
					   int* numero_veicoli);						/* Argomento 2 funzione: valore intero che rappresenta il numero di veicoli e che viene passato come puntatore perche' voglio tenere conto delle modifiche */
					   
/* funzione che permette di calcolare il valore piu' grande (secondo l'ordine lessicografico) del codice alfanumerico rappresentante il veicolo */
veicolo Ricerca_valore_massimo(veicolo *array_veicoli, 				/* Argomento 1 funzione: array che mi contiene i veicoli		     										  											   */
							   int numero_veicoli);					/* Argomento 2 funzione: valore intero che rappresenta il numero di veicoli		     															  		   */
							   
/* funzione che permette di calcolare il valore piu' piccolo (secondo l'ordine lessicografico) del codice alfanumerico rappresentante il veicolo */
veicolo Ricerca_valore_minimo(veicolo *array_veicoli, 				/* Argomento 1 funzione: array che mi contiene i veicoli		     										  											   */
							  int numero_veicoli);					/* Argomento 2 funzione: valore intero che rappresenta il numero di veicoli		     															  		   */

/* funzione utilizzata dal programma per liberare il buffer */
void LiberaBuffer();

/* funzione utilizzata dal programma per acquisire in input le 4 informazioni riguardanti il veicolo */
veicolo Recupero_dati_veicolo();

/* funzione utilizzata dal programma per stampare a schermo i veicoli contenuti nell'array con le rispettive informazioni*/
void Stampa_array(veicolo *array_veicoli, 							/* Argomento 1 funzione: array che mi contiene i veicoli		     										  											   */
				  int numero_veicoli);								/* Argomento 2 funzione: valore intero che rappresenta il numero di veicoli		     															  		   */

int main(int argc, char *argv[]) 
{
	veicolo *array_veicoli = NULL;		/* variabile che mi conterra' i veicoli con le rispettive informazioni 				    */
	veicolo valore_massimo;				/* variabile che mi conterra' il veicolo piu' grande (secondo l'ordine lessicografico)  */
	veicolo valore_minimo;				/* variabile che mi conterra' il veicolo piu' piccolo (secondo l'ordine lessicografico) */
	
	int numero_veicoli 			   = 0, /* variabile intera che mi permette di tenere conto del numero totale di veicoli	   																					*/
	    numero_veicoli_inseriti    = 0, /* variabile intera che mi permette di tenere conto del numero di veicoli che l'utente vuole inserire 																	*/
      	valore_controllo_menu 	   = 0, /* variabile intera che mi permette di validare il valore acquisito in input che rappresenta la scelta della voce del menu' 											*/
	    valore_controllo_scanf	   = 0, /* variabile intera che mi permette di controllare che il valore di ritorno della scanf riguardante l'input che rappresenta la scelta della voce del menu' sia corretto */
	    posizione_valore_ricercato = 0;	/* variabile intera che mi permette di tenere conto della posizione fisica (all'interno dell'array) in cui si trova il veicolo che l'utente vuole ricercare 			*/
		
	char nome_file[30];					/* stringa che mi conterra' il nome del file che contiene le informazioni iniziali necessarie al programma																*/
	
	printf("Programma per un sistema informativo che gestisce i dati relativi ad un'anagrafe di autoveicoli.\n");
	printf("Il sistema permette di mantenere, per ogni veicolo, questi dati:\n");
	printf("- veicolo: codice univoco alfanumerico rappresentato da una stringa concatenazione di quattro lettere e due numeri;\n");
	printf("- proprietario: codice rappresentato da una stringa concatenazione di tre lettere e tre numeri;\n");
	printf("- modello del veicolo: stringa di massimo 20 caratteri;\n");
	printf("- anno di immatricolazione: un numero intero.\n\n");
	
	printf("Le informazioni sono memorizzate su un file in formato testo. Per questo motivo la prima cosa che vi verra' chiesta sara' inserire il nome del file su cui sono memorizzati i dati.\n\n");
	
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
		printf("\nLe informazioni sono memorizzate nel modo che segue... \n\n");	
		Stampa_array(array_veicoli, numero_veicoli);
	}
	
	/* interfaccia utente all'interno di un "do/while" per riproporla ogni volta che l'input della scelta della voce del menu' e' errata oppure dopo che viene terminata l'esecuzione di una delle funzionalita' del programma */
	do
	{
		printf("\n[MENU' PER LA GESTIONE DEL PROGRAMMA]\n");
		printf("Digitare 1 per aggiungere uno o piu' veicoli all'elenco (il file dati verra' aggiornto automaticamente alla fine dell'operazione);\n");
		printf("Digitare 2 per ricercare uno specifico veicolo dell'elenco;\n");
		printf("Digitare 3 per rimuovere uno specifico veicolo dall'elenco;\n");
		printf("Digitare 4 per calcolare il valore piu' piccolo (secondo l'ordine lessicografico) del codice alfanumerico rappresentante il veicolo;\n");
		printf("Digitare 5 per calcolare il valore piu' grande (secondo l'ordine lessicografico) del codice alfanumerico rappresentante il veicolo;\n");
		printf("Digitare 6 per interrompere l'esecuzione del programma e uscire dall'applicazione;\n\n");
		
		valore_controllo_menu = 0;	
		
		printf("Digita un valore: ");
		valore_controllo_scanf = scanf("%d", &valore_controllo_menu);
		
		LiberaBuffer();
		
		/* controllo che l'utente abbia inserito un valore congruo a quelli che il programma si aspetta */
		if(valore_controllo_menu > 6 || valore_controllo_menu <= 0 || valore_controllo_scanf == 0)
		{
			printf("\nERRORE! IL VALORE DIGITATO NON CORRISPONDE A NESSUNA VOCE DEL MENU' RIPROVARE!\n");
		}
		else
		{
			/* vado ad eseguire una delle funzionalita' del programma in base alla scelta dell'utente   */
			switch(valore_controllo_menu)
			{
				case 1:
					printf("\nQuanti veicoli vuoi inserire? ");
					valore_controllo_scanf = scanf("%d", &numero_veicoli_inseriti);
					
					LiberaBuffer();
					
					/* controllo che l'utente abbia inserito un valore congruo a quelli che il programma si aspetta */				
					if(numero_veicoli_inseriti <= 0 || valore_controllo_scanf == 0)
					{
						printf("\nErrore! Il numero di veicoli deve corrispondere ad un valore positivo e diverso da 0!\n");
					}
					else
					{	
						/* viene invocata la funzione "Inserisci_veicolo" per permettere all'utente di inserire nuovi veicoli */
						array_veicoli = Inserisci_veicolo(array_veicoli, &numero_veicoli, numero_veicoli_inseriti);
				
						printf("\nElenco dei veicoli aggiornato come segue...\n\n");
						
						/* stampo l'elelenco dei veicoli aggiornato */
						Stampa_array(array_veicoli, numero_veicoli);
						
						/* aggiorno il file con le nuove informazioni */
						Scrivi_su_file(array_veicoli, numero_veicoli, nome_file);
					}
					
					break;
				case 2:
					/* viene invocata la funzione "Ricerca_veicolo" per permettere all'utente di ricercare uno specifico veicolo e salvo il valore di ritorno all'interno di "posizione_valore_ricercato" */
					posizione_valore_ricercato = Ricerca_veicolo(array_veicoli, numero_veicoli);
					
					/* se il veicolo non viene trovato la funzione "Ricerca_veicolo" inizializza "posizione_valore_ricercato" a -1 in modo da poterlo comunicare all'utente*/
					if(posizione_valore_ricercato == -1)
					{
						printf("\nVeicolo non trovato in memoria\n");
					} 
		
					break;
				case 3:
					/* viene invocata la funzione "Ricerca_veicolo" per permettere all'utente di rimuovere uno specifico veicolo */
					Rimozione_veicolo(array_veicoli, &numero_veicoli);
					
					/* aggiorno il file con le informazioni modificate*/
					Scrivi_su_file(array_veicoli, numero_veicoli, nome_file);
					
					break;
				case 4:
					
					/* viene invocata la funzione "Ricerca_valore_minimo" per calcolare il valore piu' piccolo (secondo l'ordine lessicografico) e salvo il valore di ritorno all'interno di "valore_minimo"  */
					valore_minimo = Ricerca_valore_minimo(array_veicoli, numero_veicoli);
					printf("\nValore minimo: %s\n", valore_minimo.codice_veicolo);
					break;
				case 5:
					/* viene invocata la funzione "Ricerca_valore_massimo" per calcolare il valore piu' grande (secondo l'ordine lessicografico) e salvo il valore di ritorno all'interno di "valore_massimo" */
					valore_massimo = Ricerca_valore_massimo(array_veicoli, numero_veicoli);
					printf("\nValore massimo: %s\n", valore_massimo.codice_veicolo);
					break;
				case 6:
					
					/* per terminare l'esecuzione del programma */
					
					break;	
			}
		}
	}while(valore_controllo_menu != 6);

	return 0;
}

veicolo* Leggi_su_File(char* nome_file, int* numero_veicoli)
{
	veicolo tmp_veicolo; 		 		/* variabile che mi permette di salvare temporaneamente le informazioni riguardanti un veicolo presenti su una riga del file  	 */
	veicolo *array_veicoli;		 		/* array in cui salvare i veicoli con le rispettive informazioni														  	  	 */
	
	char* valore_ritorno_fgets;	 		/* variabile che mi conterra' il valore di ritorno delle fgets per eventuali controlli 									  	  	 */

	FILE *file;					 		/* variabile di tipo file per poter agire sul file di input in modalità lettura/scrittura									  	 */
	
	int count 					= 0,	/* variabile intera che mi permette di tenere conto del numero di righe contenenti informazioni sui veicoli all'interno del file */						
	    valore_controllo_scanf  = 0,	/* variabile intera che mi conterra' il valore di ritorno delle scanf per eventuali controlli 									 */	
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
			  			printf("\nErrore in lettura!\n");
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
							printf("\nErrore in lettura!!\n");
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
					   	   		printf("\nErrore in lettura!\n");
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
			  			printf("\nErrore in lettura!\n");
					}
					else
					{
						valore_ritorno_fgets = fgets(array_veicoli[count].nome_veicolo,
				            	 				 	 21,
				             				     	 file);
				      		
						if(valore_ritorno_fgets == NULL)
						{
							printf("\nErrore in lettura!!\n");
						}
						else
						{
							valore_controllo_fscanf = fscanf(file,
					      	   	   					  "%d\n",
					     	       					  &array_veicoli[count].anno_immatricolazione);
					     	
					     	if(valore_controllo_fscanf == 0)
					     	{
					     		printf("\nErrore in lettura!\n");
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
	int i; 		/* variabile intera che verra' utilizzata come contatore per scorrere gli elementi dell'array */
	
	FILE *file; /* variabile di tipo file per poter agire sul file di input in modalità lettura/scrittura	  */
	
	/* il file viene aperto in modalità scrittura per aggiornarlo con le nuove informazioni					  */
	file = fopen(nome_file,
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
		printf("\nErrore in apertura del file!\n\n");
	}		 	
}

veicolo* Inserisci_veicolo(veicolo *array_veicoli, int* numero_veicoli, int numero_veicoli_inseriti)
{
	int dim = *numero_veicoli + numero_veicoli_inseriti, 					  /* variaible intera che mi rappresenta il numero di veicoli totali che avro' dopo l'inserimento   */
		i;																	  /* variabile intera che verra' utilizzata come contatore per scorrere gli elementi dell'array 	*/
	
	array_veicoli = (veicolo*)realloc(array_veicoli, sizeof(veicolo) * dim); /* ri-alloco dinamicamente la memoria per fare in modo che l'array possa contenere i nuovi veicoli */
	
	/* controllo per verificare che la realloc vada a buon fine*/
	if(array_veicoli == NULL)
	{
		printf("\nErrore durante l'allocazione dinamica della memoria!\n");
	}
	else
	{
		/* scorro gli elementi dell'array e ad ogni iterazione inserisco all'interno della i-esima cella di memoria il nuovo valore */ 
		for(i = *numero_veicoli; i < dim; i++)
		{
			/* invovo ad ogni iterazione la funzione "recupero_dati_veicolo" per acquisire in input le informazioni del nuovo veicolo */
			array_veicoli[i] = Recupero_dati_veicolo();			
				
			printf("\nVeicolo Inserito con successo!\n");
		}	
		
		/* aggiorno "numero_veicoli" al numero di veicoli totali che si avra' dopo l'inserimento*/
		*numero_veicoli = dim;
	}
	
	return(array_veicoli);
}

veicolo Recupero_dati_veicolo()
{
	veicolo nuovo_veicolo;				/* variabile che mi conterra' il nuovo veicolo ritornato dalla funzione e salvato all'interno dell'iesima cella dell'array 						   */
	
	char tmp_string[7];					/* stringa che mi conterra' temporneamente codice veicolo e codice proprietario											   						   */
	char tmp_string_nome_veicolo[21];	/* stringa che mi conterra' temporneamente il nome del veicolo			 												   						   */
	
	int anno_immatricolazione,			/* variabile intera che mi conterra' temporneamente l'anno di immatricolazione del veicolo 								  						   */
	    lunghezza_stringa 	   = 0,		/* variabile intera utilizzata per tenere conto della lunghezza della stringa per successive modifiche 					  						   */
	    valore_controllo 	   = 1,		/* variabile intera utilizzata dal programma per capire se deve ri-eseguire determinate acquisizioni											   */
	    valore_controllo_scanf = 0,		/* variabile intera che mi conterra' il valore di ritorno delle scanf per eventuali controlli 									 				   */	
        i;								/* variabile contatore per scorrere i caratteri che formano le stringhe introdotte precedentemente 												   */

	char* valore_ritorno_fgets;			/* variabile intera che mi conterra' il valore di ritorno delle fgets per eventuali controlli 									 				   */	
	
	
	/* acquisizione con validazione del codice veicolo*/
	do
	{
		printf("\nInserisci il codice del veicolo (formato da 4 lettere maiuscole e 2 numeri)...\n");
		valore_controllo_scanf = scanf("%s", tmp_string);
		
		/* controllo il valore di ritorno della fscanf per verificare che cio' che e' stato letto da file sia corretto */
		if(valore_controllo_scanf == 0)
		{
			printf("\nErrore!!\n");
			LiberaBuffer();
		}
		else
		{	
			/* nel caso in cui uno dei successivi controlli non sia andato a buon fine "valore_controllo" viene inizializzato con 0 per ri-eseguire l'acquisizione */
			/* nel momento in cui una acquisizione viene ri-eseguita "valore_controllo" viene inizializzato nuovamente a 1 per non entrare in un loop			   */
			if(valore_controllo == 0)
			{
				valore_controllo = 1;
			}
			
			/* controllo che la stringa non superi la lunghezza stabilita */
			if(strlen(tmp_string) != 6)
			{
				printf("\nValore inserito errato! Valore con un formato diverso da quello atteso! Riprovare!\n\n");
				valore_controllo = 0;
			}
			
			/* controllo che i primi 4 caratteri della stringa siano lettere maiuscole */
			for(i = 0; i < 4 && valore_controllo == 1; i++)
			{
				if(!(isupper(tmp_string[i])))
				{
					printf("\nValore inserito errato! Le prime 4 cifre del codice cliente devono essere lettere maiuscole! Riprovare!\n\n");
					valore_controllo = 0;
				}	
			}			
		
			/* controllo che gli ultimi 2 caratteri della stringa siano numeri */
			for(i = 4; i < 6 && valore_controllo == 1; i++)
			{
				if(!(isdigit(tmp_string[i])))
				{
					printf("\nValore inserito errato! Le ultime 2 cifre del codice cliente devono essere numeri interi e positivi! Riprovare!\n\n");
					valore_controllo = 0;
				}	
			}
		}
	}while(valore_controllo == 0 || valore_controllo_scanf == 0);
	
	
	/* utilizzo la "strcmp" per copiare il contenuto della stringa temporanea all'interno della variabile stringa della struttura "veicolo" */
	strcpy(nuovo_veicolo.codice_veicolo, tmp_string);
	
	/* acquisizione con validazione del codice proprietario*/
	do
	{
		printf("Inserisci il codice del proprietario (formato da 3 lettere maiuscole e 3 numeri)...\n");
		valore_controllo_scanf = scanf("%s", tmp_string);
		
		/* controllo il valore di ritorno della fscanf per verificare che cio' che e' stato letto da file sia corretto */
		if(valore_controllo_scanf == 0)
		{
			printf("\nErrore\n");
			LiberaBuffer();
		}
		else
		{
				
			/* nel caso in cui uno dei successivi controlli non sia andato a buon fine "valore_controllo" viene inizializzato con 0 per ri-eseguire l'acquisizione */
			/* nel momento in cui una acquisizione viene ri-eseguita "valore_controllo" viene inizializzato nuovamente a 1 per non entrare in un loop			   */	
			if(valore_controllo == 0)
			{
				valore_controllo = 1;
			}
			
			/* controllo che la stringa non superi la lunghezza stabilita */
			if(strlen(tmp_string) != 6)
			{
				printf("\nValore inserito errato! Valore con un formato diverso da quello atteso! Riprovare!\n\n");
				valore_controllo = 0;
			}
			
			/* controllo che i primi 3 caratteri della stringa siano lettere maiuscole */
			for(i = 0; i < 3 && valore_controllo == 1; i++)
			{
				if(!(isupper(tmp_string[i])))
				{
					printf("\nValore inserito errato! Le prime 3 cifre del codice proprietario devono essere lettere maiuscole! Riprovare!\n\n");
					valore_controllo = 0;
				}	
			}		
		
			/* controllo che gli ultimi 3 caratteri della stringa siano numeri */
			for(i = 3; i < 6 && valore_controllo == 1; i++)
			{
				if(!(isdigit(tmp_string[i])))
				{
					printf("\nValore inserito errato! Le ultime 3 cifre del codice proprietario devono essere numeri interi e positivi! Riprovare!\n\n");
					valore_controllo =  0;
				}
			}
		}
	}while(valore_controllo == 0 || valore_controllo_scanf == 0);
	
	/* utilizzo la "strcmp" per copiare il contenuto della stringa temporanea all'interno della variabile stringa della struttura "veicolo" */
	strcpy(nuovo_veicolo.codice_proprietario, tmp_string);
	
	/* acquisizione con validazione dell'anno di immatricolazione del veicolo*/
	do
	{
		printf("Inserisci l'anno di immatricolazione (massimo 4 numeri)...\n");
		valore_controllo_scanf = scanf("%d", &anno_immatricolazione);
		
		/* controllo il valore di ritorno della fscanf per verificare che cio' che e' stato letto da file sia corretto */
		if(valore_controllo_scanf == 0)
		{
			printf("\nErrore!! Input invalido, riprovare!\n\n");
			LiberaBuffer();
		}
		else
		{
			/* nel caso in cui uno dei successivi controlli non sia andato a buon fine "valore_controllo" viene inizializzato con 0 per ri-eseguire l'acquisizione */
			/* nel momento in cui una acquisizione viene ri-eseguita "valore_controllo" viene inizializzato nuovamente a 1 per non entrare in un loop			   */	
			if(valore_controllo == 0)
			{
				valore_controllo = 1;
			}
			
			/* controllo che il valore inserito non sia negativo*/
			if(anno_immatricolazione < 0)
			{
				printf("\nValore inserito errato! Inserire l'anno di immatricolazione formato da 4 numeri interi e positivi!\n\n");
				valore_controllo = 0;
			}
			
			/* controllo che il valore inserito non sia maggiore di 2021, ovvero l'anno in cui ci troviamo */
			if(anno_immatricolazione > 2021)
			{
				printf("\nValore inserito errato! Siamo nel 2021!\n\n");
				valore_controllo = 0;
			}
		}	
	}while(valore_controllo == 0 || valore_controllo_scanf == 0);
	
	/* inizializzo la variabile intera della struttura "veicolo" al contenuto della variabile intera temporanea */
	nuovo_veicolo.anno_immatricolazione = anno_immatricolazione;
	
	/* in questo punto il buffer viene liberato perche' altrimenti la fgets verrebbe saltata e il nome del veicolo verrebbe acquisito */
	LiberaBuffer();
	
	/* acquisizione con validazione del nome del veicolo*/
	do
	{
		printf("Inserisci il nome del modello (massimo 20 caratteri)...\n");
		valore_ritorno_fgets = fgets(tmp_string_nome_veicolo, 20, stdin);  
		
		/* viene liberato il buffer anche dopo la fgets perche' nel caso in cui la stringa acquisita sia superiore a 20 caratteri 
		 * causa problemi alle acquisizioni successive nel momento in cui si torna nel main 									  			   */
		/* questo purtroppo porta a dover premere due volte invio dopo questa acquisizione ma non vi era modo diverso di risolvere il problema */
		LiberaBuffer();
		
		/* nel caso in cui uno dei successivi controlli non sia andato a buon fine "valore_controllo" viene inizializzato con 0 per ri-eseguire l'acquisizione */
		/* nel momento in cui una acquisizione viene ri-eseguita "valore_controllo" viene inizializzato nuovamente a 1 per non entrare in un loop			   */
		if(valore_controllo == 0)
		{
			valore_controllo = 1;			
		}
		
		/* controllo il valore di ritorno della fgets per verificare che cio' che e' stato acquisito sia corretto */
		if(valore_ritorno_fgets == NULL)
		{
			printf("\nErrore! Riprovare!\n");
		}
		else
		{
			/* viene inizializzato l'ultimo elemento della stringa al carattere di terminazione della stringa */
			tmp_string_nome_veicolo[20] = '\0'; 
			
			/* controllo di sicurezza per verificare che la stringa non sia più grande del dovuto */
			if(strlen(tmp_string_nome_veicolo) > 20)
			{
				printf("\nValore inserito errato! Valore con un formato diverso da quello atteso! Riprovare!\n\n");
				valore_controllo = 0;
			}
			else
			{
				/* verifico la lunghezzza della stringa */
				lunghezza_stringa = strlen(tmp_string_nome_veicolo);
				
				/* se la stringa acquisita ha meno di 20 caratteri vado a riempire gli elementi vuoti con degli spazi  */
				/* questo viene fatto per poter mantenere, durante la stampa, l'indentazione comunicata dalla specifica*/
				for(i = lunghezza_stringa - 1; i < 20; i++)
				{
					tmp_string_nome_veicolo[i] = ' ';
				}
			}	
		}	
	}while(valore_controllo == 0);
	
	/* utilizzo la "strcmp" per copiare il contenuto della stringa temporanea all'interno della variabile stringa della struttura "veicolo" */
	strcpy(nuovo_veicolo.nome_veicolo, tmp_string_nome_veicolo);
	
	return(nuovo_veicolo);
}

int Ricerca_veicolo(veicolo *array_veicoli, int numero_veicoli)
{
	char codice_da_ricercare[7];	/* stringa che mi conterra' il codice riguardante il veicolo che l'utente vuole ricercare  															*/
	
	int valore_controllo 	 = 1,	/* variabile intera utilizzata dal programma per capire se deve ri-eseguire l'acquisizione 															*/
	    posizione_valore 	 = -1,	/* variabile che mi conterra' il valore rappresentante la posizione fisica di dove si trova l'elemento da ricercare nell'array  				 	*/
	    							/* inizialmente inizializzato a -1 che rappresenta il valore di default se il veicolo da ricercare non e' presente in memoria 						*/
	    risultato_confronto,		/* variabile che mi conterra' il valore risultante dal confronto del valore da ricercare con uno alla volta quelli presenti all'interno dell'array  */
	    valore_ritorno_scanf = 0,	/* variabile intera che mi conterra' il valore di ritorno delle scanf per eventuali controlli 									 				    */
	    i;							/* variabile intera contatore per scorrere gli elementi dell'array																					*/
	
	/* acquisizione codice veicolo da ricercare in memoria */	
	do
	{
		printf("\nDigita il codice relativo al veicolo che ti interessa: ");
		valore_ritorno_scanf = scanf("%s", codice_da_ricercare);
		
		/* controllo il valore di ritorno della fscanf per verificare che cio' che e' stato acquisito sia corretto */	
		if(valore_ritorno_scanf == 0)
		{
			printf("\nErrore!!\n");
		}
		else
		{
			/* pulisco il buffer */
			LiberaBuffer();
		
			/* nel caso in cui uno dei successivi controlli non sia andato a buon fine "valore_controllo" viene inizializzato con 0 per ri-eseguire l'acquisizione */
			/* nel momento in cui una acquisizione viene ri-eseguita "valore_controllo" viene inizializzato nuovamente a 1 per non entrare in un loop			   */
			if(valore_controllo == 0)
			{
				valore_controllo = 1;
			}
			
			/* controllo che la stringa non superi la lunghezza stabilita */
			if(strlen(codice_da_ricercare) != 6)
			{
				printf("\nValore inserito errato! Lunghezza maggiore di quella necessaria! Riprovare!\n\n");
				valore_controllo = 0;
			}
		
			/* controllo che i primi 4 caratteri della stringa siano lettere maiuscole */
			for(i = 0; i < 4 && valore_controllo == 1; i++)
			{
				if(!(isupper(codice_da_ricercare[i])))
				{
					printf("\nValore inserito errato! Le prime 4 cifre del codice cliente devono essere lettere maiuscole! Riprovare!\n\n");
					valore_controllo = 0;
				}	
			}		
			
			/* controllo che gli ultimi 2 caratteri della stringa siano numeri */
			for(i = 4; i < 6 && valore_controllo == 1; i++)
			{
				if(!(isdigit(codice_da_ricercare[i])))
				{
					printf("\nValore inserito errato! Le ultime 2 cifre del codice cliente devono essere numeri interi e positivi! Riprovare!\n\n");
					valore_controllo = 0;
				}	
			}
		}
	}while(valore_controllo == 0);
	
	/* scorro gli elementi dell'array */
	for(i = 0; i < numero_veicoli; i++)
	{
		/* ad ogni iterazione confronto l'elemento i-esimo dell'array con il valore acquisito in input */
		/* essendo confronto tra stringhe utilizzo la "strcmp" 										   */
		risultato_confronto = strcmp(array_veicoli[i].codice_veicolo, codice_da_ricercare);
		
		/* se "risultato_confronto" uguale 0, vuol dire che le due stringhe sono uguali																 */
		/* quindi comunico all'utente tutte le informazioni riguardanti il veicolo trovato e ne salvo la posizione nell'array per eventuali utilizzi */
		if(risultato_confronto == 0)
		{
			printf("\nVeicolo\tProprietario\tModello            \tAnno\n");
			printf("%-7s\t%-12s\t%s\t%d\n", array_veicoli[i].codice_veicolo, array_veicoli[i].codice_proprietario, array_veicoli[i].nome_veicolo, array_veicoli[i].anno_immatricolazione);
			posizione_valore = i;
		}
	}
	
	return(posizione_valore);
}

void Rimozione_veicolo(veicolo *array_veicoli, int *numero_veicoli)
{
	int posizione_veicolo_eliminare,	/* variabile che mi conterra' il valore rappresentante la posizione fisica di dove si trova l'elemento da eliminare nell'array */
		dim = (*numero_veicoli),		/* variaible intera che mi rappresenta il numero di veicoli totali che avro' dopo la rimozione   							   */
	    i;								/* variabile intera contatore per scorrere gli elementi dell'array															   */
	    
	/* utilizzo la funzione "Ricerca_veicolo" per trovare in memoria la posizione fisica del veicolo che voglio eliminare */
	posizione_veicolo_eliminare = Ricerca_veicolo(array_veicoli, dim);
	
	/* se il valore di ritorno della funzione "Ricerca_veicolo" e' maggiore di -1 vuol dire che il veicolo e' stato trovato in memoria e proseguo con l'eliminazione */
	if(posizione_veicolo_eliminare > -1)
	{
		/* scorro gli elementi dell'array a partire dall'elemento che voglio eliminare 									     */
		/* ad ogni iterazione scambio l'elemento che voglio eliminare con il successivo fino a portarlo alla fine dell'array */
		for(i = posizione_veicolo_eliminare; i < dim; i++)
		{
			array_veicoli[i] = array_veicoli[i + 1];
		}
		
		/* diminuisco dim di 1 perche' dopo l'eliminazione avro' un veicolo in meno */
		dim -= 1;
		
		/* vado a ri-dimensionare il blocco di memoria in modo che mi contenga un elemento in meno in quanto voglio eliminare un veicolo 																		  */
		/* la realloc e' l'azione contemporanea di malloc e free, quindi taglia dalla fine dell'array un determinato numero di elementi se gli si fornisce una dimensione minore di quella che il blocco presenta */
		array_veicoli = (veicolo*)realloc(array_veicoli, sizeof(veicolo) * dim);
		
		/* aggiorno numero_veicoli */
		*numero_veicoli = dim;
		
		printf("\nElenco dei veicoli aggiornato come segue dopo la rimozione...\n\n");
		
		/* stampo l'elenco aggiornato */
		Stampa_array(array_veicoli, *numero_veicoli);
	}
	else if(posizione_veicolo_eliminare == -1)
	{
		printf("\nVeicolo non trovato in memoria\n");
	}
}

veicolo Ricerca_valore_massimo(veicolo *array_veicoli, int numero_veicoli)
{
	int i;					/* variabile contatore utilizzata per scorrere uno alla volta gli elementi dell'array 											  */
	int controllo;			/* variabile che mi conterra' il valore risultante dal confronto tra i valori presenti all'interno dell'array  					  */
	
	veicolo tmp_veicolo;	/* variabile che mi conterra' il veicolo piu' grande (ottenuto confrontando i codici dei veicoli secondo l'ordine lessicografico) */
	
	/* scorro gli elementi dell'array */
	for(i = 0; i < numero_veicoli; i++)
	{
		/* alla prima iterazione non faccio altro che prendere come elemento di riferimento il primo veicolo */
		if(i == 0)
		{
			tmp_veicolo = array_veicoli[i];
		}
		else
		{
			/* confronto tramite "strcmp" (che mi permette il confronto tramite ordine lessicografico) i codici dei veicoli */
			controllo = strcmp(tmp_veicolo.codice_veicolo, array_veicoli[i].codice_veicolo);
			
			/* se confronto e' minore di 0, vuol dire che il codice veicolo i-esimo confrontato con l'elemento di riferimento e' piu' grrande 																		*/
			/* quindi mi diventa il mio nuovo elemento di riferimento e lo confrontero' con gli elementi successivi	fino a quando non trovo un nuovo elemento piu' grande o finche' non arrivo alla fine dell'array	*/
			if(controllo < 0)
			{
				tmp_veicolo = array_veicoli[i];
			}
		}
	}
	
	return(tmp_veicolo);
}

veicolo Ricerca_valore_minimo(veicolo *array_veicoli, int numero_veicoli)
{
	int i = 0;			 /* variabile contatore utilizzata per scorrere uno alla volta gli elementi dell'array 												*/
	int controllo;		 /* variabile che mi conterra' il valore risultante dal confronto tra i valori presenti all'interno dell'array  					*/	
	
	veicolo tmp_veicolo; /* variabile che mi conterra' il veicolo piu' piccolo (ottenuto confrontando i codici dei veicoli secondo l'ordine lessicografico) */
	
	/* scorro gli elementi dell'array */
	for(i = 0; i < numero_veicoli; i++)
	{
		/* alla prima iterazione non faccio altro che prendere come elemento di riferimento il primo veicolo */
		if(i == 0)
		{
			tmp_veicolo = array_veicoli[i];
		}
		else
		{
			/* confronto tramite "strcmp" (che mi permette il confronto tramite ordine lessicografico) i codici dei veicoli */
			controllo = strcmp(tmp_veicolo.codice_veicolo, array_veicoli[i].codice_veicolo);
			
			/* se confronto e' maggiore di 0, vuol dire che il codice veicolo i-esimo confrontato con l'elemento di riferimento e' piu' piccolo 																	 */
			/* quindi mi diventa il mio nuovo elemento di riferimento e lo confrontero' con gli elementi successivi fino a quando non trovo un nuovo elemento piu' piccolo o finche' non arrivo alla fine dell'array */
			if(controllo > 0)
			{
				tmp_veicolo = array_veicoli[i]; 
			}
		} 
	}
	
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
