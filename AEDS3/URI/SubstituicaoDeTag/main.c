#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findBefore(char * txt, int position){
   int i;
   for(i=position; i>=0; i--){
      if(txt[i] == 60) return 1;
      else if(txt[i] == 62) return 0;
   }
   return 0;
}

int findAfter(char * txt, int position){
   int i;
   for(i=position; txt[i] != '\0'; i++){
      if(txt[i] == 62) return 1;
      else if(txt[i] == 60) return 0;
   }
   return 0;
}


int isTag(char * txt, int position){
   return findBefore(txt, position) && findAfter(txt, position) ? 1 : 0;
}

int isEqual(char letter, char key){
   if(letter > 64 && letter < 91) return letter == key || letter + 32 == key ? 1 : 0;
   else if(letter > 96 && letter < 123) return letter == key || letter - 32 == key ? 1 : 0;
   else return 0;
}

void shift(char * new_txt, int position, char * aux){
   int i;
   for(i=0; aux[i] != '\0'; i++){
      if(aux[i+1] == '\0') new_txt[position+i+1] = '\0';
      new_txt[position+i] = aux[i];
   }
   return;
}

char * substitution(char * new_txt, char * num, int position, int key_size){
   char aux[51];
   int i;
   int index = position + key_size;
   for(i=0; i<51; i++){
      if(new_txt[index+i] == '\0'){
         aux[i] = '\0';
         break;
      }
      aux[i] = new_txt[index+i];
   }
   // //I've created a copy from the rest of the text after the key
   for(i=0; i<=strlen(num)-1; i++){
      if(i == strlen(num)-1){
         shift(new_txt, position+i, aux);
         break;;
      }
      //copying the number to the key's place in the text
      new_txt[position+i] = num[i];
   }
   return new_txt;
}

int search(char * txt, char * key, int key_size, int position){
   int i;
   for(i=1; i < key_size; i++){
      if(!isEqual(key[i], txt[position])) return 0;
      position ++;
   }
   return 1;
}

int main(){
   char key[12], buff[6], txt[52], new_txt[52];
   int i;
	while(fgets(key, 12, stdin)){
		int key_size = strlen(key) - 1;
      
      fgets(buff, 6, stdin);
      int num = atoi(buff);
      
      fgets(txt, 52, stdin);
      
      strcpy(new_txt, txt);
      for(i=0; txt[i] != '\0'; i++){
         if(isEqual(txt[i], key[0])){
            //if a first match
            if(search(txt, key, key_size, i+1) && isTag(txt, i)){
               //if there is a full match
               strcpy(txt, substitution(txt, buff, i, key_size));
            }
         }
      }
      printf("%s", txt);
   }
}