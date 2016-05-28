#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

void initializeCString(char s[], int size){
    for (int i = 0; i < size-1; i++){
        s[i] = '_';
    }
    s[size-1]='\0';
}


void encryptIntoMorse(char message[], char morseResult[]){
    char morseTable[26][5] = {"*-", "-***","-*-*","-**","*","**-*","--*","****","**","*---","-*-","*-**","--",
    "-*","---","*--*","--*-","*-*","***","-","**-","***-","*--","-**-","-*--","--*"};
    /*for (int i =0; i < 26; i++){
        cout<<morseTable[i]<<endl;
    }*/
    
    int position;
    for (int i = 0; i < strlen(message); i++){
        message[i] = toupper(message[i]);
        if (message[i] == ' '){
            strcat(morseResult, "X");
        }
        else if (isalpha(message[i])){
            //ASCII TABLE, A = 65
            position = message[i]-65;
            strcat(morseResult, morseTable[position]);
            strcat(morseResult, "X");
        }
    }
    strcat(morseResult, "X");
    cout<<morseResult<<endl;
}

void removeDuplicate(char key[], char result[]){
    char alphabet[27] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    int position = 0;
    cout<<"What position would you like the table 2 to start at"<<endl;
    cin>>position;
    for (int i = 0; i < strlen(key); i++){
        if (isalpha(key[i])){
            key[i] = toupper(key[i]);
            
            if (strchr(result, key[i]) == NULL){
                result[position] = key[i];
                position++;
                if (position >25){
                    position = 0;
                }
            }
        }
    }
    cout<<result<<endl;
    for (int i = 0; i < 26; i++){
        if (strchr(result, alphabet[i]) == NULL){
            result[position] = alphabet[i];
            position++;
            if (position >25){
                position = 0;
            }

        }
    }
    result[26] = '\0';
    cout<<result<<endl;
}

void morseIntoLetter(char morseResult[], char table2Row[], char encryptResult[]){
    char group[4];
    initializeCString(group, 4);
    int i;
    char table2[26][4] = {"***", "**-", "**X", "*-*", "*--", "*-X", "*X*", "*X-", "*XX", "-**", "-*-", "-*X", "--*", "---", "--X", "-X*",
        "-X-", "-XX", "X**", "X*-", "X*X", "X-*","X--", "X-X", "XX*","XX-"};
    
    cout<<"The result: ";
    for ( i = 0; i < strlen(morseResult); i+=3){
        group[0]=morseResult[i];
        group[1]=morseResult[i+1];
        group[2]=morseResult[i+2];

        //cout<<group<<endl;
        
        for (int j = 0; j < 26; j++){
            if ((group[0] == table2[j][0]) && (group[1] == table2[j][1]) && (group[2] == table2[j][2])){
                if (i != 0){
                    //print a space for every 5 letters
                    if(i%15 == 0){
                        cout<<" ";
                    }
                }
                cout<<table2Row[j];
                encryptResult[i/3] = table2Row[j];
                break;
            }
        }
    }
    cout<<endl;
    encryptResult[i/3] ='\0';
}


int main(){
   char message[255];
    char morseResult[255];
    //initialize morse result
    morseResult[0] = '\0';
    char table2Row[27];
    initializeCString(table2Row, 27);
    char encryptResult[255];
    initializeCString(encryptResult, 255);


   string m;
   cout<<"Please enter the message you wish to encrypt"<<endl;
   cin.getline(message, 255);
    cout<<"This is the morse code"<<endl;
    encryptIntoMorse(message, morseResult);

   char key[255];
   cout<<"Please enter the replacement key"<<endl;
   cin.getline(key, 255);
    removeDuplicate(key, table2Row);
    
    morseIntoLetter(morseResult,table2Row, encryptResult);
    
   return 0;
}


