# Spring概述

## 1. 认识框架

* spring全家桶：
  * spring
  * springmvc
  * spring boot
  * spring cloud
* spring：出现是在2002左右，解决企业开发的难度。减轻对项目模块之间的管理，类和类之间的管理，帮助开发人员创建对象，管理对象之间的关系。spring核心技术：ioc、aop。能实现模块之间，类之间的解耦合。
* 依赖：类A中使用类B的属性或者方法，叫做类A依赖类B。

* 官网：https://spring.io



## 2. 框架内部模块

* Spring优点？
  1. 轻量
     * Spring框架使用的 jar 都比较小，一般在1M以下或者击败kb。Spring核心功能的所需的jar总共在3M左右。
     * Spring框架运行占用的资源少，运行效率高。不依赖其他jar。
  2. 针对接口编程，解耦合
     * Spring提供了Ioc控制翻转，有容器管理对象，对象的依赖关系。原来在程序代码中的对象创建方式，现在由容器完成。对象之间的依赖解耦合。
  3. AOP 编程的支持
     * 通过Spring提供的AOP功能，方便进行面向切面的编程，许多不容易用传统OOP实现的功能可以通过AOP轻松应付。
     * 在Spring中，开发人员可以从繁杂的事务管理代码中解脱处理，通过声明式的方式灵活的进行事务的管理，提高开发效率和质量。
  4. 方便集成各种优秀框架
     * Spring不排斥各种优秀的开源框架，相反Spring可以降低各种框架的使用难度，Spring提供了对各种优秀框架（如Struts、Hibernate、MyBatis）等的直接支持。简化框架的使用。Spring像插线板一样，其他框架是插头，可以容易的组合到一起。需要使用哪个框架，就把这个插头放入插线板。不需要可以轻易地移除。

# IOC控制反转

## 1. IOC概念

* 框架怎么学：框架是一个软件， 其它人写好的软件。

  1. 知道枢架能做什么，mybatis--访 问数据库，对 表中的数据执行增删改查。
  2. 框架的语法，框架要完成- 一个功能，需要一定的步骤支持的，
  3. 框架的内部实现，框架 内部怎么做。原理是什么。
  4. 通过学习，可以实现一个框架。

* spring的第一个核心功能IOC

  * IOC（Inversion of Control）：控制反转，是一个理论，概念，思想。
  * 描述的：把对象的创建，赋值，管理工作都交给代码之外的容器实现，也就是对象的创建是有其它外部资源完成。
  * 控制：创建对象，对象的属性赋值，对象之间的关系管理。
  * 正转：由开发人员在代码中，使用new构造方法创建对象，开发 人员主动管理对象。
  * 反转：把原来的开发人员管理，创建对象的权限转移给代码之外的容器实现。由容器代替开发人员管理对象、创建对象、给属性赋值。
  * 容器：是一个服务器软件，一个框架（Spring）

  * 为什么要使用IOC：目的就是减少对代码的改动，也能实现不同的功能。实现解耦合。

  * java中创建对象的方式：

    1. 构造方法，new Student();
    2. 反射
    3. 序列化
    4. 克隆
    5. ioc：容器创建对象。
    6. 动态代理

  * IOC的体现

    * servlet 

      1. :创建类 继承Httpservelt

      2. 在web.xml 注册servlet，使用

         \<servlet-nane\> myservlet \</servlet-nano\>
         \<servelt-class\>xxx .MyServ1et1\</servlet-class\>

      3. 没有创建servlet对象， 没有 MyServlet myservlet = new MnyServlet();

      4. Servlet 是Tomcat服务器它能你创建的。Tomcat也称为容器。Tomcat作为容器：里面存放的有Servlet对象，Listener ，Pilter对象。

  * IOC的技术实现

    * DI（Dependency Injection）：依赖注入，我们只需要在程序中提供要使用的对象名称就可以，至于对象如何在容器中创建，赋值，查找都有容器内部实现。
    * DI是IOC的技术实现。

  * spring是使用的di实现了IOC的功能，spring底层创建对象，使用的是反射机制。

  * spring是一一个容器，管理对象，给属性赋值，底层是反射创建对象。

## 2. 第一个例子

* 使用的IOC，有Spring创建对象

* 实现的步骤：

  1. 创建maven项目
  2. 加入maven依赖

  ```xml
  <!-- Spring依赖 -->
  <dependency>
      <groupId>org.springframework</groupId>
      <artifactId>spring-context</artifactId>
      <version>5.3.5</version>
  </dependency>
  
  <!-- 单元测试 -->
  <dependency>
      <groupId>junit</groupId>
      <artifactId>junit</artifactId>
      <version>4.12</version>
      <scope>test</scope>
  </dependency>
  
  <!-- 插件 -->
  ```

  3. 创建类（接口和他的实现类）：和没有使用框架一样，就是普通的类。

  ```java
  // 1. 接口
  public interface SomeService {
      public void doSome();
  }
  
  // 2. 普通实现
  public class SomeServiceImpl implements SomeService {
      @Override
      public void doSome() {
          System.out.println("执行了SomeServiceImpl的doSome()方法");
      }
  }
  
  //测试
  @Test
  public void test01(){
      SomeService service = new SomeServiceImpl();
      service.doSome();
  }
  
  /* 执行结果：
  	执行了SomeServiceImpl的doSome()方法
  */
  ```

  4. 创建Spring需要使用的配置文件。声明类的信息，这些类有Spring创建和管理

     Spring的配置文件

     1. beans：是根标签，spring把java对象称为bean。
     2. spring-beans.xsd：是约束文件，和mybatis中的dtd文件是一样的。

  ```xml
  <?xml version="1.0" encoding="UTF-8"?>
  <beans xmlns="http://www.springframework.org/schema/beans"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://www.springframework.org/schema/beans
                             http://www.springframework.org/schema/beans/spring-beans.xsd">
      <!-- 告诉spring创建对象
          声明bean，就是告诉spring要创建某个类的对象
          id：对象的自定义名称，唯一值。spring通过这个名称找到对象
          class：类的全限定名称（不能是接口，因为Spring是反射机制创建对象，必须使用类）
  
          spring就完成SomeService someService = new SomeServiceImpl();
          spring是吧创建好的对象放入到map中，spring框架有一个map是存放对象的
              springMap.put(id的值，对象);
          一个bean标签声明一个对象
  -->
      <bean id="someService" class="ctgu.qiny.service.impl.SomeServiceImpl"/>
  </beans>
  ```

  5. 测试Spring创建对象

  ```java
  @Test
  public void test02(){
      // 使用spring容器创建的对象
      // 1. 指定spring配置文件的名称
      String config = "beans.xml";
      // 2. 创建表示spring容器的对象，ApplicationContext
      // ApplicationContext就是表示Spring的容器，通过容器获取对象了
      // ClassPathXmlApplicationContext：表示从类路径中加载spring的配置文件
      ApplicationContext context = new ClassPathXmlApplicationContext(config);
      // 3. 从容器中获取某个对象，你要调用对象的方法。
      SomeService service = (SomeService) context.getBean("someService");
      // 4. 使用spring创建好的对象
      service.doSome();
  }
  /* 运行结果：
  	执行了SomeServiceImpl的doSome()方法
  */
  ```

## 3. Spring创建对象的时机

* spring默认创建对象的时间：在创建spring的容器时，会创建配置文件中的所有的对象。

  ```java
  // 此时就已经获取到了SomeServiceImpl对象
  ApplicationContext context = new ClassPathXmlApplicationContext(config);
  
  // 若对SomeServiceImpl的无参构造方法进行修改
  public SomeServiceImpl(){
      System.out.println("SomeServiceImpl的无参构造方法");
  }
  ```

  ```xml
  <!-- 修改配置文件 -->
  <beans>
      <bean id="someService" class="ctgu.qiny.service.impl.SomeServiceImpl"/>
      <bean id="someService1" class="ctgu.qiny.service.impl.SomeServiceImpl"/>
  </beans>
  
  <!-- 再次运行测试，可得
  	SomeServiceImpl的无参构造方法 // 第一个someService被创建
      SomeServiceImpl的无参构造方法 // 第二个someService被创建
      执行了SomeServiceImpl的doSome()方法 // 调用了第一个someService的doSome
  -->
  ```

## 4. 获取Spring容器中java对象的信息

* 对象的数量

```java
// 使用Spring提供的方法，获取容器中定义的对象的数量
System.out.println(context.getBeanDefinitionCount());
// 2：表示容器里有两个对象
```

* 对象的名称

```java
// 容器中每个定义的对象的名称
String[] names = context.getBeanDefinitionNames();
Arrays.asList(names).forEach(System.out::println);
/*
    someService
    someService1
*/
```

## 5. 创建非自定义对象

> Spring既能创建自己定义的对象，也可以创建本身已有的对象

* bean配置（以java.util.Date为例）

```xml
<bean id="myDate" class="java.util.Date" />
```

* 测试容器

```java
@Test
public void test04() {
    System.out.println(
        new ClassPathXmlApplicationContext("beans.xml")
        	.getBean("myDate"));
}
/*
	Tue Mar 30 22:02:24 CST 2021
*/
```

# 基于XML的依赖注入

> 在spring的配置文件中，给java对象的属性赋值。
>
> di：依赖注入，表示创建对象，给属性赋值
>
> * di的实现语法有两种：
>   1. 在spring的配置文件中，使用标签和属性来完成，叫做基于XML的di实现。
>   2. 使用spring中的注解，完成属性赋值，叫做基于注解的id实现。
> * di的语法分类
>   1. set注入(设置注入) : spring调用类的set方法 ，在set方法可以实现属性的赋值。80%左右都是使用的set注入。
>   2. 构造注入，spring调用类的有参数构造方法，创建对象。在构造方法中完成赋值。

## 1. 设值注入

### 1.0 没有设值的情况

*  实体类Student

```java
public class Student {

    private String name;
    private Integer age;
    // 省略setter 和toString()
}
```

* beans

```xml
<!-- 声明student对象 -->
<bean id="myStudent" class="ctgu.qiny.entity.Student" />
```

* test

