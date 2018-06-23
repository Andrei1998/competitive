class B[Char] {
    def m(x: Char) = println("It's a char: " + x)
}

object Main {
    def main(args: Array[String]) {
        val obj = new B[Int]
        
        obj.m(2)   // It's a char: 2
        obj.m('a') // It's a char: 97 
    }
}
