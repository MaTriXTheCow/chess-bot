class Rook : public Piece {
private:
  bool hasMoved;
  Pixel** rookImage;

public:
  using Piece::Piece;

  Rook(bool clr, Square* s) {
    SetColor(clr);
    SetSquare(s);
    SetValue(5);
    SetType(ROOK);

    hasMoved = false;
  };

  void GetLegalMoves(Coordinates* legalMoves, bool *succeeded) {
    if(HasCacheForTurn(boardG -> GetTurn())) {
      GetLegalMovesCache(legalMoves, succeeded);
      return;
    }

    Coordinates currentRow = GetSquare() -> GetPosition();
    bool directions[4] = {true,true,true,true};
    int step = 0;

    int currentIndex = 0;

    for(int i = 0; i < 14; i++) {
      succeeded[i] = false;
    }

    while(directions[0] || directions[1] || directions[2] || directions[3]) {
      for(int i = 0; i < 4; i++) {
        if(!(directions[i])) continue;

        int upDownDir = 0;
        int leftRightDir = 0;

        if(i == 0 || i == 2) {
          upDownDir = 1-i + (1-i)*step;
        }

        if(i == 1 || i == 3) {
          leftRightDir = 2-i + (2-i)*step;
        }

        Coordinates checkPos = currentRow.MakeNewCoordinatesAdd(leftRightDir, upDownDir);

        if(!checkPos.IsInBounds(0,0,8,8)) {
          directions[i] = false;
          continue;
        }

        //std::cout << checkPos.x << " " << checkPos.y << "\n";

        Square* checkSq = boardG -> GetSquareFromCoordBoard(checkPos);

        if(!(checkSq -> HasPiece())) {
          succeeded[currentIndex] = true;
          legalMoves[currentIndex] = checkPos;

          currentIndex++;
          
          continue;
        }

        Piece* p = checkSq -> GetPiece();

        if((p -> GetColor()) != GetColor()) {
          succeeded[currentIndex] = true;
          legalMoves[currentIndex] = checkPos;

          currentIndex++;
        }

        directions[i] = false;

      }

      step++;
    }

    SetLegalMovesCache(legalMoves, succeeded, boardG -> GetTurn());
  }
};
