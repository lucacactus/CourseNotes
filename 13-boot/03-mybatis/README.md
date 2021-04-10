## 1.引入操作持久层的pom依赖

```xml
<!-- mybatis官方starter -->
<dependency>
    <groupId>org.mybatis.spring.boot</groupId>
    <artifactId>mybatis-spring-boot-starter</artifactId>
    <version>2.1.4</version>
</dependency>

<!-- mysql驱动 -->
<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <!-- version: 5.1.49 -->
</dependency>
```

## 2. 配置文件配置mybatis

### 2.1 大致步骤

1. 导入mybatis官方starter
2. 编写mapper接口，标注@Mapper注解
3. 编写sql映射文件并绑定mapper接口
4. 在SpringBoot的配置文件中指定Mapper配置文件的位置，以及指定全局配置文件的信息（建议配置在SpringBoot的配置文件中的mybatis.configuration中）

### 2.2 示例：User的查询操作

* user表

  | Field | Type             | Comment |
  | ----- | ---------------- | ------- |
  | id    | int(20) NOT NULL | 主键ID  |
  | name  | varchar(30) NULL | 姓名    |
  | age   | int(11) NULL     | 年龄    |
  | email | varchar(50) NULL | 邮箱    |

* User实体类

  ```java
  public class User {
      private Integer id;
      private String name;
      private Integer age;
      private String email;
      //省略getter、setter以及toString方法
  }
  ```

* application.properties关于mybatis的相关配置

  ```properties
  # 配置数据源
  ## mysql5数据源配置
  # spring.datasource.url=jdbc:mysql://localhost:3306/boot-test?useSSL=false
  # spring.datasource.driver-class-name=com.mysql.jdbc.Driver
  ## mysql8数据源配置
  spring.datasource.url=jdbc:mysql://localhost:3307/boot-test?useSSL=false&serverTimezone=UTC
  spring.datasource.driver-class-name=com.mysql.cj.jdbc.Driver
  spring.datasource.username=root
  spring.datasource.password=123456
  # spring配置jdbcTemplate
  # 查询超时属性（默认单位是s）
  spring.jdbc.template.query-timeout=3
  # 指定mybatis的全局配置文件
  #mybatis.config-location=classpath:mybatis/mybatis-config.xml
  mybatis.mapper-locations=classpath:mybatis/mapper/*.xml
  # 代替mybatis全局配置文件
  # 开启驼峰命名
  mybatis.configuration.map-underscore-to-camel-case=true
  # 配置日志输出
  mybatis.configuration.log-impl=org.apache.ibatis.logging.stdout.StdOutImpl
  ```

* UserMapper接口

  ```java
  @Mapper// 标注@Mapper表示这是一个Mapper
  public interface UserMapper {
      // 按id查询User
      User selectUserById(int id);
  	// 查询所有User
      List<User> selectAllUsers();
  }
  ```

* Mapper配置文件UserMapper.xml

  ```xml
  <?xml version="1.0" encoding="utf8" ?>
  <!DOCTYPE mapper
          PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
          "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
  <mapper namespace="ctgu.qiny.dao.UserMapper">
      <select id="selectUserById" resultType="ctgu.qiny.entity.User">
          select `id`, `name`, `email`, `age` from `user` where `id` = #{id}
      </select>
      <select id="selectAllUsers" resultType="ctgu.qiny.entity.User">
          select `id`, `name`, `email`, `age` from `user` order by `id`
      </select>
  </mapper>
  ```

* 配置service接口及其实现类

  ```java
  // UserService
  public interface UserService {
      User getUserById(int id);
      List<User> getAllUsers();
  }
  // UserServiceImpl
  
  @Service
  public class UserServiceImpl implements UserService {
      @Resource// 自动注入userMapper
      UserMapper userMapper;
  
      @Override// 由于没有复杂业务逻辑，这里就直接返回查询结果
      public User getUserById(int id) {
          return userMapper.selectUserById(id);
      }
  
      @Override
      public List<User> getAllUsers() {
          return userMapper.selectAllUsers();
      }
  }
  ```

* 测试类

  ```java
  @SpringBootTest
  public class DataTest {
      @Autowired
      UserService userService;
  
      @Test// 测试按id查询
      public void test01() {
          System.out.println(userService.getUserById(2));
      }
  
      @Test// 测试查询所有
      public void test02() {
          List<User> userList = userService.getAllUsers();
          userList.forEach(System.out::println);
      }
  }
  ```

  

