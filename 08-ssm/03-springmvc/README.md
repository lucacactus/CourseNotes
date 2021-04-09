# 第1章 SpringMVC概述

## 1.1 SpringMVC 简介

> SpringMVC：是基于Spring的一个框架，实际上就是Spring的一个模块，专门做web开发的。
>
> ​						可以理解是Servlet的一个升级。
>
> ​						web开发底层是servlet，框架是在servlet基础上面加入一些功能，让web开发更加方便。

> SpringMVC就是一个Spring：
>
> * Spring是容器，IOC能够管理对象，使用\<bean\>标签，@Component，@Repository，@Service，@Controller。
> * SpringMVC能够创建对象，放入到容器中（SpringMVC容器），SpringMVC容器中放的是控制器对象，
> * 我们要做的是使用@Controller创建控制器对象，把对象放入到SpringMVC容器中，把创建的对象作为控制器使用这个控制器对象能接收用户的请求，显示处理结果，就当做是一个servlet使用。
> * 使用@Controller注解创建的是一个普通类的对象，不是servlet。SpringMVC赋予了控制器对象一些额外的功能。

>Web开发底层是Servlet，SpringMVC中有一个对象是Servlet：DispatcherServlet
>
>**DispatherServlet**：负责接收用户的所有请求，用户把请求给了DispatherServlet，之后DispatherServlet把请求转发给我们的Controller对象，最后是Controller对象处理请求。

**前端--->DispatcherServlet（Servlet）--->转发，分配给--->Controller对象（@Controller注解创建的对象）**

## 1.2 SpringMVC 优点

1. 基于MVC架构
   基于MvC架构，功能分工明确。解耦合，
2. 容易理解，上手快；使用简单。
   就可以开发一个注解的SpringMVC项目，SpringMVC也是轻量级的，jar很小。不依赖的特定的接口和类。
3. 作为Spring框架一部分，能够使用Spring的IOC和AOP。方便整合Struts，MyBatis，Hiberate，JPA 等其他框架。
4. SpringMVC强化注解的使用，在控制器，Service，Dao都可以使用注解。方便灵活。
   使用@Controller创建处理器对象，@Service创建业务对象，@Autowired或者@Resource在控制器类中注入Service，Service类中注入Dao。

## 1.3 第一个SpringMVC项目

需求：用户在页面发起一个请求，请求交给SpringMVC的控制器对象，并显示请求的处理结果（在结果页面显示一个欢迎语句）。

实现步骤：

1. 新建web maven工程
2. 加入依赖
   * spring-webmvc依赖，间接把spring的依赖都加入到项目
   * jsp，servlet依赖。
3. 重点：在web.xml中注册SpringMVC框架的核心对象DispatcherServlet.
   1. DispatcherServlet叫做中央调度器，是一个Servlet，它的父类是继承HttpServlet。
   2. DispatcherServlet也叫作前端控制器（front controller）
   3. DispatcherServlet负责接收用户提交的请求，调用其他的控制器对象，并把请求的处理结果显示给用户。
4. 创建一个发起请求的页面：index.jsp
5. 创建控制器类
   1. 在类的上面加入@Controller注解，创建对象，并放入到SpringMVC容器中
   2. 在类中的方法上面加入@RequestMapping注解。
6. 创建一个作为结果的jsp，显示请求的处理结果。
7. 创建springmvc的配置文件（spring的配置文件一样）
   1. 声明组件扫描器，指定@Contorller注解所在的包名
   2. 声明视图解析器。帮助处理视图的。

* 引入依赖

```xml
<dependencies>
    <!-- servlet-api -->
    <dependency>
        <groupId>javax.servlet</groupId>
        <artifactId>javax.servlet-api</artifactId>
        <version>4.0.1</version>
        <scope>provided</scope>
    </dependency>

    <dependency>
        <groupId>org.springframework</groupId>
        <artifactId>spring-webmvc</artifactId>
        <version>5.3.5</version>
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
                <source>1.8</source>
                <target>1.8</target>
            </configuration>
        </plugin>
    </plugins>
</build>
```

* web.xml

