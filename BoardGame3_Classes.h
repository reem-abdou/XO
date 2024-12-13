#include <iostream>

#ifndef _BOARDGAME_CLASSES_H
#define _BOARDGAME_CLASSES_H

#include <string>
#include <vector>
#include <fstream>

using namespace std;


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
class Game1 : public Board<T> {
    int i,j;
    int m,n;
    T play[3][3];
public:
    Game1(): Board<T>(){
        this->rows=9;
        this->columns=9;
        this->board = new T*[9];
        
        for (int i = 0; i < 9; ++i) {
            this->board[i] = new T[9]();
        }
        for(int i = 0; i < 3; ++i){
            for(int j = 0; j < 3; ++j){
                play[i][j]=0;
            }
        }
    }

    ~Game1(){
        for (int i = 0; i < 9; ++i) {
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
        for(int i = 0 ; i < 9; i++){
            cout << "        ";
            for(int j = 0 ; j < 9; j++){
                if(!this->board[i][j]){
                    cout << i << "," <<j;
                }
                else{
                    cout << " " <<this->board[i][j] << " ";
                }
                if((j+1)%3==0){
                cout << "   ";
            }
                cout << "  ";
            
            }
            if((i+1)%3==0){
                cout << "\n" ;
            }
            cout << "\n" ;
        }
    }
    

    void check(){
        int x = this->i;
        int y = this->j;
        if(x<=2 && x>=0 && y<=2 && y>=0){
            if(x+y==2){
                if(this->board[0][2] == this->board[1][1] && this->board[2][0] == this->board[1][1]){
                    play[0][0]=this->board[0][2];
                    this->m = 0;
                    this->n = 0;
                    return;
                }
            }
            if(y==0){
                if(this->board[0][0] == this->board[1][0] && this->board[2][0] == this->board[1][0]){
                    play[0][0]=this->board[0][0];
                    this->m = 0;
                    this->n = 0;
                    return;
                }
            }
            if(y==1){
                if(this->board[0][1] == this->board[1][1] &&  this->board[2][1] == this->board[1][1]){
                    play[0][0]=this->board[0][1];
                    this->m = 0;
                    this->n = 0;
                    return;
                }
            }
            if(y==2){
                if(this->board[0][2] == this->board[1][2] && this->board[2][2] == this->board[1][2]){
                    play[0][0]=this->board[0][2];
                    this->m = 0;
                    this->n = 0;
                    return;
                }
            }
            if(x==1){
                if(this->board[1][0] == this->board[1][1] && this->board[1][2] == this->board[1][1]){
                    play[0][0]=this->board[1][0];
                    this->m = 0;
                    this->n = 0;
                    return;
                }
            }
            if(x==0){
                if(this->board[0][0] == this->board[0][1] && this->board[0][2] == this->board[0][1]){
                    this->play[0][0]=this->board[0][2];
                    this->m = 0;
                    this->n = 0;
                    return;
                }
            }
            if(x==2){
                if(this->board[2][0] == this->board[2][1] && this->board[2][2] == this->board[2][1]){
                    play[0][0]=this->board[2][2];
                    this->m = 0;
                    this->n = 0;
                    return;
                }
            }
            if(x==y){
                if(this->board[0][0] == this->board[1][1] && this->board[2][2] == this->board[1][1]){
                    play[0][0]=this->board[0][0];
                    this->m = 0;
                    this->n = 0;
                    return;
                }
            }
        }
        
        
        if(x<=2 && x>=0 && y<=5 && y>=3){
            if(x+y==5){
                if(this->board[0][5] == this->board[1][4] && this->board[2][3] == this->board[1][4]){
                    this->play[0][1]=this->board[0][5];
                    this->m = 0;
                    this->n = 1;
                    return;
                }
            }
            if(y==3){
                if(this->board[0][3] == this->board[1][3] && this->board[2][3] == this->board[1][3]){
                    this->play[0][1]=this->board[0][3];
                    this->m = 0;
                    this->n = 1;
                    return;
                }
            }
            if(y==4){
                if(this->board[0][4] == this->board[1][4] &&  this->board[2][4] == this->board[1][4]){
                    this->play[0][1]=this->board[2][4];
                    this->m = 0;
                    this->n = 1;
                    return;
                }
            }
            if(y==5){
                if(this->board[0][5] == this->board[1][5] && this->board[2][5] == this->board[1][5]){
                    this->play[0][1]=this->board[0][5];
                    this->m = 0;
                    this->n = 1;
                    return;
                }
            }
            if(x==1){
                if(this->board[1][3] == this->board[1][4] && this->board[1][5] == this->board[1][4]){
                    this->play[0][1]=this->board[1][3];
                    this->m = 0;
                    this->n = 1;
                    return;
                }
            }
            if(x==0){
                if(this->board[0][3] == this->board[0][4] && this->board[0][5] == this->board[0][4]){
                   this->play[0][1]=this->board[0][3];
                    this->m = 0;
                    this->n = 1;
                    return;
                }
            }
            if(x==2){
                if(this->board[2][3] == this->board[2][4] && this->board[2][5] == this->board[2][4]){
                    this->play[0][1]=this->board[2][3];
                    this->m = 0;
                    this->n = 1;
                    return;
                }
            }
            if(x+3==y){
                if(this->board[0][3] == this->board[1][4] && this->board[2][4] == this->board[1][4]){
                    this->play[0][1]=this->board[0][3];
                    this->m = 0;
                    this->n = 1;
                    return;
                }
            }
        }
        
        
        if(x<=2 && x>=0 && y<=8 && y>=6){
            if(x+y==8){
                if(this->board[0][8] == this->board[1][7] && this->board[2][7] == this->board[1][7]){
                    this->play[0][2]=this->board[0][8];
                    this->m = 0;
                    this->n = 2;
                    return;
                   
                }
            }
            if(y==6){
                if(this->board[0][6] == this->board[1][6] && this->board[2][6] == this->board[1][6]){
                    this->play[0][2]=this->board[0][6];
                    this->m = 0;
                    this->n = 2;
                    return;
                }
            }
            if(y==7){
                if(this->board[0][7] == this->board[1][7] &&  this->board[2][7] == this->board[1][7]){
                    this->play[0][2]=this->board[0][7];
                    this->m = 0;
                    this->n = 2;
                    return;
                }
            }
            if(y==8){
                if(this->board[0][8] == this->board[1][8] && this->board[2][8] == this->board[1][8]){
                    this->play[0][2]=this->board[0][8];
                    this->m = 0;
                    this->n = 2;
                    return;
                }
            }
            if(x==1){
                if(this->board[1][6] == this->board[1][7] && this->board[1][8] == this->board[1][7]){
                    this->play[0][2]=this->board[1][7];
                    this->m = 0;
                    this->n = 2;
                    return;
                }
            }
            if(x==0){
                if(this->board[0][6] == this->board[0][7] && this->board[0][8] == this->board[0][7]){
                    this->play[0][2]=this->board[0][7];
                    this->m = 0;
                    this->n = 2;
                    return;
                }
            }
            if(x==2){
                if(this->board[2][6] == this->board[2][7] && this->board[2][8] == this->board[2][7]){
                    this->play[0][2]=this->board[2][7];
                    this->m = 0;
                    this->n = 2;
                    return;
                }
            }
            if(x+6==y){
                if(this->board[0][6] == this->board[1][7] && this->board[2][7] == this->board[1][7]){
                    this->play[0][2]=this->board[0][6];
                    this->m = 0;
                    this->n = 2;
                    return;
                }
            }
        }
        
        
        if(x<=5 && x>=3 && y<=2 && y>=0){
            if(x+y==5){
                if(this->board[3][2] == this->board[4][1] && this->board[5][0] == this->board[4][1]){
                    this->play[1][0] = this->board[4][1];
                    this->m = 1;
                    this->n = 0;
                    return;
                   
                }
            }
            if(y==0){
                if(this->board[3][0] == this->board[4][0] && this->board[5][0] == this->board[4][0]){
                    this->play[1][0]=this->board[4][0];
                    this->m = 1;
                    this->n = 0;
                    return;
                }
            }
            if(y==1){
                if(this->board[3][1] == this->board[4][1] &&  this->board[5][1] == this->board[4][1]){
                    this->play[1][0]=this->board[3][1];
                    this->m = 1;
                    this->n = 0;
                    return;
                }
            }
            if(y==2){
                if(this->board[3][2] == this->board[4][2] && this->board[5][2] == this->board[4][2]){
                    this->play[1][0]=this->board[4][2];
                    this->m = 1;
                    this->n = 0;
                    return;
                }
            }
            if(x==4){
                if(this->board[4][0] == this->board[4][1] && this->board[4][2] == this->board[4][1]){
                    this->play[1][0]=this->board[4][0];
                    this->m = 1;
                    this->n = 0;
                    return;
                }
            }
            if(x==3){
                if(this->board[3][0] == this->board[3][1] && this->board[3][2] == this->board[3][1]){
                    this->play[1][0]=this->board[3][1];
                    this->m = 1;
                    this->n = 0;
                    return;
                }
            }
            if(x==5){
                if(this->board[5][0] == this->board[5][1] && this->board[5][2] == this->board[5][1]){
                    this->play[1][0]=this->board[5][0];
                    this->m = 1;
                    this->n = 0;
                    return;
                }
            }
            if(x==y+3){
                if(this->board[3][0] == this->board[4][1] && this->board[5][2] == this->board[4][1]){
                    this->play[1][0]=this->board[3][0];
                    this->m = 1;
                    this->n = 0;
                    return;
                }
            }
        }
        
        
        if(x<=8 && x>=6 && y<=2 && y>=0){
            if(x+y==8){
                if(this->board[6][2] == this->board[7][1] && this->board[8][0] == this->board[7][1]){
                    this->play[0][2]=this->board[6][2];
                    this->m = 2;
                    this->n = 0;
                    return;
                }
            }
            if(y==0){
                if(this->board[6][0] == this->board[7][0] && this->board[8][0] == this->board[7][0]){
                    this->play[2][0]=this->board[6][0];
                    this->m = 2;
                    this->n = 0;
                    return;
                }
            }
            if(y==1){
                if(this->board[6][1] == this->board[7][1] &&  this->board[8][1] == this->board[7][1]){
                    this->play[2][0]=this->board[6][1];
                    m = 2;
                    n = 0;
                    return;
                }
            }
            if(y==2){
                if(this->board[6][2] == this->board[7][2] && this->board[8][2] == this->board[7][2]){
                    this->play[2][0]=this->board[6][2];
                    this->m = 2;
                    this->n = 0;
                    return;
                }
            }
            if(x==7){
                if(this->board[7][0] == this->board[7][1] && this->board[7][2] == this->board[7][1]){
                    this->play[2][0]=this->board[7][2];
                    this->m = 2;
                    this->n = 0;
                    return;
                }
            }
            if(x==6){
                if(this->board[6][0] == this->board[6][1] && this->board[6][2] == this->board[6][1]){
                    this->play[2][0]=this->board[6][2];
                    this->m = 2;
                    this->n = 0;
                    return;
                }
            }
            if(x==8){
                if(this->board[8][0] == this->board[8][1] && this->board[8][2] == this->board[8][1]){
                    this->play[2][0]=this->board[8][2];
                    this->m = 2;
                    this->n = 0;
                    return;
                }
            }
            if(x==y+6){
                if(this->board[6][0] == this->board[7][1] && this->board[8][2] == this->board[7][1]){
                    this->play[2][0]=this->board[8][2];
                    this->m = 2;
                    this->n = 0;
                    return;
                }
            }
        }
        
        
        if(x<=5 && x>=3 && y<=5 && y>=3){
            if(x+y==8){
                if(this->board[3][5] == this->board[4][4] && this->board[5][3] == this->board[4][4]){
                    this->play[1][1]=this->board[3][5];
                    this->m = 1;
                    this->n = 1;
                    return;
                }
            }
            if(y==3){
                if(this->board[3][3] == this->board[4][3] && this->board[5][3] == this->board[4][3]){
                    this->play[1][1]=this->board[3][3];
                    this->m = 1;
                    this->n = 1;
                    return;
                }
            }
            if(y==4){
                if(this->board[3][4] == this->board[4][4] &&  this->board[5][4] == this->board[4][4]){
                    this->play[1][1]=this->board[3][4];
                    m = 1;
                    n = 1;
                    return;
                }
            }
            if(y==5){
                if(this->board[3][5] == this->board[4][5] && this->board[5][5] == this->board[4][5]){
                    this->play[1][1]=this->board[3][5];
                    m = 1;
                    n = 1;
                    return;
                }
            }
            if(x==4){
                if(this->board[4][3] == this->board[4][4] && this->board[4][5] == this->board[4][4]){
                    this->play[1][1]=this->board[4][3];
                    this->m = 1;
                    this->n = 1;
                    return;
                }
            }
            if(x==3){
                if(this->board[3][0] == this->board[3][1] && this->board[3][2] == this->board[3][1]){
                    this->play[1][1]=this->board[3][0];
                    this->m = 1;
                    this->n = 1;
                    return;
                }
            }
            if(x==5){
                if(this->board[5][3] == this->board[5][4] && this->board[5][5] == this->board[5][4]){
                   this->play[1][1]=this->board[5][3];
                    this->m = 1;
                    this->n = 1;
                    return;
                }
            }
            if(x==y){
                if(this->board[3][3] == this->board[4][4] && this->board[5][5] == this->board[4][4]){
                    this->play[1][1]=this->board[3][3];
                    this->m = 1;
                    this->n = 1;
                    return;
                }
            }
        }
        
        if(x<=5 && x>=3 && y<=8 && y>=6){
            if(x+y==11){
                if(this->board[3][8] == this->board[4][7] && this->board[5][6] == this->board[4][7]){
                    this->play[1][2]=this->board[3][8];
                    this->m = 1;
                    this->n = 2;
                    return;
                }
            }
            if(y==6){
                if(this->board[3][6] == this->board[4][6] && this->board[5][6] == this->board[4][6]){
                    this->play[1][2]=this->board[3][6];
                    this->m = 1;
                    this->n = 2;
                    return;
                }
            }
            if(y==7){
                if(this->board[3][7] == this->board[4][7] &&  this->board[5][7] == this->board[4][7]){
                    this->play[1][2]=this->board[3][7];
                    this->m = 1;
                    this->n = 2;
                    return;
                }
            }
            if(y==8){
                if(this->board[3][8] == this->board[4][8] && this->board[5][8] == this->board[4][8]){
                    this->play[1][2]=this->board[3][8];
                    this->m = 1;
                    this->n = 2;
                    return;
                }
            }
            if(x==4){
                if(this->board[4][6] == this->board[4][7] && this->board[4][8] == this->board[4][7]){
                    this->play[1][2]=this->board[4][8];
                    this->m = 1;
                    this->n = 2;
                    return;
                }
            }
            if(x==3){
                if(this->board[3][6] == this->board[3][7] && this->board[3][8] == this->board[3][7]){
                    this->play[1][2]=this->board[3][8];
                    this->m = 1;
                    this->n = 2;
                    return;
                }
            }
            if(x==5){
                if(this->board[5][6] == this->board[5][7] && this->board[5][8] == this->board[5][7]){
                   this->play[1][2]=this->board[5][8];
                    this->m = 1;
                    this->n = 2;
                    return;
                }
            }
            if(x+3==y){
                if(this->board[3][6] == this->board[4][7] && this->board[5][8] == this->board[4][7]){
                    this->play[1][2]=this->board[3][6];
                    this->m = 1;
                    this->n = 2;
                    return;
                }
            }
        }
        
        if(x<=8 && x>=6 && y<=8 && y>=6){
            if(x+y==14){
                if(this->board[6][8] == this->board[7][7] && this->board[8][6] == this->board[7][7]){
                    this->play[2][2]=this->board[6][8];
                    this->m = 2;
                    this->n = 2;
                    return;
                }
            }
            if(y==6){
                if(this->board[6][6] == this->board[7][6] && this->board[8][6] == this->board[7][6]){
                    this->play[2][2]=this->board[6][6];
                    this->m = 2;
                    this->n = 2;
                    return;
                }
            }
            if(y==7){
                if(this->board[6][7] == this->board[7][7] &&  this->board[8][7] == this->board[7][7]){
                    this->play[2][2]=this->board[6][7];
                    this->m = 2;
                    this->n = 2;
                    return;
                }
            }
            if(y==8){
                if(this->board[6][8] == this->board[7][8] && this->board[8][8] == this->board[7][8]){
                    this->play[2][2]=this->board[6][8];
                    this->m = 2;
                    this->n = 2;
                    return;
                }
            }
            if(x==7){
                if(this->board[7][6] == this->board[7][7] && this->board[7][8] == this->board[7][7]){
                    this->play[2][2]=this->board[7][8];
                    this->m = 2;
                    this->n = 2;
                    return;
                }
            }
            if(x==6){
                if(this->board[6][6] == this->board[6][7] && this->board[6][8] == this->board[6][7]){
                    this->play[2][2]=this->board[6][8];
                    this->m = 2;
                    this->n = 2;
                    return;
                }
            }
            if(x==8){
                if(this->board[8][6] == this->board[8][7] && this->board[8][8] == this->board[8][7]){
                    this->play[2][2]=this->board[8][8];
                    this->m = 2;
                    this->n = 2;
                    return;
                }
            }
            if(x==y){
                if(this->board[6][6] == this->board[7][7] && this->board[8][8] == this->board[7][7]){
                    this->play[2][2]=this->board[8][8];
                    this->m = 2;
                    this->n = 2;
                    return;
                }
            }
        }
        
        if(x<=8 && x>=6 && y<=3 && y>=8){
            if(x+y==11){
                if(this->board[6][5] == this->board[7][4] && this->board[8][3] == this->board[7][4]){
                    this->play[2][1]=this->board[6][5];
                    this->m = 2;
                    this->n = 1;
                    return;
                   
                }
            }
            if(y==3){
                if(this->board[6][3] == this->board[7][3] && this->board[8][3] == this->board[7][3]){
                    this->play[2][1]=this->board[6][3];
                    this->m = 2;
                    this->n = 1;
                    return;
                }
            }
            if(y==4){
                if(this->board[6][4] == this->board[7][4] &&  this->board[8][4] == this->board[7][4]){
                    this->play[2][1]=this->board[6][4];
                    this->m = 2;
                    this->n = 1;
                    return;
                }
            }
            if(y==5){
                if(this->board[6][5] == this->board[7][5] && this->board[8][5] == this->board[7][5]){
                    this->play[2][1]=this->board[6][5];
                    this->m = 2;
                    this->n = 1;
                    return;
                }
            }
            if(x==7){
                if(this->board[7][3] == this->board[7][4] && this->board[7][5] == this->board[7][4]){
                    this->play[2][1]=this->board[7][4];
                    this->m = 2;
                    this->n = 1;
                    return;
                }
            }
            if(x==6){
                if(this->board[6][3] == this->board[6][4] && this->board[6][5] == this->board[6][4]){
                    this->play[2][1]=this->board[6][3];
                    this->m = 2;
                    this->n = 1;
                    return;
                }
            }
            if(x==8){
                if(this->board[8][3] == this->board[8][4] && this->board[8][5] == this->board[8][4]){
                    this->play[2][1]=this->board[8][5];
                    this->m = 2;
                    this->n = 1;
                    return;
                }
            }
            if(x==y+3){
                if(this->board[6][3] == this->board[7][4] && this->board[8][5] == this->board[7][4]){
                    this->play[2][1]=this->board[6][3];
                    this->m = 2;
                    this->n = 1;
                    return;
                }
            }
        } 
        
    }
    
    

    bool is_win(){
        this->check();
        int m = this->m;
        int n = this->n;
        if(play[m][n]==0 || m>3 || n>3){
            return false;
        }
        if(m+n==2){
            if(this->play[0][2] == this->play[1][1] && this->play[2][0] == this->play[1][1]){
               return true;
            }
        }
        if(n==0){
            if(this->play[0][0] == this->play[1][0] && this->play[2][0] == this->play[1][0]){
                return true;
            }
        }
        if(n==1){
            if(this->play[0][1] == this->play[1][1]  && this->play[2][1] == this->play[1][1]){
                return true;
            }
        }
        if(n==2){
            if(this->play[0][2] == this->play[1][2] && this->play[2][2] == this->play[1][2]){
                return true;
              
            }
        }
        if(m==1){
            if(this->play[1][0] == this->play[1][1]  && this->play[1][2] == this->play[1][1]){
                return true;
            }
        }
        if(m==0){
            if(this->play[0][0] == this->play[0][1]  && this->play[0][2] == this->play[0][1]){
                return true;
            }
        }
        if(m==2){
            if(this->play[2][0] == this->play[2][1]  && this->play[2][2] == this->play[2][1]){
               return true;
        }
        }
        if(m==n){
            if(this->play[0][0] == this->play[1][1]  && this->play[2][2] == this->play[1][1]){
                return true;;
            }
        }
        return false;
    }
    bool is_draw(){
        //int x = 2;
        /*for(int i = 0 ; i < 3 ; i++){
            for(int j = 0 ; j < 3 ; j++){
                if(this->board[i][j]==0){
                    return false;
                }
            }
            x--;
        }*/
        return false;
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
        while(x>8 || x<0 || y>8 || y<0){
            cout << "Invalid CHOICE, PLEASE TRY AGAIN\n";
            cin >> x >> y;
        }
    }
};

#endif //_BOARDGAME_CLASSES_H
