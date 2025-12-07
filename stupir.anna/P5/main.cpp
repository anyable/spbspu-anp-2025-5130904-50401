namespace stupir
{
  struct point_t;
  struct rectangle_t;
  struct Shape;
  struct Rectangle;
}
struct point_t
{
  double x;
  double y;
};
struct rectangle_t
{
  double width;
  double height;
  point_t pos;
};
struct Shape
{
  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  virtual void move(point_t);
  virtual void move(double x, double y);
  virtual void scale(double k) = 0;
  virtual ~Shape();
};


