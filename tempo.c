#include "tempo.h"
#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

void StringToData(char *str, DATA *data)
{
    int i = 0, c=0;
    char tmp[5];
    while( str[i] != '/')
    {
        tmp[c++] = str[i++];        
    }
    tmp[c] = 0;
    data->dia = atoi(tmp);
    c = 0;
    i++;
    while( str[i] != '/')
    {
        tmp[c++] = str[i++];        
    }
    tmp[c] = 0;
    data->mes = atoi(tmp);
    c = 0;
    i++;
    while( str[i] != 0)
    {
        tmp[c++] = str[i++];        
    }
    tmp[c] = 0;
    data->ano = atoi(tmp);    
}

DATA hoje()
{
    //char instante[30];
    struct tm *instante ;
    DATA d;
    time_t result = time(NULL);
    instante = localtime(&result);
    //strcpy(instante, ctime(&result));
    // printf("Agora: %s");
    // distribuindo 
    d.hora = instante->tm_hour;
    d.minuto = instante->tm_min;
    d.segundo = instante->tm_sec;
    d.ano = instante->tm_year + 1900;
    d.mes = instante->tm_mon + 1; 
    d.dia = instante->tm_mday;
    return d;
    //

}

int DataToString(DATA p, char *output, bool complete)
{
    if (complete == false) 
        sprintf(output,"%02d\\%02d\\%d", p.dia, p.mes, p.ano);
    else
        sprintf(output,"%02d:%02d:%02d %02d\\%02d\\%d", p.hora,p.minuto, p.segundo, p.dia, p.mes, p.ano);
    
    return strlen(output);
}


int comparaValor(int t)
{
    if (t == 0 )
        return 0; 
    else if ( t > 0 )
        return 1;
    else return -1;        
}

int DataCmp(DATA d1, DATA d2)
{
    int tmp;    
    tmp = d1.ano - d2.ano;
    tmp = comparaValor(tmp);
    if (tmp != 0)
        return tmp;
    tmp = d1.mes - d2.mes;
    tmp = comparaValor(tmp);
    if (tmp != 0)
        return tmp;
    tmp = d1.dia - d2.dia;
    tmp = comparaValor(tmp);
    return tmp;   
}