```java
ApplicationContext context = 
    new ClassPathXmlApplicationContext("applicationContext.xml");
// 从容器中获取Student对象
Student student = (Student) context.getBean("myStudent");
System.out.println(student);// Student{name='null', age=null}
```

### 1.1 简单类型的set注入（设值注入）

> 注入：就是赋值的意思
>
> 简单类型：spring中规定java的基本数据类型和String都是简单类型。
>
> spring 调用类的set方法，你可以在set方法中完成属性赋值。

* beans

```xml
<!-- 简单类型的set注入
    <property name="属性名" value="此属性的值" />
    一个property只能给一个属性赋值
 -->
<bean id="zhangsan" class="ctgu.qiny.entity.Student">
    <property name="name" value="张三" />
    <property name="age" value="20" />
</bean>
```

* test

```java
@Test
public void test02() {
    ApplicationContext context = 
        new ClassPathXmlApplicationContext("applicationContext.xml");
    // 从容器中获取Student对象
    Student student = (Student) context.getBean("zhangsan");
    System.out.println(student);// Student{name='张三', age=20}
}
```

### 1.2 单元测试junit

> junit：单元测试，一个工具类库，做测试方法使用的。
> 单元：指定的是方法，一个类中有很多方法，一个方法称为单元。

* 使用单元测试

  1. 加入junit依赖

  ```xml
  <!-- 单元测试 -->
  <dependency>
      <groupId>junit</groupId>
      <artifactId>junit</artifactId>
      <version>4.12</version>
      <scope>test</scope>
  </dependency>
  ```

  2. 创建测试作用的类：叫做测试类。`src/test/java`下创建类

  3. 测试方法
     1. public方法
     2. 没有返回值（返回值为void）
     3. 方法名称自定义，建议名称是test + 你要测试方法名称
     4. 方法没有参数
     5. 方法的上面加入@Test，这样的方法是可以单独执行的。不需要使用main方法。

### 1.3 设值注入的注意事项

* spring进行设值注入时会先调用实体类的无参数构造方法，再调用set方法。

* 实体类必须要有相应的set方法。
  * 比如property中name为email，实体类中必须要有setEmail这个方法。
* set方法里可以不进行赋值。
* 也可以没有对应的属性。
  * 比如property中name为email，实体类中不一定要有email这个属性。
  * 也就是说，只要这个类有setXxx方法，spring就可以用bean来调用。

### 1.4 引用类型的设值注入

* 实体类School

```java
public class School {
    private String name;
    private String address;
    // 省略setter和toString
}
```

* Student添加school属性

```java
public class Student {
    private String name;
    private Integer age;
    private School school;
    // 省略setter和toString
}
```

* beans

```xml
<!-- 引用类型的set注入：spring调用类的set方法
    <property name="属性名称" ref="bean的id"/>
-->
<bean id="lisi" class="ctgu.qiny.entity.Student">
    <property name="name" value="李四"/>
    <property name="age" value="23"/>
    <property name="school" ref="tsingHua"/>
</bean>
<bean id="tsingHua" class="ctgu.qiny.entity.School">
    <property name="name" value="清华大学"/>
    <property name="address" value="北京"/>
</bean>
```

* test

```java
@Test
public void test03() {
    ApplicationContext context =
        new ClassPathXmlApplicationContext("applicationContext.xml");
    System.out.println(context.getBean("lisi"));
}
// Student{name='李四', age=23, school=School{name='清华大学', address='北京'}}
```

## 2. 构造注入

* 创建有参数构造方法

```java
public Student(String name, Integer age, School school) {
    this.name = name;
    this.age = age;
    this.school = school;
}
```

* beans

```xml
<!-- 构造注入：spring调用类有参数构造方法，在创建对象的同时，在构造方法中给属性赋值。
    构造注入使用<constructor-arg> 标签
    <constructor-arg>标签: 一个<constructor-arg>表示构造方法一个参数。
    <constructor-arg>标签属性:
        name：   表示构造方法的形参名
        index：  表示构造方法的参数的位置，参数从左往右位置是0，1, 2的顺 序
        value：  构造方法的形参类型是简单类型的，使用value
        ref：    构造方法的形参类型是引用类型的，使用ref
-->
<bean id="wangwu" class="ctgu.qiny.entity.Student">
    <constructor-arg name="age" value="20"/>
    <constructor-arg name="name" value="王五"/>
    <constructor-arg name="school" ref="tsingHua"/>
</bean>

<!-- 或者 -->
<bean id="wangwu" class="ctgu.qiny.entity.Student">
    <constructor-arg index="0" value="王五"/>
    <constructor-arg index="1" value="20"/>
    <constructor-arg index="2" ref="tsingHua"/>
</bean>

<!-- 甚至可以直接省略index：条件就是要与构造方法非参数顺序一致 -->
<bean id="wangwu" class="ctgu.qiny.entity.Student">
    <constructor-arg value="王五"/>
    <constructor-arg value="20"/>
    <constructor-arg ref="tsingHua"/>
</bean>

<!-- 当然，用name可读性更高 -->
```

* test

```java
@Test
public void test04() {
    ApplicationContext context =
        new ClassPathXmlApplicationContext("applicationContext.xml");
    System.out.println(context.getBean("wangwu"));
}
// Student{name='王五', age=20, school=School{name='清华大学', address='北京'}}
```

## 3. 引用类型的自动注入

> spring框架根据某些规则可以给引用类型赋值。不用你再给引用类型赋值了。
>
> 使用的规则常用的是byName，byType

### 3.1 byName（按名称注入）

* java类中引用类型的属性名和spring容器中(配置文件) \<bean\>的id名称一样，且数据类型是一致的，这样的容器中的bean，spring能够赋值給引用类型。

* 语法：**`\<bean id="xx" class="yyy" autowire="byName"\>`**

* beans

```xml
<!-- 测试自动注入 - - byName -->
<bean id="zhaoliu" class="ctgu.qiny.entity.Student" autowire="byName">
    <property name="name" value="赵六" />
    <property name="age" value="24" />
</bean>

<!-- bean的id要和实体类的属性名一致 -->
<bean id="school" class="ctgu.qiny.entity.School">
    <property name="name" value="同济大学" />
    <property name="address" value="上海" />
</bean>
```

* Test

```java
@Test
public void test01() {
    ApplicationContext context = 
        new ClassPathXmlApplicationContext("applicationContext.xml");
    
    Student student = (Student) context.getBean("zhaoliu");
    System.out.println(student);
}
// Student{name='赵六', age=24, school=School{name='同济大学', address='上海'}}
```

### 3.2 byType（按类型注入）

* java中引用类型的数据类型和spring容器（配置文件）中\<bean\>的class属性是同源关系的，这样的bean能够赋值给引用类型。
  * 同源关系：同源就是一类的意思
    1. java类中引用类型的数据类型和\<bean\>的class的值是一样的。
    2. java类中引用类型的数据类型和\<bean\>的class的值是父子类关系的。
    3. java类中引用类型的数据类型和\<bean\>的class的值是接口和实现关系的。

* beans

```xml
<!-- bean的id要和实体类的属性名一致 -->
<bean id="tongji" class="ctgu.qiny.entity.School">
    <!-- <bean id="school" class="ctgu.qiny.entity.School"> -->
    <property name="name" value="同济大学" />
    <property name="address" value="上海" />
</bean>

<!-- 测试自动注入 - - byType -->
<bean id="zhouqi" class="ctgu.qiny.entity.Student"
      autowire="byType">
    <property name="name" value="周琪" />
    <property name="age" value="23" />
</bean>

<!-- bean的class不一定要与实体类的属性一致，但一个配置文件中只能有一个这个属性（或者与这个属性同源的）的bean -->
```

* test

```java
@Test
public void test02() {
    ApplicationContext context = 
        new ClassPathXmlApplicationContext("applicationContext.xml");
    Student student = (Student) context.getBean("zhouqi");
    System.out.println(student);
    // Student{name='周琪', age=23, school=School{name='同济大学', address='上海'}}
}
```

### 3.3 多配制文件

* 多配制文件的优势
  1. 每个文件的大小比一个文件要小很多，效率高。
  2. 避免多人竞争带来的冲突
* 如果你的项目有多个模块（相关的功能在一起），一个模块一个配置文件，例如：
  1. 学生考勤模块一个配置文件
  2. 学生成绩模块一个配置文件

* 多文件的分配方式
  1. 按功能模块，一个模块一个配置文件
  2. 按类的功能，数据库相关的配置一个配置文件，做事务的功能一个配置文件，做service功能的一个配置文件等。

* 使用多配置文件

  1. spring-student.xml

  ```xml
  <!-- student模块所有bean的声明 -->
  <bean id="zhangsan" class="ctgu.qiny.entity.Student">
      <property name="name" value="张三"></property>
      <property name="age" value="30"></property>
  </bean>
  ```

  2. spring-school.xml

  ```xml
  <!-- school模块所有bean的声明，school模块的配置文件 -->
  <bean id="hangkong" class="ctgu.qiny.entity.School">
      <property name="name" value="航空大学"></property>
      <property name="address" value="北京海淀区"></property>
  </bean>
  ```

  3. spring-total.xml

  ```xml
  <!-- spring-total表示主配置文件：用来包含其他的配置文件，一般不用来定义对象。 -->
  <!-- 语法：<import resource="其他配置文件的路径"/> -->
  <!-- 关键字："classpath:"表示类路径（class文件所在的目录） -->
  <!-- 在spring配置文件中要指定其他文件的位置，需要使用classpath，告诉spring到哪去加载读取文件。 -->
  
  <import resource="classpath:spring-student.xml" />
  <import resource="classpath:spring-school.xml" />
  
  <!-- 好像不能这样子写了，会报错No bean named 'xxx' available -->
  <!-- 包含关系的配置文件中，可以使用通配符（*表示任意字符） -->
  <!-- <import resource="classpath:spring-*.xml" /> -->
  ```

  4. test

  ```java
  @Test
  public void test01() {
      ApplicationContext context = new ClassPathXmlApplicationContext("total.xml");
      // 从容器中获取Student对象
      Student student = (Student) context.getBean("zhangsan");
      System.out.println(student);
  
      // Student{name='张三', age=30, school=School{name='航空大学', address='北京海淀区'}}
  }
  ```

