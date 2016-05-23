def Binominal(k:Int, n:Int): Int = {
  if ((k == n) || (k == 0)) {
    1
  }
  else {
    Binominal(k, n - 1) + Binominal(k - 1, n - 1)
  }
}
//Binominal(3, 5)