```xml
<?xml version="1.0" encoding="UTF-8"?>
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">
    <!-- 声明，注册SpringMVC的核心对象DispatcherServlet
            需要在tomcat服务器启动后，创建DispatcherServlet对象的实例。
            为什么要创建DispatcherServlet对象的实例呢?
            因为DispatcherServlet在他的创建过程中，会同时创建SpringMVC容器对象，
            读取SpringMVC的配置文件，把这个配置文件中的对象都创建好，
            当用户发起请求时就可以直接使用对象了。

            Servlet的初始化会执行init()方法。DispatcherServlet在init()中 {
                // 创建容器，读取配置文件
                WebApplicationContext ctx =
                    new ClassPathXMlApplicationContext("springmvc.xml");
                // 把容器对象放入到ServletContext中
                getServletContext().setAttribute(key, ctx);
            }

            启动tomcat报错，读取这个文件/WEB-INF/springmvc-servlet.xml(/WEB-INF/springmvc-servlet.xml)
            springmvc创建容器对象是，读取配置文件默认是/WEB-INF/<servlet-name>-servlet.xml
     -->
    <servlet>
        <servlet-name>springmvc</servlet-name>
        <servlet-class>org.springframework.web.servlet.DispatcherServlet</servlet-class>
        <!-- 在tomcat启动后，创建Servlet对象
            load-on-startup：表示Tomcat启动后创建对象的顺序。
            它的值是整数，数值越小，tomcat创建对象的时间越早。
            大于等于0的整数。
         -->
        <!-- 自定义springmvc读取的配置文件的位置 -->
        <init-param>
            <!-- springmvc的配置文件的位置的属性 -->
            <param-name>contextConfigLocation</param-name>
            <!-- 指定自定义文件的位置 -->
            <param-value>classpath:springmvc.xml</param-value>
        </init-param>
        <load-on-startup>1</load-on-startup>
    </servlet>
</web-app>
```

* springmvc.xml（让web.xml找到mvc的配置文件）

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd">

</beans>
```

* web.xml配置url-pattern

```xml
<servlet-mapping>
    <servlet-name>springmvc</servlet-name>
    <!--
        使用框架的时候，url-pattern可以使用两种值
            1. 使用扩展名的方式，语法 *.xxx，xxx是自定义的扩展名。常用的方式 *.do、*.action、*.mvc等等
                http://localhost:8080/myweb/some.do
                http://localhost:8080/myweb/other.do
            2. 使用斜杠 "/"
    -->
    <url-pattern>*.do</url-pattern>
</servlet-mapping>
```

* index.jsp（用于返回请求）

```jsp
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
    <head>
        <title>Title</title>
    </head>
    <body>
        <p>第一个springmvc项目</p>
        <p><a href="some.do">发起some.do请求</a></p>
    </body>
</html>
```

* show.jsp（用于展示Controller处理后的数据）

```jsp
<%--
  Created by IntelliJ IDEA.
  User: 34984
  Date: 2021/4/6
  Time: 16:40
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Title</title>
</head>
<body>
    <h3>show.jsp从request作用域获取数据</h3>
    <h3>message: ${message}</h3>
