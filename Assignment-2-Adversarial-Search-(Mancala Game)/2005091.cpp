#include <bits/stdc++.h>
using namespace std;

#define BINS 6 // no. of bins in mancala
#define STONES 4 // initial no. of stones in each bin
#define P0 0 // player 0
#define P1 1 // player 1
#define DEPTH 10
#define W1 3
#define W2 4
#define W3 3
#define W4 4
int HEURISTIC;

//depth 3 huris 2 player 1 jite

class Board {
    vector<vector<int>>board;
    vector<vector<pair<int,int>>>next_bin;

    void init_next_bin()
    {
        for(int j=1;j<BINS;j++){
            next_bin[1][j]={1,j+1};
        }
        next_bin[1][BINS]={1, 0};
        next_bin[1][0] = {0, BINS};

        for (int j = BINS; j > 0; j--) {
            next_bin[0][j] = {0, j-1};
        }
        next_bin[0][0] = {1, 1};
    }

public:
    Board() {
        board = vector<vector<int>>(2, vector<int>(BINS+1));
        next_bin = vector<vector<pair<int, int>>> (2, vector<pair<int, int>> (BINS+1));
        init_next_bin();
        for (int i = 0; i < 2; i++) {
            for (int j = 1; j <= BINS; j++) {
                board[i][j] = STONES;
            }
        }
    }


    void copy_board(Board &other) 
    {
        board = other.board;
    }

    bool check_valid_bin(int player, int bin)
    {
        if (player == P1) {
            return board[P1][bin];
        }
        return board[P0][BINS-bin+1];
    }

    void print() {
        for (int j = 0; j <= BINS; j++) {
            cout << board[0][j] << '\t';
        }
        cout << "\n\t";
        for (int j = 1; j <= BINS; j++) {
            cout << board[1][j] << '\t';
        }
        cout << board[1][0] << '\n';
    }

    int get_storage(int player) {
        return board[player][0];
    }

    int get_rem_stones(int player) 
    {
        int ans=0;
        for(int i=1;i<=BINS;i++)
        {
            ans+=board[player][i];
        }
        return ans;
    }

    pair<int,int> play_move(int player, int bin) 
    {
        int move_earned = 0;
        int stones_captured = 0;
        pair<int, int> curr;
        if (player == P1) {
            curr = make_pair(player, bin);
        }
        else {
            curr = make_pair(player,BINS-bin+1);
        }

        auto valTem=curr;
        auto x=valTem.first;
        auto y=valTem.second;

        int rem = board[x][y];
        board[x][y] = 0;
        while (rem) {
            curr = next_bin[curr.first][curr.second];
            auto valTem1=curr;
            auto xx=valTem1.first;
            auto yy=valTem1.second;
            ///////////////////////////////////////////////
            if(yy==0)
            {
                if(xx!=player)continue;
            }
            board[xx][yy]++;
            rem--;
        }
        if (curr == make_pair(player, 0)) {
            move_earned = 1;
        }
        else {
            auto valTem1=curr;
            auto xx=valTem1.first;
            auto yy=valTem1.second;
            if ((board[xx][yy] == 1) && (xx == player) && (board[xx^1][yy]!=0)) {
                board[player][0] += board[xx][yy] + board[xx^1][yy];
                stones_captured += board[xx][yy] + board[xx^1][yy];
                board[xx][yy] = 0;
                board[xx^1][yy] = 0;
            }
        }
        return {move_earned,stones_captured};
    }

    int get_score(int player) {
        return get_storage(player) + get_rem_stones(player);
    }

    bool check_game_end(int player) {
        for (int i = 1; i <= BINS; i++) {
            if (check_valid_bin(player, i)) {
                return false;
            }
        }
        return true;
    }
};


Board mainBoard;



