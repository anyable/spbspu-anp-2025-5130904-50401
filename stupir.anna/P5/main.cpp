#include <iostream>
#include <cmath>
namespace stupir
{
  struct point_t;
  struct rectangle_t;
  struct seg_t;
  struct Shape;
  struct Rectangle;
  struct Square;
  struct Xquare;
  void scalePoint(point_t, double, Shape &);
  std::ostream & operator<<(std::ostream &, const rectangle_t &);
  rectangle_t getFrameAll(rectangle_t &, rectangle_t &, rectangle_t &);
}

struct stupir::point_t
{
  double x;
  double y;
};

struct stupir::rectangle_t
{
  double width;
  double height;
  point_t pos;
};

struct stupir::Shape
{
  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  virtual void move(point_t) = 0;
  virtual void move(double , double) = 0;
  virtual void scale(double) = 0;
  virtual ~Shape() = default;
};

struct stupir::Rectangle : Shape
{
  Rectangle(point_t center, double weight, double hight);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(point_t) override;
  void move(double x, double y) override;
  void scale(double k) override;
  protected:
    point_t c_;
    double w_;
    double h_;
};

void stupir::Rectangle::scale(double k)
{
  h_ *= k, w_ *= k;
}

void stupir::Rectangle::move(double x, double y)
  {
    c_.x += x;
    c_.y += y;
  }

void stupir::Rectangle::move(point_t p)
{
  c_ = p;
}

stupir::Rectangle::Rectangle(point_t center, double weight, double hight):
  Shape(), c_(center), w_(weight), h_(hight)
  {}

double stupir::Rectangle::getArea() const
{
  return w_ * h_;
}

stupir::rectangle_t stupir::Rectangle::getFrameRect() const
{
  return {w_, h_, c_};
}

struct stupir::Square : Rectangle
{
  Square(point_t , double);
};

stupir::Square::Square(point_t center, double len):
  Rectangle(center, len, len)
  {}

struct stupir::Xquare : Square
{
  Xquare(point_t, double);
  rectangle_t getFrameRect() const override;
};

stupir::Xquare::Xquare(point_t center, double len):
  Square(center, len)
  {}

stupir::rectangle_t stupir::Xquare::getFrameRect() const
{
  double d = std::sqrt(w_ * w_ + h_ * h_);
  return {d , d , c_};
}

void stupir::scalePoint(point_t p, double k, Shape & f)
{
  point_t mid = f.getFrameRect().pos;
  point_t end = {mid.x + p.x, mid.y + p.y};
  f.move(p.x, p.y);
  f.scale(k);
  point_t begin = {mid.x * 2 - end.x, mid.y * 2 - end.y};
  f.move(begin.x, begin.y);
}

std::ostream & stupir::operator<<(std::ostream & out, const rectangle_t & rec)
{
  out << "hight = " << rec.height << ", weight = " << rec.width << ", pos = {" ;
  out << rec.pos.x << ", " << rec.pos.y << "}\n";
  return out;
}

stupir::rectangle_t stupir::getFrameAll(rectangle_t & f1, rectangle_t & f2, rectangle_t & f3)
{
  double maxX = std::max(std::max(f1.pos.x, f2.pos.x), f3.pos.x);
  double minX = std::min(std::min(f1.pos.x, f2.pos.x), f3.pos.x);
  double maxY = std::max(std::max(f1.pos.y, f2.pos.y), f3.pos.y);
  double minY = std::min(std::min(f1.pos.y, f2.pos.y), f3.pos.y);
  double newWidht = std::abs(maxX - minX);
  double newHight = std::abs(maxY - minY);
  point_t newPos = {maxY + maxX / 2, minX + minY / 2};
  return {newWidht, newHight, newPos};
}

int main()
{
  namespace stu = stupir;
  double k = 0;
  stu::point_t scalePoint{0, 0};
  std::cin >> scalePoint.x >> scalePoint.y >> k;
  if (std::cin.fail())
  {
    std::cerr << "\nNot correct data for scale\n";
    return 1;
  }
  else if (k <= 0)
  {
    std::cerr << "\nNot correct coefficient for scale(negative)\n";
    return 1;
  }
  int err = 0;
  stu::Shape ** f = nullptr;
  try
  {
    f = new stu::Shape * [3]{nullptr};
    f[0] = new stu::Rectangle({0, 0}, 2, 3);
    f[1] = new stu::Square({3, 5}, 12);
    f[2] = new stu::Xquare({-1, 4}, 5);
    double areaRec = f[0] -> getArea();
    double areaSq = f[1] -> getArea();
    double areaXq = f[2] -> getArea();
    stu::rectangle_t recRec = f[0] -> getFrameRect();
    stu::rectangle_t recSq = f[1] -> getFrameRect();
    stu::rectangle_t recXq = f[2] -> getFrameRect();

    std::cout << "Area rectangle = " << areaRec << '\n';
    std::cout << "The bounding rectangle of rectangle - " << recRec;
    std::cout << "Area square = " << areaSq << '\n';
    std::cout << "The bounding rectangle of square - " << recSq;
    std::cout << "Area xquare = " << areaXq << '\n';
    std::cout << "The bounding rectangle of xquare - " << recXq;
    std::cout << "Summa areas all figure = " << areaRec + areaSq + areaXq << '\n';
    std::cout << "The bounding rectangle of all figure - ";
    std::cout << stu::getFrameAll(recRec, recSq, recXq);

    f[0] -> move({2, -6});
    f[1] -> scale(4.5);
    stu::scalePoint({6, -2}, 3.1, *f[2]);
    double areaRecCh = f[0] -> getArea();
    double areaSqCh = f[1] -> getArea();
    double areaXqCh = f[2] -> getArea();
    stu::rectangle_t recRecCh = f[0] -> getFrameRect();
    stu::rectangle_t recSqCh = f[1] -> getFrameRect();
    stu::rectangle_t recXqCh = f[2] -> getFrameRect();

    std::cout << "Area rectangle = " << areaRecCh << '\n';
    std::cout << "The bounding rectangle of rectangle - " << recRecCh;
    std::cout << "Area square = " << areaSqCh << '\n';
    std::cout << "The bounding rectangle of square - " << recSqCh;
    std::cout << "Area xquare = " << areaXqCh << '\n';
    std::cout << "The bounding rectangle of xquare - " << recXqCh;
    std::cout << "Summa areas all figure = " << areaRecCh + areaSqCh + areaXqCh << '\n';
    std::cout << "The bounding rectangle of all figure - ";
    std::cout << stu::getFrameAll(recRecCh, recSqCh, recXqCh);
  }
  catch(...)
  {
    std::cerr << "Could not allocete memory\n";
    err = 1;
    if (!f)
    {
      return err;
    }
  }
  delete f[0];
  delete f[1];
  delete f[2];
  delete [] f;
  return err;
}
