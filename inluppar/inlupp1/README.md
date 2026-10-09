# Inlupp1 - Hashtabeller och Iteratorer

## Bygga och köra tester

    make                # kompilerar alla program
    make all_test       # kompilerar alla tester
    make run_all        # kör alla tester
    make clean          # tar bort alla byggfiler

Enskilda tester:

    make hash_test      # bara hashtabellen
    make linked_test    # bara länkade listan

Minneskontroll och täckning:

    make mem_all        # valgrind på alla tester
    make coverage_all   # gcov för linked_list.c och hash_table.c

## Köra frekvensräknaren

    make freq_count     # kompilera filen 'freq_count.c'

    make 1k-words       # freq_count med .txt fil som har 1000 långa ord
    make 10k-words      # freq_count med .txt fil som har 10000 ord
    make 16k-words      # freq_count med .txt fil som har 16000 ord

## Initial Profiling Results
För körning med 1k-long-words var topp 3 funktionerna string_cmpr, find_previous entry och string_hash.

För körning med 10k-words var topp 3 funktionerna string_cmpr, find_previous entry och string_hash.

För körning av 16k-words var topp 3 funktionerna string_cmpr, find_previous entry och _init.

De som förekommer i topp 3 för samtliga funktioner är string_cmpr och find_previous. Detta är logiskt med tanke på att både lookup och insert använder sig av find_previous och dessa funktioner körs frekvent i koden. Samma med str_cmpr som körs på varje entry fram tills antingen slutet av listan eller tills rätt key är hittat. 

10k och 1k Words har string_hash i topp-3. Det kan bero på att varje enskild måste hashas till sin rätta plats.

_init, som är en uppstarskod hamnar i topp 3 i 16k-words troligen eftersom den behöver i ca. 25% av fallen köra strcmp på hela listan då antalet unika ord är mer än en fjärde del av de totala orden. Eftersom strcmp är en bliblioteksfunktion som inte har någon profilieringsinformation, hamnar _init i topp 3. 

_init finns inte med i topp 3 för de två andra eftersom majoriteten av orden som förekommer är dubletter. I snitt behöver man då bara kör strcmp på hälften av listan istället för hela. En annan förklaring är att programmet körs för kort tid för att _init ska kunna räknas med. Detta med tanke på att det inte finns någon procentuell körtid för någon av funktionerna. 

Str_compare är funktionen som körs mest, man skulle kunna få programmet att gå snabbare med en effektivare
 


## Designbeslut

* Ett designbeslut vi tog var att vi valde att använda oss av sentinel nodes hellre än dubbelpekare, detta var för att det skulle bli lättare att förstå eftersom vi redan använt oss av sentinel nodes i tidigare tickets.

* Ett annat designbeslut vi tog var att i 'hash_table.c' så valde vi att skriva både våra hash_table funktioner samt våra hash_table_iterator funktioner. Detta var för att vi själva tyckte att det var lättare att ha allt i en och samma fil hellre än två separata filer.