## 3. 纯注解方式配置mybatis

> user表和配置数据源同2
>
> 建议使用xml方式

* 修改Mapper、Service以Service实现类

```java
/* UserMapper.insertUser方法 */
@Insert("insert into `user` values (#{id}, #{name}, #{age}, #{email})")
// 动态参数要与User实体类属性的顺序一致
int insertUser(User user);

/* UserService.addUser方法 */
int addUser(User user);

/* UserServiceImpl.addUser方法 */
@Override
public int addUser(User user) {
    return userMapper.insertUser(user);
}
```

* 添加mybatis日志输出

```properties
# 配置日志输出
mybatis.configuration.log-impl=org.apache.ibatis.logging.stdout.StdOutImpl
```

* 添加User的测试方法

```java
@Test
public void test03() {
    User user = new User();
    user.setId(6);
    user.setName("Navicat");
    user.setEmail("navicat@gmail.com");
    user.setAge(20);
    userService.addUser(user);
}
```

* 运行结果

```shell
  .   ____          _            __ _ _
 /\\ / ___'_ __ _ _(_)_ __  __ _ \ \ \ \
( ( )\___ | '_ | '_| | '_ \/ _` | \ \ \ \
 \\/  ___)| |_)| | | | | || (_| |  ) ) ) )
  '  |____| .__|_| |_|_| |_\__, | / / / /
 =========|_|==============|___/=/_/_/_/
 :: Spring Boot ::                (v2.4.4)

2021-04-10 17:08:48.644  INFO 17904 --- [           main] ctgu.qiny.DataTest                       : Starting DataTest using Java 1.8.0_281 on DESKTOP-D57MCED with PID 17904 (started by 34984 in D:\projects\idea\boot-learning\learning01-data)
2021-04-10 17:08:48.653  INFO 17904 --- [           main] ctgu.qiny.DataTest                       : No active profile set, falling back to default profiles: default
Logging initialized using 'class org.apache.ibatis.logging.stdout.StdOutImpl' adapter.
Parsed mapper file: 'file [D:\projects\idea\boot-learning\learning01-data\target\classes\mybatis\mapper\UserDao.xml]'
2021-04-10 17:08:51.274  INFO 17904 --- [           main] o.s.s.concurrent.ThreadPoolTaskExecutor  : Initializing ExecutorService 'applicationTaskExecutor'
2021-04-10 17:08:52.086  INFO 17904 --- [           main] ctgu.qiny.DataTest                       : Started DataTest in 3.943 seconds (JVM running for 5.341)

Creating a new SqlSession
SqlSession [org.apache.ibatis.session.defaults.DefaultSqlSession@3ad85136] was not registered for synchronization because synchronization is not active
2021-04-10 17:08:52.511  INFO 17904 --- [           main] com.zaxxer.hikari.HikariDataSource       : HikariPool-1 - Starting...
2021-04-10 17:08:53.111  INFO 17904 --- [           main] com.zaxxer.hikari.HikariDataSource       : HikariPool-1 - Start completed.
JDBC Connection [HikariProxyConnection@1480816641 wrapping com.mysql.jdbc.JDBC4Connection@6af5bbd0] will not be managed by Spring
==>  Preparing: insert into `user` values (?, ?, ?, ?)
==> Parameters: 6(Integer), Navicat(String), 20(Integer), navicat@gmail.com(String)
<==    Updates: 1
Closing non transactional SqlSession [org.apache.ibatis.session.defaults.DefaultSqlSession@3ad85136]

2021-04-10 17:08:53.285  INFO 17904 --- [extShutdownHook] o.s.s.concurrent.ThreadPoolTaskExecutor  : Shutting down ExecutorService 'applicationTaskExecutor'
2021-04-10 17:08:53.286  INFO 17904 --- [extShutdownHook] com.zaxxer.hikari.HikariDataSource       : HikariPool-1 - Shutdown initiated...
2021-04-10 17:08:53.293  INFO 17904 --- [extShutdownHook] com.zaxxer.hikari.HikariDataSource       : HikariPool-1 - Shutdown completed.

Process finished with exit code 0

```