# 基于注解的依赖注入

> 通过注解完成java对象创建，属性赋值

* 使用注解的步骤：

  1. 加入maven的依赖 spring-context，在你加入spring-context的同时，间接加入spring-aop的依赖。

     使用注解必须使用spring-aop依赖。

  2. 在类中加入spring的注解（多个不同功能的注解）

  3. 在spring的配置文件中，加入一个组件扫描器的标签，说明注解在你的项目中的位置。

* 学习的注解

  1. @Component

  2. @Repository
  3. @Service
  4. @Controller
  5. @Value
  6. @Autowire
  7. @Resource

## 1. @Component注解的使用

* 通过spring的注解完成java对象的创建，属性。代替xml文件

* 实现步骤：

  1. 加入依赖

  2. 创建里，在类中加入注解

  3. 创建spring的配置文件

     声明组件扫描器的标签，知名注解在你的项目中的位置。

  4. 使用注解创建的对象，创建容器ApplicationContext

* 实体类

```java
/*
 * @Component：创建对象的，等同于<bean>的功能
 * * 属性：	value 就是对象的名称，也就是bean的id值，
 * * 		value的值是惟一的，创建的对象在整个spring容器中就一个
 * * 位置：	在类的上面。
 * 
 * @Component(value = "myStudent")等同于
 * * <bean id="myStudent" class="ctgu.qiny.entity.Student" />
 */

// 使用value属性，指定对象的名称
// @Component(value = "myStudent")
// value也可以省略
// @Component("myStudent")// 指定了bean的id
// 不指定id时，容器默认给一个id
@Component // id为类的首字母小写
public class Student {
	private String name;
	private Integer age;
}
```

* 在配置文件中定义组件扫描器

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xmlns:context="http://www.springframework.org/schema/context"
       xsi:schemaLocation="http://www.springframework.org/schema/beans
                           http://www.springframework.org/schema/beans/spring-beans.xsd
                           http://www.springframework.org/schema/context
                           http://www.springframework.org/schema/context/spring-context-3.0.xsd">

    <!-- 声明组件扫描器（component-scan），组件就是java对象 -->
    <!-- * 	base-package：指定注解在你的项目中的包名 -->
    <!-- *	component-scan工作方式：spring会扫描遍历base-package指定的包 -->
    <!-- *		把包中和子包中的所有类，找到类中的注解，按照注解的功能创建对象，或给属性赋值 -->
    <context:component-scan base-package="ctgu.qiny.entity" />

</beans>
```

* 测试

```java
@Test
public void test01() {
    ApplicationContext context = 
        new ClassPathXmlApplicationContext("applicationContext.xml");
    // Student student = (Student) context.getBean("myStudent");
    Student student = (Student) context.getBean("student");
    System.out.println(student);
    // Student [name=null, age=null]
}
```

* spring中和@Component功能一致，创建对象的注解还有：
  1. @Repository（用在持久层类的上面）：放在dao的实现类上面，表示创建dao对象，dao对象是能访问数据库的。
  2. @Service（用在业务层类的上面）：放在service的实现类上面，创建service对象，service对象是做业务处理，可以有事务等功能的。
  3. @Controller（用在控制器的上面）：放在控制器（处理器）类的上面，创建控制器对象的，孔梅花之气对象，能够接收用户提交的参数，显示请求的处理结果。
  4. 以上三个注解的使用语法和Component一样。都能创建对象，但是这三个注解还有额外的功能。是给项目的对象分层的。

* 指定多个包的方式
  1. 第一种方式：使用多次组件扫描器，指定不同的包。
  2. 第二种方式：使用分隔符（;或,）分隔多个包名。
  3. 第三种方式：指定父包。

## 2. 简单类型的属性赋值

* @Value：简单类型的属性赋值
  * 属性：value 是string类型的， 表示简单类型的属性值。
  * 位置：
    1. 在属性定义的上面，无需set方法，推荐使用。
    2. 在set方法的上面

* 实体类

```java
@Component // id为类的小写
public class Student {
	@Value(value = "张飞")
	private String name;
	@Value(value = "29")
	private Integer age;
    // 省略toString
}
```

* 再次执行test类，可得

```shell
Student [name=张飞, age=29]
```

## 3. 引用类型@Autowired

### 3.1 基本使用

* spring框架提供的注解，实现引用类型的赋值。
* spring中通过注解给引用类型赋值，使用的是自动注入原理，支持byName，byType。
* @Autowired：默认使用的是byType自动注入。
* 位置：
  * 在属性定义的上面，无需set方法，推荐使用
  * 在set方法的上面
* School实体类

```java
@Component
public class School {
	@Value("清华大学")
    private String name;
	@Value("上海")
    private String address;
    // 省略toString
}
```

* Student实体类

```java
@Component
public class Student {

	@Value(value = "张飞")
	private String name;
	@Value(value = "29")
	private Integer age;
	@Autowired
	private School school;
    // 省略toString
}
```

* 再次执行测试

```shell
Student [name=张飞, age=29, school=School{name='清华大学', address='上海'}]
```

### 3.2 @Autowired的byName

* 如果要使用byName方式，需要做的是: 

  1. 在属性上面加入@Autowired
  2. 在属性上面加入@Qualifier(value= "bean的id")，表示使用指定名称的bean完成赋值。

  ```java
  // 两个注解没有先后顺序
  @Autowired
  @Qualifier("mySchool")
  private School school;
  
  // 获取名为"mySchool"的引用类型的数据
  @Component("mySchool")
  public class School {...}
  ```

### 3.3 @Autowired的required属性

* 属性：required， 是一个boolean类型的，默认true
  * required=true：表示引用类型赋值失败，程序报错，并终止执行。
  * required=false：引用类型如果赋值失败，程序正常执行 ，引用美型Enull

```java
@Autowired(required = false)
@Qualifier("mySchool-1")
private School school;

// 运行时如果没有名为mySchool-1的bean就不会报错，而会显示
// Student [name=张飞, age=29, school=null]
```

> 推荐使用required=true

## 4. 引用类型Resource

* 来自jdk中的注解，spring框架提供了对这个注解的功能支持，可以使用它给引用类型赋。

  使用的也是自动注入原理，支byName、byType。默认是byName

* 位置：

  * 在属性定义的上面，无需set方法，推荐使用。
  * 在set方法的上面

* 默认是byName：先使用byName自动注入，如果byName赋值失败，再使用byType

* @Resource只使用byName方式，需要增加个属性 name。name的值是bean的id (名称)

```java
// 只使用byName的方式
@Resource(name = "mySchool")
private School school;
```

## 5. xml和注解方式的对比

变化多的用xml。

变化不多的用注解。

# AOP 面向切面编程

## 1. 动态代理

* 动态代理的实现方式常用的有两种：使用JDK的Proxy，与通过CGLIB生成代理。

### 1.1 JDK动态代理

* Jdk的动态要求目标对象必须实现接口，这是java设计上的要求。
* 从jdk1.3以来，java 语言通过java.lang.reflect包提供三个类支持代理模式Proxy, Method 和InovcationHandler。

### 1.2 CGLIB 动态代理(了解)

* CGLIB（Code Generation Library）是一个开源项目。是一个强大的，高性能，高质量的Code生成类库，它可以在运行期扩展Java类与实现Java 接口。它广泛的被许多AOP的框架使用，例如Spring AOP。
* 使用JDK 的Proxy 实现代理，要求目标类与代理类实现相同的接口。若目标类不存在接口，则无法使用该方式实现。但对于无接口的类，要为其创建动态代理，就要使用CGLIB来实现。
* CGLIB代理的生成原理是生成目标类的子类，而子类是增强过的，这个子类对象就是代理对象。所以，使用CGLIB生成动态代理，要求目标类必须能够被继承，即不能是final的类。
* CGLIB经常被应用在框架中，例如Spring ，Hibernate等。cglib 的代理效率高于Jdk。项目中直接使用动态代理的地方不多。一般都使用框架提供的功能。

### 1.3 业务方法增加功能

* 原始的业务逻辑代码

```java
public void doSome() {
    // 真正的业务逻辑代码
    System.out.println("执行业务方法doSome");
}

public void doOther() {
    // 真正的业务逻辑代码
    System.out.println("执行业务方法doOther");
}
```

* 项目运行一段时间之后，又添加的新的需求

```java
public void doSome() {
    //项目运行一段时间，又有新的需求：在方法执行前打印运行时间
    System.out.println("方法的执行时间"+new Date());

    // 真正的业务逻辑代码
    System.out.println("执行业务方法doSome");

    //项目运行一段时间，又有新的需求：在方法执行后提交事务
    System.out.println("方法执行完毕后，提交事务");
}

