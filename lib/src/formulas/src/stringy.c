#include<string.h>
#include<stdio.h>

int str_length(char *s)
{
    int i;
    for (i = 0 ; s[i] != '\0' ; i++);
    return i;
}

char *str_concat(char *s1, char *s2)
{
    int length, s1_length, s2_length;
    int i;
    char *concat;

    s1_length = str_length(s1);
    s2_length = str_length(s2);
    length = s1_length + s2_length;

    concat = (char *) calloc(sizeof(char), length + 1);

    for (i = 0 ; i < s1_length ; i++)
	concat[i] = s1[i];

    for (i = 0 ; i < s2_length ; i++)
	concat[s1_length + i] = s2[i];

    concat[length + 1] = '\0';

    return concat;
}

char *str_copy(char *s)
{
    char *empty;
    empty = (char *) malloc(sizeof(char));
    empty[0] = '\0';

    return str_concat(s, empty);
}