</body>
</html>
```

* 创建Controller

```java
// @Controller：创建处理器对象，对象放在springmvc容器中。
// 位置：在类的上面
// 和Spring中讲的@Service，@Component一致
@Controller
public class MyController {
    /*
        处理用户提交的请求，springmvc中是使用方法来处理的。
        方法是自定义的,可以有多种返回值，多种参数，方法名称自定义。

    */
    /*
        准备使用doSome方法处理some.do请求。
        @RequestMapping：请求映射，作用是把一个请求地址和一个方法绑定在一起。
                         一个请求指定一个方法处理。
            属性：1. value是一个String表示请求的uri地址的。
                    value的值必须是唯一的，不能重复。在使用是，推荐地址以“/”开头
            位置：
                 1. 在方法的上面，常用的。
                 2. 在类的上面
            说明：   使用RequestMapping修饰的方法叫做处理器方法或者控制器方法。
                    使用@RequestMapping修饰的方法可以处理请求的，类似Servlet中的doGet，doPost
             返回值：ModelAndView 表示本次请求的处理结果
                    Model：数据，请求处理完成后，要显示给用户的数据
                    View：视图，比如jsp等等
    */
    @RequestMapping("/some.do")
    public ModelAndView doSome() {
        // 处理some.do请求，不调用service就当service调用处理完成了。
        ModelAndView mv = new ModelAndView();
        // 添加数据，框架在请求的最后把数据放入到request作用域。
        // 相当于request.setAttribute("message","Welcome to SpringMVC");
        mv.addObject("message", "Welcome to SpringMVC");
        // 指定视图，指定视图的完整路径
        // 框架对视图执行的forward操作，request.getRequestDispatcher("/show.jsp").forward(..);
        mv.setViewName("/show.jsp");
        //返回mv
        return mv;
    }
}
```

* 在springmvc.xml中声明组件扫描器

```xml
<context:component-scan base-package="ctgu.qiny.controller"/>
```

* 运行项目，点击链接发送some.do请求，就能得到返回的show.jsp

## 1.4 SpringMVC请求处理的过程

* 发起some.do请求。
* tomcat收到请求，读取web.xml文件，根据文件的url-pattern的映射规则知道*.do的请求是给DispatcherServlet（中央调度器）的。
* 中央调度器根据init-param获取springmvc的配置文件的位置。
* 根据springmvc.xml的注解扫描配置知道some.do是给MyController类的doSome()方法的。
* DispatcherServlet把some.do转发给MyController的doSome()方法。
* 框架执行doSome()，把得到的ModelView进行处理，转发到show.jsp。

## 1.5 SpringMVC执行过程源代码分析

1. tomcat启动，创建容器的过程

   通过load-on-start标签指定的1，创建DisaptcherServlet对象，
   DisaptcherServlet它的父类是继承HttpServlet的，它是一个serlvet，在被创建时，会执行init()方法。

   在init()方法中

   ```java
   // 创建容器,读取配置文件
   webApplicationcontext ctx = new classPathXmlApplicationcontext ("springmvc.xml" );
   //把容器对象放入到ServletContext中
   getServletContext().setAttribute(key,ctx);
   ```

   上面创建容器作用：创建@Controller注解所在的类的对象，创建MyController对象，
   这个对象放入到 springmvc的容器中，容器是map ，类似map.put ("myController", MyController对象)

2. 请求的处理过程

   执行servlet的service()

   ```java
   protected void service(HttpServletRequest request, HttpServletResponse response);
   
   protected void doService(HttpServletRequest request, HttpServletResponse response);
   
   DispatcherServlet doDispatch(request, response){
       // 调用MyController的.doSome()方法
   }
   ```

## 1.6 配置视图解析器

* 为了防止用户随意访问，将show.jsp放在WEB-INF的子目录下。

* 在springmvc.xml下声明视图解析器，帮助开发人员设置视图文件的路径

```xml
<!-- 视图解析器 -->
<bean class="org.springframework.web.servlet.view.InternalResourceViewResolver">
    <!-- 后缀的视图解析器 -->
    <property name="prefix" value="/WEB-INF/view/"/>
    <!-- 前缀的视图解析器 -->
    <property name="suffix" value=".jsp"/>
