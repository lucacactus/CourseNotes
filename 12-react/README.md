# 一 React入门

## React简介

### 1. React是什么

1. 发送请求获取数据
2. 处理数据(过滤、 整理格式等)
3. 操作DOM呈现页面

> 是一个将数据渲染为HTML视图的开源JavaScript库。

### 2. 谁开发的？

> 由Facebook开发，且开源。

1. 起初由Facebook的软件工程师Jordan Walke创建。
2. 于2011年部署于Facebook 的newsteed。
3. 随后在2012年部署于Instagram。
4. 2013 年5月直布开源。

<strong style="color:red">近十年"陈酿”React 正在被腾讯、阿里等一线大厂 广泛使用。</strong>

### 3.为什么要学？

1. 原生JavaScript操作DOM繁琐、效率低（<strong style="color:red">DOM-API操作UI</strong>）。

   ```js
   document.getElementById('app')
   document.querySelector('#app')
   document.getElementsByTagName('span')
   ```

2. 使用JavaScript直接操作DOM,浏览器会进行大量的<strong style="color:red">重绘重排</strong>。

3. 原生JavaScript没有<strong style="color:red">组件化</strong>编码方案，代码复用率低。

### 4. React的特点

1. 采用<strong style="color:red">组件化</strong>模式、<strong style="color:red">声明式编码</strong>，提高开发效率及组件复用率。
2. 在React Native中可以使用React语法进行<strong style="color:red">移动端开发</strong>。
3. 使用<strong style="color:red">虚拟DOM</strong>+优秀的<strong style="color:red">Diffing算法</strong>，尽量减少与真实DOM的交互。

### 5. 学习React之前你要掌握的JavaScript基础知识

* 判断this的指向
* class(类)
* ES6语法规范
* npm包管理器
* 原型、原型链
* 数组常用方法
* 模块化

## Hello React案例

```html
<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8" />
        <title>Document</title>
    </head>
    <body>
        <!-- 准备好一个容器 -->
        <div id="test"></div>
        <!-- 引入react核心库 -->
        <script src="../lib/16/react.development.js"></script>
        <!-- 引入react-dom，用于支持react操作DOM -->
        <script src="../lib/16/react-dom.development.js"></script>
        <!-- 引入babel，用于将jsx转为js -->
        <script src="../lib/16/babel.min.js"></script>

        <script type="text/babel">
          /* 此处一定要使用babel */
          //1. 创建虚拟DOM
          var vdom = <h1>Hello, React</h1>; /* 此处一定不要写引号，因为不是字符串 */
          //2. 渲染虚拟DOM到页面
          ReactDOM.render(vdom, document.querySelector("#test"));
        </script>
    </body>
</html>
```

## jsx和js创建虚拟DOM的对比

```jsx
// 使用jsx
const vdom = <h1 id="title">Hello, React</h1>;
// 使用js
const vdom = React.createElement("h1", { id: "title" }, "Hello React");

// 使用jsx
const vdom = <h1 id="title"><span>Hello, React</span></h1>;
// 使用js
const span = React.createElement("span", { }, "Hello React");
const vdom = React.createElement("h1", { id: "title" }, span);

// 如果使用更深层次的嵌套，使用js来创建dom会显得越来越繁琐
```

## 虚拟DOM和真实DOM

* 使用控制台打印测试，可以看出vdom是一个对象类型

```js
console.log("虚拟DOM：" + vdom);// 虚拟DOM：[object Object]
console.log("typeof vdom：" + typeof vdom);// typeof vdom：object
```

* 虚拟DOM比较“轻”，真实DOM比较“重”，因为虚拟DOM是React内部在用，无需真实DOM上那么多的属性。

* 虚拟DOM最终会被React转化为真实DOM。呈现在页面上。

## JSX语法规则

1. 定义虚拟DOM是，不要写引号。
2. 标签中混入JS表达式时要用`{}`。
   1. `{}`内只能使用js表达式。
   2. js表达式：一个表达式会产生一个值，可以放在任何一个需要值的地方

3. 样式类名指定不要用class，要用className。

4. 内联样式，要用style={{key:value}}的形式去写。
5. 只有一个根标签。
6. 标签必须闭合。

7. 标签首字母
   1. 若小写字母开头，则将改标签转为htm1中同名元素，若html中无该标签对应的同名元素，则报错。
   2. 若大写字母开头，react就去渲染对应的组件，若组件没有定义，则报错。

## JSX练习 - 动态展示列表

```html
<!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="UTF-8" />
  <title>js小练习</title>
</head>

<body>
  <div id="test"></div>
  <script src="../lib/16/react.development.js"></script>
  <script src="../lib/16/react-dom.development.js"></script>
  <script src="../lib/16/babel.min.js"></script>

  <script type="text/babel">
    const data = ["Angular", "React", "Vue"];
    const vdom = (
      <div>
        <h1 id="title">Hello, React</h1>
        <ul>
          {data.map(item => <li key={item}>{item}</li>)}
        </ul>
      </div>
    );
    ReactDOM.render(vdom, document.querySelector("#test"));
  </script>
</body>

</html>
```

# 二 React面向组件编程

## 1. 函数式组件

```jsx
// 创建函数式组件
function Demo() {
    return <h2>我是函数式定义的组件</h2>;
}
// 渲染组件到页面
ReactDOM.render(<Demo/>, document.querySelector("#test"));
```

## 2. 复习类的基本知识

```js

```

