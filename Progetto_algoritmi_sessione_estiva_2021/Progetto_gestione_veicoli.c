#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
	char codice_veicolo[7];
	char codice_proprietario[7];
	char nome_veicolo[21];
	int anno_immatricolazione;
} veicolo;

veicolo* Leggi_su_File(char*, int*);
void Scrivi_su_file(veicolo *array_veicoli, int numero_veicoli, char*);
veicolo* Inserisci_veicolo(veicolo *array_veicoli, int*, int);
int Ricerca_veicolo(veicolo *array_veicoli, int);
void Rimozione_veicolo(veicolo *array_veicoli, int*);
veicolo Ricerca_valore_massimo(veicolo *array_veicoli, int);
veicolo Ricerca_valore_minimo(veicolo *array_veicoli, int);

/* funzione utilizzata dal programma per liberare il buffer 																																 */
void LiberaBuffer();

veicolo Recupero_dati_veicolo();
void Stampa_array(veicolo *array_veicoli, int);

int main(int argc, char *argv[]) 
{
	veicolo *array_veicoli = NULL;
	veicolo valore_massimo;
	veicolo valore_minimo;
	
	int numero_veicoli = 0,
	    numero_veicoli_inseriti = 0,
      	    valore_controllo_menu = 0,
	    valore_controllo_scanf = 0,
	    posizione_valore_ricercato = 0;	
		
	char nome_file[30];
	
	printf("Programma per un sistema informativo che gestisce i dati relativi ad un'anagrafe di autoveicoli.\n");
	printf("Il sistema permette di mantenere, per ogni veicolo, questi dati:\n");
	printf("- veicolo: codice univoco alfanumerico rappresentato da una stringa concatenazione di quattro lettere e due numeri;\n");
	printf("- proprietario: codice rappresentato da una stringa concatenazione di tre lettere e tre numeri;\n");
	printf("- modello del veicolo: stringa di massimo 20 caratteri;\n");
	printf("- anno di immatricolazione: un numero intero.\n\n");
	
	printf("Le informazioni sono memorizzate su un file in formato testo. Per questo motivo la prima cosa che vi verra' chiesta sara' inserire il nome del file su cui sono memorizzati i dati.\n\n");
	
	array_veicoli = Leggi_su_File(nome_file, &numero_veicoli);
	
	if(array_veicoli->anno_immatricolazione == 0)
	{
		printf("\nFile vuoto!\n");
	}
	else
	{
		printf("\nLe informazioni sono memorizzate nel modo che segue... \n\n");	
		Stampa_array(array_veicoli, numero_veicoli);
	}

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

		if(valore_controllo_menu > 6 || valore_controllo_menu <= 0 || valore_controllo_scanf == 0)
		{
			printf("\nERRORE! IL VALORE DIGITATO NON CORRISPONDE A NESSUNA VOCE DEL MENU' RIPROVARE!\n");
		}
		
		switch(valore_controllo_menu)
		{
			case 1:
				printf("\nQuanti veicoli vuoi inserire? ");
				valore_controllo_scanf = scanf("%d", &numero_veicoli_inseriti);
				
				LiberaBuffer();
								
				if(numero_veicoli_inseriti <= 0 || valore_controllo_scanf == 0)
				{
					printf("\nErrore! Il numero di veicoli deve corrispondere ad un valore positivo e diverso da 0!\n");
				}
				else
				{
					array_veicoli = Inserisci_veicolo(array_veicoli, &numero_veicoli, numero_veicoli_inseriti);
			
					printf("\nElenco dei veicoli aggiornato come segue...\n\n");
					
					Stampa_array(array_veicoli, numero_veicoli);
					Scrivi_su_file(array_veicoli, numero_veicoli, nome_file);
				}
				
				break;
			case 2:
				posizione_valore_ricercato = Ricerca_veicolo(array_veicoli, numero_veicoli);
			
				if(posizione_valore_ricercato == -1)
				{
					printf("\nVeicolo non trovato in memoria\n");
				} 
	
				break;
			case 3:
				Rimozione_veicolo(array_veicoli, &numero_veicoli);
				
				Scrivi_su_file(array_veicoli, numero_veicoli, nome_file);
				break;
			case 4:
				valore_minimo = Ricerca_valore_minimo(array_veicoli, numero_veicoli);
				printf("\nValore minimo: %s\n", valore_minimo.codice_veicolo);
				break;
			case 5:
				valore_massimo = Ricerca_valore_massimo(array_veicoli, numero_veicoli);
				printf("\nValore massimo: %s\n", valore_massimo.codice_veicolo);
				break;
			case 6:
				break;	
		}
	}while(valore_controllo_menu != 6);

	return 0;
}

