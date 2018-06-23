class Triangle
class OpaqueTriangle extends Triangle

class Renderer {
    def accept(a: Triangle) {
        println("Accepted Triangle!")
    }
}

class OpaqueRenderer extends Renderer {
    def accept(a: OpaqueTriangle) {
        println("Accepted OpaqueTriangle!")
    }
}

object Main {
    def main(args: Array[String]) {
        val a: OpaqueTriangle = new OpaqueTriangle
        val r: Renderer = new OpaqueRenderer
        
        r.accept(a) // Accepted Triangle!
    }
}
