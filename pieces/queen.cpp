class Queen : public Piece {
private:
  Pixel** queenImage;

public:
  using Piece::Piece;

  Queen(bool clr, Square* s) {
    SetColor(clr);
    SetSquare(s);
    SetValue(9);
    SetType(QUEEN);
  };

  void GetLegalMoves(Coordinates* legalMoves, bool* succeeded) {
    if(HasCacheForTurn(boardG -> GetTurn())) {
      GetLegalMovesCache(legalMoves, succeeded);
      return;
    }

    Coordinates currentRow = GetSquare() -> GetPosition();
    int step = 1;
    bool directions[8] = {true, true, true, true, true, true, true, true};

    int currentIndex = 0;

    while(directions[0] || directions[1] || directions[2] || directions[3] || directions[4] || directions[5] || directions[6] || directions[7]) {
      for(int i = 0; i < 8; i++) {
        if(!directions[i]) continue;

        int upDown = 0;
        int rightLeft = 0;

        if(i == 0 || i == 1 || i == 7) {
          upDown = step;
        }

        if(i == 3 || i == 4 || i == 5) {
          upDown = -step;
        }

        if(i == 1 || i == 2 || i == 3) {
          rightLeft = step;
        }

        if(i == 5 || i == 6 || i == 7) {
          rightLeft = -step;
        }

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

        directions[i] = false;

        Piece* checkPiece = checkSq -> GetPiece();

        if(checkPiece -> GetColor() != GetColor()) {
          legalMoves[currentIndex] = checkCoordinates;
          succeeded[currentIndex] = true;

          currentIndex++;
        }
      }

      step++;
    }

    SetLegalMovesCache(legalMoves, succeeded, boardG -> GetTurn());
  }
};
