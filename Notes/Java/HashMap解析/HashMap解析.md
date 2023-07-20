## Lab06的实现——HashMap

> 哈希表（hash table）
> 也叫散列表，是一种非常重要的数据结构，应用场景及其丰富，许多缓存技术（比如memcached）的核心其实就是在内存中维护一张大的哈希表，本文会对java集合框架中HashMap的实现原理进行讲解，并对JDK7的HashMap源码进行分析。

**一、什么是哈希表**

在讨论哈希表之前，我们先大概了解下其他数据结构在新增，查找等基础操作执行性能

**数组**：采用一段连续的存储单元来存储数据。对于指定下标的查找，时间复杂度为O(1)；通过给定值进行查找，需要遍历数组，逐一比对给定关键字和数组元素，时间复杂度为O(n)，当然，对于有序数组，则可采用二分查找，插值查找，斐波那契查找等方式，可将查找复杂度提高为O($logn$)；对于一般的插入删除操作，涉及到数组元素的移动，其平均复杂度也为O(n)

**线性链表**：对于链表的新增，删除等操作（在找到指定操作位置后），仅需处理结点间的引用即可，时间复杂度为O(1)，而查找操作需要遍历链表逐一进行比对，复杂度为O(n)

**二叉树**：对一棵相对平衡的有序二叉树，对其进行插入，查找，删除等操作，平均复杂度均为O($logn$)。

**哈希表**：相比上述几种数据结构，在哈希表中进行添加，删除，查找等操作，性能十分之高，不考虑哈希冲突的情况下（后面会探讨下哈希冲突的情况），仅需一次定位即可完成，时间复杂度为O(1)，接下来我们就来看看哈希表是如何实现达到惊艳的常数阶O(1)的。

我们知道，数据结构的物理存储结构只有两种：**顺序存储结构**和**链式存储结构**（像栈，队列，树，图等是从逻辑结构去抽象的，映射到内存中，也这两种物理组织形式），而在上面我们提到过，在数组中根据下标查找某个元素，一次定位就可以达到，哈希表利用了这种特性，**哈希表的主干就是数组**。