public void doOther() {
    //项目运行一段时间，又有新的需求：在方法执行前打印运行时间
    System.out.println("方法的执行时间"+new Date());

    // 真正的业务逻辑代码
    System.out.println("执行业务方法doOther");

    //项目运行一段时间，又有新的需求：在方法执行后提交事务
    System.out.println("方法执行完毕后，提交事务");
}
```

* 发现业务逻辑方法中加入了许多和业务逻辑无关的重复代码
* 现在期望的是，在不改变原有业务逻辑代码的前提下增加功能。

### 1.4 动态代理实现功能的添加

* 动态代理：可以在程序的执行过程中 ， 创建代理对象。
  通过代理对象执行方法，给目标类的方法增加额外的功能（功能增强）。

* jdk动态代理实现步骤:
  1. 创建目标类，SomeServiceImpl 目标类，给它的doSome，doOther增加输出时间，事务。 
  2. 创建InvocationHandler接口的实现类，在这个类实现给目标方法增加功能。
  3. 使用jdk中类Proxy，创建代理对象。 实现创建对象的能力。

* 创建MyInvocationHandler实现InvocationHandler

  ```java
  public class MyInvocationHandler implements InvocationHandler {
      // 目标对象
      private Object target; // 最终会是SomeServiceImpl类
  
      public MyInvocationHandler(Object target) {
          this.target = target;
      }
  
      @Override
      public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
          // 通过代理对象执行方法是，会调用执行这个invoke()
          Object res = null;
  
          SomeServiceTools.doLog();
  
          // 执行目标类的方法，通过Method类实现
          res = method.invoke(target, args);
  
          SomeServiceTools.doTrans();
  
          // 目标方法的执行结果
          return res;
      }
  
  }
  ```

* 测试：使用Proxy进行代理

  ```java
  @Test
  public void testInvoke() {
      // 使用jdk的Proxy创建代理对象
      // 创建目标对象
      SomeService target = new SomeServiceImpl();
  
      // 创建InvocationHandler
      InvocationHandler handler = new MyInvocationHandler(target);
  
      // 使用Proxy创建代理
      SomeService proxy = (SomeService) Proxy.newProxyInstance(target.getClass().getClassLoader(),
                                                               target.getClass().getInterfaces(), handler);
  
      // 通过代理方法，会调用handler中的invoke()
      proxy.doSome();
  }
  ```

### 1.5 动态代理的作用

* 在目标类源代码不改变的情况下，增加功能.
* 减少代码的重复
* 专注业务逻辑代码
* 解耦合，让你的业务功能和日志，事务非业务功能分离。

## 2. AOP

### 2.1 AOP简介

AOP (Aspect Orient Programming)，面向切面编程。面向切面编程是从动态角度考虑程序运行过程。

AOP底层，就是采用动态代理模式实现的。采用了两种代理：JDK 的动态代理，与CGLIB的动态代理。

AOP为Aspect Oriented Programming的缩写，意为：面向切面编程，可通过运行期动态代理实现程序功能的统一维护的一种技术。AOP是Spring框架中的一个重要内容。利用AOP可以对业务逻辑的各个部分进行隔离，从而使得业务逻辑各部分之间的耦合度降低，提高程序的可重用性，同时提高了开发的效率。

面向切面编程，就是将交叉业务逻辑封装成切面，利用AOP容器的功能将切面织入到主业务逻辑中。所谓交叉业务逻辑是指，通用的、与主业务逻辑无关的代码，如安全检查、事务、日志、缓存等。

若不使用AOP，则会出现代码纠缠，即交叉业务逻辑与主业务逻辑混合在一起。这样，会使主业务逻辑变的混杂不清。

>Aop就是动态代理的规范化，把动态代理的实现步骤，方式都定义好了。
>
>让开发人员用一种统一的方式，使用动态代理。

### 2.2 理解面向切面编程

AOP （Aspect Orient Programming）面向切面编程
Aspect：切面，给你的目标类增加的功能，就是切面。像上面用的日志，事务都是切面。
				切面的特点：一般都是非业务方法，独立使用的。
Orient：面向，对着。
Programming：编程。

怎么理解面向物面编程?

1. 需要在分析项目功能时，找出切面。
2. 合理的安排切面的执行时间（在目标方法前，还是目标方法后）
3. 合理的安排切面执行的位置，在哪个类，哪个方法增加增强功能

### 2.3 一些术语

* Aspect：切面，表示增强的功能，就是一堆代码，完成某个一个功能。非业务功能，常见的切面功能有日志，事务，统计信息，参数检查，权限验证。
* JoinPoint：连接点 ，连接业务方法和切面的位置。 就某类中的业务方法。
* Pointcut：切入点，指多个连接点方法的集合。多个方法。
* 目标对象：给哪个 类的方法增加功能，这个类就是 目标对象
* Advice:通知，邇知表示切面功能执行的时间。

说一个切面有三个关键的要素:

1. 切面的功能代码，切面干什么
2. 切面的执行位置，使用Pointcut表示切面执行的位置
3. 切面的执行时间，使用Advice表示时间， 在目标方法之前，还是目标方法之后。

### 2.4 AOP的实现

* aop是一个规范，是动态的一个规范化，一个标准

* aop的技术实现框架：

  1. spring: spring在内部实现了aop规范，能做aop的工作。
     spring主要在事务处理时使用aop:
     我们项目开发中很少使用spring的aop实现。因为spring的aop比较笨重。

  2. aspectJ: 一个开源的专门做aop的框架。 spring框架中集成了aspectj框架， 通过spring就能使用aspectj的功能。
     aspectJ框架实现aop有两种方式:
     1. 使用xm1的配置文件:配置 全局事务
     2. 使用注解，我们在项目中要做aop功能，一般都使用注解，aspectj有5个注解。

### 2.5 aspectJ框架的使用

1. 切面的执行时间，这个执行时间在规范中叫Advice（通知，增强）。在aspectj框架中使用注解表示的。也可以使用xml配置文件中的标签。
   1. @Before
   2. @AfterReturning
   3. @Around
   4. @AfterThrowing
   5. @After

2. 表示切面执行的位置，使用的是切入点表达式。

```java
"execution(访问权限类型（可选） 返回值的数据类型 方法所在的类的全限定名称（可选） 方法名(方法的参数部分) 方法抛出的异常（可选）)"
```

3. 切入点表达式要匹配的对象就是目标方法的方法名。所以，execution表达式中明显就是方法的签名。注意，表达式中黑色文字表示可省略部分，各部分间用空格分开。在其中可以使用以下符号:
   * \*(星号)：表示0至多个任意字符
   * ..(两个点)：用在方法参数中，表示任意多个参数。用在报名后，表示当前包及其子包路径。
   * +(加号)：用在类名后，表示当前类及其子类。用在接口后，表示当前接口及其实现类。

4. 举例：

   * `execution(public * *(..))`指定切入点为：任意公共方法。
   * `execution(* set*(..))`指定切入点为：任何一个以"set"开始的方法。
   * `execution(* com.xyz.service.*.*(..))`指定切入点为：定义在service包下任意类的任意方法。
   * `execution(* com.xyz.service..*.*(..))`指定切入点为：定义在service包及其子包下任意类的任意方法。

   * `execution(* *..service.*.*(..))`指定所有报下的service子包下所有类（接口）中所有方法为切入点。
   * `execution(* *.service.*.*(..))`指定只有一级包下的service子包下所有类（接口）中所有方法为切入点。

5. 使用步骤

   1. 新建maven项目

   2. 加入依赖

      1. spring依赖
      2. aspectj依赖

      3. junit单元测试

   3. 创建目标类：接口和他的实现类。要做的是给类中的方法增加功能。

   4. 创建切面类:普通类

      1. 在类的上面加入@Aspect
      2. 在类中定义方法，方法就是切面要执行的功能代码。
         在方法的上面加入aspectj中的通知注解，例如Before
         有需要指定切入点表达式execution()

   5. 创建spring的配置文件：声明对象，把对象交给容器统一管理
      声明对象你可以使用注解或者xml配置文件\<bean\>

      1. 声明目标对象
      2. 声明切面类对象
      3. 声明aspectj框架中的自动代理生成器标签。
         自动代理生成器：用来完成代理对象的自动创建功能的。

   6. 创建测试类，从spring容器中获取目标对象（实际就是代理对象）。
      通过代理执行方法， 实现aop的功能增强。

* pom.xml

```xml
<!-- Spring依赖 -->
<dependency>
    <groupId>org.springframework</groupId>
    <artifactId>spring-context</artifactId>
    <version>5.3.5</version>
</dependency>

<!-- 单元测试 -->
<dependency>
    <groupId>junit</groupId>
    <artifactId>junit</artifactId>
    <version>4.12</version>
    <scope>test</scope>
</dependency>

<!-- aspectJ依赖 -->
<dependencies>
    <dependency>
        <groupId>org.springframework</groupId>
        <artifactId>spring-aspects</artifactId>
        <version>5.3.5</version>
    </dependency>
</dependencies>
```

* 切面类

```java
/*@Aspect：是aspectj框架中的注解
 * 	作用：表示当前类是切面类
 *	切面类：是用来给业务方法增加功能的类，在这个类中有切面的功能代码
 *	位置：在类定义的上面
 */
@Aspect
public class MyAspect {
	/*定义方法，方法是实现切面功能的。
	 *	方法的定义要求：
	 *		1. 公共方法public
	 *		2. 方法没有返回值
	 *		3. 方法名称自定义
	 * 		4. 方法可以有参数， 也可以没有参数。
	 *			如果有参数，参数不是自定义的，有几个参数类型可以使用。 
	 */
	public void myBefore() {
		// 就是切面要执行的代码
		System.out.println("前置通知，切面功能：在目标方法之前输出执行时间" + new Date());
	}
}

```

* applicationContext.xml

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xmlns:aop="http://www.springframework.org/schema/aop"
       xsi:schemaLocation="http://www.springframework.org/schema/beans
                           http://www.springframework.org/schema/beans/spring-beans.xsd
                           http://www.springframework.org/schema/aop
                           http://www.springframework.org/schema/aop/spring-aop.xsd">

    <!-- 把对象交给spring容器，有spring容器统一创建，管理对象 -->
    <!-- 声明目标对象 -->
    <bean id="someService"
          class="ctgu.qiny.service.impl.SomeServiceImpl" />

    <!-- 声明切面类对象 -->
    <bean id="myAspect" class="ctgu.qiny.service.aspect.MyAspect" />

    <!-- 声明自动代理生成器：使用aspectj框架内部的功能，创建你目标对象的代理对象。 -->
    <!-- 创建代理对象实在内存中实现的，修改目标对象的内存中的结构。创建为代理对象。 -->
    <!-- 所以目标对象就是被修改后的代理对象。 -->

    <!-- aspectj-autoproxy：会把spring容器中的所有目标对象，一次性都生成代理对象 -->
    <aop:aspectj-autoproxy />
</beans>
```

* 测试

```java
@Test
public void testProxy() {
    ApplicationContext context = 
        new ClassPathXmlApplicationContext("applicationContext.xml");
    SomeService service = (SomeService)context.getBean("someService");
    service.doSome();
}
// 前置通知，切面功能：在目标方法之前输出执行时间Sat Apr 03 16:54:04 CST 2021
// 执行业务方法doSome
```

### 2.6 指定通知方法中的参数：JoinPoint

