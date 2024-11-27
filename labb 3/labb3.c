#include "egen.h"
//GUI och val menyn
void userInterface(){
    int antal;
    int lottorad[25][7];
    int val=0;
    bool giltig=true;

//s� l�nge giltig �r true s� kommer menyn att visas
    while(giltig){
          printf("Ange Val:\n");
    printf("1.Slumpa lottorader.\n");
    printf("2.L�sa tdigare slumpade rader.\n");
    printf("3.EXIT.\n");
    printf("V�lj (1/2/3)\n");
    scanf("%d",&val);

//kontrollera valet
    if(val==1){
                printf("ange antal rader: ");
       scanf("%i", &antal);
       lottoGeneration(lottorad, antal);
       giltig=false;
        }
        else if(val==2){
            printf("tidigare slumpade lottorader:\n");
            readFile();
            giltig=false;
        }
        else if(val==3){
            printf("Hejd�!");
            break;
        }
        else{
            printf("ange ett giltig val 1 eller 2.\n\n");
            continue;
        }
    }
}


//funktion f�r att generera, sortera och spara lottorader
void lottoGeneration(int lottorad[][7],int antal){

    srand(time(NULL));
//slumpa ett tall mellan 1 och 35
    for (int i =0;i<antal; i++){
        for(int l=0; l<7;l++){
            bool unik=true;
            int tal;
            do{
                tal= rand()% 35+ 1;
                unik=true;
                for(int j=0; j<i; j++){
                    if(lottorad[i][j]==tal){
                        unik=false;
                        break;
                    }
                }
            }while(!unik);
            lottorad[i][l]=tal;
        }

}

//sortera talen i arrayen
int temp;
for (int i=0; i<antal;i++){
    for (int j=0; j<7;j++){
        for(int k=6; k>j;k--){
            if(lottorad[i][k-1]>lottorad[i][k]){
                temp=lottorad[i][k];
                lottorad[i][k]=lottorad[i][k-1];
                lottorad[i][k-1]=temp;
            }
        }
    }
}

//skriver den sorterade raden
    for (int i = 0; i < antal; i++) {
        for (int j = 0; j < 7; j++) {
            printf("%d ", lottorad[i][j]);

        }
        printf("\n");
    }


    //sparar raderan i en txt fil
    //vi valde att spara de i en text fil f�r att det �r ett s�pass simpelt program
    //vilket g�r det l�ttare att spara i txt, samt kan man dubbelkolla att programmet skrivit in r�tt
    //mindre storlek och b�ttre prestanda
    //och vi beh�ver inte anv�nda ftell/fseek eftersom vi skriver �ver det tidigare dokumentet
    FILE *fptr;
    fptr = fopen("lotto.txt", "w");
     for (int i = 0; i < antal; i++) {
        fprintf(fptr,"\n");
        for (int j = 0; j < 7; j++) {
        fprintf(fptr," %d" ,lottorad[i][j]);

        }
    }

    fclose(fptr);


userInterface();
}


//l�sa filen
void readFile(){
    char buffer[250];
FILE *fptr;
fptr=fopen("lotto.txt", "r");

while (!feof (fptr)){
    printf("%s",fgets(buffer, sizeof(buffer), fptr));
}
fclose(fptr);
userInterface();
}

//main funktionen
int main() {
userInterface();
   return 0;
}
