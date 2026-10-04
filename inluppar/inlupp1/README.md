# Inlupp1 - Hashtabeller och Iteratorer

## Bygga och köra tester

    make                # kompilerar alla program
    make test           # kompilerar och kör alla tester
    make clean          # tar bort alla byggfiler

Enskilda tester:

    make hash_test      # bara hashtabellen
    make linked_test    #bara länkade listan

Minneskontroll och täckning:

    make mem_all        # valgrind på alla tester
    make coverage_all   # gcov för linked_list.c och hash_table.c

Kräver: gcc, make, CUnit, valgrind och gcov

## Köra frekvensräknaren

    make freq_count
    ./freq_count <fil>

Exempel: './freq_count <10k-words.txt>

## Designbeslut

*
*
*

## Antaganden

*
*
*