* JoinPoint：业务方法，要就切面功能的业务方法。
* 作用是：可以在通知方法中获取方法执行时的信息，例如方法名称，方法的实参。
* 如果你的切面功能中需要用到方法的信息，就加入JoinPoint
* 这个JoinPoint参数的值是由框架赋予，必须是第一个位置的参数

```java
@Before("execution(public void *..service..*.doSome(..))")
public void myBefore(JoinPoint jp) {
    // 获取方法的完整定义
    System.out.println("方法的签名 = " + jp.getSignature());
    System.out.println("方法的名称 = " + jp.getSignature().getName());
    // 方法的实参
    System.out.println("方法的实参：");
    Arrays.asList(jp.getArgs()).forEach(System.out::println);
    // 就是切面要执行的代码
    System.out.println("前置通知，切面功能：在目标方法之前输出执行时间" + new Date());
}
```

### 2.7 后置通知 @AfterReturning

后置通知定义方法，方法是实现切面功能的。

* 方法的定义要求:

  1. 公共方法public
  2. 方法没有返回值
  3. 方法名称自定义
  4. 方法有参数的，推荐是Object，参数名自定义

* @AfterReturning：后置通知

  * 属性：

    * value：切入点表达式

    * returning：自定义的变脸，表示目标方法的返回值的。

      自定义变量名必须和通知方法的形参名一样

  * 位置：在方法定义的上面
  * 特点：
    1. 在目标方法之后执行的。
    2. 能够获取到目标方法的返回值，可以根据这个返回值做不同的处理功能
    3. 可以修改这个返回值

```java
// SomeServiceImpl.doOther
@Override
public Integer doOther(Integer before, Integer after) {
    return before * 10 + after;
}

// MyAspect.myAfter
// 注意returning的值要与参数变量名一致
@AfterReturning(value = "execution(public Integer *..service..*.doOther(..))", 
                returning = "res")
public void myAfter(Object res) {
    // System.out.println("后置通知，提交事务");
    System.out.println("后置通知：在目标方法之后执行的，获取的返回值是：" + res);
}

// 测试
public void testProxy() {
    ApplicationContext context = 
        new ClassPathXmlApplicationContext("applicationContext.xml");
    SomeService service = (SomeService) context.getBean("someService");
    Integer sum = service.doOther(4, 5);
    System.out.println(sum);
}
// 后置通知：在目标方法之后执行的，获取的返回值是：45
// 45 
```

### 2.8 环绕通知 @Around

* 环绕通知方法的定义格式
  1. public
  2. 必须有一个返回值，推荐使用Object
  3. 方法名称自定义
  4. 方法有参数，固定的参数 ProceedingJoinPoint

* 属性：value 切入点表达式
* 位置：在方法定义的上面
* 特点：
  1. 它是功能最强的通知
  2. 在目标方法的前后都能增强功能
  3. 控制目标方法是否被调用执行
  4. 修改原理的目标方法的执行结果，影响最后的调用结果
* 环绕通知，等同于jdk的动态代理。
* 参数：ProceedingJoinPoint 就等同于Method
* 作用：执行目标方法的
* 返回值：就是执行目标方法的执行结果。
* 经常做事务，在目标方法之前开启事务，执行目标方法，在目标方法之后提交事务

SomeServiceImpl.doFirst

```java
public String doFirst(String name, Integer age) {
    System.out.println("执行doFirst事务");
    return "Student = {name = " + name + ", age = " + age + "}";
}
```

myAround

```java
@Around(value="execution(* *..SomeService.doFirst(..))")
public Object myAround(ProceedingJoinPoint pjp) throws Throwable {
    // 实现环绕通知
    Object result = null;
    System.out.println("环绕通知：在目标方法之前，输出时间："+new Date());
    // 1. 目标方法调用
    result = pjp.proceed();

    System.out.println("环绕通知：在目标方法之后，提交事务");
    // 2. 在目标方法前或者后加入功能

    // 返回目标方法的执行结果
    return result;
}
```

test

```java
@Test
public void testAround() {
    ApplicationContext ctx = 
        new ClassPathXmlApplicationContext("applicationContext.xml");
    SomeService service = (SomeService) ctx.getBean("someService");
    System.out.println(service.doFirst("小红", 18));
}
// 环绕通知：在目标方法之前，输出时间：Sat Apr 03 23:08:09 CST 2021
// 执行doFirst事务
// 环绕通知：在目标方法之后，提交事务
// Student = {name = 小红, age = 18}
```

### 2.9 异常通知 @AfterThrowing

* 异常通知方法的定义格式

  1. public
  2. 没有返回值
  3. 方法名称自定义
  4. 方法可以有一个参数Exception，如果有还有，就是JoinPoint。

* @AfterThrowing：异常通知

  * 属性：

    1. value：切入点表达式

    2. throwing：自定义的变量，表示目标方法抛出的异常对象。

       变量名必须和方法的参数名一致

  * 特点

    1. 在目标方法抛出异常时执行的

    2. 可以做异常的监控程序，监控目标方法执行时是不是有异常。

       如果有异常，可以发送邮件，短信进行通知

SomeServiceImpl.doSecond

```java
@Override
public void doSecond() {
    int n = 1/0;// 手动抛出除0异常
}
```

MyAspect.myAfterThrowing

```java
@AfterThrowing(value = "execution(* *..SomeServiceImpl.doSecond(..))", throwing = "e")
public void myAfterThrowing(Exception e) {
    System.out.println("异常通知：方法发生异常时，执行：" + e.getMessage());
    // 发送邮件，短信，通知开发人员
}
```

test

```java
@Test
public void testAfterThrowing() {
    ApplicationContext ctx = 
        new ClassPathXmlApplicationContext("applicationContext.xml");
    SomeService service = (SomeService) ctx.getBean("someService");
    service.doSecond();
}
```

### 2.10 最终通知 @After

* 最终通知方法的定义格式
  1. public
  2. 没有返回值
  3. 方法名称自定义
  4. 方法没有参数，如果有，就是JoinPoint。
* @After：最终通知
  * 属性：value：切入点表达式
  * 位置：在方法的上面
* 特点：
  1. 总是会执行
  2. 在目标方法之后执行的

SomeServiceImpl.doThird

```java
@Override
public void doThird() {
    System.out.println("执行业务逻辑代码");		
}
```

MyAspect.myAfter

```java
@After(value = "execution(* *..SomeServiceImpl.doThird(..))")
public void myAfter() {
    System.out.println("执行最终通知");
    // 一般是做资源清除工作的
}
```

### 2.11 Pointcut注解

* 定义和管理切入点，如果你的项目中有多个切入点表达式是重复的，可以复用的。可以使用@Pointcut
* 属性：value：切入点表达式
* 位置：在自定义的方法上面
* 特点：
  * 当使用@Pointcut定义在一个方法的上面，此时这个方法的名称就是切入点表达式的别名。
  * 其他的通知中，value属性可以使用这个方法名称，代替切入点表达式了

```java
@Pointcut(value = "execution(* *..SomeServiceImpl.doFirst(..))")
private void myPointcut() {
}

@Around(value = "myPointcut()")
public Object myAround(ProceedingJoinPoint pjp) throws Throwable {
    // 实现环绕通知
    Object result = null;
    System.out.println("环绕通知：在目标方法之前，输出时间：" + new Date());
    // Arrays.asList(pjp.getArgs()).forEach(System.out::println);
    // 1. 目标方法调用
    result = pjp.proceed();

    System.out.println("环绕通知：在目标方法之后，提交事务");
    // 2. 在目标方法前或者后加入功能

    // 返回目标方法的执行结果
    return result;
}

// 等价于
@Around(value = "execution(* *..SomeService.doFirst(..))")
public Object myAround(ProceedingJoinPoint pjp) throws Throwable {
    // 实现环绕通知
    Object result = null;
    System.out.println("环绕通知：在目标方法之前，输出时间：" + new Date());
    // Arrays.asList(pjp.getArgs()).forEach(System.out::println);
    // 1. 目标方法调用
    result = pjp.proceed();

    System.out.println("环绕通知：在目标方法之后，提交事务");
    // 2. 在目标方法前或者后加入功能

    // 返回目标方法的执行结果
    return result;
}
```

### 2.12 没有接口是CGLIB代理，有接口是JDK动态代理

### 2.13 有接口也能使用动态代理。

* 如果你期望目标类有接口，使用cglib代理

* 修改applicationContext.xml

```xml
<!-- proxy-target-class="true"
	告诉框架，要使用cglib动态代理 
-->
<aop:aspectj-autoproxy proxy-target-class="true"/>
```

# Spring整合mybatis

## 1. 思路

* 把mybatis框架和spring集成在一起，像一个框架一样使用。

* 用的技术是：ioc

* 为什么ioc：能把mybatis和spring集成在一起，像一个框架，是因为ioc能创建对象。可以把mybatis框架中的对象交给spring统一创建，开发人员从spring中获取对象。开发人员就不要同时面对两个或多个对象了，就面对一个spring。

* mybatis使用步骤，对象

  1. 定义dao接口StudentDao
  2. 定义mapper文件StudentDao.xml
  3. 定义mybatis的主配置文件mybatis.xml
  4. 创建dao的代理对象StudentDao dao = SqlSession.getMapper(StudentDao.class);

  List\<Student\> students = dao.selectStudents();

* 要使用dao对象，需要使用getMapper()方法。怎么能使用getMapper()方法，需要哪些条件？

  1. 获取SqlSession对象，需要使用SqlSessionFactory的openSession()方法。
  2. 创建SqlSessionFactory对象，通过读取mybatis的主配置文件，能创建SqlSessionfactory对象。

* 需要sqlsessionFactory对象，使用Factory能获取Sqlsession ，有了SqlSession就能有dao，目的就是获取dao对象。
  Factory创建需要读取主配置文件。

* 主配置文件：

  1. 数据库信息
  2. mapper文件的位置

* 我们会使用独立的连按池类替换mybatis默认自己带的，把连接池类也交给spring创建。

* 通过以上的说明，我们需要让spring创建以下对象。

  1. 独立的连接池类的对象，使用 阿里的druid连接池

  2. SqlsessionFactory对象
  3. 创建出dao对象

