object Main extends App {
    class A {
        def m(x: Int) {
            println("Int")
        }
    }

    class B extends A {
        def m(x: Any) {
            println("Any")
        }
    }

    class C {
        def m(x: Int) {
            println("Int")
        }
        def m(x: Any) {
            println("Any")
        }
    }

    val x = new B
    //x.m(1)   // Compile error
    x.m("abc") // Any

    val y = new C
    y.m(1)     // Int
    y.m("abc") // Any
}
