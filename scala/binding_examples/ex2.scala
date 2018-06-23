class Food
class Bone extends Food


class Animal {
    def eat(m: Food) {
        println("Animal eats food!")
    }
    
    // How do the answers change if we include this piece of code?
    // def eat(o: Bone) {
    //     println("Animal eats bone!")
    // }
}

class Dog extends Animal {
    override def eat(m: Food) {
        println("The dog eats food!")
    }   

    def eat(o: Bone) {
        println("The dog eats bone!")
    }
}

object Main {
    def main(args: Array[String]) {
        val an: Animal = new Animal
        val d1: Animal = new Dog
        val d2: Dog    = new Dog        
        
        val f: Food  = new Food
        val b1: Food = new Bone
        val b2: Bone = new Bone

        an.eat(f)  // Animal eats food!
        an.eat(b1) // Animal eats food!
        an.eat(b2) // Animal eats food!

        d1.eat(f)  // The dog eats food!
        d1.eat(b1) // The dog eats food!
        d1.eat(b2) // The dog eats food!

        d2.eat(f)  // The dog eats food!
        d2.eat(b1) // The dog eats food!
        d2.eat(b2) // The dog eats bone!
    }
}
