#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


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

int Ricerca_veicolo(veicolo *array_veicoli, int, int);
void Rimozione_veicolo(veicolo *array_veicoli, int*, int);
int Ricerca_veicolo_rimuovere(veicolo *array_veicoli, int numero_veicoli, int posizione_centrale_array, int* steps);
veicolo Ricerca_valore_massimo(veicolo *array_veicoli, int);
veicolo Ricerca_valore_minimo(veicolo *array_veicoli, int);

/* funzione utilizzata dal programma per liberare il buffer 																																 */
void LiberaBuffer();

veicolo Recupero_dati_veicolo(int*);
void Stampa_array(veicolo *array_veicoli, int);

int main(int argc, char *argv[]) 
{
	int posizione_valore_ricercato,
	    numero_veicoli_inseriti,
	    numero_veicoli,
        posizione_centrale_array;
		
	veicolo *array_veicoli = NULL;
	veicolo valore_massimo;
	veicolo valore_minimo;
	
	char nome_file[30];

	srand (time(NULL));
	
	array_veicoli = Leggi_su_File(nome_file, &numero_veicoli);
	
	printf("\n\nLe informazioni sono memorizzate nel modo che segue... \n\n");	
	Stampa_array(array_veicoli, numero_veicoli);
	
	printf("\nQuanti veicoli vuoi inserire? ");
	scanf("%d", &numero_veicoli_inseriti);
	
	LiberaBuffer();
	
	if(numero_veicoli_inseriti <= 0)
	{
		printf("\n\nErrore! Il numero di veicoli deve corrispondere ad un valore positivo e diverso da 0!\n\n");
	}
	else
	{
		array_veicoli = Inserisci_veicolo(array_veicoli, &numero_veicoli, numero_veicoli_inseriti);	
	
		posizione_centrale_array = numero_veicoli / 2;
			
		posizione_valore_ricercato = Ricerca_veicolo(array_veicoli, numero_veicoli, posizione_centrale_array);
		
		if(posizione_valore_ricercato == -1)
		{
			printf("\nVeicolo non trovato in memoria\n");
		} 
	
		Rimozione_veicolo(array_veicoli, &numero_veicoli, posizione_centrale_array);
		
		valore_minimo = Ricerca_valore_minimo(array_veicoli, numero_veicoli);
		printf("Valore minimo: %s\n", valore_minimo.codice_veicolo);	
	
		valore_massimo = Ricerca_valore_massimo(array_veicoli, numero_veicoli);
		printf("Valore massimo: %s\n", valore_massimo.codice_veicolo);
	}
				
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
			  			printf("\nErrore!\n");
					}
					else
					{
						valore_ritorno_fgets = fgets(tmp_veicolo.nome_veicolo,
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
					   	   	       					  &tmp_veicolo.anno_immatricolazione);
					   	   	
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
	
	file = fopen("dati.txt",
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
		printf("Errore in apertura del file!");
	}		 	
}

veicolo* Inserisci_veicolo(veicolo *array_veicoli, int* numero_veicoli, int numero_veicoli_inseriti)
{
	int dim = *numero_veicoli + numero_veicoli_inseriti;
	int i,
		steps = 0;
	
	array_veicoli = (veicolo*)realloc(array_veicoli, sizeof(veicolo) * dim);
	steps++;

	if (array_veicoli == NULL) 
	{
		steps++;
    	printf("errore!");

	}
	else
	{
		steps++;
		for(i = *numero_veicoli; i < dim; i++)
		{
			steps++;
			array_veicoli[i] = Recupero_dati_veicolo(&steps);
			steps++;	
		}	
	
		*numero_veicoli = dim;
		steps++;
	}
	
	printf("\nElenco dei veicoli aggiornato come segue...\n\n");
	Stampa_array(array_veicoli, dim);
	steps++;
	
	printf("\nL'algoritmo ha impiegato %d passi per inserire %d veicoli\n", steps, dim - 1);

	return(array_veicoli);
}