**比如我们要新增或查找某个元素，我们通过把当前元素的关键字 通过某个函数映射到数组中的某个位置，通过数组下标一次定位就可完成操作。**
　　
这个函数可以简单描述为：**存储位置 = f(关键字)** ，这个函数f一般称为哈希函数，这个函数的设计好坏会直接影响到哈希表的优劣。举个例子，比如我们要在哈希表中执行插入操作：
插入过程如下图所示
![1024555-20161113180447499-1953916974.png](https://github.com/Eggze2/md_pic/blob/main/HashMap%E8%A7%A3%E6%9E%90/1024555-20161113180447499-1953916974.png?raw=true)

查找操作同理，先通过哈希函数计算出实际存储地址，然后从数组中对应地址取出即可。

对于HashMap而言，有如下几个重要属性（JDK 1.8标准）：

```java
public class HashMap<k,v> extends AbstractMap<k,v> implements Map<k,v>, Cloneable, Serializable {
    private static final long serialVersionUID = 362498820763181265L;
    static final int DEFAULT_INITIAL_CAPACITY = 1 << 4; // aka 16
    static final int MAXIMUM_CAPACITY = 1 << 30;//最大容量
    static final float DEFAULT_LOAD_FACTOR = 0.75f;//填充比
    //当add一个元素到某个位桶，其链表长度达到8时将链表转换为红黑树
    static final int TREEIFY_THRESHOLD = 8;
    static final int UNTREEIFY_THRESHOLD = 6;
    static final int MIN_TREEIFY_CAPACITY = 64;
    transient Node<k,v>[] table;//存储元素的数组
    transient Set<map.entry<k,v>> entrySet;
    transient int size;//实际存储的key-value键值对的个数
    transient int modCount;
    /**被修改的HashMap被改变的次数，由于HashMap非线程安全，在对HashMap进行迭代时，
	 *如果期间其他线程的参与导致HashMap的结构发生变化了（比如put，remove等操作），
	 *需要抛出异常ConcurrentModificationException
	 */
    int threshold;
    /**阈值，当table == {}时，该值为初始容量（初始容量默认为16）；当table被填充了，也就是为table分配内存空间后，threshold  	   *一般为 capacity*loadFactory。HashMap在进行扩容时需要参考threshold，后面会详细谈到
     */
    final float loadFactor;
    /**负载因子，代表了table的填充度有多少，默认是0.75
	 *加载因子存在的原因，还是因为减缓哈希冲突，如果初始桶为16，等到满16个元素才扩容，某些桶里可能就有不止一个元素了。
	 *所以加载因子默认为0.75，也就是说大小为16的HashMap，到了第13个元素，就会扩容成32。
     */
```



**哈希冲突**

然而万事无完美，**如果两个不同的元素，通过哈希函数得出的实际存储地址相同怎么办**？也就是说，当我们对某个元素进行哈希运算，得到一个存储地址，然后要进行插入的时候，发现已经被其他元素占用了，其实这就是所谓的**哈希冲突**，也叫**哈希碰撞**。前面我们提到过，哈希函数的设计至关重要，好的哈希函数会尽可能地保证 计算简单和散列地址分布均匀,但是，我们需要清楚的是，数组是一块连续的固定长度的内存空间，再好的哈希函数也不能保证得到的存储地址绝对不发生冲突。那么哈希冲突如何解决呢？哈希冲突的解决方案有多种:开放定址法（发生冲突，继续寻找下一块未被占用的存储地址），再散列函数法，链地址法，而HashMap即是采用了**链地址法**，也就是**数组+链表**的方式。

**二、HashMap的实现原理**

注：为了说明的便利性，我们先对少量数据，不涉及红黑树的情况进行解析。HashMap的主干是一个Entry数组。Entry是HashMap的基本组成单元，每一个Entry包含一个key-value键值对。（其实所谓Map其实就是保存了两个对象之间的映射关系的一种集合）

```java
//HashMap的主干数组，可以看到就是一个Entry数组，初始值为空数组{}，主干数组的长度一定是2的次幂。
//至于为什么这么做，后面会有详细分析。
transient Entry<K,V>[] table = (Entry<K,V>[]) EMPTY_TABLE;
```

Entry是HashMap中的一个静态内部类。代码如下

```java
    static class Entry<K,V> implements Map.Entry<K,V> {
        final K key;
        V value;
        Entry<K,V> next;//存储指向下一个Entry的引用，单链表结构
        int hash;//对key的hashcode值进行hash运算后得到的值，存储在Entry，避免重复计算

        /**
         * Creates new entry.
         */
        Entry(int h, K k, V v, Entry<K,V> n) {
            value = v;
            next = n;
            key = k;
            hash = h;
        }
```

所以，HashMap的总体结构如下：
![20181102221702492.png](https://github.com/Eggze2/md_pic/blob/main/HashMap%E8%A7%A3%E6%9E%90/20181102221702492.png?raw=true)

简单来说，**HashMap由数组+链表组成的**，数组是HashMap的主体，链表则是主要为了解决哈希冲突而存在的，如果定位到的数组位置不含链表（当前entry的next指向null）,那么查找，添加等操作很快，仅需一次寻址即可；如果定位到的数组包含链表，对于添加操作，其时间复杂度为O(n)，首先遍历链表，存在即覆盖，否则新增；对于查找操作来讲，仍需遍历链表，然后通过key对象的equals方法逐一比对查找。所以，性能考虑，**HashMap中的链表出现越少，性能才会越好。**

HashMap有4个构造器，其他构造器如果用户没有传入initialCapacity 和loadFactor这两个参数，会使用默认值

initialCapacity默认为16，loadFactory默认为0.75

我们看下其中一个

```java
public HashMap(int initialCapacity, float loadFactor) {
　　　　　//此处对传入的初始容量进行校验，最大不能超过MAXIMUM_CAPACITY = 1<<30(230)
        if (initialCapacity < 0)
            throw new IllegalArgumentException("Illegal initial capacity: " +
                                               initialCapacity);
        if (initialCapacity > MAXIMUM_CAPACITY)
            initialCapacity = MAXIMUM_CAPACITY;
        if (loadFactor <= 0 || Float.isNaN(loadFactor))
            throw new IllegalArgumentException("Illegal load factor: " +
                                               loadFactor);

        this.loadFactor = loadFactor;
        threshold = initialCapacity;
　　　　　
        init();//init方法在HashMap中没有实际实现，不过在其子类如 linkedHashMap中就会有对应实现
}
```

从上面这段代码我们可以看出，在常规构造器中，没有为数组table分配内存空间（有一个入参为指定Map的构造器例外），**而是在执行put操作的时候才真正构建table数组**

OK,接下来我们来看看put操作的实现

```java
public V put(K key, V value) {
        //如果table数组为空数组{}，进行数组填充（为table分配实际内存空间），入参为threshold，
        //此时threshold为initialCapacity 默认是1<<4(24=16)
        if (table == EMPTY_TABLE) {
            inflateTable(threshold);
        }
       //如果key为null，存储位置为table[0]或table[0]的冲突链上
        if (key == null)
            return putForNullKey(value);
        int hash = hash(key);//对key的hashcode进一步计算，确保散列均匀
        int i = indexFor(hash, table.length);//获取在table中的实际位置
        for (Entry<K,V> e = table[i]; e != null; e = e.next) {
        //如果该对应数据已存在，执行覆盖操作。用新value替换旧value，并返回旧value
            Object k;
            if (e.hash == hash && ((k = e.key) == key || key.equals(k))) {
                V oldValue = e.value;
                e.value = value;
                e.recordAccess(this);
                return oldValue;
            }
        }
        modCount++;//保证并发访问时，若HashMap内部结构发生变化，快速响应失败
        addEntry(hash, key, value, i);//新增一个entry
        return null;
}
```

inflateTable这个方法用于为主干数组table在内存中分配存储空间，通过roundUpToPowerOf2(toSize)可以确保capacity为大于或等于toSize的最接近toSize的二次幂，比如toSize=13, 则capacity=16; to_size=16, capacity=16; to_size=17, capacity=32.

```java
private void inflateTable(int toSize) {
        int capacity = roundUpToPowerOf2(toSize);//capacity一定是2的次幂
        /**此处为threshold赋值，取capacity*loadFactor和MAXIMUM_CAPACITY+1的最小值，
        capaticy一定不会超过MAXIMUM_CAPACITY，除非loadFactor大于1 */
        threshold = (int) Math.min(capacity * loadFactor, MAXIMUM_CAPACITY + 1);
        table = new Entry[capacity];
        initHashSeedAsNeeded(capacity);
}
```

roundUpToPowerOf2中的这段处理使得数组长度一定为2的次幂，Integer.highestOneBit是用来获取最左边的bit（其他bit位为0）所代表的数值.

```java
 private static int roundUpToPowerOf2(int number) {
     // assert number >= 0 : "number must be non-negative";
     return number >= MAXIMUM_CAPACITY
         ? MAXIMUM_CAPACITY
         : (number > 1) ? Integer.highestOneBit((number - 1) << 1) : 1;
 }
```

hash函数

```java
/**这是一个神奇的函数，用了很多的异或，移位等运算
对key的hashcode进一步进行计算以及二进制位的调整等来保证最终获取的存储位置尽量分布均匀*/
final int hash(Object k) {
    int h = hashSeed;
    if (0 != h && k instanceof String) {
        return sun.misc.Hashing.stringHash32((String) k);
    }

    h ^= k.hashCode();

    h ^= (h >>> 20) ^ (h >>> 12);
    return h ^ (h >>> 7) ^ (h >>> 4);
}

//Integer类型的 HashCode ,就是value本身
public static int hashCode(int value) {
    return value;
}
 
//HashMap中的hash(), 小于2^16的值的hashCode都是其本身
static final int hash(Object key) {
    int h;
    return (key == null) ? 0 : (h = key.hashCode()) ^ (h >>> 16);
}
```

以上hash函数计算出的值，通过indexFor进一步处理来获取实际的存储位置

```java
/**
 * 返回数组下标
 */
static int indexFor(int h, int length) {
    return h & (length-1);
}
```

h&（length-1）保证获取的index一定在数组范围内，举个例子，默认容量16，length-1=15，h=18,转换成二进制计算为index=2。位运算对计算机来说，性能更高一些（HashMap中有大量位运算）

```
        1  0  0  1  0
    &   0  1  1  1  1
    __________________
        0  0  0  1  0    = 2
```

所以最终存储位置的确定流程是这样的：
![20181102214046362.png](https://github.com/Eggze2/md_pic/blob/main/HashMap%E8%A7%A3%E6%9E%90/20181102214046362.png?raw=true)

再来看看addEntry的实现：

```java
void addEntry(int hash, K key, V value, int bucketIndex) {
    if ((size >= threshold) && (null != table[bucketIndex])) {
        resize(2 * table.length);//当size超过临界阈值threshold，并且即将发生哈希冲突时进行扩容
        hash = (null != key) ? hash(key) : 0;
        bucketIndex = indexFor(hash, table.length);
    }

    createEntry(hash, key, value, bucketIndex);
}
```

通过以上代码能够得知，**当发生哈希冲突并且size大于阈值的时候，需要进行数组扩容，扩容时，需要新建一个长度为之前数组2倍的新的数组，然后将当前的Entry数组中的元素全部传输过去，扩容后的新数组长度为之前的2倍，所以扩容相对来说是个耗资源的操作。**

**三、为何HashMap的数组长度一定是2的次幂？**

我们来继续看上面提到的resize方法

```java
void resize(int newCapacity) {
    Entry[] oldTable = table;
    int oldCapacity = oldTable.length;
    if (oldCapacity == MAXIMUM_CAPACITY) {
        threshold = Integer.MAX_VALUE;
        return;
    }

    Entry[] newTable = new Entry[newCapacity];
    transfer(newTable, initHashSeedAsNeeded(newCapacity));
    table = newTable;
    threshold = (int)Math.min(newCapacity * loadFactor, MAXIMUM_CAPACITY + 1);
}
```

如果数组进行扩容，数组长度发生变化，而存储位置 index = h&(length-1),index也可能会发生变化，需要重新计算index，我们先来看看transfer这个方法

```java
void transfer(Entry[] newTable, boolean rehash) {
    int newCapacity = newTable.length;
    //for循环中的代码，逐个遍历链表，重新计算索引位置，将老数组数据复制到新数组中去（数组不存储实际数据，所以仅仅是拷贝引用而已）
    for (Entry<K,V> e : table) {
        while(null != e) {
            Entry<K,V> next = e.next;
            if (rehash) {
                e.hash = null == e.key ? 0 : hash(e.key);
            }
            int i = indexFor(e.hash, newCapacity);
            //将当前entry的next链指向新的索引位置,newTable[i]有可能为空，有可能也是个entry链，如果是entry链，直接在链表头部插入。
            e.next = newTable[i];
            newTable[i] = e;
            e = next;
        }
    }
}
```

这个方法将老数组中的数据逐个链表地遍历，扔到新的扩容后的数组中，我们的数组索引位置的计算是通过 对key值的hashcode进行hash扰乱运算后，再通过和 length-1进行位运算得到最终数组索引位置。

HashMap的数组长度一定保持2的次幂，比如16的二进制表示为 10000，那么length-1就是15，二进制为01111，同理扩容后的数组长度为32，二进制表示为100000，length-1为31，二进制表示为011111。从下图可以我们也能看到这样会保证低位全为1，而扩容后只有一位差异，也就是多出了最左位的1，这样在通过 h&(length-1)的时候，只要h对应的最左边的那一个差异位为0，就能保证得到的新的数组索引和老数组索引一致(大大减少了之前已经散列良好的老数组的数据位置重新调换)，个人理解。

![1024555-20161115215812138-679881037.png](https://github.com/Eggze2/md_pic/blob/main/HashMap%E8%A7%A3%E6%9E%90/1024555-20161115215812138-679881037.png?raw=true)

还有，数组长度保持2的次幂，length-1的低位都为1，会使得获得的数组索引index更加均匀

![1024555-20161116001404732-625340289.png](https://github.com/Eggze2/md_pic/blob/main/HashMap%E8%A7%A3%E6%9E%90/1024555-20161116001404732-625340289.png?raw=true)
我们看到，上面的&运算，高位是不会对结果产生影响的（hash函数采用各种位运算可能也是为了使得低位更加散列)，我们只关注低位bit，如果低位全部为1，那么对于h低位部分来说，任何一位的变化都会对结果产生影响，也就是说，要得到index=21这个存储位置，h的低位只有这一种组合。这也是数组长度设计为必须为2的次幂的原因。
![1024555-20161116001717560-1455096254.png](https://github.com/Eggze2/md_pic/blob/main/HashMap%E8%A7%A3%E6%9E%90/1024555-20161116001717560-1455096254.png?raw=true)
如果不是2的次幂，也就是低位不是全为1此时，要使得index=21，h的低位部分不再具有唯一性了，哈希冲突的几率会变的更大，同时，index对应的这个bit位无论如何不会等于1了，而对应的那些数组位置也就被白白浪费了。

**get方法**：

```java
 public V get(Object key) {
     //如果key为null,则直接去table[0]处去检索即可。
     if (key == null)
         return getForNullKey();
     Entry<K,V> entry = getEntry(key);
     return null == entry ? null : entry.getValue();
}
```

get方法通过key值返回对应value，如果key为null，直接去table[0]处检索。我们再看一下getEntry这个方法

```java
final Entry<K,V> getEntry(Object key) { 
    if (size == 0) {
        return null;
    }
    //通过key的hashcode值计算hash值
    int hash = (key == null) ? 0 : hash(key);
    //indexFor (hash&length-1) 获取最终数组索引，然后遍历链表，通过equals方法比对找出对应记录
    for (Entry<K,V> e = table[indexFor(hash, table.length)];
         e != null;
         e = e.next) {
        Object k;
        if (e.hash == hash && 
            ((k = e.key) == key || (key != null && key.equals(k))))
            return e;
    }
    return null;
}
```

可以看出，get方法的实现相对简单，key(hashcode)–>hash–>indexFor–>最终索引位置，找到对应位置table[i]，再查看是否有链表，遍历链表，通过key的equals方法比对查找对应的记录。要注意的是，有人觉得上面在定位到数组位置之后然后遍历链表的时候，e.hash == hash这个判断没必要，仅通过equals判断就可以。其实不然，试想一下，如果传入的key对象重写了equals方法却没有重写hashCode，而恰巧此对象定位到这个数组位置，如果仅仅用equals判断可能是相等的，但其hashCode和当前对象不一致，这种情况，根据Object的hashCode的约定，不能返回当前对象，而应该返回null，后面的例子会做出进一步解释。

**四、重写equals方法需同时重写hashCode方法**

这是一个老生常谈的问题，“重写equals时也要同时覆盖hashcode”，举个小例子来看看，如果重写了equals而不重写hashcode会发生什么样的问题

```java
public class MyTest {
    private static class Person{
        int idCard;
        String name;

        public Person(int idCard, String name) {
            this.idCard = idCard;
            this.name = name;
        }
        @Override
        public boolean equals(Object o) {
            if (this == o) {
                return true;
            }
            if (o == null || getClass() != o.getClass()){
                return false;
            }
            Person person = (Person) o;
            //两个对象是否等值，通过idCard来确定
            return this.idCard == person.idCard;
        }

    }
    public static void main(String []args){
        HashMap<Person,String> map = new HashMap<Person, String>();
        Person person = new Person(1234,"乔峰");
        //put到hashmap中去
        map.put(person,"天龙八部");
        //get取出，从逻辑上讲应该能输出“天龙八部”
        System.out.println("结果:"+map.get(new Person(1234,"萧峰")));
    }
}

实际输出结果：null
```

尽管在进行get和put操作的时候，使用的key从逻辑上讲是等值的（通过equals比较是相等的），但由于没有重写hashCode方法，所以put操作时，key(hashcode1)–>hash–>indexFor–>最终索引位置 ，而通过key取出value的时候 key(hashcode1)–>hash–>indexFor–>最终索引位置，由于hashcode1不等于hashcode2，导致没有定位到一个数组位置而返回逻辑上错误的值null（也有可能碰巧定位到一个数组位置，但是也会判断其entry的hash值是否相等，上面get方法中有提到。）

所以，在重写equals的方法的时候，必须注意重写hashCode方法，同时还要保证通过equals判断相等的两个对象，调用hashCode方法要返回同样的整数值。而如果equals判断不相等的两个对象，其hashCode可以相同（只不过会发生哈希冲突，应尽量避免）。

**五、JDK1.8中HashMap的性能优化**

在JDK1.6，JDK1.7中，HashMap采用位桶+链表实现，即使用链表处理冲突，同一hash值的链表都存储在一个链表里。但是当位于一个桶中的元素较多，即hash值相等的元素较多时，通过key值依次查找的效率较低。而JDK1.8中，HashMap采用位桶+链表+红黑树实现，当链表长度超过阈值（8）时，将链表转换为红黑树，这样大大减少了查找时间。在jdk1.8版本后，java对HashMap做了改进，在链表长度大于8的时候，将后面的数据存在红黑树中（包括之前的），以加快检索速度。

 JDK1.8HashMap的红黑树是这样解决的:

如果某个桶中的记录过大的话（当前是TREEIFY_THRESHOLD = 8），HashMap会动态的使用一个专门的treemap实现来替换掉它。这样做的结果会更好，是O(logn)，而不是O(n)。

前面产生冲突的那些KEY对应的记录只是简单的追加到一个链表后面，这些记录只能通过遍历来进行查找。但是超过这个阈值后HashMap开始将列表升级成一个二叉树，使用哈希值作为树的分支变量，如果两个哈希值不等，但指向同一个桶的话，较大的那个会插入到右子树里。如果哈希值相等，HashMap希望key值是实现了Comparable接口的，这样它可以按照顺序来进行插入。实现原理前文已详细描述，此处不再赘述。

上面说过HashMap可以看成是一个大的数组，然后每个数组元素的类型是Node类型，源码里定义如下：

```java
transient Node<K,V>[] table;
```

注意Node类还有两个子类：TreeNode和Entry

```java
TreeNode <K,V> extends Entry<K,V> extends Node<K,V>
```

链表即为Node类，而红黑树正是TreeNode类

在无参构造函数时，JDK8仅仅是初始化loadFactor让其等于默认值。Map通过构造函数new一个HashMap时，其内部存储数据的数组并没有实例化，而是在PUT方法中去做了一件判断table是否为空的事，若为空就会调用resize()方法，resize()第一次调用就会实例化一个长度为DEFAULT_INITIAL_CAPACITY的Node[]。

![20190720113958166.png](https://github.com/Eggze2/md_pic/blob/main/HashMap%E8%A7%A3%E6%9E%90/20190720113958166.png?raw=true)

**1、 put(K key,V value)**

```java
//对外开发使用
public V put(K key, V value) {
    return putVal(hash(key), key, value, false, true);
}
//存值的真正执行者
final V putVal(int hash, K key, V value, boolean onlyIfAbsent, boolean evict) {
    
    //定义一个数组，一个链表，n永远存放数组长度，i用于存放key的hash计算后的值，即key在数组中的索引        
    Node<K,V>[] tab; Node<K,V> p; int n, i;
    
    //判断table是否为空或数组长度为0，如果为空则通过resize()实例化一个数组并让tab作为其引用，并且让n等于实例化tab后的长度        
    if ((tab = table) == null || (n = tab.length) == 0)
        n = (tab = resize()).length;
    
    //根据key经过hash()方法得到的hash值与数组最大索引做与运算得到当前key所在的索引值，并且将当前索引上的Node赋予给p并判断是否	该Node是否存在
    if ((p = tab[i = (n - 1) & hash]) == null)
        tab[i] = newNode(hash, key, value, null);//若tab[i]不存在，则直接将key-value插入该位置上。
    
        //该位置存在数据的情况  
    else {
        Node<K,V> e; K k; //重新定义一个Node，和一个k
        
	    // 该位置上数据Key计算后的hash等于要存放的Key计算后的hash并且该位置上的Key等于要存放的Key     
        if (p.hash == hash &&((k = p.key) == key || (key != null && key.equals(k))))
            e = p;	//true，将该位置的Node赋予给e
	else if (p instanceof TreeNode)  //判断当前桶类型是否是TreeNode
	    //ture，进行红黑树插值法,写入数据
            e = ((TreeNode<K,V>)p).putTreeVal(this, tab, hash, key, value); 	
        else {	
	    //false, 遍历当前位置链表
            for (int binCount = 0; ; ++binCount) {
                //查找当前位置链表上的表尾，表尾的next节点必然为null,找到表尾将数据赋给下一个节点
                if ((e = p.next) == null) {
                     p.next = newNode(hash, key, value, null);	//是，直接将数据写到下个节点
                    // 如果此时已经到第八个了，还没找个表尾，那么从第八个开始就要进行红黑树操作
		    if (binCount >= TREEIFY_THRESHOLD - 1)
                        //红黑树插值具体操作，注意：该方法不一定会将该位置的Node转换成红黑树
                        treeifyBin(tab, hash);	
                        break;
                }
                //如果当前位置的key与要存放的key的相同，直接跳出，不做任何操作   
                if (e.hash == hash && ((k = e.key) == key || (key != null && key.equals(k))))
                    break;
                //将下一个给到p进行逐个查找节点为空的Node
		p = e;
            }
        }
        //如果e不为空，即找到了一个去存储Key-value的Node 
	if (e != null) { // existing mapping for key
            V oldValue = e.value;    
	    if (!onlyIfAbsent || oldValue == null)
                e.value = value;
            afterNodeAccess(e);
            return oldValue;
        }
    }
    ++modCount;
    //当最后一次调整之后Size大于了临界值，需要调整数组的容量
    if (++size > threshold)
        resize();
    afterNodeInsertion(evict);
    return null;
}
```
**2、 get(K key)**

```java
//对外公开方法
public V get(Object key) {
        Node<K,V> e;
        return (e = getNode(hash(key), key)) == null ? null : e.value;
    }
 
//实际逻辑控制方法
final Node<K,V> getNode(int hash, Object key) {
	//定义相关变量
    Node<K,V>[] tab; Node<K,V> first, e; int n; K k;
	//保证Map中的数组不为空，并且存储的有值，并且查找的key对应的索引位置上有值
    if ((tab = table) != null && (n = tab.length) > 0 && (first = tab[(n - 1) & hash]) != null) {
        // always check first node 第一次就找到了对应的值
	if (first.hash == hash && ((k = first.key) == key || (key != null && key.equals(k))))
            return first;
	//判断下一个节点是否存在
	if ((e = first.next) != null) {
            //true,检测是否是TreeNode
            if (first instanceof TreeNode)
                return ((TreeNode<K,V>)first).getTreeNode(hash, key); //通过TreeNode的get方法获取值
            //否，遍历链表
	    do {
		//判断下一个节点是否是要查找的对象
                if (e.hash == hash && ((k = e.key) == key || (key != null && key.equals(k))))
                    return e;
            }while ((e = e.next) != null);
        }
    }//未找到，返回null
    return null;
 }
```

**3、resize()**

```java
final Node<K,V>[] resize() {
    Node<K,V>[] oldTab = table;
    int oldCap = (oldTab == null) ? 0 : oldTab.length;	//未扩容时数组的容量
    int oldThr = threshold;
    int newCap, newThr = 0;//定义新的容量和临界值
    //当前Map容量大于零，非第一次put值
    if (oldCap > 0) {
        if (oldCap >= MAXIMUM_CAPACITY) {	//超过最大容量:2^30
			//临界值等于Integer类型的最大值 0x7fffffff=2^31-1
            threshold = Integer.MAX_VALUE;	
            return oldTab;
        }
		//当前容量在默认值和最大值的一半之间
        else if ((newCap = oldCap << 1) < MAXIMUM_CAPACITY && oldCap >= DEFAULT_INITIAL_CAPACITY)
            newThr = oldThr << 1;	//新临界值为当前临界值的两倍
    }
	//当前容量为0，但是当前临界值不为0，让新的容量等于当前临界值
    else if (oldThr > 0) 
        newCap = oldThr;
    //当前容量和临界值都为0,让新的容量为默认值，临界值=初始容量*默认加载因子
	else {
        newCap = DEFAULT_INITIAL_CAPACITY;
        newThr = (int)(DEFAULT_LOAD_FACTOR * DEFAULT_INITIAL_CAPACITY);
    }
	//如果新的临界值为0
    if (newThr == 0) {
        float ft = (float)newCap * loadFactor;
        newThr = (newCap < MAXIMUM_CAPACITY && ft < (float)MAXIMUM_CAPACITY ? (int)ft : Integer.MAX_VALUE);
    }
	//临界值赋值
    threshold = newThr;
    //扩容table
    Node<K,V>[] newTab = (Node<K,V>[])new Node[newCap];
    table = newTab;
    if (oldTab != null) {
        for (int j = 0; j < oldCap; ++j) {
            Node<K,V> e;
            if ((e = oldTab[j]) != null) {
                oldTab[j] = null;
                if (e.next == null)
                    newTab[e.hash & (newCap - 1)] = e;//此时newCap = oldCap*2
                else if (e instanceof TreeNode) //节点为红黑树，进行切割操作
                    ((TreeNode<K,V>)e).split(this, newTab, j, oldCap);
                else { //链表的下一个节点还有值，但节点位置又没有超过8
                    //lo就是扩容后仍然在原地的元素链表
					//hi就是扩容后下标为  原位置+原容量  的元素链表，从而不需要重新计算hash。
					Node<K,V> loHead = null, loTail = null;
                    Node<K,V> hiHead = null, hiTail = null;
                    Node<K,V> next;
                    //循环链表直到链表末再无节点
					do {
                        next = e.next;
						//e.hash&oldCap == 0 判断元素位置是否还在原位置
                        if ((e.hash & oldCap) == 0) {
                            if (loTail == null)
                                loHead = e;
                            else
                                loTail.next = e;
                            loTail = e;
                        }
                        else {
                            if (hiTail == null)
                                hiHead = e;
                            else
                                hiTail.next = e;
                            hiTail = e;
                        }
                    } while ((e = next) != null);
					//循环链表结束，通过判断loTail是否为空来拷贝整个链表到扩容后table
                    if (loTail != null) {
                       loTail.next = null;
                        newTab[j] = loHead;
                    }
                    if (hiTail != null) {
                        hiTail.next = null;
                        newTab[j + oldCap] = hiHead;
                    }
                }
            }
        }
    }
    return newTab;
}
```

**六、HashMap常用方法**

1. put(Object key, Object value) //添加键值对

2. putAll(Collection c) //添加指定的映射关系到目标映射关系

3. get(Object key) //根据键来获取对应的值

4. getOrDefault(Object key, V defaultValue) //map中存在key则使用对应的value，否则使用defaultValue

5. containsKey(Object key) //是否有指定key的映射

6. containsValue(Object value) //是否有指定value的映射

7. remove(Object key) //删除该键值对

8. values() //返回所有值，返回形式为Collection

9. isEmpty() //测试映射是否为空

10. size() //返回大小

**七、HashMap遍历**

**方式一：**
使用entrySet遍历
①通过迭代器遍历

```java
Iterator iter = map1.entrySet().iterator(); 
while (iter.hasNext()) { 
	Map.Entry entry = (Map.Entry) iter.next(); 

	String key = (String) entry.getKey();
	String val = (String)entry.getValue();

	System.out.println(key + "--" + val);
}
```

②通过foreach循环遍历

```java
for(Map.Entry<String, String> map:map1.entrySet()) {
	System.out.println(map.getKey() + ":" + map.getValue());
}
```

**方式二：**
使用keySet遍历
①通过迭代器遍历

```java
Set<String> keys = map1.keySet();
Iterator<String> it1 = keys.iterator();
while(it1.hasNext()){
	String key = it1.next();
	System.out.println(key + "--" + map1.get(key));
}
```

②通过foreach循环遍历

```java
Set<String> keys = map1.keySet();
for (String key : keys) {
	System.out.println(key + " " + map1.get(key));
}
```
