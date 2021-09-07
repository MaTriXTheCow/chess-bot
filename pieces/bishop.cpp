class Bishop : public Piece {
private:
  Pixel** bishopImage;

public:
  using Piece::Piece;

  Bishop(bool clr, Square* s) {
    SetColor(clr);
    SetSquare(s);
    SetValue(3);
    SetType(BISHOP);
  };

  void GetLegalMoves(Coordinates* legalMoves, bool* succeeded) {
    if(HasCacheForTurn(boardG -> GetTurn())) {
      GetLegalMovesCache(legalMoves, succeeded);
      return;
    }

    Coordinates currentRow = GetSquare() -> GetPosition();
    int step = 1;
    bool directions[4] = {true, true, true, true};

    int currentIndex = 0;

    while(directions[0] || directions[1] || directions[2] || directions[3]) {
      for(int i = 0; i < 4; i++) {
        if(!directions[i]) continue;

        int upDown = ((i == 0 || i == 1) ? 1 : -1) * step;
        int rightLeft = ((i == 0 || i == 3) ? 1 : -1) * step;

        Coordinates checkCoordinates = currentRow.MakeNewCoordinatesAdd(rightLeft, upDown);

        if(!checkCoordinates.IsInBounds(0,0,8,8)) {
          directions[i] = false;
          continue;
        }

        Square* checkSq = boardG -> GetSquareFromCoordBoard(checkCoordinates);

        if(!(checkSq -> HasPiece())) {
          legalMoves[currentIndex] = checkCoordinates;
          succeeded[currentIndex] = true;

          currentIndex++;
          continue;
        }

        Piece* checkPiece = checkSq -> GetPiece();

        if((checkPiece -> GetColor()) != GetColor()) {
          legalMoves[currentIndex] = checkCoordinates;
          succeeded[currentIndex] = true;

          currentIndex++;
        }

        directions[i] = false;
      }

      step++;
    }

    SetLegalMovesCache(legalMoves, succeeded, boardG -> GetTurn());
  }
};
