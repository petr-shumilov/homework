import math._
def find_roots(coefficients: Array[Double]): List[Double] = {
  def quadratic(quad: Array[Double]): List[Double] = {
    val a: Double = quad(0)
    val b: Double = quad(1)
    val c: Double = quad(2)
    val D: Double = pow(b,2) - 4 * a * c
    if (D >= 0) {
      List((-b + sqrt(D)) / (2 * a), (-b - sqrt(D)) / (2 * a))
    } else {
      List()
    }
  }
  def cubic(cub: Array[Double]): List[Double] = {
    val i: Double = cub(0)
    val a: Double = cub(1) / i
    val b: Double = cub(2) / i
    val c: Double = cub(3) / i
    val Q: Double = (a * a - 3 * b) / 9
    val R: Double = (2 * a * a * a - 9 * a * b + 27 * c) / 54
    if (pow(Q,3) - pow(R,2) > 0) {
      val phi: Double = acos(R / pow(Q, 1.5)) / 3
      List(-2 * sqrt(Q) * cos(phi) - a / 3,
        -2 * sqrt(Q) * cos(phi - 2 * Pi / 3) - a / 3,
        -2 * sqrt(Q) * cos(phi + 2 * Pi / 3) - a / 3)
    } else {
      val m: Double = -signum(R) * pow(abs(R) + sqrt(pow(R,2) - pow(Q,3)), 1/3)
      var n: Double = 0
      if (m != 0) {
        n = Q / m
      }
      if (m == n) {
        List((m + n) - a / 3, -m - a / 3)
      } else {
        List((m + n) - a / 3)
      }
    }
  }
  if (coefficients(0) == 0) {
    quadratic(coefficients.tail)
  } else {
    cubic(coefficients)
  }
}
var coef : Array[Double] = Array(1, -12, 41, -30)
find_roots(coef)
