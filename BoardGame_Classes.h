#ifndef _BOARDGAME_CLASSES_H
#define _BOARDGAME_CLASSES_H

#include <string>
#include <vector>
#include <fstream>

using namespace std;
bool isfound (ifstream& file, const string& word){
    string tst;
    while(!file.eof()){
        tst = "";
        file.ignore(3000,word[0]);
        getline(file,tst);
        if(tst.size()==2){
            tst = "C" + tst;
            if(word==tst){
                return true;
            }
        }
    }
    return false;
}

bool isfound (string word){
    return true;
}

template <typename T>
class Board {
protected:
    int rows, columns;
    T** board;
    int n_moves = 0;

public:


    /// Return true if move is valid and put it on the board
    /// within board boundaries in an empty cell
    /// Return false otherwise
    virtual bool update_board(int x, int y, T symbol) = 0;

    /// Display the board and the pieces on it
    virtual void display_board() = 0;

    /// Returns true if there is any winner
    virtual bool is_win() = 0;

    /// Return true if all moves are done and no winner
    virtual bool is_draw() = 0;

    /// Return true if the game is over
    virtual bool game_is_over() = 0;
};

template <typename T>
class Player {
protected:
    string name;
    T symbol;
    Board<T>* boardPtr;  // Pointer to the board
public:
    /// Two constructors to initiate players
    /// Give the player a symbol to use in playing
    /// It can be X, O, or others
    /// Optionally, you can give them a name
    Player(string n, T symbol);
    Player(T symbol); // For computer players

    virtual void getmove(int& x, int& y) = 0;
    T getsymbol();
    string getname();
    void setBoard(Board<T>* b);
};

/// This class represents a random computer player
/// that generates random positions x, y
/// If invalid, the game manager asks to regenerate
template <typename T>
class RandomPlayer : public Player<T>{
protected:
    int dimension;
public:
    // Take a symbol and pass it to the parent
    RandomPlayer(T symbol);
    // Generate a random move
    virtual void getmove(int& x, int& y) = 0;
};

template <typename T>
class GameManager {
private:
    Board<T>* boardPtr;
    Player<T>* players[2];
public:
    GameManager(Board<T>*, Player<T>* playerPtr[2]);

    void run();
};


//--------------------------------------- IMPLEMENTATION

#include <iostream>
using namespace std;

template <typename T>
GameManager<T>::GameManager(Board<T>* bPtr, Player<T>* playerPtr[2]) {
    boardPtr = bPtr;
    players[0] = playerPtr[0];
    players[1] = playerPtr[1];
}

template <typename T>
void GameManager<T>::run() {
    int x, y;

    boardPtr->display_board();

    while (!boardPtr->game_is_over()) {
        for (int i : {0, 1}) {
            players[i]->getmove(x, y);
            while (!boardPtr->update_board(x, y, players[i]->getsymbol())) {
                players[i]->getmove(x, y);
            }
            boardPtr->display_board();
            if (boardPtr->is_win()) {
                cout << players[i]->getname() << " wins\n";
                return;
            }
            if (boardPtr->is_draw()) {
                cout << "Draw!\n";
                return;
            }
        }
    }
}


using namespace std;
// Constructor for Player with a name and symbol
template <typename T>
Player<T>::Player(std::string n, T symbol) {
    this->name = n;
    this->symbol = symbol;
}

// Constructor for Player with only a symbol (e.g., for computer players)
template <typename T>
Player<T>::Player(T symbol) {
    this->name = "Computer";
    this->symbol = symbol;
}

// Constructor for RandomPlayer, passing the symbol to the parent Player class
template <typename T>
RandomPlayer<T>::RandomPlayer(T symbol) : Player<T>(symbol) {}

// Getter for player's name
template <typename T>
std::string Player<T>::getname() {
    return this->name;
}

// Getter for player's symbol
template <typename T>
T Player<T>::getsymbol() {
    return this->symbol;
}

// Method to set the board pointer in the Player class
template <typename T>
void Player<T>::setBoard(Board<T>* b) {
    this->boardPtr = b;
}




template <typename T>
class Game1 : public Board<T>{
    int i,j;
    ifstream file;
public:
    Game1(): Board<T>(){
        this->rows=3;
        this->columns=3;
        this->board = new T*[3];
        this->file.open ("C:\\Users\\loly\\CLionProjects\\Game2\\dic.txt");
        for (int i = 0; i < 3; ++i) {
            this->board[i] = new T[3]();
        }
    }

    ~Game1(){
        for (int i = 0; i < 3; ++i) {
            delete[] this->board[i];
        }
        delete[] this->board;
    }



    bool update_board(int x, int y, T symbol){
        this->board[x][y] = symbol;
        i = x;
        j = y;
        return true;
    }

