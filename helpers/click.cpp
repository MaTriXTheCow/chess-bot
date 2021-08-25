class WindowClick {
private:
  bool clicked;
  Coordinates coord;

public:
  WindowClick() {

  }

  Coordinates GetCoordinates() {
    return coord;
  }

  bool CurrentClick() {
    clicked = false;
    return clicked;
  }

  void SetCoordinates(int x, int y) {
    coord.x = x;
    coord.y = y;
  }

  void SetClicked() {
    clicked = true;
  }
};