void print_game_results()
{
    int s0=mainBoard.get_score(P0);
    int s1=mainBoard.get_score(P1);
    cout << "Game ended\n";
    cout << "Player 0: " << s0 << "\nPlayer 1: " << s1 << "\n";
    if (s0 > s1) {
        cout << "Player 0 wins";
    }
    else if (s0 < s1) {
        cout << "Player 1 wins";
    }
    else {
        cout << "Tie";
    }
    cout << "!\n";
    cout<<"Final Board"<<endl;
    mainBoard.print();
}



void moveOfHuman(int player)
{
    if(mainBoard.get_storage(0)>24 || mainBoard.get_storage(1)>24)
    {
        print_game_results();
        return;
    }
    if(mainBoard.check_game_end(player))
    {
        print_game_results();
        return;
    }
    if(mainBoard.check_game_end((player^1)))
    {
        print_game_results();
        return;
    }
    mainBoard.print();
    // cout<<"You are player:"<<player<<endl;
    // cout<<"Enter a bin number: ";
    int bin;
    // cin>>bin;

    while (1)
    {
        cout<<"You are player:"<<player<<endl;
        cout<<"Enter a bin number: ";
        cin>>bin;
        if(!mainBoard.check_valid_bin(player,bin))
        {
            cout<<"In your selected bin,value is zero"<<endl;
        }
        else break;
    }
    


    pair<int,int>tem=mainBoard.play_move(player,bin);
    cout<<tem.first<<" "<<tem.second<<endl;
    if(tem.first)
    {
        cout<<"testing"<<endl;
        moveOfHuman(player);
    }

}







///////////////////////////////////////////////
int heuristic_func1(Board board) {
    return board.get_storage(P0) - board.get_storage(P1);
}

int heuristic_func2(Board board) {
    return W1 * heuristic_func1(board) + W2 * (board.get_rem_stones(P0) - board.get_rem_stones(P1));
}

int heuristic_func3(Board board,int additional_move_earned) {
    return heuristic_func2(board) + W3 * additional_move_earned;
}

int heuristic_func4(Board board,int additional_move_earned,int stones_captured) {
    return heuristic_func3(board,additional_move_earned) + W4 * stones_captured;
}

int findOptimal(int player,int bin,Board board,int alpha,int beta,int additional_move_earned,int stones_captured,int depth){
    pair<int,int>tem=board.play_move(player,bin);

    if(depth==DEPTH)
    {
        // cout<<"///////////////////////////////////////////////"<<endl;
        if(HEURISTIC==1)return heuristic_func1(board);
        if(HEURISTIC==2)return heuristic_func2(board);
        if(HEURISTIC==3)return heuristic_func3(board,additional_move_earned);
        if(HEURISTIC==4)return heuristic_func4(board,additional_move_earned,stones_captured);
    }
    
    if(player==0)
    {
        int flag=0;
        for (int i = BINS; i >= 1; i--) {
            if (board.check_valid_bin(player, i)) {
                flag=1;
                int val;
                if(tem.first==1)
                {
                    if(player==0)val=findOptimal(player,i,board,alpha,beta,additional_move_earned+1,stones_captured,depth+1);
                    else val=findOptimal(player,i,board,alpha,beta,additional_move_earned,stones_captured,depth+1);
                }
                else 
                {
                    if(player==0)val=findOptimal(player^1,i,board,alpha,beta,additional_move_earned,stones_captured+tem.second,depth+1);
                    else val=findOptimal(player^1,i,board,alpha,beta,additional_move_earned,stones_captured,depth+1);
                }
                
                if(val>alpha)
                {
                    alpha=val;
                    if(val>beta)
                    {
                        return val;
                    }
                }
            }
        }
        if(flag==0)
        {
            // return board.get_score(player);
            if(HEURISTIC==1)return heuristic_func1(board);
            if(HEURISTIC==2)return heuristic_func2(board);
            if(HEURISTIC==3)return heuristic_func3(board,additional_move_earned);
            if(HEURISTIC==4)return heuristic_func4(board,additional_move_earned,stones_captured);
        }
        else return alpha;
    }
    else{
        int flag=0;
        for (int i = 1; i <= BINS; i++) {
            if (board.check_valid_bin(player, i)) {
                flag=1;
                int val;
                // if(tem.first==1)
                // {
                //     val=findOptimal(player,i,board,alpha,beta,additional_move_earned+1,stones_captured,depth+1);
                // }
                // else val=findOptimal(player^1,i,board,alpha,beta,additional_move_earned,stones_captured+tem.second,depth+1);
                if(tem.first==1)
                {
                    if(player==0)val=findOptimal(player,i,board,alpha,beta,additional_move_earned+1,stones_captured,depth+1);
                    else val=findOptimal(player,i,board,alpha,beta,additional_move_earned,stones_captured,depth+1);
                }
                else 
                {
                    if(player==0)val=findOptimal(player^1,i,board,alpha,beta,additional_move_earned,stones_captured+tem.second,depth+1);
                    else val=findOptimal(player^1,i,board,alpha,beta,additional_move_earned,stones_captured,depth+1);
                }
                if(val<beta)
                {
                    beta=val;
                    if(val<alpha)
                    {
                        return val;
                    }
                }
            }
        }
        if(flag==0)
        {
            // return board.get_score(player);
            if(HEURISTIC==1)return heuristic_func1(board);
            if(HEURISTIC==2)return heuristic_func2(board);
            if(HEURISTIC==3)return heuristic_func3(board,additional_move_earned);
            if(HEURISTIC==4)return heuristic_func4(board,additional_move_earned,stones_captured);
        }
        else return beta;
    }
}


