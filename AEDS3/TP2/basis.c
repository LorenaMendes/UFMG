#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct T_word{
    char * word;
    int distance;
} T_word;

//function used by qsort() to sort an array
int sortstring(const void * a, const void * b){
    T_word *A = (T_word *)a;
    T_word *B = (T_word *)b;
    if(!(A->distance - B->distance)) return strcmp( A->word, B->word );
    else return (A->distance - B->distance);
}

//returns the lowest value between three ones
int find_lowest(int a, int b, int c){
    int lowest = a;
    if(lowest > b) lowest = b;
    if(lowest > c) lowest = c;
    return lowest;
}

//returns the Levenshtein distance between two words
static int calc_distance (const char * first_word, int first_size, const char * second_word, int second_size){
    int i, j, matrix[first_size + 1][second_size + 1];
    int insert, delete, change;
    
    //fills basic rows and columns
    for (i = 0; i <= first_size; i++) matrix[i][0] = i;
    for (i = 0; i <= second_size; i++) matrix[0][i] = i;

    for (i = 1; i <= first_size; i++) {
        char letter1 = first_word[i-1];
        for (j = 1; j <= second_size; j++) {
            char letter2 = second_word[j-1];
            //compares each letter
            if (letter1 == letter2) matrix[i][j] = matrix[i-1][j-1];
            else {
                delete = matrix[i-1][j] + 1;
                insert = matrix[i][j-1] + 1;
                change = matrix[i-1][j-1] + 1;
                matrix[i][j] = find_lowest(insert, delete, change);
            }
        }
    }
    return matrix[first_size][second_size];
}

int main (){
    int num_words, changes, i;
    char * key = malloc(10000 * sizeof(char));
    char * word = malloc(10000 * sizeof(char));

    
    //reads parameters
    scanf("%d%d\n", &num_words, &changes);
    fgets(key, 10000, stdin);
    int pos = 0;
    int dist;

    T_word * selected = (T_word *) malloc(num_words * sizeof(T_word));
    for (i = 0; i < 10000; i++){
        selected[i].word = malloc (10000 * sizeof(char));
    }

    //reads the input file and calculates each Levenshtein distance
    for(i=0; i<num_words; i++){
        fgets(word, 10000, stdin);
        dist = calc_distance(key, strlen(key)-1, word, strlen(word)-1);
        //if less than or equals to the changes number, put word in array 
        if(dist <= changes){
            strcpy(selected[pos].word, word); 
            selected[pos].distance = dist;
            pos ++;
        }
    }
    //sort the array of selected words
    qsort (selected, pos, sizeof(T_word), sortstring);
    for(i=0; i<pos; i++) printf("%s", selected[i].word);
    
    //free allocated memory
    free(key);
    free(word);
    free(selected);
    return 0;
}