</bean>
```

* 多个请求也可以放在一个Controller的方法里面
* 语法：

```java
@RequestMapping({"/some.do","/first.do"})
```

# 第2章 SpringMVC注解式开发

### 2.1 @RequestMapping详细

* @RequestMapping放在Controller类上面可以为这个Controller的方法的处理路由添加前缀



* method属性可以控制请求的处理方式，不指定时，任意请求方式都能够被接收。

  ```java
  @RequestMapping(value = "/some.do", method = RequestMethod.POST)// 指定为post请求方式
  ```

## 2.2 处理器方法的参数

### 2.2.1 使用request对象接收请求参数

* 原始方式：参数中使用HttpServletRequest对象的getParameter方法获取请求参数。

  ```java
  @RequestMapping(value = "/some.do")
  public ModelAndView doSome(HttpServletRequest request) {
      if (request.getParameter("req") != null) {
          System.out.println(request.getParameter("req"));
      }
      //...
  }
  //xxx/some.do?req=hello访问时可以在控制台看到打印出来的hello信息
  ```

### 2.2.2 框架接收参数——逐个接收  

  > 要求：处理器（控制器）方法的形参名和请求中参数名必须一致
  >
  > 同名的请求参数赋值给同名的形参。

  * 框架接收请求参数——使用request对象接收请求参数

    ```java
    String strName = request.getParameter("name");
    String strAge = request.getParameter("age");
    ```

  * SpringMVC框架通过DispatcherServlet调用MyController 的dosome()方法
    调用方法时，按名称对应，把接收的参数赋值给形参
    dosome (strName , Integer.valueOf(strAge))
    框架会提供类型转换的功能，能把string转为 int、long、float、double等类型。

  * 使用int接收空串时会报解析错误(400)，所以可以用包装类Integer来接收null

  ```java
  @RequestMapping("/get01.do")
  public void doGet01(String name, Integer age) {
      System.out.println(name);
      System.out.println(age);
  }
  // 发请求localhost:端口号/get01.do?name=zhangsan&age=24
  /*结果：
  zhangsan
  24
  */
  // 虽然页面会返回404，不过控制台还是能正常显示的，问题不大。
  ```

* 当使用get方式接收中文参数时，会发生乱码错误
* 当使用post方式接收中文参数时，会发生乱码错误

### 2.2.3 过滤器方式解决中文乱码错误

* 在web.xml中配置

```xml
<!--  注册声明过滤器，解决post请求乱码的问题  -->
<filter>
    <filter-name>characterEncodingFilter</filter-name>
    <filter-class>org.springframework.web.filter.CharacterEncodingFilter</filter-class>
    <!-- 设置项目中使用的字符编码 -->
    <init-param>
        <param-name>encoding</param-name>
        <param-value>utf8</param-value>
    </init-param>
    <!-- 强制请求对象（HttpServletRequest）使用encoding编码 -->
    <init-param>
        <param-name>forceRequestEncoding</param-name>
        <param-value>true</param-value>
    </init-param>
    <!-- 强制应答对象（HttpServletResponse）使用encoding编码 -->
    <init-param>
        <param-name>forceResponseEncoding</param-name>
        <param-value>true</param-value>
    </init-param>
