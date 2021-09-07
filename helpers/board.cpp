class Board {
private:
  Square* boardArray[8][8] = {{nullptr}};
  bool isCheck;
  bool isCheckMate;

  unsigned int turn;

  Square* currentClicked;

  void initBoard() {
    char startingBoard[8][8] = {
      {'R','B','N','K','Q','N','B','R'},
      {'P','P','P','P','P','P','P','P'},
      {' ',' ',' ',' ',' ',' ',' ',' '},
      {' ',' ',' ',' ',' ',' ',' ',' '},
      {' ',' ',' ',' ',' ',' ',' ',' '},
      {' ',' ',' ',' ',' ',' ',' ',' '},
      {'P','P','P','P','P','P','P','P'},
      {'R','B','N','Q','K','N','B','R'}
    };

    int piecesCount = 0;

    for(int r = 0; r < 8; r++) {
      for(int c = 0; c < 8; c++) {
        boardArray[r][c] = new Square(r,c);
        char pieceChar = startingBoard[r][c];

        if(pieceChar == ' ') continue;

        bool colorPiece = ((piecesCount < 16) == playingAs);

        boardArray[r][c] -> SetPiece(Piece::MakePieceFromChar(pieceChar, colorPiece, boardArray[r][c]));

        piecesCount++;
      }
    }
  };

public:
  Board() {
    isCheck = false;
    isCheckMate = false;
    turn = 0;

    currentClicked = nullptr;

    initBoard();
  }

  void Destroy() {
    for(int i = 0; i < 8; i++) {
      for(int j = 0; j < 8; j++) {
        boardArray[i][j] -> GetPiece() -> Destroy();
      }
    }
  }

  Square* GetSquare(int row, int col) {
    return boardArray[row][col];
  }

  unsigned int GetTurn() {
    return turn;
  }

  bool IsKingChecked(bool color) {
    
  }

  bool HasPiece(int row, int col) {
    return GetSquare(row,col) -> HasPiece();
  }

  void Move(Piece* piece, Coordinates destination) {

  }

  Square* GetSquareFromCoordBoard(Coordinates pos) {
    return GetSquare(pos.y, pos.x);
  }

  Square* GetSquareFromCoordPixels(Coordinates pos) {
    int row = pos.y/80;
    int col = pos.x/80;

    return GetSquare(row, col);
  }

  Square* GetClicked() {
    return currentClicked;
  }

  bool SetClicked(Square* sq) {
    if(currentClicked != nullptr) currentClicked -> ToggleClicked();

    currentClicked = (sq -> ToggleClicked()) ? sq : nullptr;

    return currentClicked != nullptr;
  }

  bool HasClicked() {
    return currentClicked != nullptr;
  }

  void PrintBoard() {
    std::string line = "-----------------";
    std::cout << line << "\n";

    for(int row = 0; row < 8; row++) {
      std::string s = "|||||||||||||||||";

      for(int col = 0; col < 8; col++) {
        int index = col*2 + 1;

        if(!HasPiece(row,col)) {
          s[index] = ' ';

          continue;
        }

        s[index] = enumToString[GetSquare(row, col) -> GetPiece() -> GetType()];
      }

      std::cout << s << "\n";
    }

    std::cout << line << "\n";
  }

};
