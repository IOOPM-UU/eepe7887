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

    make 1k-words       # freq_count med .txt fil som har 1000 långa ord
    make 10k-words      # freq_count med .txt fil som har 10 000 ord
    make 16k-words      # freq_count med .txt fil som har 16 000 ord

## Initial Profiling Results

* 
* 
* 

## Designbeslut

* Ett designbeslut vi tog var att vi valde att använda oss av sentinel nodes hellre än dubbelpekare, detta var för att det skulle bli lättare att förstå eftersom vi redan använt oss av sentinel nodes i tidigare tickets.

* Ett annat designbeslut vi tog var att i 'hash_table.c' så valde vi att skriva både våra hash_table funktioner samt våra hash_table_iterator funktioner. Detta var för att vi själva tyckte att det var lättare att ha allt i en och samma fil hellre än två separata filer.