* 需要学习就是上面三个对象的创建语法，使用xml的bean标签。

* 步骤

  1. 新建maven项目
  2. 加入maven的依赖
     1. spring依赖
     2. mybatis依赖
     3. mysql驱动
     4. spring的事务的依赖
     5. mybatis和spring集成的依赖：mybatis官方提供的，用来在spring项目中创建mybatis的sqlsesissonFactory、dao对象的
  3. 创建实体类
  4. 创建dao接口和mapper文件
  5. 创建mybatis主配置文件
  6. 创建Service接口和实现类,属性是dao。
  7. 创建spring的配置文件：声明mybatis的对象交给spring创建
     1. 数据源
     2. sqlSessionFactory
     3. Dao对象
  8. 创建测试类，获取Service对象，通过service调用dao完成数据库的访问

## 2. 引入依赖和插件、搭建mybatis运行环境

```xml
<dependencies>
    <!-- 单元测试 -->
    <dependency>
        <groupId>junit</groupId>
        <artifactId>junit</artifactId>
        <version>4.12</version>
        <scope>test</scope>
    </dependency>

    <!-- Spring核心IOC -->
    <dependency>
        <groupId>org.springframework</groupId>
        <artifactId>spring-context</artifactId>
        <version>5.3.5</version>
    </dependency>

    <!-- 做Spring事务用到的 -->
    <dependency>
        <groupId>org.springframework</groupId>
        <artifactId>spring-tx</artifactId>
        <version>5.3.5</version>
    </dependency>
    <dependency>
        <groupId>org.springframework</groupId>
        <artifactId>spring-jdbc</artifactId>
        <version>5.3.5</version>
    </dependency>

    <!-- mybatis依赖 -->
    <dependency>
        <groupId>org.mybatis</groupId>
        <artifactId>mybatis</artifactId>
        <version>3.5.6</version>
    </dependency>

    <!-- mybatis和spring集成的依赖 -->
    <dependency>
        <groupId>org.mybatis</groupId>
        <artifactId>mybatis-spring</artifactId>
        <version>2.0.6</version>
    </dependency>

    <!-- mysql驱动 -->
    <dependency>
        <groupId>mysql</groupId>
        <artifactId>mysql-connector-java</artifactId>
        <version>5.1.49</version>
    </dependency>

    <!-- 阿里巴巴的数据库连接池 -->
    <dependency>
        <groupId>com.alibaba</groupId>
        <artifactId>druid</artifactId>
        <version>1.2.5</version>
    </dependency>
</dependencies>
<build>
    <resources>
        <resource>
            <directory>src/main/java</directory>
            <includes>
                <include>**/*.properties</include>
                <include>**/*.xml</include>
            </includes>
            <filtering>true</filtering>
        </resource>
        <resource>
            <directory>src/main/resources</directory>
            <includes>
                <include>**/*.properties</include>
                <include>**/*.xml</include>
            </includes>
            <filtering>true</filtering>
        </resource>
    </resources>
    <plugins>
        <plugin>
            <groupId>org.apache.maven.plugins</groupId>
            <artifactId>maven-compiler-plugin</artifactId>
            <configuration>
                <source>8</source>
                <target>8</target>
            </configuration>
        </plugin>
    </plugins>
</build>
```

* mybatis的主配置文件

```xml
<?xml version="1.0" encoding="UTF8" ?>
<!DOCTYPE configuration
        PUBLIC "-//mybatis.org//DTD Config 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-config.dtd">
<configuration>

    <!--  控制mybatis全局行为  -->
    <settings>
        <!-- 设置mybatis输出日志 -->
        <setting name="logImpl" value="STDOUT_LOGGING"/>
    </settings>

    <!--  设置别名  -->
    <typeAliases>
        <package name="ctgu.qiny.entity"/>
    </typeAliases>

    <mappers>
        <package name="ctgu.qiny.dao"/>
    </mappers>
</configuration>
```

* 创建的Student实体类、StudentDao、StudentDao.xml参考mybatis

## 3. 创建Service类

* StudentService

```java
public interface StudentService {

    int addStudent(Student student);

    List<Student> queryStudent();

}
```

* StudentServiceImpl

```java
public class StudentServiceImpl implements StudentService {

    private StudentDao studentDao;

    public void setStudentDao(StudentDao studentDao) {
        this.studentDao = studentDao;
    }

    @Override
    public int addStudent(Student student) {
        return studentDao.insertStudent(student);
    }

    @Override
    public List<Student> queryStudent() {
        return studentDao.selectStudents();
    }
}
```

## 4. 在主配置文件中配置DataSource 和dao对象

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd">

    <!-- 声明数据源DataSource，作用书链接数据库的 -->
    <bean id="dataSource" class="com.alibaba.druid.pool.DruidDataSource"
          init-method="init" destroy-method="close">
        <property name="url"
                  value="jdbc:mysql://localhost:3306/mybatis-learning?useSSL=false"/>
        <property name="username" value="root"/>
        <property name="password" value="123456"/>
        <property name="maxActive" value="20"/>
    </bean>

    <!--  声明的是mybatis中提供的SQLSessionFactoryBean类，这个类内部创建SqlSessionFactory的  -->
    <bean id="sqlSessionFactory" class="org.mybatis.spring.SqlSessionFactoryBean">
        <!-- set注入，把数据流链接池付给了dataSource属性 -->
        <property name="dataSource" ref="dataSource"/>
        <!-- mybatis主配置文件的位置
                configLocation属性是Resource类型，读取配置文件
                它的赋值，使用value，指定文件的路径，使用classpath:表示文件的位置
        -->
        <property name="configLocation" value="classpath:mybatis.xml"/>
    </bean>
    <!--  创建dao对象，使用SqlSession的getMapper(StudentDao.class)
        MapperScannerConfigurer：在内部调用getMapper()生成每个dao接口的代理对象。
      -->
    <bean class="org.mybatis.spring.mapper.MapperScannerConfigurer">
        <!--  指定SqlSessionFactory对象的id  -->
        <property name="sqlSessionFactoryBeanName" value="sqlSessionFactory"/>
        <!-- 指定包名，包名是dao接口所在的包名。
            MapperScannerConfigurer会扫描这个包中的所有接口，
            把每个接口都执行一次getMapper()方法，得到每个接口的dao对象。
            创建好的dao对象放入发哦spring的容器中的。
         -->
        <property name="basePackage" value="ctgu.qiny.dao"/>
    </bean>
</beans>
```

## 5. 测试

```java
@Test
public void test03() {
    ApplicationContext context =
        new ClassPathXmlApplicationContext("applicationContext.xml");
    StudentService studentService = (StudentService) context.getBean("studentService");
    studentService.queryStudent().forEach(System.out::println);
}
```

## 6. 使用属性配置文件配置数据库连接信息

* jdbc.properties

```properties
jdbc.username=root
jdbc.password=123456
jdbc.url=jdbc:mysql://localhost:3306/mybatis-learning?useSSL=false
```

* 修改spring的主配置文件

```xml
<!--  把数据库的配置信息，写在一个独立的文件，编译修改数据库的配置内容
        让spring支持jdbc.properties文件的位置
-->
<context:property-placeholder location="classpath:jdbc.properties"/>

<!-- 声明数据源DataSource，作用书链接数据库的 -->
<bean id="dataSource" class="com.alibaba.druid.pool.DruidDataSource"
      init-method="init" destroy-method="close">
    <!-- 使用属性配置文件中的数据，语法：${key} -->
    <property name="url" value="${jdbc.url}"/>
    <property name="username" value="${jdbc.username}"/>
    <property name="password" value="${jdbc.password}"/>
    <property name="maxActive" value="${jdbc.maxActive}"/>
