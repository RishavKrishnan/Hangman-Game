#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<time.h>
using namespace std;
void printmessage(string message, bool printtop= true, bool printbottom= true)
{
    if(printtop)
    {
        cout<<"+----------------------------------------+"<<endl;
    }
    cout<<"|";
    bool front=true;
    for(int i=message.length();i<40;i++)
    {
        if(front)
        {
            message = " " + message;
        }
        else{
            message = message + " ";
        }
        front=!front;
    }
    cout<< message.c_str();
    cout<<"|"<<endl;
    if(printbottom)
    {
        cout<<"+----------------------------------------+"<<endl;
    }
    
}
void drawhangman(int guesscount=0)
{
    if(guesscount>=1)
        printmessage("|", false, false);
    else{
        printmessage("", false, false);
    }

    if(guesscount>=2)
        printmessage("|", false, false);
    else{
        printmessage("", false, false);
    }

    if(guesscount>=3)
        printmessage("O", false, false);
    else{
        printmessage("", false, false);
    }

    if(guesscount==4)
        printmessage("/", false, false);

    if(guesscount==5)
        printmessage("/|", false, false);

    if(guesscount>=6)
        printmessage("/|\\", false, false);
    else{
        printmessage("", false, false);
    }

    if(guesscount>=7)
        printmessage("|", false, false);
    else{
        printmessage("", false, false);
    }

    if(guesscount==8)
        printmessage("/", false, false);

    if(guesscount>=9)
        printmessage("/ \\", false, false);
    else{
        printmessage("", false, false);
    }   

}
void printletters(string input,char from, char to)
{
    string s;
    for(char i= from;i<=to;i++)
    {
        if(input.find(i)==string::npos)
        {
            s += i;
            s+=" ";
        }
        else
            s+=" ";
    }
    printmessage(s,false,false);
}
void printavailableletters(string taken)
{
    printmessage("AVAILABLE LETTERS");
    printletters(taken, 'A','M');
    printletters(taken, 'N','Z');
}
bool check(string word,string guessed)
{
    bool won= true;
    string s;
    for(int i=0;i<word.length();i++)
    {
        if(guessed.find(word[i])==string::npos)
        {
            won=false;
            s+="_ ";
        }
        else
        {
            s+=word[i];
            s+=" ";
        }
    }
    printmessage(s,false);
    return won;
}
string loadword(string path)
{
     int linecount=0;
     string word;
     vector<string> v;
    ifstream reader(path);
    if(reader.is_open())
    {
        while(std::getline(reader,word))   
            v.push_back(word);
        
        int randomline=rand()%v.size();

        word=v.at(randomline);
        reader.close();
    }
    return word;
}
int triesleft(string word, string guessed)
{
    int error=0;
    for(int i=0;i<guessed.length();i++)
    {
        if(word.find(guessed[i])==string::npos)
        {
                error++;
        }
    }
    return error;           
}
int main()
{
    srand(time(0));
    string wordtoguess;
    string guesses;

    wordtoguess= loadword("words.txt");
    
    int tries=0;
    bool win=false;
    do
    {
        /* code */
        system("cls");
        printmessage("HANGMAN");
        drawhangman(tries); 
        printavailableletters(guesses);
        if(tries>=9)
        {
            printmessage("YOU LOST!!");
            break;
        }
        printmessage("Guess the word");
        win=check(wordtoguess,guesses);

        if(win)
            break;
        char x;
        cout<<">";cin>>x;
        if(guesses.find(x)==string::npos)
        {
            guesses+=x;
        }
        tries=triesleft(wordtoguess,guesses);
    } while (tries<=9);
    getchar();
    return 0;
}