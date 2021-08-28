class Square;

enum pieceType {PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING};

const char enumToString[] = {
  'P',
  'N',
  'B',
  'R',
  'Q',
  'K',
};


const bool BLACK = false;
const bool WHITE = true;

class Piece {
private:
  int value;
  pieceType type;
  Square* square;
  bool color;
  Pixel** PPMimages[12];

public:
  Piece() {
    PPMimages[0] = reader -> ReadImage("images/pawn_white.ppm");
    PPMimages[1] = reader -> ReadImage("images/pawn_black.ppm");

    PPMimages[2] = reader -> ReadImage("images/knight_white.ppm");
    PPMimages[3] = reader -> ReadImage("images/knight_black.ppm");

    PPMimages[4] = reader -> ReadImage("images/bishop_white.ppm");
    PPMimages[5] = reader -> ReadImage("images/bishop_black.ppm");

    PPMimages[6] = reader -> ReadImage("images/rook_white.ppm");
    PPMimages[7] = reader -> ReadImage("images/rook_black.ppm");

    PPMimages[8] = reader -> ReadImage("images/queen_white.ppm");
    PPMimages[9] = reader -> ReadImage("images/queen_black.ppm");

    PPMimages[10] = reader -> ReadImage("images/king_white.ppm");
    PPMimages[11] = reader -> ReadImage("images/king_black.ppm");
  };

  pieceType GetType() {
    return type;
  }

  int GetValue();
  bool GetColor() {
    return color;
  }

  Square* GetSquare() {
    return square;
  }

  void SetSquare(Square* s) {
    square = s;
  }

  void SetValue(int val) {
    value = val;
  }

  void SetColor(bool clr) {
    color = clr;
  }

  void SetType(pieceType t) {
    type = t;
  }

  virtual int DrawPixel(Coordinates pixelCoord) {
    if(!pixelCoord.IsInBounds(0,0,80,80)) {
      return -1;
    }

    Pixel** pieceImage = PPMimages[type*2 + (int)(!color)];

    bool isSquareClicked = GetSquare() -> IsClicked();

    int r = pieceImage[79-pixelCoord.y][pixelCoord.x].r;
    int g = pieceImage[79-pixelCoord.y][pixelCoord.x].g;
    int b = pieceImage[79-pixelCoord.y][pixelCoord.x].b;

    if(IsTransparent(r,g,b)) {
      int squareColor = GetSquare() -> GetColor();

      if(isSquareClicked) {
        if(squareColor == whiteSq) return 0xf9f788;

        return 0xb7cb44;
      }


      return squareColor;
    }

    return (r << 16) + (g << 8) + b;
  }

  bool isMoveLegal(Square* s);

  static Piece* MakePieceFromChar(char pieceChar, bool colorPiece, Square* sq);
};
