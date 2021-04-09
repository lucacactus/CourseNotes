## 安装和配置方式

* 目前前端流行的三大框架, 都有自己的路由实现:
  * Angular的ngRouter
  * React的ReactRouter
  * Vue的vue-router
* 当然, 我们的重点是vue-router
* vue-router是Vue.js官方的路由插件，它和vue.js是深度集成的，适合用于构建单页面应用。
* 我们可以访问其官方网站对其进行学习: https://router.vuejs.org/zh/
* vue-router是基于路由和组件的
* 路由用于设定访问路径, 将路径和组件映射起来.
* 在vue-router的单页面应用中, 页面的路径的改变就是组件的切换。

## 安装和使用vue-router

* 因为我们已经学习了webpack,后续开发中我们主要是通过工程化的方式进行开发的。

  * 所以在后续,我们直接使用npm来安装路由即可。

  * 步骤一: 安装vue-router

    ```shell
    npm install vue-router --save
    ```

  * 步骤二：在模块化工程中使用它(因为是一个插件, 所以可以通过Vue.use0来安装路由功能)

    * 第一步：导入路由对象,并且调用Vue.use(VueRouter)
    * 第二步：创建路由实例,并且传，入路由映射配置
    * 第三步：在Vue实例中挂载创建的路由实例

编写router `router/index.js`

```js
import Vue from 'vue'
import VueRouter from 'vue-router'

// 1. 通过Vue.use(插件)，安装插件
Vue.use(VueRouter)

// 2. 创建VueRouter对象
const routes = []
const router = new VueRouter({
    //配置路由和组件之间的映射关系
    routes
})


// 3. 将router对象传入到Vue实例
export default router
```

Vue实例接收router `main.js`

```js
import Vue from 'vue'
import App from './App.vue'
import router from './router'

Vue.config.productionTip = false

// cli2
new Vue({
    el:'#app'
    router,
    render: h => h(App)
})

// cli3
new Vue({
    router,
    render: h => h(App)
}).$mount('#app')
```

## 路由映射配置和呈现

* 映射配置

`router/index.js`

```js
const routes = [
    {
        path: '/home',
        component: Home //Home组件要导入进来
    }，
    {    
        path: '/about',
        component: About //About组件要导入进来
    }
]
```

* 显示路由

`App.vue`

```vue
<template>
	<div id="app">
        <!-- 选择组件 -->
        <router-link to="/home">首页</router-link>
        <router-link to="/about">关于</router-link>
        <!-- 显示组件 -->
        <router-view></router-view>
    </div>
</template>
```

* 配置重定向

`router/index.js`

```js
const routes = [
    // 开始进入时自动重定向到/home路由中
    {
        path: '',
        redirect: '/home'
    },
    {
        path: '/home',
        component: Home
    }，
    {    
        path: '/about',
        component: About
    }
]
```

* 设置为history模式

`router/index.js`

```js
const router = new VueRouter({
    routes,
    mode: 'history' //设置路由模式为history
})
```

## router-link的其他属性补充

|    属性名    | 作用                                                         |
| :----------: | ------------------------------------------------------------ |
|      to      | 指定跳转路径                                                 |
|     tag      | 指定 &lt;router-link&gt; 渲染成什么标签，默认为a标签。比如tag="button"可以将&lt;router-link&gt; 渲染成button标签。 |
|   replace    | history改为replace模式（跳转路由时不会出现回退功能）         |
| active-class | 设置路由活跃时 &lt;router-link&gt; 的类名（用于设置CSS样式）,也可以在`router/index.js`中设置路由属性**linkActiveClass**。用于统一修改，节省代码量。 |

## 动态路由的使用

* 创建组件

```vue
<template>
	<div>
        <h2>我是用户界面</h2>
        <p>我是用户的相关信息，嘿嘿嘿</p>
        <h2>{{userId}}</h2>
    </div>
</template>

<script>
    export default {
        name:"User",
        computed:{
            userId(){
                return this.$route.params.userId// 获取动态路由
            }
        }
    }
</script>
```

* 配置路由

```js
{
    path: '/user/:userId',
    component: User
},
```

* App里应用组件

```vue
<!-- 绑定userId -->
<router-link :to="'/user/'+userId" tag="button" replace>用户</router-link>
<script>
    export default {
        name: 'App',
        data(){
            return{
                userId:'zhangsan'
            }
        }
    }
</script>
```

## 路由的懒加载

* 当打包构建应用时，Javascript包会变得非常大，影响页面加载。
* 如果我们能把不同路由对应的组件分割成不同的代码块，然后当路由被访问的时候才加载对应组件，这样就更
  加高效了。
  * 首先，我们知道路由中通常会定义很多不同的页面。
  * 这个页面最后被打包在哪里呢？一般情况下，是放在一 个js文件中。
  * 但是，页面这么多放在一个js文件中，必然会造成这个页面非常的大。
  * 如果我们一次性从服务器请求下来这个页面，可能需要花费一定的时间，甚至用户的电脑上还出现了短暂空白的情况。
  * 如何避免这种情况呢？使用路由懒加载就可以了。
* 路由懒加载做了什么？
  * 路由懒加载的主要作用就是将路由对应的组件打包成一个个的js代码块。
  * 只有在这个路由被访问到的时候，才加载对应的组件。