veicolo Recupero_dati_veicolo(int* steps)
{
	veicolo nuovo_veicolo;
	char tmp_string[7];
	int anno_immatricolazione,
	    lunghezza_stringa = 0,
	    i,
		j;
		
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
	
	
	for (i=0; i<4; i++)
	{	
		(*steps)++;
		tmp_string[i] = 65 + rand() % (91 - 65);
		(*steps)++;
	}
	
	for (i=4; i<6; i++)
	{	
		(*steps)++;
		tmp_string[i] = 48 + rand() % (58 - 48);
		(*steps)++;
	}
	
	strcpy(nuovo_veicolo.codice_veicolo, tmp_string);
	(*steps)++;
	
	for (i=0; i<3; i++)
	{
		(*steps)++;
		tmp_string[i] = 65 + rand() % (91 - 65);
		(*steps)++;
	}
	
	for (i=3; i<6; i++)
	{
		(*steps)++;
		tmp_string[i] = 48 + rand() % (58 - 48);
		(*steps)++;
	}
	
	strcpy(nuovo_veicolo.codice_proprietario, tmp_string);
	(*steps)++;
	
	j = (rand()%10) + 1;
	(*steps)++;
		
	lunghezza_stringa = strlen(nomi_veicoli[j]);
	(*steps)++;

	for(i = lunghezza_stringa; i < 20; i++)
	{
		(*steps)++;
		nomi_veicoli[j][i] = ' ';
		(*steps)++;
	}
		
	nomi_veicoli[j][20] = '\0';
	(*steps)++;
			
	if(strlen(nomi_veicoli[j]) != 20)
	{
		(*steps)++;
		printf("\nValore inserito errato! Valore con un formato diverso da quello atteso! Riprovare! Riprovare!\n\n");
		(*steps)++;
	}

	strcpy(nuovo_veicolo.nome_veicolo, nomi_veicoli[j]);
	(*steps)++;

	anno_immatricolazione = rand()%121 + 1900;
	(*steps)++;

	nuovo_veicolo.anno_immatricolazione = anno_immatricolazione;	
	(*steps)++;
	
	return(nuovo_veicolo);
}

int Ricerca_veicolo(veicolo *array_veicoli, int numero_veicoli, int posizione_centrale_array)
{
	int posizione_valore = -1,
	    risultato_confronto,
	    i,
	    steps = 0;
		
	for(i = 0; i < numero_veicoli; i++)
	{
		steps++;
		risultato_confronto = strcmp(array_veicoli[i].codice_veicolo, array_veicoli[posizione_centrale_array].codice_veicolo);
		steps++;
	
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
	int posizione_veicolo_eliminare;
	int dim = (*numero_veicoli);
	int i,
		steps = 0;
	
	posizione_veicolo_eliminare = Ricerca_veicolo_rimuovere(array_veicoli, dim, posizione_centrale_array, &steps);
	steps++;
	
	printf("\nVeicolo\tProprietario\tModello            \tAnno\n");
			printf("%-7s\t%-12s\t%s\t%d\n", array_veicoli[posizione_veicolo_eliminare].codice_veicolo, array_veicoli[posizione_veicolo_eliminare].codice_proprietario, array_veicoli[posizione_veicolo_eliminare].nome_veicolo, array_veicoli[posizione_veicolo_eliminare].anno_immatricolazione);
	
	if(posizione_veicolo_eliminare > -1)
	{
		steps++;
		for(i = posizione_veicolo_eliminare; i < dim; i++)
		{
			steps++;
			array_veicoli[i] = array_veicoli[i + 1];
			steps++;
		}
		
		dim -= 1;
		steps++;
		
		array_veicoli = (veicolo*)realloc(array_veicoli, sizeof(veicolo) * dim);
		steps++;
				
		*numero_veicoli = dim;
		steps++;
		
		printf("\nL'algoritmo ha impiegato %d passi per rimuovere il veicolo centrale tra %d veicoli\n", steps, dim + 1);
	}
}

int Ricerca_veicolo_rimuovere(veicolo *array_veicoli, int numero_veicoli, int posizione_centrale_array, int* steps)
{
	int posizione_valore = -1,
	    risultato_confronto,
	    i;
		
	for(i = 0; i < numero_veicoli; i++)
	{
		(*steps)++;
		risultato_confronto = strcmp(array_veicoli[i].codice_veicolo, array_veicoli[posizione_centrale_array].codice_veicolo);
		(*steps)++;
	
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
	int i,
		controllo,
		steps = 0;
	veicolo tmp_veicolo;
	
	for(i = 0; i < numero_veicoli; i++)
	{
		steps++;
		if(i == 0)
		{
			steps++;
			tmp_veicolo = array_veicoli[i];
			steps++;
		}
		else
		{
			steps++;
			controllo = strcmp(tmp_veicolo.codice_veicolo, array_veicoli[i].codice_veicolo);
			steps++;
			
			if(controllo < -1)
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
	int i,
		controllo,
		steps = 0;
		
	veicolo tmp_veicolo;
	
	for(i = 0; i < numero_veicoli; i++)
	{
		steps++;
		if(i == 0)
		{
			steps++;
			tmp_veicolo = array_veicoli[i];
			steps++;
		}
		else
		{
			steps++;
			controllo = strcmp(tmp_veicolo.codice_veicolo, array_veicoli[i].codice_veicolo);
			steps++;
						
			if(controllo > 1)
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

