Piece* Piece::MakePieceFromChar(char pieceChar, bool colorPiece, Square* sq) {
  switch(pieceChar) {
    case 'P': {
      return new Pawn(colorPiece, sq);
    } break;

    case 'R': {
      return new Rook(colorPiece, sq);
    } break;

    case 'B': {
      return new Bishop(colorPiece, sq);
    } break;

    case 'N': {
      return new Knight(colorPiece, sq);
    } break;

    case 'K': {
      return new King(colorPiece, sq);
    } break;

    case 'Q': {
      return new Queen(colorPiece, sq);
    } break;

    return NULL;
  }
}
