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
  rectangle_t getFrameAll(rectangle_t * arr, size_t len);
  void printParametrFigures(Shape ** f, double * arrAreaFigure, rectangle_t * arrRecFigure,
    double & sumArea, const size_t numFigure);
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
  point_t t = f.getFrameRect().pos;
  point_t change = {p.x - t.x, p.y - t.y};
  f.move(p);
  f.scale(k);
  f.move(-change.x * 2, -change.y * 2);
}

std::ostream & stupir::operator<<(std::ostream & out, const rectangle_t & rec)
{
  out << "hight = " << rec.height << ", weight = " << rec.width << ", pos = {" ;
  out << rec.pos.x << ", " << rec.pos.y << "}\n";
  return out;
}

stupir::rectangle_t stupir::getFrameAll(rectangle_t * arr, size_t len)
{
  double maxX = arr[0].pos.x + arr[0].width / 2;
  double minX = arr[0].pos.x - arr[0].width / 2;
  double maxY = arr[0].pos.y + arr[0].height / 2;
  double minY = arr[0].pos.y - arr[0].height / 2;

  for (size_t i = 1; i < len; ++i)
  {
    double xMax = arr[i].pos.x + arr[i].width / 2;
    double xMin = arr[i].pos.x - arr[i].width / 2;
    double yMax = arr[i].pos.y + arr[i].height / 2;
    double yMin = arr[i].pos.y - arr[i].height / 2;
    maxX = (xMax > maxX) ? xMax : maxX;
    minX = (xMin < minX) ? xMin : minX;
    maxY = (yMax > maxY) ? yMax : maxY;
    minY = (yMin < minY) ? yMin : minY;
  }
  point_t newPos = {(maxX + minX) / 2, (maxY + minY) / 2};
  return {maxX - minX, maxY - minY, newPos};
}

void stupir::printParametrFigures(Shape ** f, double * arrAreaFigure, rectangle_t * arrRecFigure,
  double & sumArea, const size_t numFigure)
{
  for (size_t i = 0; i < numFigure; ++i)
    {
      double area = f[i] -> getArea();
      sumArea += area;
      arrAreaFigure[i] = f[i] -> getArea();
      arrRecFigure[i] = f[i] -> getFrameRect();
    }
    for (size_t i = 0; i < numFigure; ++i)
    {
      std::cout << "Area figure" << i + 1 << " = " << arrAreaFigure[i] << '\n';
      std::cout << "The bounding rectangle of figure" << i + 1 << " - " << arrRecFigure[i];
    }
    std::cout << "Summa areas all figure = " << sumArea << '\n';
    std::cout << "The bounding rectangle of all figure - ";
    std::cout << getFrameAll(arrRecFigure, numFigure) << '\n';
}

int main()
{
  namespace stu = stupir;
  int err = 0;
  stu::Shape ** f = nullptr;
  stu::rectangle_t * arrRecFigure = nullptr;
  double * arrAreaFigure = nullptr;
  size_t numFigure = 3;
  try
  {
    f = new stu::Shape * [numFigure]{nullptr};
    f[0] = new stu::Rectangle({0, 0}, 2, 3);
    f[1] = new stu::Square({3, 5}, 4);
    f[2] = new stu::Xquare({-1, 4}, 3);
    arrAreaFigure = new double[numFigure];
    arrRecFigure = new stu::rectangle_t[numFigure];
    double sumArea = 0;
    printParametrFigures(f, arrAreaFigure, arrRecFigure, sumArea, numFigure);

    double k = 0;
    stu::point_t scalePoint{0, 0};
    std::cin >> scalePoint.x >> scalePoint.y >> k;
    if (std::cin.fail())
    {
      throw std::logic_error("\nNot correct data for scale");
    }
    else if (k <= 0)
    {
      throw std::logic_error("\nNot correct coefficient for scale(negative)");
    }

    f[2] -> move({2, -6});
    f[0] -> scale(4.5);
    stu::scalePoint(scalePoint, k, *f[1]);

    delete [] arrAreaFigure;
    delete [] arrRecFigure;
    sumArea = 0;
    arrAreaFigure = new double[numFigure];
    arrRecFigure = new stu::rectangle_t[numFigure];
    std::cout << "\nAfter scale\n";
    printParametrFigures(f, arrAreaFigure, arrRecFigure, sumArea, numFigure);
  }
  catch (const std::logic_error & e)
  {
    std::cerr << e.what() << '\n';
    err = 1;
  }
  catch (const std::bad_alloc & e)
  {
    std::cerr << "Could not allocete memory\n";
    err = 1;
    if (!f)
    {
      return err;
    }
  }
  delete [] arrAreaFigure;
  delete [] arrRecFigure;
  delete f[0];
  delete f[1];
  delete f[2];
  delete [] f;
  return err;
}
