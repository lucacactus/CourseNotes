# 框架概述

## 三层架构

三层架构包含的三层:

* 界面层(User Interface layer)、业务逻辑层( Business Logic Layer)、数据访问层( Data access layer)
* 三层的职责
  1. 界面层(表示层，视图层)：主要功能是接受用户的数据，显示请求的处理结果。使用web页面和
     用户交互，手机app也就是表示层的，用户在app中操作，业务逻辑在服务器端处理。
  2. 业务逻辑层：接收表示传递过来的数据，检查数据，计算业务逻辑，调用数据访问层获取数据。
  3. 数据访问层：与数据库打交道。主要实现对数据的增、删、改、查。将存储在数据库中的数据提交
     给业务层，同时将业务层处理的数据保存到数据库。

## 框架

> 框架(Framework) 是整个或部分系统的可重用设计，表现为一组抽象构件及构件实例间交互的方法；另一种认为，框架是可被应用开发者定制的应用骨架、模板。
> 简单的说，框架其实是半成品软件，就是一组组件，供你使用完成你自己的系统。从另一个角度来说框架一个舞台，你在舞台上做表演。在框架基础上加入你要完成的功能。
> 框架安全的，可复用的，不断升级的软件。

框架是一个舞台，一个模版
模版:

1. 规定了好了一些条款， 内容。
2. 加入自己的东西

框架是一个模块

1. 框架中定义好了一些功能。这些功能是可用的。
2. 可以加入项目中自己的功能，这些功能可以利用框架中写好的功能。|

框架是一个软件，半成品的软件，定义好了一些基础功能，需要加入你的功能就是完整的。

基础功能是可重复使用的，可升级的。

框架特点:

1. 框架一般不是全能的，不能做所有事情
2. 框架是针对某一个领域有效。特长在某一个方面，比如mybatis做数据库操作强，但是他不能做其它的。
3. 框架是一个软件

## JDBC缺陷

* 代码比较多，开发效率低
* 需要关注Connection、Statement、ResultSet 对象创建和销毁
* 对ResultSet查询的结果，需要自己封装为List
* 重复的代码比较多些
* 业务代码和数据库的操作混在一起

## MyBatis能做什么

> MyBatis框架:
>
> ​	MyBatis本是apache的一个开源项目iBatis，2010年这个项目由apache software foundation迁移到了google code，并且改名为MyBatis。2013 年11月迁移到Github。
> iBATIS一词来源于“internet" 和“abatis"的组合，是一个基于Java的持久层框架。iBATIS 提供的持久层框架包括SQL Maps和Data Access objects (DAOs)

mybatis框架

* 一个框架， 早期叫做ibatis， 代码在gi thub.

* mybatis是MyBatis SQL Mapper Framework for Java (sql 映射框架)

  * sql mapper : sql映射
    * 可以把数据库表中的一行数据映射为 一个java对象.
    * 一行数据可以看做是一个java对象.操作这个对象，就相当于操作表中的数据

  * Data Access objects (DAOs)：数据访问，对数据库执行增删改查。

mybatis提供了哪些功能:

1. 提供了创建Connection , statement, Resultset的能力，不用开发人员创建这些对象了

2. 提供了执行sq1语句的能力，不用你执行sq1

3. 提供了循环sql，把sql的结果转为java对象，List集合的能力

   ```java
   while (rs.next()){
       student stu = new Student();
       stu.setId (rs.getInt ("Id"));
       stu.setName (rs.getString ("name"));
       stu.setAge (rs.getInt ("age"));
       //从数据库取出数据转为Student 对象，封装到List 集合
       stulist. add (stu) :
   }
   ```

4. 提供了关闭资源的能力，不用你关闭Connection，Statement，Resultset

开发人员要做的是：提供SQL语句

最后是：开发人员提供SQL语句——MyBatis处理SQL——开发人员得到List集合或java对象（表中的数据）

总结：
	mybatis是一个sql映射框架，提供的数据库的操作能力。增强的JDBC，使用mybatis让开发人员集中精神写sql就可以了，不必关心Connection , Statement , ResultSet的创建，销毁，SQL的执行。

# 框架基础

## 快速上手

* 创建表student

  ```sql
  CREATE TABLE `mybatis-learning`.`student` (
      `id` INT NOT NULL AUTO_INCREMENT,
      `name` VARCHAR (80),
      `email` VARCHAR (100),
      `age` INT,
      PRIMARY KEY (`id`)
  ) ENGINE = INNODB CHARSET = utf8mb4;
  ```

* 插入数据

  |  id  | name |        email        | age  |
  | :--: | :--: | :-----------------: | :--: |
  | 1001 | 李四 |    `lisi@qq.com`    |  20  |
  | 1002 | 张三 | `zhangsan@sina.com` |  28  |

