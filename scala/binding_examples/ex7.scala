class Aux {
    def doSomething(x: Double) {
        println("He thinks I am a Double: " + x)
    }
}

class Thing[T] extends Aux {
    def doSomething(x: T) {
        println("I am a T: " + x)
    }
    def do3(t: T) {
        doSomething(3)
        doSomething(t)
    }
}

object Main {
    def main(args: Array[String]) {
        val t = new Thing[Any]
        val a      = 4
        val b: Any = 5
  
        t.do3(a) // He thinks I am a Double: 3.0
                 // I am a T: 4
        t.do3(b) // He thinks I am a Double: 3.0
                 // I am a T: 5
    }
}
