# Informazioni esame
Progetto d'esame per il corso di Algoritmi e Strutture Dati. 

# Informazioni studente
Giacchetti Filippo, matricola 282558.

# Titolo
Progetto_gestione_veicoli

# Specifica Progetto
Si supponga di dover progettare un programma per un sistema informativo che gestisce i dati relativi ad
un’anagrafe di autoveicoli. Il sistema permette di mantenere, per ogni veicolo, questi dati:
• veicolo: codice univoco alfanumerico rappresentato da una stringa concatenazione di quattro lettere e
           due numeri;
• proprietario: codice rappresentato da una stringa concatenazione di 3 lettere e tre numeri;
• modello del veicolo: stringa di massimo 20 caratteri;
• anno di immatricolazione: un numero intero.

Le informazioni sono memorizzate su un file in formato testo, secondo il seguente formato (si assumano campi
separati da tabulazione o spazio):
Ad esempio:

Veicolo Proprietario Modello  Anno
ZZYQ48  FCA001       Fiat 850 1973

Si scriva un programma ANSI C che esegue le seguenti elaborazioni:
1. Acquisisce il file e memorizza le relative informazioni in una struttura dati di tipo dinamico.
2. Ricerca e restituisce i dati relativi ad un dato veicolo. 
   Ad esempio: se l’utente chiede i dati relativi al
   veicolo CCGH07, il programma deve restituire le informazioni contenute nella riga corrispondente:
   
   Veicolo Proprietario Modello   Anno
   CCGH07  DEF130       Fiat 500  1971
   
3. Inserimento di dati relativi ad un nuovo veicolo, specificati dall’utente.
4. Rimozione di dati relativi ad un veicolo, specificati dall’utente.
5. Calcolo del valore più grande e di quello più piccolo (secondo l’ordine lessicografico) del codice alfanumerico
   rappresentante il veicolo (AAAB12 e ZZYQ48, rispettivamente, nell’esempio riportato).
   
Per quanto riguarda l’analisi teorica si deve fornire la complessità:
1. dell’algoritmo di ricerca
2. dell’algoritmo di inserimento
3. dell’algoritmo di rimozione
4. dell’algoritmo di calcolo del valore più grande
5. dell’algoritmo di calcolo del valore più piccolo

Oltre all’analisi teorica della complessità si deve effettuare uno studio sperimentale della stessa per le operazioni
sopra specificate (ricerca, inserimento, rimozione, calcolo del massimo, calcolo del minimo). Come suggerimento
si può operare generando un numero N di dati-veicolo casuali (dove N rappresenta il numero di veicoli). L’analisi
sperimentale deve quindi valutare la complessità al variare di N.

# Ambiente di sviluppo
Dev c++ e Linux mint (tramite macchina virtuale)