    void display_board(){
        for(int i = 0 ; i < 3; i++){
            cout << "      ";

            for(int j = 0 ; j < 3; j++){
                if(!this->board[i][j]){
                    cout << i << "," <<j;
                }
                else{
                    cout << " " <<this->board[i][j] << " ";
                }
                cout << "   ";
            }
            cout << "\n" << "\n";
        }
    }

    bool is_win(){
        int x = this->i;
        int y = this->j;
        string word = "   ";
        if(x+y==2){
            if(this->board[0][2] != 0 && this->board[1][1] != 0 && this->board[2][0] != 0){
                word[0] = this->board[0][2];
                word[1]=this->board[1][1];
                word[2] = this->board[2][0];
                if(isfound(this->file,word)){
                    return true;
                }
                char t = word[0];
                word[0] = word[2];
                word[2] = t;
                if(isfound(this->file,word)){
                    return true;
                }
            }
        }
        if(y==0){
            if(this->board[0][0] != 0 && this->board[1][0] != 0 && this->board[2][0] != 0){
                word[0] = this->board[0][0];
                word[1] = this->board[1][0];
                word[2] = this->board[2][0];
                if(isfound(this->file,word)){
                    return true;
                }
                char t = word[0];
                word[0] = word[2];
                word[2] = t;
                if(isfound(this->file,word)){
                    return true;
                }
            }
        }
        if(y==1){
            if(this->board[0][1] != 0 && this->board[1][1] != 0 && this->board[2][1] != 0){
                word[0] = this->board[0][2];
                word[1]=this->board[1][1];
                word[2] = this->board[2][1];
                if(isfound(this->file,word)){
                    return true;
                }
                char t = word[0];
                word[0] = word[2];
                word[2] = t;
                if(isfound(word)){
                    return true;
                }
            }
        }
        if(y==2){
            if(this->board[0][2] != 0 && this->board[1][2] != 0 && this->board[2][2] != 0){
                word[0] = this->board[0][2];
                word[1]=this->board[1][2];
                word[2] = this->board[2][2];
                if(isfound(this->file,word)){
                    return true;
                }
                char t = word[0];
                word[0] = word[2];
                word[2] = t;
                if(isfound(this->file,word)){
                    return true;
                }
            }
        }
        if(x==1){
            if(this->board[1][0] != 0 && this->board[1][1] != 0 && this->board[1][2] != 0){
                word[0] = this->board[1][0];
                word[1]=this->board[1][1];
                word[2] = this->board[1][2];
                if(isfound(this->file,word)){
                    return true;
                }
                char t = word[0];
                word[0] = word[2];
                word[2] = t;
                if(isfound(this->file,word)){
                    return true;
                }
            }
        }
        if(x==0){
            if(this->board[0][0] != 0 && this->board[0][1] != 0 && this->board[0][2] != 0){
                word[0] = this->board[0][0];
                word[1] = this->board[0][1];
                word[2] = this->board[0][2];
                if(isfound(this->file,word)){
                    return true;
                }
                char t = word[0];
                word[0] = word[2];
                word[2] = t;
                if(isfound(this->file,word)){
                    return true;
                }
            }
        }
        if(x==2){
            if(this->board[2][0] != 0 && this->board[2][1] != 0 && this->board[2][2] != 0){
                word[0] = this->board[2][0];
                word[1]=this->board[2][1];
                word[2] = this->board[2][2];
                if(isfound(this->file,word)){
                    return true;
                }
                char t = word[0];
                word[0] = word[2];
                word[2] = t;
                if(isfound(this->file,word)){
                    return true;
                }
            }
        }
        if(x==y){
            if(this->board[0][0] != 0 && this->board[1][1] != 0 && this->board[2][2] != 0){
                word[0] = this->board[0][0];
                word[1]=this->board[1][1];
                word[2] = this->board[2][2];
                if(isfound(this->file,word)){
                    return true;
                }
                char t = word[0];
                word[0] = word[2];
                word[2] = t;
                if(isfound(word)){
                    return true;
                }
            }
        }
        return false;
    }

    bool is_draw(){
        int x = 2;
        for(int i = 0 ; i < 3 ; i++){
            for(int j = 0 ; j < 3 ; j++){
                if(this->board[i][j]==0){
                    return false;
                }
            }
            x--;
        }
        return true;
    }

    bool game_is_over(){
        if (is_draw()||is_win()){
            return true;
        }
        return false;
    }

};

template <typename T>
class playerg1 : public Player<T>{
public:
    playerg1(string N , T smp):Player<T>(N,smp){}

    void getmove(int& x , int& y){
        cout<< "Enter a Move:\n";
        cin >> x >> y;
        while(x>3 || x<0 || y>3 || y<0){
            cout << "Invalid CHOICE, PLEASE TRY AGAIN\n";
            cin >> x >> y;
        }
        cout<< "Enter a letter:\n";
        cin >> this->symbol;
        this->symbol = toupper(this->symbol);
    }
};

#endif //_BOARDGAME_CLASSES_H