* 创建Maven工程，导入依赖

  ```xml
  <!-- maven依赖 -->
  <dependency>
      <groupId>org.mybatis</groupId>
      <artifactId>mybatis</artifactId>
      <version>3.5.6</version>
  </dependency>
  
  <!-- mysql驱动 -->
  <dependency>
      <groupId>mysql</groupId>
      <artifactId>mysql-connector-java</artifactId>
      <version>5.1.49</version>
  </dependency>
  
  <!-- 为了识别出java文件夹下的xml文件，需要添加如下配置 -->
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

* 创建实体类

  ```java
  public class Student {
      private Integer id;
      private String name;
      private String email;
      private Integer age;
      // 省略getter和setter
      // 省略toString()
  }
  ```

* dao接口

  ```java
  // 接口操作student表
  public interface StudentDao {
      // 查询student表的所有数据
      public List<Student> selectStudents();
  }
  ```
  
* 创建映射文件StudentDao.xml并放在与接口的同一目录下

  ```xml
  <?xml version="1.0" encoding="utf8" ?>
  <!DOCTYPE mapper
          PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
          "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
  <mapper namespace="ctgu.qiny.dao.StudentDao">
      <select id="selectStudents" resultType="ctgu.qiny.entity.Student">
          select `id`, `name`, `email`, `age` from `student` order by `id`
      </select>
  </mapper>
  ```

* 主配置文件mybatis.xml并放在resources目录下

  ```xml
  <?xml version="1.0" encoding="UTF8" ?>
  <!DOCTYPE configuration
          PUBLIC "-//mybatis.org//DTD Config 3.0//EN"
          "http://mybatis.org/dtd/mybatis-3-config.dtd">
  <configuration>
      <environments default="development">
          <environment id="development">
              <transactionManager type="JDBC"/>
              <dataSource type="POOLED">
                  <property name="driver" value="com.mysql.jdbc.Driver"/>
                  <property name="url" value="jdbc:mysql://localhost:3306/mybatis-learning?useSSL=false"/>
                  <property name="username" value="root"/>
                  <property name="password" value="123456"/>
              </dataSource>
          </environment>
      </environments>
      <mappers>
          <mapper resource="ctgu/qiny/dao/StudentDao.xml"/>
      </mappers>
  </configuration>
  ```

* 测试

  ```java
  //访问mybatis读取student数据
  //1. 定义mybatis主配置文件的名称，从类路径根开始
  String config = "mybatis.xml";
  //2. 读取这个config表示的文件org.apache.ibatis.io.Resources
  InputStream in = Resources.getResourceAsStream(config);
  //3. 创建SqlSessionFactoryBuilder对象
  SqlSessionFactoryBuilder builder = new SqlSessionFactoryBuilder();
  //4. 创建SqlSessionFactory对象
  SqlSessionFactory factory = builder.build(in);
  //5. 获取SqlSession对象，从SqlSessionFactory中获取SqlSession
  SqlSession sqlSession = factory.openSession();
  //6. 指定要执行的sql语句的标识。sql映射文件中的namespace + "." + 标签的id值
  String sqlId = "ctgu.qiny.dao.StudentDao" + "." + "selectStudents";
  //7. 执行sql语句，通弄个sqlId找到语句
  List<Student> studentList = sqlSession.selectList(sqlId);
  //8. 输出结果
  studentList.forEach(System.out::println);
  //9. 关闭SqlSession对象
  sqlSession.close();
  ```

## 复习1

mybatis

* 三层架构
  1. 界面层（视图层）完成和用户的交互，接收请求，显示请求的处理结果。
  2. 业务逻辑层 计算数据，处理业务逻辑
  3. 数据访问层（持久层）持久层
* 框架
  1. 界面层：SpringMVC
  2. 业务逻辑层：Spring
  3. 数据访问层：MyBatis

* mybatis
  * 作用：增强的JDBC，访问数据库，进行增删改查
  * 基本步骤
    1. 加入maven依赖
       * mybatis
       * mysql驱动
    2. 创建Dao接口：定义了操作数据的方法
    3. 创建mapper文件，也叫作sql映射文件：写sql语句的，和接口中方法对应的sql语句
    4. 创建mybatis的一个主配置文件
       * 连接数据库
       * 指定mapper文件的位置
    5. 使用mybatis的对象 SqlSession，通过他的方法执行sql语句。

## 增加插入功能

1. StudentDao接口中添加插入方法

```java
// 参数：student，表示要插入到数据库的数据
// 返回值：int，表示执行insert操作后的 影响数据库的行数
public int insertStudent(Student student);
```

2. StudentDao.xml映射文件中配置插入操作的sql语句

```xml
<insert id="insertStudent">
    <!-- #{} 表示动态获取的student的信息 -->
    insert into `student` values (#{id}, #{name}, #{email}, #{age})
</insert>
```

3. 测试插入

```java
//访问mybatis读取student数据
//1. 定义mybatis主配置文件的名称，从类路径根开始
String config = "mybatis.xml";
//2. 读取这个config表示的文件org.apache.ibatis.io.Resources
InputStream in = Resources.getResourceAsStream(config);
//3. 创建SqlSessionFactoryBuilder对象
SqlSessionFactoryBuilder builder = new SqlSessionFactoryBuilder();
//4. 创建SqlSessionFactory对象
SqlSessionFactory factory = builder.build(in);
//5. 获取SqlSession对象，从SqlSessionFactory中获取SqlSession
SqlSession sqlSession = factory.openSession();
//////////////////////////////////////////////////////////////////
/* 上面的代码没有发生改变 */
//////////////////////////////////////////////////////////////////
//6. 指定要执行的sql语句的标识。sql映射文件中的namespace + "." + 标签的id值
String sqlId = "ctgu.qiny.dao.StudentDao" + "." + "insertStudent";
int result = sqlSession.insert(sqlId, new Student(1003, "张飞", "zhangfei@163.com", 18));
//7. 输出查询结果
System.out.println(result);
//8. 提交事务，不然数据库中的内容不会发生改变
sqlSession.commit();
//9. 关闭sqlSession
sqlSession.close();
```

## 配置日志输出

* 主配置文件中添加如下一段

```xml
<!--  控制mybatis全局行为  -->
<settings>
    <!-- 设置mybatis输出日志 -->
    <setting name="logImpl" value="STDOUT_LOGGING"/>
</settings>
```

* 坑点：打印日志时报错：1字节的UTF-8序列的字节1无效
  * 解决方案：解决方法：把xml的encoding属性值UTF-8改为UTF8

* 测试：调用查询方法，查看日志输出

```shell
Logging initialized using 'class org.apache.ibatis.logging.stdout.StdOutImpl' adapter.
PooledDataSource forcefully closed/removed all connections.
PooledDataSource forcefully closed/removed all connections.
PooledDataSource forcefully closed/removed all connections.
PooledDataSource forcefully closed/removed all connections.
Opening JDBC Connection
Created connection 2151717.
Setting autocommit to false on JDBC Connection [com.mysql.jdbc.JDBC4Connection@20d525]
==>  Preparing: select `id`, `name`, `email`, `age` from `student` order by `id`
==> Parameters: 
<==    Columns: id, name, email, age
<==        Row: 1001, 李四, lisi@qq.com, 20
<==        Row: 1002, 张三, zhangsan@sina.com, 28
<==        Row: 1003, 张飞, zhangfei@163.com, 18
<==      Total: 3
Student{id=1001, name='李四', email='lisi@qq.com', age=20}
Student{id=1002, name='张三', email='zhangsan@sina.com', age=28}
Student{id=1003, name='张飞', email='zhangfei@163.com', age=18}
Resetting autocommit to true on JDBC Connection [com.mysql.jdbc.JDBC4Connection@20d525]
Closing JDBC Connection [com.mysql.jdbc.JDBC4Connection@20d525]
Returned connection 2151717 to pool.
```

## 主要类的介绍

* Resources

  > mybatis 中的一个类，负责读取主配置文件

  ```java
  InputStream in = Resources.getResourceAsStream("mybatis.xml");
  ```

* SqlSessionFactoryBuilder

  > 创建SqlSessionFactory对象

  ```java
  SqlSessionFactoryBuilder builder = new SqlSessionFactoryBuilder();
  
  SqlSessionFactory factory = builder.build(in);
  ```

* SqlSessionFactory

  > * 重量级对象：程序创建一个对象耗时比较唱，使用资源比较多。在整个项目中，有一个就够了。
  > * SqlSessionFactory是一个接口。
  >   * 接口实现类：DefaultSqlSessionFactory：获取SqlSession对象

  ```java
  SqlSession sqlSession = factory.openSession();
  //openSession方法说明
  //1. openSession()：五参数的，获取的是非自动提交事务的SqlSession对象
  //2. openSession(boolean)：
  //		openSession(true)	获取自动提交事务的SqlSession
  //		openSession(false)	获取非自动提交事务的SqlSession
  ```

* SqlSession

  > SqlSession接口：定义了操作数据库的方法。例如selectOne()、selectList()、insert()、update()、delete()、commit()、rollback()
  >
  > * 接口的实现类：DefaultSqlSession。
  >
  > 使用要求：SqlSession对象不是线程安全的，需要在方法内部还有，在执行sql语句之前，使用openSession()获取sqlSession对象。在执行完sql语句后，执行sqlSession.close()；这样能保证他的使用是线程安全的。

## 工具类MyBatisUtil

* 创建工具类

```java
public class MyBatisUtil {

    private static SqlSessionFactory factory = null;

    static {
        String config = "mybatis.xml";// 需要和项目中的文件名一致

        try {
            InputStream in = Resources.getResourceAsStream(config);
            // 创建SqlSession对象，使用SqlSessionFactoryBuild
            factory = new SqlSessionFactoryBuilder().build(in);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    // 获取SqlSession的方法
    public static SqlSession getSqlSession(boolean autoCommit) {
        SqlSession sqlSession = null;
        if (factory != null) {
            sqlSession = factory.openSession(autoCommit); // 非自动提交事务
        }
        return sqlSession;
    }
}
```

* 工具类的使用

```java
SqlSession sqlSession = MyBatisUtil.getSqlSession(false);
String sqlId = "ctgu.qiny.dao.StudentDao" + "." + "selectStudents";
List<Student> studentList = sqlSession.selectList(sqlId);
studentList.forEach(System.out::println);
sqlSession.close();
```

# 动态代理与传参

## 动态代理

### 传统dao使用方式

* 编写StudentDaoImpl类实现StudentDao接口

```java
@Override
public List<Student> selectStudents() {
    SqlSession sqlSession = MyBatisUtil.getSqlSession(false);
    String sqlId = "ctgu.qiny.dao.StudentDao.selectStudents";
    List<Student> studentList = sqlSession.selectList(sqlId);
    sqlSession.close();
    return studentList;
}

@Override
public int insertStudent(Student student) {
    SqlSession sqlSession  = MyBatisUtil.getSqlSession(false);
    String sqlId = "ctgu.qiny.dao.StudentDao.insertStudent";
    int num = sqlSession.insert(sqlId,student);
    sqlSession.commit();
    sqlSession.close();
    return num;
}
```

* 测试

```java
@Test
public void testDaoImpl() {
    StudentDao dao = new StudentDaoImpl();
    List<Student> studentList = dao.selectStudents();
    studentList.forEach(System.out::println);

    Student student = new Student(
        1005, "关羽", "guanyu@163.com", 24
    );
    System.out.println(dao.insertStudent(student));
}
```

### 使用动态代理的条件分析

1. dao对象，类型是StudentDao，全限定名称是：xxx.StudentDao
   * 全限定名称和namespace是一样的
2. 方法名称，selectStudents，这个方法就是mapper文件中的id值
3. 通过dao中方法的返回值也可以确定MyBatis要调用的SqlSession的方法
   * 如果返回值是List，调用的是SqlSession.selectList()方法。
   * 如果返回值是int，或是非List的看mapper文件中的标签是\<insert\>、\<update\> 就会调用SqlSession的insert，update等方法。
4. MyBatis的动态代理：mybatis根据dao的方法调用，获取执行sql语句的信息。并根据dao接口，创建出一个dao接口的实现类，并创建这个类的对象。完成SqlSession调用方法，访问数据库。

### 动态代理使用例子

* 使用mybatis的动态代理机制，使用SqlSession.getMapper(dao接口)
* getMapper能获取dao接口对应的实现类对象

```java
public void testProxy() {
    SqlSession sqlSession = MyBatisUtil.getSqlSession(false);
    StudentDao dao = sqlSession.getMapper(StudentDao.class);
    dao.selectStudents().forEach(System.out::println);
    System.out.println(dao.insertStudent(new Student(
        1004,
        "李飞", 
        "lifei@gmail.com",
        24)));
}
```

## 传入参数

* 动态代理：使用SqlSession.getMapper(dao接口.class)获取这个dao接口的对象

* 传入参数：从java代码中吧数据传入到mapper文件的sql语句中。

* parameterType：写在mapper文件的一个属性，表示dao接口中方法的参数的数据类型。

  * StudentDao接口

  ```java
  public Student selectStudentById(Integer id);
  ```

  * mapper

  ```xml
  <!--
   parameterType：dao接口中方法参数的数据类型。
  	parameterType它的值是java的数据类型全限定名称或者是mybatis定义的别名
  	例如：parameterType = "java.lang.Integer"
  	别名：parameterType = "int"
   注意：parameterType不是强制的，mybatis通过反射机制能够发现接口参数的数据类型。
   所以可以没有。一般我们也不写
  -->
  <select 
          id="selectStudentById" 
          parameterType="java.lang.Integer" 
          resultType="ctgu.qiny.entity.Student">
      select `id`, `name`, `email`, `age` from `student` where `id` = #{id}
  </select>
  ```

  * test

  ```java
  @Test
  public void testParam1(){
      SqlSession sqlSession = MyBatisUtil.getSqlSession(false);
      StudentDao dao = sqlSession.getMapper(StudentDao.class);
      Student student = dao.selectStudentById(1002);
      System.out.println(student);
  }
  ```

### 1. 传入一个简单类型

> 简单类型：mybatis把java的基本数据类型和String都叫简单类型。

* 在mapper文件获取简单类型的一个参数的值，使用**`#{任意字符}`**

* 使用#{}之后，mybatis执行sql是使用jdbc中的PreparedStatement对象

* 由mybatis执行下面的代码

  ```java
  // 1. mybatis创建Connection，PreparedStatement对象
  String sql = "select `id`, `name`, `email`, `age` from `student` where `id` = ?";
  PreparedStatement pst = conn.preparedStatement(sql);
  pst.setInt(1,1001);
  // 2. 执行sql封装为resultType="xxx.Student"这个对象
  ResultSet rs = pst.executeQuery();
  Student student = null;
  while(rs.next()){
      //从数据库取表的一行数据，存放到一个java对象属性中
      student = new Student();
      student.setId(rs.getInt("id"));
      student.setName(rs.getstring( "name")); 
      student.setEmail(rs.getstring("email"));
      student.setAge(rs.getInt("age" ));
  }
  return student; //赋给了dao方法的返回值
  ```

### 2.  多个参数 - 使用@Param命名参数

* 接口

  ```java
  // 多个参数：命名参数，在形参定义的前面加入@Param("自定义参数名称")
  public List<Student> selectMultiParam(
      @Param("studentName") String name,
      @Param("studentAge") Integer age
  );
  ```

* mapper文件

  ```xml
  <!--  多个参数，使用@Param命名  -->
  <select id="selectMultiParam" resultType="ctgu.qiny.entity.Student">
      select `id`, `name`, `email`, `age` from `student` where `name` = #{studentName} or `age` = #{studentAge}
  </select>
  ```

* test

  ```java
  @Test
  public void testMultiParam(){
      SqlSession sqlSession = MyBatisUtil.getSqlSession(false);
      StudentDao dao = sqlSession.getMapper(StudentDao.class);
      List<Student> studentList = dao.selectMultiParam("李四", 24);
      studentList.forEach(System.out::println);
  }
  ```

### 3. 使用对象传参

* QueryParam查询类

  ```java
  // 省略getter和setter
  public class QueryParam {
      private String paramName;
      private Integer paramAge;
      ...
  }
  ```

* 接口

  ```java
  // 多个参数，使用java对象作为接口中方法的参数
  List<Student> selectMultiObject(QueryParam param);
  
  List<Student> selectMultiStudent(Student student);
  ```

* mapper文件

  ```xml
  <!--
      多个参数，使java对象的属性值，作为参数的实际值
      使用对象语法：#{属性名, javaType = 类型名称, jdbcType = 数据类型} 很少用
          javaType：指java中的属性数据类型。
          jdbcType：在数据库中的数据类型
          例如：#{paramName, javaType = java.lang.String, jdbcType = VARCHAR}
      简化方式：#{属性名}
          javaType和jdbcType的值mybatis反射能够获取，不需要提供
   -->
  <select id="selectMultiObject" resultType="ctgu.qiny.entity.Student">
      select `id`, `name`, `email`, `age` from `student` where `name` = #{paramName} or `age` = #{paramAge}
  </select>
  
  <select id="selectMultiStudent" resultType="ctgu.qiny.entity.Student">
      select `id`, `name`, `email`, `age` from `student` where `name` = #{name} or `age` = #{age}
  </select>
  ```

* test

  ```java
  @Test
  public void testMultiParamObject1() {
      SqlSession sqlSession = MyBatisUtil.getSqlSession(false);
      StudentDao dao = sqlSession.getMapper(StudentDao.class);
      QueryParam param = new QueryParam();
      param.setParamName("张飞");
      param.setParamAge(24);
      List<Student> studentList = dao.selectMultiObject(param);
      studentList.forEach(System.out::println);
  }
  
  @Test
  public void testMultiParamObject2() {
      SqlSession sqlSession = MyBatisUtil.getSqlSession(false);
      StudentDao dao = sqlSession.getMapper(StudentDao.class);
      Student student = new Student();
      student.setName("张三");
      student.setAge(24);
      List<Student> studentList = dao.selectMultiStudent(student);
      studentList.forEach(System.out::println);
  }
  ```

### 4. 按位置传参（了解即可，不建议使用）

* 接口

  ```java
  /*
      多个参数，简单类型的，按位置传参
          * mybatis 3.4之前，使用#{0} #{1}
          * mybatis 3.4之后，使用#{arg0} #{arg1}
   */
  List<Student> selectMultiPosition(String name, Integer age);
  ```

* mapper文件

  ```xml
  <!--  多个参数使用位置传参  -->
  <select id="selectMultiPosition" resultType="ctgu.qiny.entity.Student">
      select `id`, `name`, `email`, `age` from `student` where
      `name` = #{arg0} or `age` = #{arg1}
  </select>
  
  ```

* test

  ```java
  @Test
  public void testMultiParamPosition() {
      SqlSession sqlSession = MyBatisUtil.getSqlSession(false);
      StudentDao dao = sqlSession.getMapper(StudentDao.class);
      List<Student> studentList = dao.selectMultiPosition("李四", 24);
      studentList.forEach(System.out::println);
  }
  ```

### 5.  使用Map传参（了解即可，不建议使用）

* 接口

  ```java
  // 多个参数，使用Map存放多个值
  List<Student> selectMultiByMap(Map<String,Object> queryMap);
  ```

* mapper文件

  ```xml
  <!-- 使用Map传参 -->
  <select id="selectMultiByMap" resultType="ctgu.qiny.entity.Student">
      select `id`, `name`, `email`, `age` from `student` where
      `name` = #{queryName} or `age` = #{queryAge}
  </select>
  ```

* test

  ```java
  @Test
  public void testSelectMultiByMap() {
      SqlSession sqlSession = MyBatisUtil.getSqlSession(false);
      StudentDao dao = sqlSession.getMapper(StudentDao.class);
      Map<String, Object> queryMap = new HashMap<>();
      queryMap.put("queryName", "李四");
      queryMap.put("queryAge", 24);
      List<Student> studentList = dao.selectMultiByMap(queryMap);
      studentList.forEach(System.out::println);
  }
  ```

### 6. 两个占位符#和$的比较

* #占位符，告诉mybatis使用实际的参数值代替。并使用PrepareStatement对象执行sql语句, #{...}代替
  sql语句的 “?” 。这样做更安全，更迅速，通常也是首选做法。

* $字符串替换，告诉mybatis使用$包含的“字符串”替换所在位置。使用Statement 把sql语句和${}的
  内容连接起来。主要用在替换表名，列名，不同列排序等操作。

### 7. 例：使用占位替换列名进行排序

* 接口

  ```java
  List<Student> selectUse$Order(@Param("colName") String colName);
  ```

* mapper文件

  ```xml
  <select id="selectUse$Order" resultType="ctgu.qiny.entity.Student">
      select `id`, `name`, `email`, `age` from `student` order by `${colName}`;
  </select>
  ```

* test

  ```java
  @Test
  public void testSelectUse$Order(){
      SqlSession sqlSession = MyBatisUtil.getSqlSession(false);
      StudentDao dao = sqlSession.getMapper(StudentDao.class);
      List<Student> studentList = dao.selectUse$Order("age");
      studentList.forEach(System.out::println);
  }
  ```

## 复习2

* mybatis

  * 使用mybatis的动态代理

    * 什么是动态代理：mybatis帮你创建dao接口的实现类，在实现类中调用SqlSession的方法执行sql语句
    * 使用动态代理的方式
      1. 获取SqlSession对象，SqlSessionFactory.openSession()
      2. 使用getMapper方法获取某个接口的对象，sqlSession.getMapper(**接口.class**)
      3. 使用dao接口的方法，调用方法就执行力mapper文件中的sql语句
    * 使用动态代理方式的要求
      1. dao接口和mapper文件放在一起，同一个目录
      2. dao接口和mapper名称一致
      3. mapper文件中的namespace的值时dao接口的全限定名称
      4. mapper文件中的\<select\>、\<insert\>、\<update\>、\<delete\>等的id是接口中方法名称
      5. dao接口中不要使用重载方法，不要使用同名的、不同参数的方法

  * 理解参数

    * 从java代码中吧实际的值传入到mapper文件中

    1. 一个简单类型的参数：#{任意字符}
    2. 多个简单类型的参数：使用@Param("自定义名称")
    3. 使用一个java对象，对象的属性值作为mapper问阿金找到参数，#{java对象的属性名称}
    4. 使用参数的位置，语法：
       1. mybatis3.4之前：#{0}，#{1}
       2. mybatis3.4之之后：#{arg0}，#{arg1}
    5. 使用Map作为参数，#{map中的key}

    

  * #和$的区别

    1. #是占位符，表示列值的，放在等号右侧
    2. $占位符，表示字符串的链接，把sql语句连接成一个字符串
    3. #占位符使用的jdbc指定的PreparedStatement对象执行SQL语句，效率高，没有sql注入的风险
    4. $使用的是Statement对象执行sql，效率低，有sql注入的风险

# mybatis的输出结果

> mybatis执行力sql语句，得到java对象。

## 1.  resultType的使用

* resultType结果类型，指sql语句执行完毕后，数据转为的java对象，java类型是任意的

  * resultType结果类型的其它值
    1. 类型的全限定名称
    2. 类型的别名（例如 java.lang.Integer的别名是int）

* 处理方式：

  1. mybatis执行sql语句，然后mybatis调用类的无参数构造方法，创建对象。
  2. mybats把ResultSet指定列值付给同名的属性。

* 例如

  ```xml
  <select id="selectStudents" resultType="ctgu.qiny.entity.Student">
      select `id`, `name`, `email`, `age` from `student` order by `id`
  </select>
  ```

* 对等的jdbc

  ```java
  ResultSet rs = executeQuery("select `id`, `name`, `email`, `age` from `student` order by `id`");
  while(rs.next()){
      Student student = new Student();
      student.setId(rs.getInt("id"));
      student.setName(rs.getString("name"));
      student.setEmail(rs.getString("email"));
      student.setAge(rs.getInt("age"));
  }
  ```

## 2. 定义自定义类型别名（还是建议使用全限定名称）

* 第一种方式
  * 在mybatis主配置文件中定义，使用 \<typeAlias\> 定义别名

  ```xml
  <!--  定义别名  -->
  <typeAliases>
      <!--
          可以指定一个类型一个自定义别名
              * type:     自定义类型的全限定名称
              * alias:    短小、容易记忆的别名
      -->
      <typeAlias type="ctgu.qiny.entity.Student" alias="student"/>
  </typeAliases>
  ```

  * 可以在resultType中使用自定义别名

  ```xml
  <!--  <select id="selectUse$Order" resultType="ctgu.qiny.entity.Student">  -->
  <select id="selectUse$Order" resultType="student">
      select `id`, `name`, `email`, `age` from `student` order by `${colName}`;
  </select>
  ```

* 第二种方式：\<package\>

  * name是报名，这个包中的所有类，类名就是别名（类名不区分大小写）

  ```xml
  <!--  定义别名  -->
  <typeAliases>
      <package name="ctgu.qiny.entity"/>
  </typeAliases>
  ```

## 3. 查询返回Map

* 接口

  ```java
  //定义方法返回Map
  public Map<Object,Object> selectMapById(Integer id
  ```

* mapper

  ```xml
  <select id="selectMapById" resultType="map">
      select `id`, `name`, `email`, `age` from `student` where `id` = #{id}
  </select>
  ```

* test

  ```java
  @Test
  public void testSelectMap(){
      SqlSession sqlSession = MyBatisUtil.getSqlSession(false);
      StudentDao dao = sqlSession.getMapper(StudentDao.class);
      System.out.println(dao.selectMapById(1002));
      
      // {name=张三, id=1002, email=zhangsan@sina.com, age=28}
  }
  ```

* 获取多行数据时要使用List\<Map\<Object, Object\>\>修饰

## 4. 列名和属性名不同的两种方案

### 4.1 第一种方式：resultMap

> 指定列名和java对象的属性对应关系。

1. 自定义列值赋给哪个属性
2. 当列名和属性名不一样是，一定要使用resultMap

```xml
<!-- 
 定义resultMap
	id: 	自定义名称，表示你定义的这个resultMap
	type:	java类型的全限定名称
-->
<resultMap id="studentMap" type="ctgu.qiny.entity.Student">
    <!-- 列名和java属性的关系 -->
    <!-- 
		主键列：使用id标签
		column：		列名
		property：	java类型的属性名
 	-->
    <id column="id" peorperty="stuId" />
	<!--非主键列：使用result标签 -->
    <id column="name" peorperty="stuName" />
    <id column="email" peorperty="stuEmaill" />
    <id column="age" peorperty="age" />
</resultMap>
```

* mapper中使用resultMap

```xml
<select id="selectMyStudent" resultMap="studentMap">
	select `id`, `name`, `email`, `age` from `student` 
</select>
```

* resultMap和resultType不能一起使用，二选其一

### 4.2 第二种方式：as起别名

```sql
select `id` as `stuId`, `name` as `stuName`, `email` as `stuEmail`, `age` as `stuAge` from `student` 
```

## 5. Like查询两种方案

### 5.1 第一种模糊查询：在java代码中指定like的内容（推荐）

* 接口

  ```java
  // 第一种模糊查询，在java代码中指定like的内容
  List<Student> selectLikeOne(String name);
  ```

* mapper

  ```xml
  <!-- 第一种like，java代码指定like的内容 -->
  <select id="selectLikeOne" resultType="ctgu.qiny.entity.Student">
      select `id`, `name`, `email`, `age` from `student` where `name` like #{name}
  </select>
  ```

* test

  ```java
  SqlSession sqlSession = MyBatisUtil.getSqlSession(false);
  StudentDao dao = sqlSession.getMapper(StudentDao.class);
  List<Student> studentList = dao.selectLikeOne("%张%");
  studentList.forEach(System.out::println);
  ```

### 5.2 第二种查询方案：在mapper中拼接like内容

* 接口

  ```java
  // 第二种模糊查询，在mapper中拼接like内容
  List<Student> selectLikeTwo(String name);
  ```

* mapper

  ```xml
  <!--  第二种方式：在mapper文件汇总拼接like内容  -->
  <select id="selectLikeTwo" resultType="ctgu.qiny.entity.Student">
       select `id`, `name`, `email`, `age` from `student` where `name` like % #{name} %
  </select>
  <!--  注意：%一定要用双引号引起来、"%"和占位符中间一定要有空格  -->
  ```

* test

  ```java
  @Test
  public void testLike(){
      SqlSession sqlSession = MyBatisUtil.getSqlSession(false);
      StudentDao dao = sqlSession.getMapper(StudentDao.class);
      List<Student> studentList = dao.selectLikeTwo("张");
      studentList.forEach(System.out::println);
  }
  ```

## 复习3

* mybatis
  * mybatis的返回结果
    * resultType：表示sql语句的执行结果，转为java对象的类型
      1. 类型的全限定名称
      2. 别名
         * 在mybatis主配置文件中定义别名
           1. 使用\<typeAlias\>
           2. 使用\<package name="包名"\>：类名就是别名
    * resultMap：自定义别名和java对象的属性名对应的关系
    * 列名和属性名不一致的解决方式
      1. 使用列名
      2. 使用resultMap
    * like的使用：
      1. 在java代码中指定like的内容
      2. 在mapper中拼接like

# 动态sql

## 1. 动态sql概述

* sql的内容是变换的，可以根据条件获取到不同的sql语句。主要是where部分发生变化。

* 动态sql的实现，使用的是mybatis提供的标签：\<if\>、\<where\>、\<foreach\>

1. \<if\>是判断条件的

   * 语法：

     ```xml
     <if test="判断java对象的属性值">
         部分sql语句
     </if>
     ```

2. \<where\>用来包含多个\<if\>的，当多个if有一个成立的，\<where\>会自动增加一个where关键字，并去掉if中多余的and，or等等

## 2. 动态sql-if

* 接口

  ```java
  // 动态sql，使用java对象作为参数
  List<Student> selectStudentIf(Student student);
  ```

* mapper

  ```xml
  <!--
      if: test="使用参数java对象的属性值作为判断条件，语法就是 属性=xxx值
   -->
  <select id="selectStudentIf" resultType="student">
      select `id`, `name`, `email`, `age` from `student` where 1 = 1
      <if test="name != null and name != ''">
          and `name` = #{name}
      </if>
      <if test="age > 0">
          and `age` > #{age}
      </if>
  </select>
  ```

* test

  ```java
  SqlSession sqlSession = MyBatisUtil.getSqlSession(false);
  StudentDao dao = sqlSession.getMapper(StudentDao.class);
  Student student = new Student();
  student.setName("李四");
  student.setAge(24);
  List<Student> studentList = dao.selectStudentIf(student);
  studentList.forEach(System.out::println);
  ```

## 3. 动态sql - where

* 接口

  ```java
  // where的使用
  List<Student> selectStudentWhere(Student student);
  ```

* mapper

  ```xml
  <select id="selectStudentWhere" resultType="student">
      select * from `student`
      <where>
          <if test="name != null and name != ''">
              `name` = #{name}
          </if>
          <if test="age > 0">
              or `age` > #{age}
          </if>
      </where>
  </select>
  ```

* test

  ```java
  SqlSession sqlSession = MyBatisUtil.getSqlSession(false);
  StudentDao dao = sqlSession.getMapper(StudentDao.class);
  Student student = new Student();
  student.setAge(24);
  // 此时name为null
  // 拼接后的sql语句为
  /*
      ==>  Preparing: select * from `student` WHERE `age` > ?
      ==> Parameters: 24(Integer)
  */
  List<Student> studentList = dao.selectStudentWhere(student);
  studentList.forEach(System.out::println);
  student.setName("李四");
  // name被赋值为"李四"后的sql为
  /* 
  	==>  Preparing: select * from `student` WHERE `name` = ? or `age` > ?
  	==> Parameters: 李四(String), 24(Integer)
  */
  studentList = dao.selectStudentWhere(student);
  studentList.forEach(System.out::println);
  ```

## 4. 动态sql - foreach

* \<foreach\> 循环java中的数组，list集合的。主要用在sql的in语句中。

  ```sql
  -- 学生id是 1001, 1002, 1003的三个学生。
  select * from `student` where id in (1001, 1002, 1003)
  ```

* 接口

  ```java
  // foreach 用法 - 基本类型List
  List<Student> selectForeachOne(List<Integer> idList);
  
  // foreach 用法 - 对象类型List
  List<Student> selectForeachTwo(List<Student> studentList);
  ```

* mapper

  ```xml
  <!--  foreach 使用 - 基本类型List  -->
  <select id="selectForeachOne" resultType="student">
      select * from `student` where `id` in
      <!--
           collection：    表示接口中的方法参数的类型，如果是数组使用array
           open：          循环开始时的字符
           close：         循环结束时的字符
           seperator：     集合成员之间的分隔符
       -->
      <foreach collection="list" item="myId" open="(" close=")" separator=", ">
          #{myId}
      </foreach>
  </select>
  
  <!--  foreach 使用 - 对象类型List  -->
  <select id="selectForeachTwo" resultType="student">
      select * from `student` where `id` in
      <foreach collection="list" item="stu" open="(" close=")" separator=", ">
          #{stu.id}
      </foreach>
  </select>
  ```

* test

  ```java
  @Test
  public void testForeachOne(){
      SqlSession sqlSession = MyBatisUtil.getSqlSession(false);
      StudentDao dao = sqlSession.getMapper(StudentDao.class);
      List<Integer> idList = new ArrayList<>();
      idList.add(1001);
      idList.add(1002);
      idList.add(1003);
      List<Student> studentList = dao.selectForeachOne(idList);
      studentList.forEach(System.out::println);
  }
  
  @Test
  public void testForeachTwo(){
      SqlSession sqlSession = MyBatisUtil.getSqlSession(false);
      StudentDao dao = sqlSession.getMapper(StudentDao.class);
      
      List<Student> queryStudentList = new ArrayList<>();
      queryStudentList.add(new Student());
      queryStudentList.add(new Student());
      queryStudentList.add(new Student());
      
      queryStudentList.get(0).setId(1001);
      queryStudentList.get(1).setId(1002);
      queryStudentList.get(2).setId(1004);
      
      List<Student> studentList = dao.selectForeachTwo(queryStudentList);
      studentList.forEach(System.out::println);
  }
  ```

## 5. 动态sql - 代码片段

* sql代码片段，就是复用一些语法

  * 步骤：

    1. 先定义\<sql id="自定义唯一名称"\>sql语句，表名，字段\</sql\>
    2. 再使用，\<include refid="id的值" /\>

  * mapper：

    ```xml
    <!--  定义sql片段  -->
    <sql id="selectStudentSql">
        select `id`, `name`, `age`, `email` from `student`
    </sql>
    
    <select id="selectStudentWhere" resultType="student">
        <!-- 
    		sql代码片段的引用
    		替换了select `id`, `name`, `age`, `email` from `student`
     	-->
        <include refid="selectStudentSql"></include>
        <where>
            <if test="name != null and name != ''">
                `name` = #{name}
            </if>
            <if test="age > 0">
                or `age` > #{age}
            </if>
        </where>
    </select>
    ```

## 复习4

* mybatis
  * 动态sql：根据条件，能够得到不同的sql语句，是mybatis的标签，例如if，where，foreach等。
    * if：判断条件的，条件为true，就会把if之间的sql加入到注sql之后
    * where：\<where\> 标签里面还是多个if，如果有一个if判断为true，会在sql的后面加入where关键字，会去掉无用的and，or等字符。
    * foreach：循环数组，list集合
      * collection：    表示接口中的方法参数的类型，如果是数组使用array
      * open：          循环开始时的字符
      * close：         循环结束时的字符
      * seperator：     集合成员之间的分隔符
    * sql代码片段：复用部分sql语句。

# 配置文件

## 5.1 主配置文件DataSource

```xml
<environments default="development">
    <environment id="development">
        <!--
                transactionManager：mybatis提交事务，回滚事务的方式
                    type：事务处理的类型
                        1. JDBC：    表示mybatis底层是调用JDBC中的Connection对象的commit，rollback
                        2. MANAGED： 把mybatis的事务处理委托给其他容器（一个服务器软件，一个框架【spring】）
             -->
        <transactionManager type="JDBC"/>
        <!--
                dataSource： 表示数据源，java体系中，规定实现了javax.sql.DataSource接口的都是数据源。
                    数据源表示Connection对象的。
                type：       指定数据源的类型
                    1. POOLED：      使用连接池，mybatis会创建PooledDataSource类
                    2. UNPOOLED：    不使用连接池，在每次执行sql语句，先创建连接，执行sql，再关闭连接
                        mybatis会创建一个UnPooledDataSource，管理Connection对象的使用。
                    3. JNDI：        java命名和目录服务（windows注册表）
             -->
        <dataSource type="POOLED">
            <property name="driver" value="com.mysql.jdbc.Driver"/>
            <property name="url" value="jdbc:mysql://localhost:3306/mybatis-learning?useSSL=false"/>
            <property name="username" value="root"/>
            <property name="password" value="123456"/>
        </dataSource>
    </environment>
</environments>
```

## 5.2 数据库属性配置文件

* 把数据库链接信息方法放在一个单独的文件中，和mybatis主配置文件分开。目的是便于修改，保存，处理多个数据库的信息

  1. 在resources目录中定义一个属性配置文件：xxxx.properties。例如：jdbc.properties。

     在属性配置文件中，定义数据。格式是：key=value

     key：一般使用 **( . )** 做多级目录的。

     例如

     ```properties
     # resources/jdbc.properties
     java.driver=com.mysql.jdbc.Driver
     java.url=jdbc:mysql://localhost:3306/mybatis-learning?useSSL=false
     java.username=root
     java.password=123456
     ```

  2. 在主配置文件**`mybatis.xml`** 下配置properties

     ```xml
     <!-- 指定properties文件的位置，从类路径根开始找文件 -->
     <!-- 根标签下 -->
     <properties resource="jdbc.properties" />
     
     <!-- 配置dataSource -->
     <dataSource type="POOLED">
         <property name="driver" value="${jdbc.driver}"/>
         <property name="url" value="${jdbc.url}"/>
         <property name="username" value="${jdbc.username}"/>
         <property name="password" value="${jdbc.password}"/>
     </dataSource>
     ```

## 5.3 指定多个mapper文件的方式

1. 第一种方式：多行标签指定多个mapper文件

   ```xml
   <mappers>
       <mapper resource="ctgu/qiny/dao/StudentDao.xml"/>
       <mapper resource="ctgu/qiny/dao/OrderDao.xml"/>
       <!-- ... -->
   </mappers>
   ```

2. 第二种方式：使用包名

   * name：xml文件（mapper文件）所在的包名，这个包中所有的xml文件一次都能加载给mybatis
   * 使用package的要求：
     1. mapper文件名称需要和接口名称一样，大小写也要一致
     2. mapper文件和dao接口需要在同一目录

# 扩展功能 - 分页插件PageHelper

* 导入maven依赖

  ```xml
  <!-- https://mvnrepository.com/artifact/com.github.pagehelper/pagehelper -->
  <dependency>
      <groupId>com.github.pagehelper</groupId>
      <artifactId>pagehelper</artifactId>
      <version>5.2.0</version>
  </dependency>
  ```

* **`mybatis.xml`**加入plugin设置

  ```xml
  <!-- 在 <environment> 之前加入 -->
  <plugins>
  	<plugin interceptor="com.github.pagehelper.PageInterceptor" />
  </plugins>
  ```

* 接口

  ```java
  // 使用PageHelper分页数据
  List<Student> selectAll();
  ```

* mapper

  ```xml
      <!-- 查询所有 -->
      <select id="selectAll" resultType="student">
          select * from `student` order by `id`
      </select>
  ```

* test

  ```java
  @Test
  public void testPageHelper() {
      SqlSession sqlSession = MyBatisUtil.getSqlSession(false);
      StudentDao dao = sqlSession.getMapper(StudentDao.class);
      // 加入PageHelper的方法，分页
      // pageNum：     第几页，从1开始
      // pageSize：    一页中有多少行数据
      PageHelper.startPage(2, 2);
      List<Student> studentList = dao.selectAll();
      studentList.forEach(System.out::println);
  }
  ```

## 复习5

* mybatis
  * mybatis主配置文件
    1. 数据库属性配置文件的使用
       1. 在resources目录中定义一个属性配置文件，xxxx.properties。例如 jdbc.properties在属性配置文件中，定义数据，格式是key=value，key一般使用.做多级目录的
       2. 在mybatis的主配置文件，使用 \<property\> 指定文件的位置。在需要使用值的地方，${key}
    2. mapper文件的位置
       1. 第一种方式：多行标签指定多个mapper文件
       2. 第二种方式：使用包名
          * name：xml文件（mapper文件）所在的包名，这个包中所有的xml文件一次都能加载给mybatis
          * 使用package的要求：
            1. mapper文件名称需要和接口名称一样，大小写也要一致
  * PageHelper分页
    * 功能：实现多种数据库的分页，mysql就是代替 limit 语句的
    * 使用步骤
      1. 加入maven依赖
      2. 在mybatis主配置文件，加入plugin
      3. 在查询方法之前，加入PageHelper方法调用