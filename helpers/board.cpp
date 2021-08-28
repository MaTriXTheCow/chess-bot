class Board {
private:
  Square* boardArray[8][8] = {{nullptr}};
  bool isCheck;
  bool isCheckMate;

  unsigned int turn;

  Square* clicked;

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
    turn = 1;

    clicked = nullptr;

    initBoard();
  }

  Square* GetSquare(int row, int col) {
    return boardArray[row][col];
  }

  bool HasPiece(int row, int col) {
    return GetSquare(row,col) -> HasPiece();
  }

  void Move(Piece* piece, Square* destination) {

  }

  Square* GetSquareFromCoord(Coordinates pos) {
    int row = pos.y/80;
    int col = pos.x/80;

    return GetSquare(row, col);
  }

  Square* GetClicked() {
    return clicked;
  }

  void SetClicked(Square* sq) {
    if(clicked != nullptr) clicked -> ToggleClicked();

    clicked = (sq -> ToggleClicked()) ? sq : nullptr;
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
