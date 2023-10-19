### JAVA类方法的调用

- 一、静态方法调用其他方法：
- - 1. 静态方法调用非静态方法
  - 2.静态方法调用静态方法
- 二、非静态方法调用其他方法
- - 1.非静态方法在同一类内调用其他方法
  - 2.非静态方法在不同类之间调用其他方法



注：调用方法——调用另一方法的方法
被调用方法——被调用的方法

# 一、静态方法调用其他方法：

## 1. 静态方法调用非静态方法

无论是否在同一类内，均需要通过对象调用

```java
//Test类
package main;

public class Test {

    public void IsSon1(){//非静态方法
        System.out.println("java大爷，你成功调用了你非静态方法里的儿子1");
    }

    public static void main(String[] args) {
        Test son1=new Test();
        son1.IsSon1();//静态方法通过对象调用此类中的非静态方法
        Son son=new Son();//静态方法通过对象调用Son类中的非静态方法
        son.IsSon();
    }
}
12345678910111213141516
//Son类
package main;

public class Son {
    public  void IsSon(){
        System.out.println("java大爷，你成功的调用了你另一个类里的儿子");
    }//Son类里的非静态方法
}
12345678
```

![输出结果](https://img-blog.csdnimg.cn/20181102223403347.png)

## 2.静态方法调用静态方法

同一类内直接调用，不同类内直接通过类名.方法名（参数表）调用

```java
package main;

public class Test {

    public static void IsSon2(){//静态方法
        System.out.println("java大爷，你成功调用了你静态方法里的儿子2");
    }

    public static void main(String[] args) {
        IsSon2();//静态方法直接调用类内的静态方法
        Son.IsSon3();//静态方法通过类名直接调用Son类中的静态方法
    }
}
12345678910111213
package main;

public class Son {
    public  static void IsSon3(){
        System.out.println("java大爷，你成功的调用了你另一个类里的静态儿子3");
    }//Son类里的静态方法
}

12345678
```

![输出结果](https://img-blog.csdnimg.cn/20181102225621578.png)

# 二、非静态方法调用其他方法

## 1.非静态方法在同一类内调用其他方法

在同一类内，非静态方法可以直接调用静态方法和非静态方法

```java
package main;

public class Test {

    public void Son1(){//非静态方法
        System.out.println("java大爷，你成功调用了你非静态方法里的儿子1");
    }
    public static void Son2(){//静态方法
        System.out.println("java大爷，你成功调用了你静态方法里的儿子2");
    }
    public void alloutput(){
        Son1();//非静态方法直接调用类内的非静态方法△
        Son2();//非静态方法直接调用类内的静态方法△
    }
    public static void main(String[] args) {
        Test test = new Test();
        test.alloutput();//前边已学静态方法通过对象调用非静态方法
    }
}
12345678910111213141516171819
```

![输出结果](https://img-blog.csdnimg.cn/20181102230539569.png)

## 2.非静态方法在不同类之间调用其他方法

在不同类之间，非静态方法需要通过对象才能调用非静态方法。
非静态方法既可以通过对象调用静态方法又可以通过类名直接调用（由于对象的调用方式属于非静态调用方式，所以建议使用类名直接调用静态方法）

```java
package main;

public class Test {

    public void output(){
        Son.IsSon1();//通过类名直接调用Son类中的静态方法，不建议使用对象调用静态方法
        Son son = new Son();
        son.IsSon2();//通过对象调用Son类中的非静态方法
    }

    public static void main(String[] args) {
        //同一类中的静态方法调用非静态方法output，前边已经涉及到
        Test test = new Test();
        test.output();
    }
}
12345678910111213141516
package main;

public class Son {

    public  static void IsSon1(){//Son类里的静态方法
        System.out.println("java大爷，你成功的调用了你另一个类里的静态儿子1");
    }

    public  void IsSon2(){//Son类里的非静态方法
        System.out.println("java大爷，你成功的调用了你另一个类里的非静态儿子2");
    }
}

12345678910111213
```

![输出结果](https://img-blog.csdnimg.cn/20181102232235488.png)

## 静态方法（static method）

> 与静态成员变量一样，属于类本身，在类装载的时候被装载到内存中，不自动进行销毁，会一直存在内存中，直到JVM关闭；

## 非静态方法（non-static method）

> 又称实例化方法，属于实例对象，实例化之后才会分配内存，必须通过类的实例来引用，当实例对象被JVM回收之后，也跟着消失

> ## 静态方法和实例方法的区别
>
> ###  1.生命周期
>
> 静态方法的生命周期从进程创建时就开始，一直到进程结束，所以说静态方法是全局的，贯穿整个进程
>
> 实例方法的生命周期，从实例化对象开始，一直到实例化对象被注销回收之后结束
>
> 所以实例方法的生命周期是短于静态方法的生命周期，这也是实例方法中不能调用静态方法的原因
>
> ###  2.调用方式
>
> 在外部调用静态方法时，可以使用 “类名.方法名”的方式，也可以使用“对象.方法名”的方式，也就是说调用静态方法时无需创建对象
>
> 实例方法只能使用“对象.方法名的方式”
>
> ## 3.访问限制
>
> 静态方法在访问本类的成员时，只允许访问静态成员（即静态变量和静态方法），而不允许访问实例成员变量和实例方法；而实例方法则无此限制
>
> 实例成员变量是属于某个对象的，在静态方法执行时，并不一定存在该对象；同理，如果允许静态方法访问实例成员方法，就间接的可以访问实例成员变量，所以也不能访问实例成员方法；基于同样的道理，静态方法中也不能使用关键字this
>
> ### 4.执行顺序
>
> 当一个class文件被ClassLoader load进入JVM之后，方法指令保存在Stack中，此时Heap区并没有数据。然后程序技术器开始执行指令，如果是静态方法，直接依次执行指令代码，当然此时指令代码是不能访问Heap数据区的；如果是实例方法（实例方法有一个隐含的传入参数，该参数是JVM给它的，这个参数就是实例对象在Stack中的内存地址，因此实例方法才可以找到在Heap中属于自己的数据），则在调用前必须实例化该对象，在Heap中分配数据，并将Stack中的内存指针通过JVM的隐含参数传给实例方法。若不实例化直接调用，由于隐含参数没有值，会报错。
>
> e.g: new Person().eat();