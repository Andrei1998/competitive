object Printer {
    def print(e: Int) {
        println("Have an Int: " + e)
    }
    def print(e: Any) {
        println("Have an Any: " + e)
    }
}

class Container[T](val elem: T) {
    def show = Printer.print(elem)
}

object Main {
    def main(args: Array[String]) {
        val t = new Container[Int](10) // Have an Any: 10
        t.show
    }
}
