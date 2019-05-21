package hello;

public class HelloWorld {
  public static void main(String[] args) {
    ProfilePoint initial = new ProfilePoint();
    ProfilePoint goal = new ProfilePoint();
        goal.position = 1.0;
        goal.velocity = 0.0;
    
//    System.out.println(goal.position);

    Greeter greeter = new Greeter();
    System.out.println(greeter.sayHello(true, initial, goal));
  }
}