void moveOfAi(int player)
{
    if(mainBoard.get_storage(0)>24 || mainBoard.get_storage(1)>24)
    {
        print_game_results();
        return;
    }
    if(mainBoard.check_game_end(player))
    {
        print_game_results();
        return;
    }
    if(mainBoard.check_game_end((player^1)))
    {
        print_game_results();
        return;
    }
    mainBoard.print();
    cout<<"You are player:"<<player<<endl;
    // cout<<"Enter a bin number: ";
    int bin;

    bin=-1;
    Board newBoard;
    newBoard.copy_board(mainBoard);
    int alpha=-1000000000;
    int beta=1000000000;

    if(player==0)
    {
        for (int i = BINS; i >= 1; i--) {
            if (newBoard.check_valid_bin(player, i)) {
                int tem=findOptimal(player,i,newBoard,alpha,beta,0,0,0);
                if(tem>alpha)
                {
                    alpha=tem;
                    bin=i;
                }
            }
        }
    }
    else{
        for (int i = 1; i <=BINS; i++) {
            if (newBoard.check_valid_bin(player, i)) {
                int tem=findOptimal(player,i,newBoard,alpha,beta,0,0,0);
                if(tem<beta)
                {
                    beta=tem;
                    bin=i;
                }
            }
        }
    }
    


    cout<<"Ai Moving bin:"<<bin<<endl;
    pair<int,int>tem=mainBoard.play_move(player,bin);
    // mainBoard.print();
    // cout<<tem.first<<" "<<tem.second<<endl;
    if(tem.first)
    {
        // cout<<"testing"<<endl;
        moveOfAi(player);
    }

}




void playHumanVsAi()
{
    int presentPlayer=0;
    while (1)
    {
        if(mainBoard.get_storage(0)>24 || mainBoard.get_storage(1)>24)
        {
            print_game_results();
            break;
        }
        if(mainBoard.check_game_end(presentPlayer))
        {
            print_game_results();
            break;
        }
        if(mainBoard.check_game_end((presentPlayer^1)))
        {
            print_game_results();
            break;
        }


        if(presentPlayer==0)
        {
            // moveOfHuman(presentPlayer);
            moveOfAi(presentPlayer);
        }
        else{
            moveOfAi(presentPlayer);
            // moveOfHuman(presentPlayer);
        }


        presentPlayer^=1;
    }
    
}


int main()
{
    cin>>HEURISTIC;
    playHumanVsAi();
    // mainBoard.print();
    // mainBoard.play_move(1,3);
    // // mainBoard.print();
    // Board tem;
    // tem.copy_board(mainBoard);
    // tem.print();
}