</bean>
```

# Spring事务

1. 什么是事务

   * 讲mysql的时候，提出了事务。事务是指一组sql语句的集合，集合中有多条sql语句。可能是insert，update ，select ，delete。我们希望这些多个sql语句都能成功，或者都失败，这些sql语句的执行是一致的，作为个整体执行。

2. 在什么时候想到使用事务

   * 当我的操作，涉及到多个表，或者是多个sql语句的insert、update、delete。 需要保证这些语句都是成功才能完成我的功能，或者都失败，保证操作是符合要求的。
   * 在java代码中写程序，控制事务，此时事务应该放在哪里呢？
   * service类的业务方法上， 因为业务方法会调用多个dao方法，执行多个sql语句

3. 通常使用JDBC访问数据库，还是mybatis访问数据库怎么处理事务。

   1. jdbc访问数据库，处理事务 Connection conn; conn.commit(); conn.rollback();
   2. mybatis访问数据库，处理事务，SqlSession sqlSession; sqlSession.commit(); sqlSession.rollback();

4. 3问题中事务的处理方式，有什么不足

   1. 不同的数据库访问技术，处理事务的对象，方法不同，
      需要了解不同数据库访问技术使用事务的原理。
   2. 掌握多种数据库中事务的处理逻辑。什么时候提交事务，什么时候回滚事务。
   3. 处理事务的多种方法。

   总结：就是多种数据库的访问技术，有不同的事务处理的机制，对象，方法。

5. 怎么解决不足

   * spring提供一致处理事务的统一模型，能使用统一步骤，方式完成多种不同数据库访问技术的事务处理。
   * 使用spring的事务处理机制，可以完成mybatis访问数据库的事务处理
   * 使用spring的事务处理机制，可以完成hibernate访问数据库的事务处理
   * ...

6. 处理事务需要怎么做，做什么

   > spring处理事务的模型，使用的步骤都是固定的。把事务使用的信息提供给spring就可以了。

   1. 事务内部提交，回滚事务，使用的事务管理器对象，代替你完成commit，rollback。

      事务管理器是一个接口和他的众多实现类.

      接口：PlatfornTransactionManager 。定义了事务重要方法commit ，rollback

      实现类：spring把每一种数据库访问技术对应的事务处理类都创建好了
      * mybatis访问数据库 --- spring创建好的是DataSourceTransaotionManager
      * hibernate访间数据库 --- spring创建的是HibernateTransactionManager

      怎么使用：你需要告诉spring你用是那种数据库的访问技术，怎么告诉spring呢?
      声明数据库访问技术对于的事务管理器实现类，在 spring的配置文件中使用\<bean\>声明就可以了

      例如，你要使用mybatis访问数据库，你应该在xn1配置文件中
      <bean id="xxx” class="...DataSourceTransactionManager">

   2. 你的业务方法需要什么样的事务，说明需要事务的类型。
      说明方法需要的事务：

      1. 事务的隔高级别：有4个值.
         DEFAULT：采用DB默认的事务隔离级别。Mysql 的默认为REPEATABLE_READ，Oracle默认 为READ _COMMITTED。

         * READ UNCOMAITTED: 读未提交。未解决任何并发问题.
         * READ COMITTED:读已提交。解决脏读，存在不可重复读与幻读.
         * REPEATABLE READ: 可重友读.解决脏读。不可重女读，存在幻读
         * SERIALIZABLE: 串行化.不存在并发问题.

      2. 事务的超时时间：表示一个方法最长的执行时间，如果方法执行时超过了时间，事务就回滚。
         单位是秒，整数值， 默认是 -1。

      3. 事务的传播行为：控制业务方法是不是有事务的，是什么样的事务的。
         7个传播行为，表示你的业务方法调用时，事务在方法之间是如果使用的。

         * PROPAGATION REQUIRED

         * PROPAGATION REQUIRES NEW

         * PROPAGATION SUPPORTS

           > 以上三个需要掌握的
           
         * PROPAGATION MANDATORY
         
         * PROPAGATION NESTED
         
         * PROPAGATION NEVER
         
         * PROPACATION_NOT_SUPPORTED
      
   3. 提交事务，回滚事务的时机

      1. 当你的业务方法，执行成功，没有异常抛出，当方法执行完毕，spring在方法执行后提交事务。事务管理器commit。

      2. 当你的业务方法抛出运行时异常， spring执行回滚，调用事务管理器的rollback。

         运行时异常的定义：RuntimeException 和它的子类都是运行时异常，例如NullPointException，NumberFormatException。

      3. 当你的业务方法抛出非运行时异常，主要是受查异常和ERROR时，提交事务

         受查异常：在你写代码中，必须处理的异常。例如IOException, SQLException

7. 总结spring的事务

   1. 管理事务的是，事务管理和它的实现类
   2. spring的事务是一个统一模型
      1. 指定要使用的事务管理器实现类，使用\<bean\>
      2. 指定哪些类，哪些方法需要加入事务的功能
      3. 指定方法需要的隔离级别，传播行为，超时

   > 你需要告诉spring，你的项目中类信息，方法的名称，方法的事务传播行为。

8. spring框架中提供的事务处理方案

   1. 适合中小项目使用的，注解方案。
      spring框架自己用aop实现给业务方法增加事务的功能，使用@Transactional注解增加事务。
      @Transactional注解是spring框架自己注解，放在public方法的上面，表示当前方法具有事务。
      可以给注解的属性赋值，表示具体的隔离级别，传播行为，异常信息等等。

      使用@Transactional的步驟：

      1. 需要声明事务管理器对象 **\<bean id="xx" class="DataSourceTransactionManager"\>**

      2. 开启事务注解去掉，告诉Spring框架，我要使用注解的方式管理事务。

         spring使用aop机制，创建@Transactional所在的类型代理对象，给方法加入事务的功能。

         spring给事务方法加入事务：

         ​	在你的业务方法执行之前，先开启事务，在业务方法之后提交或回滚事务，使用aop的环绕通知

         ```java
         @Around("你要增加的事务功能的业务方法名称")
         Objcect myAround(){ 
             // 开启事务，spring给你开启
             try {
               buy(1001, 10);
                 spring的事务管理.commit();
             }catch(Exception e) {
                 spring的事务管理.rollback();
             }
         }
         ```

      3. 在你的方法的上面加入@Transactional

## 程序举例环境搭建

* 举例：购买商品 trans_ sale 项目
  本例要实现购买商品，模拟用户下订单，向订单表添加销售记录，从商品表减少库存。

### 1. 创建数据库、表

* 订单表

```sql
CREATE TABLE `sale` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `gid` int(11) NOT NULL,
  `nums` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
```

* 商品表

```sql
CREATE TABLE `goods` (
  `id` INT (11) NOT NULL,
  `name` VARCHAR (100),
  `amount` INT (11),
  `price` FLOAT (0),
  PRIMARY KEY (`id`)
) ENGINE = INNODB CHARSET = utf8mb4;
```

| id   | name       | amount | price |
| ---- | ---------- | ------ | ----- |
| 1001 | 笔记本电脑 | 100    | 5000  |
| 1002 | 手机       | 50     | 3000  |

### 2. 创建项目、实体类

项目的依赖同“spring整合mybatis”

* Sale、SaleDao

```java
public class Sale {
    private Integer id;
    private Integer gid;
    private Integer nums;
    // 省略getter和setter
}

public interface SaleDao {
    // 增加销售记录
    int insertSale(Sale sale);
}
```

* SaleDao.xml

```xml
<?xml version="1.0" encoding="utf8" ?>
<!DOCTYPE mapper
        PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
