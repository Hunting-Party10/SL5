#include<iostream>
#include<stdio.h>
class NQueen {
private:
  int board_size;
  int *chessboard;
  int queens;
  int toArrayNotation(int ,int);
  bool isValid(int,int);
  bool placeQueen(int,int);
  bool isSafe(int,int);
  void revert(int,int);
  void displayBoard();
  void reset(){
    for (size_t i = 0; i < board_size * board_size; i++) {
      chessboard[i] = 0;
    }
  }
public:
  NQueen (int board_size, int queens){
    this->board_size = board_size;
    this->queens = queens;
    chessboard = new int[board_size * board_size];
    for (size_t i = 0; i < board_size * board_size; i++) {
      chessboard[i] = 0;
    }
  }
  bool simulate(int,int*,int,int);
  void simulateNQueens();
  void displayBoardClean();
};

void NQueen::displayBoard(){
  for (size_t i = 0; i < board_size*board_size; i++) {
    std::cout << chessboard[i]<<" ";
    if ((i+1)%(board_size) == 0)
      std::cout <<'\n';
  }
}

void NQueen::displayBoardClean(){
  for (size_t i = 0; i < board_size*board_size; i++) {
    if(chessboard[i] == -1)
    	std::cout<<"Q" <<" ";
    else
    	std::cout<<"_" <<" ";
    if ((i+1)%(board_size) == 0)
      std::cout <<'\n';
  }
}

void NQueen::simulateNQueens(){
  int positions[queens*2];
  int start_row = 0,start_col = 0;
  int c = 0;
  while(simulate(0, positions,start_row,start_col) == true)
  {
    c++;
    std::cout << "A Solution is found\n" << '\n';
    for (size_t i = 0; i < queens*2; i+=2){
      printf("Position :(%d,%d)\n",positions[i],positions[i+1] );
      chessboard[toArrayNotation(positions[i] -1,positions[i+1] -1)] = -1;
     }
    start_row = positions[0] - 1;
    start_col = positions[1];
    displayBoardClean();
    reset();
  }

  if (c==0) {
    std::cout << "No solutions found" << '\n';
  }

}

bool NQueen::simulate(int n, int *positions,int start_row,int start_col){
  if(n >= queens)
    return true;
  //std::cout << "Placing queen " <<n+1<<"\n\n\n";
  for (size_t i = start_row; i < board_size; i++) {
      for (size_t j = start_col; j < board_size; j++) {
        if (isSafe(i,j)) {
          placeQueen(i,j);
          //std::cout << "Queen "<< n+1<<" Placed" << '\n';
          //displayBoard();
          //std::cout << "\n\n" << '\n';
          positions[n*2] = i+1;
          positions[n*2 + 1] = j+1;
          if (simulate(n + 1,positions,0,0) != true){
            revert(i,j);
            //std::cout << "Queen "<< n+1<<" Removed" << '\n';
            //displayBoard();
            //std::cout << "\n\n" << '\n';
          }

          else
            return true;
        }
      }
  }
  //displayBoard();
  //std::cout << "No position found for queen " << n+1<< '\n';
  return false; //No postion found
}

int NQueen::toArrayNotation(int row,int col){
  return row*board_size + col;
}

bool NQueen::isValid(int row,int col){
  if (row >= 0 && row < board_size && col >= 0 && col < board_size)
    return true;
  return false;
}

bool NQueen::isSafe(int row,int col){
  if (chessboard[toArrayNotation(row,col)] != 0)
    return false;
  return true;
}

bool NQueen::placeQueen(int row,int col)
{
  if (!isValid(row, col) && !isSafe(row,col))
    return false;
    for (size_t i = 0; i < board_size; i++) {
      this->chessboard[toArrayNotation(i,col)] ++;
      this->chessboard[toArrayNotation(row,i)] ++;
    }
    int temp_col,temp_row;
    if(row > col){
        temp_row = row - col;
        temp_col = 0;
    }
    else
    {
      temp_row = 0;
      temp_col = col - row;
    }
    //std::cout <<temp_row<<","<<temp_col<< '\n';
    while (isValid(temp_row ,temp_col )){
      //std::cout << "Marking diagonals" << '\n';
      this->chessboard[toArrayNotation(temp_row++,temp_col++)]++;

    }

      temp_col = col;
      temp_row = row;
      while (isValid(--temp_row,++temp_col));
      temp_col--;
      temp_row++;
      while (isValid(temp_row,temp_col ))
        this->chessboard[toArrayNotation(temp_row++,temp_col--)]++;
  return true;
}

void NQueen::revert(int row,int col)
{
  for (size_t i = 0; i < board_size; i++) {
    this->chessboard[toArrayNotation(i,col)] --;
    this->chessboard[toArrayNotation(row,i)] --;
  }
  int temp_col,temp_row;
  if(row > col){
      temp_row = row - col;
      temp_col = 0;
  }
  else
  {
    temp_row = 0;
    temp_col = col - row;
  }
  while (isValid(temp_row ,temp_col ))
    this->chessboard[toArrayNotation(temp_row++,temp_col++)]--;
  temp_col = col;
  temp_row = row;
  while (isValid(--temp_row,++temp_col));
  temp_col--;
  temp_row++;
  while (isValid(temp_row ,temp_col ))
    this->chessboard[toArrayNotation(temp_row++,temp_col--)]--;

}

int main(int argc, char const *argv[]) {
  int c,q;
  std::cout << "Enter Size of chessboard :";
  std::cin >> c;
  std::cout << "Enter number of queens :";
  std::cin >> q;
  NQueen n(c,q);
  n.simulateNQueens();
  return 0;
 }