veicolo* Leggi_su_File(char* nome_file, int* numero_veicoli)
{
	veicolo tmp_veicolo;
	veicolo *array_veicoli;
	
	char* valore_ritorno_fgets;

	FILE *file;
	int count = 0,
	    valore_controllo_scanf = 0,
	    valore_controllo_fscanf = 0;	
	do
	{
		printf("Digita il nome del file (con estensione) da cui estrappolare i dati: ");
		valore_controllo_scanf = scanf("%s", nome_file);
	       
		if(valore_controllo_scanf == 0)
		{
			printf("\nErrore!\n");
		}
		else
		{

			file = fopen(nome_file,
				         "r"); 
						 
			if(file != NULL)
			{	
				while (fgetc(file) != '\n');
					
	 			while(!feof(file))
				{
					valore_controllo_fscanf = fscanf(file,
			   		 			         		     "%s%s\t",
			  		  		  					     tmp_veicolo.codice_veicolo, tmp_veicolo.codice_proprietario);	
			  		if(valore_controllo_fscanf == 0)
			  		{
			  			printf("\nErrore in lettura!\n");
					}
					else
					{
						valore_ritorno_fgets = fgets(tmp_veicolo.nome_veicolo,
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
					   	   	       					  &tmp_veicolo.anno_immatricolazione);
					   	   	
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
				
				rewind(file);
					
				array_veicoli = (veicolo*) malloc(sizeof(veicolo) * count);	
			
				count = 0;
			
				while (fgetc(file) != '\n');
							
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
				fclose(file);
			
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
	int i;
	
	FILE *file;
	
	file = fopen(nome_file,
				 "w");
	
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
		
		fclose(file);	
	}
	else
	{
		printf("\nErrore in apertura del file!\n\n");
	}		 	
}

veicolo* Inserisci_veicolo(veicolo *array_veicoli, int* numero_veicoli, int numero_veicoli_inseriti)
{
	int dim = *numero_veicoli + numero_veicoli_inseriti;
	int i;
	
	array_veicoli = (veicolo*)realloc(array_veicoli, sizeof(veicolo) * dim);
	
	if(array_veicoli == NULL)
	{
		printf("\nErrore durante l'allocazione dinamica della memoria!\n");
	}
	else
	{
		for(i = *numero_veicoli; i < dim; i++)
		{
			array_veicoli[i] = Recupero_dati_veicolo();			
				
			printf("\nVeicolo Inserito con successo!\n");
		}	
		
		*numero_veicoli = dim;
	}
	
	return(array_veicoli);
}

veicolo Recupero_dati_veicolo()
{
	veicolo nuovo_veicolo;
	char tmp_string[7];
	char tmp_string_nome_veicolo[21];
	int anno_immatricolazione,
	    lunghezza_stringa = 0,
	    valore_controllo = 1,
	    valore_controllo_scanf = 0,
        i;

	char* valore_ritorno_fgets;
	
	do
	{
		printf("\nInserisci il codice del veicolo (formato da 4 lettere maiuscole e 2 numeri)...\n");
		valore_controllo_scanf = scanf("%s", tmp_string);

		if(valore_controllo_scanf == 0)
		{
			printf("\nErrore!!\n");
			LiberaBuffer();
		}
		else
		{		
			if(valore_controllo == 0)
			{
				valore_controllo = 1;
			}
		
			if(strlen(tmp_string) != 6)
			{
				printf("\nValore inserito errato! Valore con un formato diverso da quello atteso! Riprovare!\n\n");
				valore_controllo = 0;
			}
		
			for(i = 0; i < 4 && valore_controllo == 1; i++)
			{
				if(!(isupper(tmp_string[i])))
				{
					printf("\nValore inserito errato! Le prime 4 cifre del codice cliente devono essere lettere maiuscole! Riprovare!\n\n");
					valore_controllo = 0;
				}	
			}			
		
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
	
	strcpy(nuovo_veicolo.codice_veicolo, tmp_string);
	
	do
	{
		printf("Inserisci il codice del proprietario (formato da 3 lettere maiuscole e 3 numeri)...\n");
		valore_controllo_scanf = scanf("%s", tmp_string);
		
		if(valore_controllo_scanf == 0)
		{
			printf("\nErrore\n");
			LiberaBuffer();
		}
		else
		{
			if(valore_controllo == 0)
			{
				valore_controllo = 1;
			}
		
			if(strlen(tmp_string) != 6)
			{
				printf("\nValore inserito errato! Valore con un formato diverso da quello atteso! Riprovare!\n\n");
				valore_controllo = 0;
			}
		
			for(i = 0; i < 3 && valore_controllo == 1; i++)
			{
				if(!(isupper(tmp_string[i])))
				{
					printf("\nValore inserito errato! Le prime 3 cifre del codice proprietario devono essere lettere maiuscole! Riprovare!\n\n");
					valore_controllo = 0;
				}	
			}		
		
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
	
	strcpy(nuovo_veicolo.codice_proprietario, tmp_string);

	do
	{
		printf("Inserisci l'anno di immatricolazione (massimo 4 numeri)...\n");
		valore_controllo_scanf = scanf("%d", &anno_immatricolazione);
		
		if(valore_controllo_scanf == 0)
		{
			printf("\nErrore!! Input invalido, riprovare!\n\n");
			LiberaBuffer();
		}
		else
		{
			if(valore_controllo == 0)
			{
				valore_controllo = 1;
			}
			
			if(anno_immatricolazione < 0)
			{
				printf("\nValore inserito errato! Inserire l'anno di immatricolazione formato da 4 numeri interi e positivi!\n\n");
				valore_controllo = 0;
			}
			
			if(anno_immatricolazione > 2021)
			{
				printf("\nValore inserito errato! Siamo nel 2021!\n\n");
				valore_controllo = 0;
			}
		}	
	}while(valore_controllo == 0 || valore_controllo_scanf == 0);

	nuovo_veicolo.anno_immatricolazione = anno_immatricolazione;
	
	LiberaBuffer();

	do
	{
		printf("Inserisci il nome del modello (massimo 20 caratteri)...\n");
		valore_ritorno_fgets = fgets(tmp_string_nome_veicolo, 20, stdin);  
		LiberaBuffer();
		
		if(valore_controllo == 0)
		{
			valore_controllo = 1;			
		}

		if(valore_ritorno_fgets == NULL)
		{
			printf("\nErrore! Riprovare!\n");
		}
		else
		{

			tmp_string_nome_veicolo[20] = '\0'; 
			
			if(strlen(tmp_string_nome_veicolo) > 20)
			{
				printf("\nValore inserito errato! Valore con un formato diverso da quello atteso! Riprovare!\n\n");
				valore_controllo = 0;
			}
			else
			{
				lunghezza_stringa = strlen(tmp_string_nome_veicolo);
				
				for(i = lunghezza_stringa - 1; i < 20; i++)
				{
					tmp_string_nome_veicolo[i] = ' ';
				}
			}	
		}	
	}while(valore_controllo == 0);
	
	strcpy(nuovo_veicolo.nome_veicolo, tmp_string_nome_veicolo);
	
	return(nuovo_veicolo);
}

int Ricerca_veicolo(veicolo *array_veicoli, int numero_veicoli)
{
	char codice_da_ricercare[7];
	int valore_controllo = 1,
	    posizione_valore = -1,
	    risultato_confronto,
	    valore_ritorno_scanf = 0,
	    i;
		
	do
	{
		printf("\nDigita il codice relativo al veicolo che ti interessa: ");
		valore_ritorno_scanf = scanf("%s", codice_da_ricercare);
			
		if(valore_ritorno_scanf == 0)
		{
			printf("\nErrore!!\n");
		}
		else
		{
			
			LiberaBuffer();
		
			if(valore_controllo == 0)
			{
				valore_controllo = 1;
			}
		
			if(strlen(codice_da_ricercare) != 6)
			{
				printf("\nValore inserito errato! Lunghezza maggiore di quella necessaria! Riprovare!\n\n");
				valore_controllo = 0;
			}
		
			for(i = 0; i < 4 && valore_controllo == 1; i++)
			{
				if(!(isupper(codice_da_ricercare[i])))
				{
					printf("\nValore inserito errato! Le prime 4 cifre del codice cliente devono essere lettere maiuscole! Riprovare!\n\n");
					valore_controllo = 0;
				}	
			}		
		
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
	
	for(i = 0; i < numero_veicoli; i++)
	{
		risultato_confronto = strcmp(array_veicoli[i].codice_veicolo, codice_da_ricercare);
	
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
	int posizione_veicolo_eliminare;
	int dim = (*numero_veicoli),
	    i;
	
	posizione_veicolo_eliminare = Ricerca_veicolo(array_veicoli, dim);
	
	if(posizione_veicolo_eliminare > -1)
	{
		for(i = posizione_veicolo_eliminare; i < dim; i++)
		{
			array_veicoli[i] = array_veicoli[i + 1];
		}
		
		dim -= 1;
		
		array_veicoli = (veicolo*)realloc(array_veicoli, sizeof(veicolo) * dim);
				
		*numero_veicoli = dim;
		
		printf("\nElenco dei veicoli aggiornato come segue dopo la rimozione...\n\n");
				
		Stampa_array(array_veicoli, *numero_veicoli);
	}
	else if(posizione_veicolo_eliminare == -1)
	{
		printf("\nVeicolo non trovato in memoria\n");
	}
}

veicolo Ricerca_valore_massimo(veicolo *array_veicoli, int numero_veicoli)
{
	int i;
	int controllo;
	veicolo tmp_veicolo;
	
	for(i = 0; i < numero_veicoli; i++)
	{
		if(i == 0)
		{
			tmp_veicolo = array_veicoli[i];
		}
		else
		{
			controllo = strcmp(tmp_veicolo.codice_veicolo, array_veicoli[i].codice_veicolo);
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
	int i = 0;
	int controllo;
	veicolo tmp_veicolo;

	for(i = 0; i < numero_veicoli; i++)
	{
		if(i == 0)
		{
			tmp_veicolo = array_veicoli[i];
		}
		else
		{
		
			controllo = strcmp(tmp_veicolo.codice_veicolo, array_veicoli[i].codice_veicolo);

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
	int i;
	
	printf("Veicolo\tProprietario\tModello            \tAnno\n");
	
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