</filter>
<filter-mapping>
    <filter-name>characterEncodingFilter</filter-name>
    <!-- 表示强制所有的请求先通过过滤器处理 -->
    <url-pattern>/*</url-pattern>
</filter-mapping>
```

### 2.2.4 使用@RequestParam解决参数名与请求属性名不一致的问题

* 属性值：
  * value：属性接收的请求参数
  * required：是不是必填的选项，默认为true

```java
@RequestMapping(value = "/get01.do", method = RequestMethod.POST)
public void doGet01(@RequestParam(value = "name", required = false) String name1,
                    @RequestParam(value = "age", required = false) Integer age1) {
    // name1的实参就能接收到name的请求参数值了
    // 两个参数不是必填的，可以为空
    System.out.println(name1);
    System.out.println(age1);
}
```

### 2.2.5 框架接收参数——使用对象来接收

* 处理器方法形参是java对象，这个对象的属性名和请求中参数名是一样的。
* 框架会创建形参的java地形，给属性赋值。请求中的参数名是name，框架会调用setName()

```java
// 保存请求参数值的一个普通类
public class Student {
    // 属性名和请求里的参数名一致
    private String name;
    private Integer age;
    // 省略getter、setter以及toString()
}
```

```java
@RequestMapping(value = "/get02.do")
public void doGet02(Student student) {
    System.out.println(student);
}
```

## 2.3 处理器方法的返回值

### 2.3.1 返回ModelAndView

* 若处理器方法处理完后，需要跳转到其它资源，且又要在跳转的资源间传递数据，此时处理器方法返回ModelAndView比较好。当然，若要返回 ModelAndView，则处理器方法中需要定义ModelAndView对象。
* 在使用时，若该处理器方法只是进行跳转而不传递数据，或只是传递数据而并不向任何资源跳转（如对页面的Ajax异步响应)，此时若返回ModelAndView，则将总是有一部分多余:要么Model多余，要么 View多余。即此时返回ModelAndView将不合适。

### 2.3.2 返回字符串String

> 返回值为String：表示视图，可以是逻辑名称，也可以是完整的视图路径。

* 如果配置了视图解析器，框架则会执行forward转发操作。

* 比如视图解析器已经配置了show到show.jsp中，则

```java
@RequestMapping("/restr.do")
public String returnString(HttpServletRequest request){
    // 手动添加数据到request作用域
    request.setAttribute("message", "hello");
    return "show";
}
```

### 2.3.3 返回void

不能表示数据，也不能表示视图

在处理ajax的时候，可以使用void返回值。通过HttpServletResponse输出数据。响应ajax请求。

* 使用jackson将对象转为json格式返回（引入依赖）

```xml
<!-- jackson-databind -->
<dependency>
    <groupId>com.fasterxml.jackson.core</groupId>
    <artifactId>jackson-databind</artifactId>
    <version>2.12.2</version>
</dependency>
```

```java
//处理器方法返回void，响应ajax请求（这里用postman来代替）
@RequestMapping("/void.do")
public void returnVoid(HttpServletResponse response, Student student) throws IOException {
    String value = null;
    if(student!=null){
        ObjectMapper om = new ObjectMapper();
        value = om.writeValueAsString(student);
    }
    response.setContentType("application/json;charset=utf8");
    PrintWriter writer = response.getWriter();
    writer.println(value);
    writer.flush();
    writer.close();
}
// postman向xxx/void.do发送name:张三和age:24的数据，服务器就能返回json格式
```

### 2.3.4 返回值Object

* Object：例如String，Integer，Map，List，Student等都是对象。
* 对象有属性，属性就是数据，所以返回Object表示数据，和视图无关。
* 可以使用对象表示的数据，响应ajax请求。
* SpringMVC处理器方法返回Object，可以转为json输出到浏览器，响应ajax请求。

* 步骤：

  1. 加入处理json的工具库依赖，SpringMVC默认使用的是jsckson

     > 参考2.3.3

  2. 在SpringMVC配置文件**springmvc.xml**加入\<mvc:annotation-driven\>注解驱动。

     * 一个坑点：注解驱动一定要用mvc命名空间中的。参考：https://blog.csdn.net/qq_41518597/article/details/102787135

  3. 在处理器方法的上面加入@ResponseBody注解

* SpringMVC处理器方法返回Object，可以转为json输出浏览器，响应ajax的内部原理。
  * 表示看不下去 <font color="green">**):-(**</font> 
  * **如果想看的话在这：[视频](https://www.bilibili.com/video/BV1sk4y167pD)p26后半~p27~p28**
* List列表直接返回就行了。

### 2.3.5 处理String（表示数据而不是视图）

> 参考2.3.4 直接返回String类型
>
> 在前面加入@ResponseBody就表示返回的是数据而不是视图
>
> 此时会有中文乱码问题。
>
> 此时只要指定@RequestMapping注解的属性produces="text/plain;charset=utf8"即可

```java
@ResponseBody
@RequestMapping(value = "/string.do", produces = "text/plain;charset=utf8")
public String returnString() {
    return "Hello, this is SpringMVC 这里是";
}
```

* 也可以在springmvc.xml配置，这样就不用在每个方法里面声明了

```xml
<?xml version="1.0" encoding="UTF8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xmlns:context="http://www.springframework.org/schema/context"
       xmlns:mvc="http://www.springframework.org/schema/mvc"
       xsi:schemaLocation="
                           http://www.springframework.org/schema/beans 
                           http://www.springframework.org/schema/beans/spring-beans.xsd
                           http://www.springframework.org/schema/context 
                           https://www.springframework.org/schema/context/spring-context.xsd
                           http://www.springframework.org/schema/mvc 
                           https://www.springframework.org/schema/mvc/spring-mvc-4.0.xsd">
    <context:component-scan base-package="ctgu.qiny.controller"/>
    <!-- 使用spring mvc -->
    <mvc:annotation-driven>
        <!-- 解决@ResponseBody中文乱码 -->
        <mvc:message-converters>
            <bean class="org.springframework.http.converter.StringHttpMessageConverter">
                <constructor-arg value="UTF-8"/>
            </bean>
        </mvc:message-converters>
    </mvc:annotation-driven>
</beans>
```

### 2.3.6 中央调度器的url-pattern设置为 “/”

* 正常访问静态资源（图片、js文件、html……），是交给tomcat服务器来处理的，与框架无关。
* 发起some.do请求，是交给中央调度器处理的。

* 当项目中的url-pattern使用了"/"，它会替代tomcat中的default。导致所有的静态资源都给DispatcherServlet处理，默认情况下DispatcherServlet没有处理静态资源的能力。没有控制器对象能处理静态资源的访问。所以静态资源（html、图片、js等）都是404。

## 2.4 url-pattern改为"/"后静态资源的处理

### 2.4.1 第一种静态资源的处理方式

```xml
<!-- 
	需要在springmvc配置文件加入<mvc:default-servlet-handler>
	原理是：加入这个标签后，框架会创建控制器对象DefaultServletHttpRequestHandler
	类似我们自己创建的MyController。
	DefaultServletHttpRequestHandler这个对象可以把接收的请求转发给tomcat的default这个servlet
 -->
<mvc:default-servlet-handler/>
```

### 2.4.2 第二种静态资源的处理方式

```xml
<!--
	mvc:resources 加入后框架会创建ResourceHttpRequestHandler这个处理器对象
	让这个对象处理静态资源的访问，不依赖tomcat服务器。
		mapping: 访问静态资源的uri地址，可以使用通配符**
			例如image/**：表示image/p1.jpg、image/user/logo.gif……
		location: 静态资源在你的项目中的目录位置。
-->

<mvc:resources mapping="/images/**" location="/image/"/>
<mvc:resources mapping="/html/**" location="/html/"/>
<mvc:resources mapping="/js/**" location="/js/"/>
<mvc:resources mapping="/css/**" location="/css/"/>
```

### 2.4.3 一条配置处理所有的静态资源

> 其实就是把mapping改为/static/**，然后所有资源都放在static目录下面。

## 2.5 相对路径和绝对路径

> 在jsp、html中使用的地址；都是在前端页面中的地址，都是相对地址。

* 地址分类：

  1. 绝对地址，带有协议名称的是绝对地址，http://www.baidu.com

  2. 相对地址，没有协议开头的，例如 user/some.do、/user/some.do

     相对地址不能独立使用，必须有一个参考地址，通过参考地址+相对地址本身才能指定资源。

  3. 参考地址

     * 在你的页面中的，访问地址不加“/”，访问的是当前页面的地址+连接的地址

     * 在你的页面中的，访问地址加“/”，访问的是服务器地址+连接的地址

# 第3章 SSM整合开发

SpringMVC：视图层，界面层，负责接收请求，显示处理结果的。

Spring：业务层，管理service，dao，工具类对象的。

MyBatis：持久层，用来访问数据库的。

* 用户发起请求--->SpringMVC接收请求--->Spring中的service对象--->MyBatis处理数据

SSM整合也叫做SSI（IBatis也就是mybatis的前身），整合中有容器。

1. 第一个容器springMVC容器,管理controller控制器对象的。
2. 第二个容器spring容器，管理service，Dao，工具类对象的

* 我们要做的就是把使用的对象交给合适的容器创建，管理。
  * 把Controller还有web开发的相关对象交给springmvc容器，这些web用的对象写在springmvc配置文件中
  * service，dao对象定义在Spring的配置文件中，让Spring来管理这些对象。

* SpringMVC容器和spring容器是有关系的，关系已经确定好了
  SpringMVC容器是spring容器的子容器，类似java中的继承。子可以访问父的内容。
  在子容器中的Controller可以访问父容器中的Service对象，就可以实现Controller使用Service对象

实现步骤：

0. 创建数据库
1. 新建maven web项目
2. 加入依赖
   * springmvc
   * spring
   * mybatis
   * jackson
   * mysql驱动
   * druid连接池
   * servlet、jsp

3. 写web.xml
   * 注册DispatcherServlet，目的：
     * 创建SpringMVC容器对象，才能创建Controller类对象。
     * 创建的是Servlet，才能接受用户的请求
   * 注册Spring的监听器：ContextLoaderListener，目的：
     * 创建Spring的容器对象，才能创建Service，Dao等对象。
   * 注册字符集过滤器，解决post请求乱码的问题
4. 创建包，Controller包，Service包，Dao包，实体类包
5. 写SpringMVC、Spring、MyBatis的配置文件。
   * SpringMVC配置文件。
   * Spring配置文件。
   * MyBatis主配置文件。
   * 数据库的属性配置文件。
6. 写代码：dao接口和mapper文件，service和实现类，controller，实体类。
7. 写jsp页面

## 3.1 依赖和插件

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
    <!-- servlet-api -->
    <dependency>
        <groupId>javax.servlet</groupId>
        <artifactId>javax.servlet-api</artifactId>
        <version>4.0.1</version>
        <scope>provided</scope>
    </dependency>

    <dependency>
        <groupId>org.springframework</groupId>
        <artifactId>spring-webmvc</artifactId>
        <version>5.3.5</version>
    </dependency>

    <!-- jackson-databind -->
    <dependency>
        <groupId>com.fasterxml.jackson.core</groupId>
        <artifactId>jackson-databind</artifactId>
        <version>2.12.2</version>
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

## 3.2 web.xml配置

```xml
<?xml version="1.0" encoding="UTF8"?>
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">

    <!--  中央调度器 -->
    <servlet>
        <servlet-name>springmvc</servlet-name>
        <servlet-class>org.springframework.web.servlet.DispatcherServlet</servlet-class>
        <init-param>
            <param-name>contextConfigLocation</param-name>
            <param-value>classpath:springmvc.xml</param-value>
        </init-param>
        <load-on-startup>1</load-on-startup>
    </servlet>
    <servlet-mapping>
        <servlet-name>springmvc</servlet-name>
        <url-pattern>/</url-pattern>
    </servlet-mapping>

    <!--  注册spring的监听器  -->
    <context-param>
        <param-name>contextConfigLocation</param-name>
        <param-value>classpath:applicationContext.xml</param-value>
    </context-param>
    <listener>
        <listener-class>org.springframework.web.context.ContextLoaderListener</listener-class>
    </listener>

    <!-- utf8字符过滤 -->
    <filter>
        <filter-name>characterEncodingFilter</filter-name>
        <filter-class>org.springframework.web.filter.CharacterEncodingFilter</filter-class>
        <init-param>
            <param-name>encoding</param-name>
            <param-value>utf8</param-value>
        </init-param>
    </filter>
    <filter-mapping>
        <filter-name>characterEncodingFilter</filter-name>
        <url-pattern>/*</url-pattern>
    </filter-mapping>
</web-app>
```

## 3.3 springmvc的配置文件

```xml
<?xml version="1.0" encoding="UTF8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xmlns:context="http://www.springframework.org/schema/context"
       xmlns:mvc="http://www.springframework.org/schema/mvc"
       xsi:schemaLocation="
                           http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd
                           http://www.springframework.org/schema/context https://www.springframework.org/schema/context/spring-context.xsd
                           http://www.springframework.org/schema/mvc https://www.springframework.org/schema/mvc/spring-mvc-4.0.xsd">
    <!--  声明组件扫描器  -->
    <context:component-scan base-package="ctgu.qiny.controller"/>

    <!--  视图解析器  -->
    <bean class="org.springframework.web.servlet.view.InternalResourceViewResolver">
        <property name="prefix" value="/WEB-INF/jsp"/>
        <property name="suffix" value=".jsp"/>
    </bean>

    <!-- 使用spring mvc注解驱动 -->
    <mvc:annotation-driven>
        <!-- 解决@ResponseBody中文乱码 -->
        <mvc:message-converters>
            <bean class="org.springframework.http.converter.StringHttpMessageConverter">
                <constructor-arg value="UTF-8"/>
            </bean>
        </mvc:message-converters>
    </mvc:annotation-driven>

    <!-- 静态资源访问 -->
    <mvc:resources mapping="/static/**" location="/static/"/>
</beans>
```

## 3.4 配置数据库信息

```properties
jdbc.username=root
jdbc.password=123456
jdbc.url=jdbc:mysql://localhost:3306/mybatis-learning?useSSL=false
jdbc.maxActive=20
```

## 3.5 配置applicationContext

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xmlns:context="http://www.springframework.org/schema/context"
       xsi:schemaLocation="http://www.springframework.org/schema/beans
       http://www.springframework.org/schema/beans/spring-beans.xsd
       http://www.springframework.org/schema/context
       https://www.springframework.org/schema/context/spring-context.xsd">

    <!--  spring配置文件：声明service、dao、工具类等对象  -->
    <!--  加载数据库信息配置文件  -->
    <context:property-placeholder location="classpath:jdbc.properties"/>

    <!--  声明数据源，连接数据库  -->
    <bean id="dataSource" class="com.alibaba.druid.pool.DruidDataSource" init-method="init" destroy-method="close">
        <property name="url" value="${jdbc.url}"/>
        <property name="username" value="${jdbc.username}"/>
        <property name="password" value="${jdbc.password}"/>
        <property name="maxActive" value="${jdbc.maxActive}"/>
    </bean>

    <!--  SqlSessionFactoryBean创建SqlSessionFactory  -->
    <bean id="sqlSessionFactory" class="org.mybatis.spring.SqlSessionFactoryBean">
        <property name="dataSource" ref="dataSource"/>
        <property name="configLocation" value="classpath:mybatis.xml"/>
    </bean>

    <!-- 声明mybatis的扫描器，创建dao对象 -->
    <bean class="org.mybatis.spring.mapper.MapperScannerConfigurer">
        <property name="sqlSessionFactoryBeanName" value="sqlSessionFactory"/>
        <property name="basePackage" value="ctgu.qiny.dao"/>
    </bean>

    <!-- 声明service注解@Service所在的包名位置 -->
    <context:component-scan base-package="ctgu.qiny.service"/>

    <!-- 事务配置：注解的配置，aspectJ的配置 -->
</beans>
```

## 3.6 mybatis主配置文件

```xml
<!DOCTYPE configuration
        PUBLIC "-//mybatis.org//DTD Config 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-config.dtd">
<configuration>
    <!-- 设置别名 -->
    <typeAliases>
        <package name="ctgu.qiny.entity"/>
    </typeAliases>
    <mappers>
        <package name="ctgu.qiny.dao"/>
    </mappers>
</configuration>
```

## 3.7 编写实体类和dao接口

* Student实体类

```java
public class Student {
    private Integer id;
    private String name;
    private Integer age;
    private String email;
    // 省略getter、setter以及toString()
}
```

* StudentDao接口

```java
public interface StudentDao {

    int insertStudent(Student student);

    List<Student> selectStudents();

}
```

* StudentDao.xml mapper文件

```xml
<?xml version="1.0" encoding="utf8" ?>
<!DOCTYPE mapper
        PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
<mapper namespace="ctgu.qiny.dao.StudentDao">
    <insert id="insertStudent">
        insert into `student` values (#{id}, #{name}, #{email}, #{age})
    </insert>
    <select id="selectStudents" resultType="Student">
        select `id`, `name`, `email`, `age` from `student` order by `id`
    </select>
</mapper>
```

## 3.8 创建StudentService接口及其实现类

* StudentService接口

```java
public interface StudentService {

    int addStudent(Student student);

    List<Student> findStudents();

}
```

* StudentServiceImpl实现类

```java
@Service
public class StudentServiceImpl implements StudentService {

    @Resource
    private StudentDao studentDao;

    public void setStudentDao(StudentDao studentDao) {
        this.studentDao = studentDao;
    }

    @Override
    public int addStudent(Student student) {
        return this.studentDao.insertStudent(student);
    }

    @Override
    public List<Student> findStudents() {
        return this.studentDao.selectStudents();
    }
}
```

## 3.9 编写Controller类

```java
@Controller
@RequestMapping("/student")
public class StudentController {

    @Resource
    private StudentService studentService;

    // 注册学生
    @ResponseBody
    @RequestMapping("/add")
    public Boolean addStudent(Student student) {
        return this.studentService.addStudent(student) == 1;
    }

    // 查询学生
    @ResponseBody
    @RequestMapping("/find")
    public List<Student> findStudents() {
        return this.studentService.findStudents();
    }

}

```