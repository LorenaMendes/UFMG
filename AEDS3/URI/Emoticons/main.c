#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0

int search(char * txt, char * key, int key_size, int position){
   int i;
   for(i=1; i<key_size; i++){
      if(key[i] != txt[position]){
         return 0;
      }
      position ++;
   }
   return 1;
}

char * delete(char * text, int emo_pos, int text_size, int emo_size){
   char * final = malloc(10000);
   char * new_text = malloc(10000);
   int i;
   //finds the end of the string
   for(i=emo_pos+emo_size; i<=text_size; i++){
      final[i - (emo_pos+emo_size)] = text[i];
   }
   if(DEBUG) printf("Final of the line: %s\n", final);

   //changes the original string
   for(i=0; i<emo_pos; i++){
      new_text[i] = text[i];
   }
   strcat(new_text, final);
   return new_text;
}

int main(){
   int i, j, k, counter = 0, bla = 0;
   int num_lines, num_emo, lola = 1;
   char * line = malloc(10000 * sizeof(char));
   
   while(!feof(stdin)){
      scanf("%d %d\n", &num_emo, &num_lines);
      if(num_emo == 0 && num_lines == 0) break;
      if(DEBUG) printf("\n############################### THIS IS THE CASE %d\n", lola);
      lola++;
      if(DEBUG) printf("%d EMOTICONS e %d LINHAS\n", num_emo, num_lines);
      
      char ** emoticons = malloc(num_emo * sizeof(char *));
      for(i=0; i<num_emo; i++) emoticons[i] = malloc(sizeof(char));
      
      //allocates emoticons in a vector
      for(i=0; i<num_emo; i++){
         fgets(emoticons[i], 16, stdin);
         // /*if(DEBUG) */printf("EMOTICON %d: %s", i+1, emoticons[i]);
      }

      //reads a line and       
      for(i=0; i<num_lines; i++){
         fgets(line, 10000, stdin);
         if(DEBUG) printf("Linha %d de tamanho %ld: %s\n", i+1, strlen(line)-1, line);
         if(DEBUG) printf("LINHA %d: %s", i+1, line);
         //for each emoticon, search the entire line

         for(j=0; j<num_emo; j++){
            for(k==; k<(strlen(line)-1); k++){
               if(line[k] == emoticons[j][0]){
                  if(DEBUG) printf("Searching for emoticon %s\n", emoticons[j]);
                  if(search(line, emoticons[j], strlen(emoticons[j])-1, k+1)){
                     if(DEBUG) printf("I found %s\n", emoticons[j]);
                     counter ++;
                     //delete emoticon
                     strcpy(line, delete(line, k, strlen(line)-1, strlen(emoticons[j])-1));
                     if(DEBUG) printf("New line: %s\n", line);
                     k=-1;
                     j=0;
                  } else {
                     if(DEBUG) printf("I didn't find %s\n", emoticons[j]);
                  }
               }
            }
         }
         if(DEBUG) printf("\nNumber of emoticons found in line %d: %d\n", i+1, counter);
         bla += counter;
         counter = 0;
      }
      if(DEBUG) printf("\nTotal number of emoticons found: %d\n", bla);
      printf("%d\n", bla);
      if(DEBUG) printf("\n");
      counter = 0;
      bla = 0;
   }
}