```js
// import Home from '../components/Home'
// import About from '../components/About'
// import User from '../components/User'
// 不导入组件

const Home = () => import('../components/Home');
const About = () => import('../components/About');
const User = () => import('../components/User');
// 采用懒加载
```

## 路由的嵌套使用

* 嵌套路由是一个很常见的功能
  * 比如在home页面中，我们希望通过/home/news和/home/message访向一些内容。
  * 一个路径映射一个组件，访问这两个路径也会分别渲染两个组件。
* 实现嵌套路由有两个步骤
  * 创建对应的子组件，并且在路由映射中配置对应的子路由
  * 在组件内部使用&lt;router-view&gt;标签

```js
// 引入子路由
const HomeNews = () => import('../components/HomeNews');
const HomeMessage = () => import('../components/HomeMessage');

// 在父路由下配置子路由
{
    path: '/home',// 父路由是Home
    component: Home,
    children: [
      {
        path: '',
        redirect: 'news' 
      },// 重定向
      {
        path: 'news',// 子路由的路径不需要加上斜杠
        component: HomeNews
      },
      {
        path: 'message',
        component: HomeMessage
      }
    ]
  },// /home
```

`Home.vue`

```vue
<!-- 父路由下配置router-link和router-view -->
<router-link to="/home/news">新闻</router-link>
<router-link to="/home/message">消息</router-link>
<router-view></router-view>
```

## 参数传递

* 传递参数的方式
  * 传递参数主要有两种类型：params和query
  * params的类型:
    * 配置路由格式：/router/:id
    * 传递的方式：在path后面跟上对应的值
    * 传递后形成的路径：/router/123，/router/abc
  * query的类型:
    * 配置路由格式：/router，也就是普通配置
    * 传递的方式：对象中使用query的key作为传递方式
    * 传递后形成的路径：/router?id=123，/router?id=abc

```js
// 引入Profile路由（参考上面）
{
    path: '/profile',
    component: Profile
},// /profile
```

```vue
<router-link :to="{ path: '/profile', query: { name: 'zhangsan', age: 24 } }" replace>方案</router-link>
```

## $route和$router



## 全局导航守卫

* 我们来考虑一个需求：在一个SPA应用中，如何改变网页的标题呢？

  * 网页标题是通过\<title\>来显示的，但是SPA只有一个固定的HTML，切换不同的页面时，标题并不会改变。
  * 但是我们可以通过JavaScript来修改\<title\>的内容。window.document.title = '新的标题'。
  * 那么在Vue项目中，在哪里修改？什么时候修改比较合适呢？

* 普通的修改方式：

  * 我们比较容易想到的修改标题的位置是每一个路由对应的组件.vue文件中。
  * 通过mounted声明周期函数，执行对应的代码进行修改即可。
  * 但是当页面比较多时，这种方式不容易维护(因为需要在多个页面执行类似的代码)。

* router.beforeEach **`router/index.js`** 前置守卫

  ```js
  {
      path: '/...',
      component: XXX,
      meta:{
          title:'xxx'// to.title访问的就是这个数据
      }
  }//在每个路由里添加元数据meta
  
  // 跳转路由前调用的函数
  router.beforeEach(function (to, from, next) {
  	// 从from跳转到to
      // matched[0]是为了解决嵌套路由时找不到元数据的问题
      document.title = to.matched[0].meta.title;
      //next必须要调用，否则不会跳转
      next();
  })
  ```

* router.afterEach **`router/index.js`** 后置钩子
* 路由独享的守卫
  
  * beforeEnter
* 组件内的守卫
  * beforeRouteEnter
  * beforeRouteUpdate（2.2 新增）
  * beforeRouteLeave

## keep-alive 状态保留

* keep-alive是Vue内置的一个组件，可以使被包含的组件保留状态，或避免重新渲染。
* router-view也是一个组件，如果直接被包在keep-alive里面，所有路径匹配到的视图组件都会被缓存

```vue

```

## Tabbar

* 全局安装vue

```shell
npm install -g @vue/cli-init
```

* 创建项目

```shell
vue init webpack tabbar 
? Project name tabbar
? Project description A Vue.js project
? Author lucacactus <alexanderashilie1@gmail>
? Vue build runtime
? Install vue-router? No
? Use ESLint to lint your code? No
? Set up unit tests No
? Setup e2e tests with Nightwatch? No
? Should we run `npm install` for you after the project has been created? (recommended) npm
```

* 清除组件，搭建基本框架

**`asset/css/base.css`**

```css
body {
  margin: 0;
  padding: 0;
}
```

**`App.vue`**

```vue
<template>
<div id="app">
    <div id="tab-bar">
        <div class="tab-bar-item">首页</div>
        <div class="tab-bar-item">分类</div>
        <div class="tab-bar-item">购物车</div>
        <div class="tab-bar-item">我的</div>
    </div>
    </div>
</template>

<script>
    export default {
        name: "App"
    };
</script>

<style>
    @import "./assets/css/base.css";

    #tab-bar {
        display: flex;

        background-color: #f4f4f4;
        position: fixed;
        left: 0;
        right: 0;
        bottom: 0;

        box-shadow: 0 5px 10px rgba(100, 100, 100, 0.8);
    }

    .tab-bar-item {
        flex: 1;
        text-align: center;
        height: 49px;
        line-height: 49px;
    }
</style>

```



# 原码阅读

p114

p117 生命周期