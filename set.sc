// init predicate
type Set = Int => Boolean

// set range bound
val bound = 1000

// elem in set?
def contains(s: Set, elem: Int): Boolean = {
    s(elem)
}

// make Set by single elem
def singletonSet(elem: Int): Set = {
  x => (elem == x)
}

def union(s: Set, t: Set): Set = {
  d => contains(s, d) || contains(t, d)
}

def intersect(s: Set, t: Set): Set = {
  d => contains(s, d) && contains(t, d)
}

// xor
def diff(s: Set, t: Set): Set = {
  d => contains(s,d) && !contains(t,d)
}

def filter(s: Set, p: Int => Boolean): Set = {
  x => contains(s, x) && p(x)
}

def forall(s: Set, p: Int => Boolean): Boolean = {
  def iter(a: Int): Boolean = {
    if (a > bound) {
      true
    } else if (contains(s, a) && !p(a)){
      false
    } else {
      iter(a + 1)
    }
  }
  iter(-bound)
}

def exists(s: Set, p: Int => Boolean): Boolean = {
  !forall(s, x => !p(x))
}

def map(s: Set, f: Int => Int): Set = {
  def iter(a: Int): Set = {
    if (a > bound){
      x => false
    } else if (contains(s, a)) {
      union(singletonSet(f(a)),iter(a+1))
    } else {
      iter(a + 1)
    }
  }
  iter(-bound)
}

def toString(s: Set): String = {
  val xs = for (i <- -bound to bound if contains(s, i)) yield i
  xs.mkString("{", ",", "}")
}

val test : Set = (x: Int) => if (x % 2 == 0) true else false
toString(test)