#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>

const char *weekdays[] = {"Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", 
                            "Freitag", "Samstag"};

int main(int argc, const char *argv[]){

    if (argc != 4){
        fprintf(stderr, "Aufruf: %s tag monat jahr", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct tm datum = {
        .tm_hour = 12, 
        .tm_min = 12, 
        .tm_sec = 12, 
        .tm_mday = atoi(argv[1]),
        .tm_mon = atoi(argv[2]) - 1,
        .tm_year = atoi(argv[3]) - 1900,
        .tm_isdst = -1};

    struct tm *datumPtr = &datum;

    time_t sekunden = mktime(datumPtr);

    if (sekunden == -1){
        fprintf(stderr, "%s error: %s", argv[0], strerror(errno));
        exit(EXIT_FAILURE);
    }

    time_t *sekundenPtr = &sekunden;

    struct tm *ergebnisDatum = localtime(sekundenPtr);

    printf("Datum: %d.%d.%d\n", ergebnisDatum->tm_mday, ergebnisDatum->tm_mon+1, ergebnisDatum->tm_year+1900);

    printf("Total Days: %d\n", ergebnisDatum->tm_yday);
    printf("Week Day: %s\n", weekdays[ergebnisDatum->tm_wday]);

    exit(EXIT_SUCCESS);
}