<mapper namespace="ctgu.qiny.dao.SaleDao">
    <insert id="insertSale">
        insert into `sale` (`gid`, `nums`) values (#{gid}, #{nums})
    </insert>
</mapper>
```

* Good、GoodDao

```java
public class Good {
    private Integer id;
    private String name;
    private Integer amount;
    private Float price;
    // 省略getter和setter
}

public interface GoodDao {
    // 更新库存
    // goods表示本次用户购买的商品信息，id，购买数量
    int updateGood(Good goods);

    // 查询商品的信息
    Good selectGood(Integer id);
}
```

* GoodDao.xml

```xml
<?xml version="1.0" encoding="utf8" ?>
<!DOCTYPE mapper
        PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
<mapper namespace="ctgu.qiny.dao.GoodDao">
    <update id="updateGood">
        update `goods` set `amount` = `amount` - #{amount}
    </update>

    <select id="selectGood" resultType="ctgu.qiny.entity.Good">
        select `id`, `name`, `amount`, `price` from `goods` where `id` = #{gid}
    </select>
</mapper>
```

* mybatis主配置文件

```xml
<?xml version="1.0" encoding="UTF8" ?>
<!DOCTYPE configuration
        PUBLIC "-//mybatis.org//DTD Config 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-config.dtd">
<configuration>

    <!--  设置别名  -->
    <typeAliases>
        <package name="ctgu.qiny.entity"/>
    </typeAliases>

    <mappers>
        <package name="ctgu.qiny.dao"/>
    </mappers>
</configuration>
```

* NotEnoughException异常类

```java
// 自定义的运行时异常
public class NotEnoughException extends RuntimeException{
    public NotEnoughException() {
        super();
    }

    public NotEnoughException(String message) {
        super(message);
    }
}
```

* BuyGoodService及其实现类

```java
public interface BuyGoodService {
    // 购买商品的方法，id：购买商品的编号，nums：购买的数量
    void buy(Integer id, Integer nums);
}


public class BuyGoodServiceImpl implements BuyGoodService {
    private SaleDao saleDao;
    private GoodDao goodDao;

    public BuyGoodServiceImpl() {
    }

    @Override
    public void buy(Integer id, Integer nums) {
        System.out.println("==== buy方法的开始 ====");

        Sale sale = new Sale();
        sale.setGid(id);
        sale.setNums(nums);
        saleDao.insertSale(sale);

        // 更新库存
        Good good = goodDao.selectGood(id);
        if (good == null) {
            // 商品不存在
            throw new NullPointerException("商品编号[" + id + "]: 商品不存在");
        }else if (good.getAmount()<nums){
            // 商品库存不足
            throw new NotEnoughException("商品编号[" + id + "]: 商品库存不足");
        }

        // 修改库存
        Good buyGood = new Good();
        buyGood.setId(id);
        buyGood.setAmount(nums);
        goodDao.updateGood(buyGood);
        System.out.println("==== buy方法的完成 ====");
    }

    public void setSaleDao(SaleDao saleDao) {
        this.saleDao = saleDao;
    }

    public void setGoodDao(GoodDao goodDao) {
        this.goodDao = goodDao;
    }
}
```

* spring主配置文件

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xmlns:context="http://www.springframework.org/schema/context"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd http://www.springframework.org/schema/context https://www.springframework.org/schema/context/spring-context.xsd">
    
    <context:property-placeholder location="classpath:jdbc.properties"/>

    <bean id="dataSource" class="com.alibaba.druid.pool.DruidDataSource"
          init-method="init" destroy-method="close">
        <property name="url" value="${jdbc.url}"/>
        <property name="username" value="${jdbc.username}"/>
        <property name="password" value="${jdbc.password}"/>
        <property name="maxActive" value="${jdbc.maxActive}"/>
    </bean>

    <bean id="sqlSessionFactory" class="org.mybatis.spring.SqlSessionFactoryBean">
        <property name="dataSource" ref="dataSource"/>
        <property name="configLocation" value="classpath:mybatis.xml"/>
    </bean>
    
    <bean class="org.mybatis.spring.mapper.MapperScannerConfigurer">
        <property name="sqlSessionFactoryBeanName" value="sqlSessionFactory"/>
        <property name="basePackage" value="ctgu.qiny.dao"/>
    </bean>

    <bean id="buyGoodServiceImpl" class="ctgu.qiny.service.impl.BuyGoodServiceImpl">
        <property name="goodDao" ref="goodDao"/>
        <property name="saleDao" ref="saleDao"/>
    </bean>
</beans>
```

* 测试

```java
@Test
public void test01() {
    ApplicationContext context =
            new ClassPathXmlApplicationContext("applicationContext.xml");
    BuyGoodService buyGoodService =
            (BuyGoodService) context.getBean("buyGoodServiceImpl");
    buyGoodService.buy(1001, 1);
}
```

### 3. 使用spring的事务管理机制

* 在spring配置文件中配置事务管理

```xml
<!--  使用spring的事务管理  -->
<!--  1. 声明事务管理器  -->
<bean id="transactionManager" class="org.springframework.jdbc.datasource.DataSourceTransactionManager">
    <!-- 连接的数据库，指定数据源 -->
    <property name="dataSource" ref="dataSource"/>
</bean>

<!-- 2. 开启事务注解驱动，告诉spring使用注解管理事务，创建代理对象
         transaction-manager：事务管理器对象的id   -->
<tx:annotation-driven transaction-manager="transactionManager"/>
```

* 给需要使用事务的方法中添加@Transactional注解

```java
/*@Transactional(
        propagation = Propagation.REQUIRED,
        isolation = Isolation.DEFAULT,
        readOnly = false,
        rollbackFor = {
                NullPointerException.class, NotEnoughException.class
        }
)*/
// 使用的是事务控制的默认值，默认的传播行为是REQUIRED，默认的隔离级别是DEFAULT
// 默认抛出运行时异常，回滚事务
@Transactional
@Override
public void buy(Integer id, Integer nums) {...
```

* 测试

```java
ApplicationContext context =
    new ClassPathXmlApplicationContext("applicationContext.xml");
BuyGoodService buyGoodService =
    (BuyGoodService) context.getBean("buyGoodServiceImpl");
System.out.println("service是代理："+buyGoodService.getClass().getName());
buyGoodService.buy(1001, 0);
/*
    service是代理：com.sun.proxy.$Proxy18
    ==== buy方法的开始 ====
    ==== buy方法的完成 ====
*/    
// 当执行buyGoodService.buy(1005, 0);时，会抛出NotEnoughException异常，但sale数据不会增加
```

## aspectJ配置aop处理事务

适合大型项目，有很多的类，方法，需要大量的配置事务，便用aspect框架功能，在spring配置文件中声明类，方法需要的事务。这种方式业务方法和事务配置完全分离。

实现步骤：都是在xml 配置文件中实现。

1. 要使用的是aspectj框架，需要加入依赖

```xml
<!-- aspect框架 -->
<dependency>
    <groupId>org.springframework</groupId>
    <artifactId>spring-aspects</artifactId>
    <version>5.3.5</version>
</dependency>
```

2. 声明事务管理器对象

```xml
<bean id="xx" class="DataSourceTransactionManager">...
```

3. 声明方法需要的事务类型（配置方法的事务属性【隔离级别，传播行为，超时】）
4. 配置aop：指定哪些哪类要创建代理

```xml
<!-- 2. 声明业务方法它的事务属性（隔离级别，传播行为，超过时间） -->
<tx:advice id="transactionInterceptor" transaction-manager="transactionManager">
    <!-- tx:attributes：配置事务属性 -->
    <tx:attributes>
        <!-- tx:method：给具体方法配置事务属性，method可以有多个，分别给不同的方法设置事务属性
                name：方法名称，  1) 完整的方法名称，不带有包和类
                                 2) 方法可以使用通配符，*表示任意字符
                propagation：传播行为，枚举值
                isolation：隔离行为
                rollback-for：你指定的异常类名，全限定类名。发生异常是一定会回滚。
        -->
        <tx:method name="buy" propagation="REQUIRED" isolation="DEFAULT"
                   rollback-for="java.lang.NullPointerException, ctgu.qiny.exce.NotEnoughException"/>
        <tx:method name="*" propagation="SUPPORTS" read-only="true"/>
    </tx:attributes>
</tx:advice>

<!-- 配置aop -->
<aop:config>
    <!-- 配置切入点表达式：指定哪些包中类要用事务
        id：切入点表达式的名称，唯一值
        expression：切入点表达式，指定哪些类要使用事务，aspectJ会创建代理对象。            
     -->
    <aop:pointcut id="servicePointcut" expression="execution(* *..service..*.*(..))"/>
    <!-- 配置增强器： 关联advice和pointcut
            advice-ref：通知，上面tx:advice那里的配置
            pointcut-ref：切入点表达式的id
    -->
    <aop:advisor advice-ref="transactionInterceptor" pointcut-ref="servicePointcut"/>
</aop:config>
```

## 复习

* spring
  * 什么是spring
    * 是一个框架，核心技术是IOC和AOP，实现解耦合。
    * 是一个容器，容器中存放的是java对象，需要的是把对象放入到容器中。
  * 怎么使用spring？
    * 把项目中用的对象放入到容器中
    * 让容器完成对象的创建，对象之间关系的管理（属性赋值）。
    * 我们在程序中从容器中获取要使用的对象。
  * 什么样的对象放入容器中
    * dao类、service类、controller类、工具类。
      1. 使用xml配置文件，\<bean\>。
      2. 使用注解。
    * spring中的对象默认都是单例的，在容器中这个名称的对象只有一个。
  * 不放入到spring容器中的对象有哪些？
    * 实体类对象，实体类数据是来自数据库的。
    * servlet、listener、filter这些对象应该交给tomcat进行管理。
  * 使用spring框架的步骤：
    1. 加入依赖
    2. 创建类：接口+实现类 | 没有接口的类
    3. 创建spring的配置文件，使用\<bean\>声明对象
    4. .我们使用容器中的对象，通过ApplicationContext接口和他的实现类ClassssPathXmlApplcactionContext的getBean方法
  * 核心技术
    * IOC：控制反转
      * 是一个理论、思想、概念：指导开发人员在容器中，代码之外管理对象，给属性赋值，管理依赖。
      * IOC的技术实现使用的是DI（依赖注入）：开发人员在项目中只需要提供对象的名称，对象的创建、查找赋值等都由容器内部实现。
      * spring使用的是DI的技术，底层使用的是反射机制。
      * 给属性赋值
        * set注入：: spring调用类的set方法实现属性赋值。
          * 简单类型的set注入：property-name-value
          * 引用类型的set注入：property-name-ref
        * 构造往入: spring调用有参数构适方法。
          1. \<constructor-arg\>的name属性。name表示构造方法的形参名。
          2. \<constructor-arg\>的index属性。name表示构造方法的形参的位置，从0开始。
        * 自动注入：由spring根据某些规则，给引用类型完成赋值。常用的有byName和byType
          1. byName：按名称注入，java类中引用类型的属性名和spring容器中bean的[id] -样,数据类型-样。这样的bean赋值给引用类型
          2. byType：按类型注入，java类中引用类型的是数据类型和spring容器中bean的class是同源关系的，这样的bean能够赋值给引用类型
      * 常用注解
        1. @Component 创建对象
        2. @Repository 创建dao对象
        3. @Service 创建Service对象，处理业务逻辑的，可以有事务功能。
        4. @Controller创建控制器对象，接收请求，显示处理结果的。
        5. @Value 简单类型的属性赋值
        6. @Autowired Spring框架中引用类型的赋值注解，支持byName，默认是byType。
        7. @Resource jdk中的注解，使用自动注入给引用类型赋值。支持byName、byType。默认是byName。
        8. 注解的使用步骤
           1. 加入依赖 spring-context；间接加入了spring-aop
           2. 在类中加入注解
           3. 在spring的配置文件中，加入组件扫描器的标签\<context:component-scan base-package="包名”>
      * IOC能实现解耦合
        * IOC能够实现业务对象之间的解耦合。例Iservice和dao对象之间的解耦合。
    * AOP：面向切面编程

      * 底层是动态代理

        1. jdk动态代理

           * 使用jdk反射包中的类实现创建代理对象的功能

           * 要求：目标类必须实现接口

        2. 2.cglib动态代理

           * 使用第三方的工具库,实现代理对象的创建
           * 一个要求：目标类必须能够继承,不能是final
           * 原理：就是继承，子类就是代理

      * aop：看做是动态代理的规范化，把视线动态代理的步骤进行了一个规范，定义

      * aop作用：

        1. 在目标类不修改源代码的情况下，增加功能
        2. 减少重复的代码
        3. 专注业务功能的实现
        4. 解耦合：业务功能和日志，事务这些非业务功能的耦合。

      * 什么时候考虑使用aop技术

        1. 当你要给一个系统中存在的类修改功能，但是原有类的功能不完善，但是你还有源代码，使用aop就增加功能
        2. 你要给项目中的多个类.增加个相同的功能，使用aop
        3. 给业务方法增加事务，日志输出

      * aop的实现框架
        1. spring实现了aop，实现方式是接口
        2. aspectj框架
           1. 使用注解可以实现aop的功能
           2. 使用xml配置文件中的标签实现aop功能
      * aop中的概念
        1. aspect：切面，表示给业务方法增加的功能，一般日志输出，事务，权限检查等是切面
        2. pointcut：切入点，是一个或多个JoinPoint的集合，表示切面功能执行的位置
        3. advice：通知，也叫增强，表示切面执行的时间，在方法前，方法后等等。
      * aspectj框架的使用
        1. 表示切面的执行时间，使用的通知注解
           1. @Before：前置通知，在目标方法之前先执行切面的功能。
           2. @AfterReturning：后置通知，在目标方法之后执行的，能够获取到目标方法的返回值。
           3. @Around：环绕通知，在目标方法前和后都能增强功能，控制目标方法的访问，修改返回值
           4. @AfterThrowing：异常通知，在目标方法抛出异常后执行的通知。
           5. @After：最终通知，总是会被执行的代码。
           6. @Pointcut 定义和管理切入点的辅助注解。
           7. 代理的使用方式
              1. 如果目标类有接口，框架使用jdk动态代理
              2. 如果目标没有接口，默认使用的CGLIB动态代理
              3. 有接口也可以强制使用CGLIB动态代理。
        2. 表示切面位置的切入点表达式：execution(访问修饰符 返回值 包名.类名.方法名称(方法的参数) 异常)
    * spring整合mybatis
      * 整合的想法：使用spring的ioc核心技术，把mybatis框架中使用的对象交给spring统一创建和管理。spring是容器，存放你项目中要使用的各种对象，例如Service对象，Dao对象，工具类等等。
    * 交给spring的mybatis对象
      1. 数据源DataSource，使用阿里公司的Druid连接池
      2. SqlSessionFactory对象，使用的SqlSessionFactoryBean在内部创建的SqlSessionFactory
      3. Dao代理对象，使用的MapperScanConfigure，在这个类的内部，调用getMapper，创建接口的Dao对象。