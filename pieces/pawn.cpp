class Pawn : public Piece {
private:
  bool isFirstMove;
  Pixel** pawnImage;

  Coordinates legalMovesCache[4];
  bool legalMovesSuccededCache[4];
  int legalMovesLastTurnCalled;

public:
  using Piece::Piece;

  Pawn(bool clr, Square* square) {
    SetColor(clr);
    SetSquare(square);
    SetValue(1);
    SetType(PAWN);

    isFirstMove = true;
  };

  void GetLegalMoves(Coordinates *legalMoves, bool *succeeded) {
    if(HasCacheForTurn(boardG -> GetTurn())) {
      GetLegalMovesCache(legalMoves, succeeded);
      return;
    }

    Coordinates currentRow = GetSquare() -> GetPosition();

    int directionForward = (GetColor() == playingAs) ? 1 : -1;

    Coordinates stepForward = currentRow.MakeNewCoordinatesAdd(0, directionForward);

    if(!(boardG -> GetSquareFromCoordBoard(stepForward) -> HasPiece())) {
      legalMoves[0] = stepForward;
      succeeded[0] = true;

      if(isFirstMove) {
        stepForward = stepForward.MakeNewCoordinatesAdd(0, directionForward);
        if(!(boardG -> GetSquareFromCoordBoard(stepForward) -> HasPiece())) {
          legalMoves[1] = stepForward;
          succeeded[1] = true;
        }
      }
    }

    Coordinates rightDiagStep = currentRow.MakeNewCoordinatesAdd(1, directionForward);
    Coordinates leftDiagStep = currentRow.MakeNewCoordinatesAdd(-1, directionForward);

    if(boardG -> GetSquareFromCoordBoard(rightDiagStep) -> HasPiece() && rightDiagStep.IsInBounds(0,0,8,8)) {
      if(boardG -> GetSquareFromCoordBoard(rightDiagStep) -> GetPiece() -> GetColor() != GetColor()) {
        legalMoves[2] = rightDiagStep;
        succeeded[2] = true;
      }
    }

    if(boardG -> GetSquareFromCoordBoard(leftDiagStep) -> HasPiece() && leftDiagStep.IsInBounds(0,0,8,8)) {
      if(boardG -> GetSquareFromCoordBoard(leftDiagStep) -> GetPiece() -> GetColor() != GetColor()) {
        legalMoves[3] = leftDiagStep;
        succeeded[3] = true;
      }
    }

    SetLegalMovesCache(legalMoves, succeeded, boardG -> GetTurn());
  }
};
