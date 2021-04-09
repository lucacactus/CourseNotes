## CSS 三角

* 网页中常见一些三角形，使用CSS直接画出来就可以，不必做成图片或者字体图标

* 只要给没有大小的边框设置一端的边框颜色，其余边框颜色都设置为透明色即可

  ```css
  .box2 {
    	/* 边框大小设置为0 */  
      width: 0;
      height: 0;
      /* 兼容低版本浏览器 */
      line-height: 0;
      font-size: 0;
      /* 设置所有边都为透明色 */
      border: 50px solid transparent;
      /* 利用层叠性设置一端的颜色 */
      border-left-color: pink;
  }
  ```

  ```html
  <div class="box2"></div>
  ```

* 案例：京东效果

  ```css
  .jd {
      position: relative;
      width: 120px;
      height: 249px;
      background-color: pink;
  }
  .jd span {
      position: absolute;
      right: 15px;
      /* 边框为5px 所以像素是10px */
      top: -10px;
      width: 0;
      height: 0;
      /* 为了照顾兼容性 */
      line-height: 0;  
      font-size: 0;
      border: 5px solid transparent;
      border-bottom-color: pink;
  }
  ```

  ```html
  <div class="jd">
      <span></span>
  </div>
  ```

## 用户界面样式

### 1. 鼠标样式 cursor

| 属性值      | 描述      |
| ----------- | --------- |
| default     | 小白 默认 |
| pointer     | 小手      |
| move        | 移动      |
| text        | 文本      |
| not-allowed | 禁止      |

### 2. 去掉表单轮廓线、防止拖拽文本域

```css
input, textarea {
    /* 取消表单轮廓 */
    outline: none;
}
textarea {
    /* 防止拖拽文本域 */
    resize: none;
}
```

## vertical-align 实现行内块和文字垂直居中对齐

> CSS的 vertical-align 属性使用场景：经常用于设置图片或者表单(行内块元素)文字垂直对齐。
> 官方解释：用于设置一个元素的垂直对齐方式，但是它只针对于行内元素或者行内块元素有效。

* 语法

```css
elem {
    vertical-align: baseline | top | middle | bottom
}
```

|    值    |                   描述                   |
| :------: | :--------------------------------------: |
| baseline |     默认。元素放置在父元素的基线上。     |
|   top    |  把元素的顶端与行中最高元素的顶端对齐。  |
|  middle  |       把此元素放置在父元素的中部。       |
|  bottom  | 把元素的顶端与行中最低的元素的顶端对齐。 |

## 图片底侧空白缝隙解决方案

bug：图片底侧会有一个空白缝隙，原因是行内块元素会和文字的基线对齐。

主要解决方法有两种：

1. 给图片添加 vertical-align: middle| top | bottom等。( 提倡使用的）
2. 把图片转换为块级元素

## 文字溢出省略号显示

* 单行文本溢出显示省略号——必须满足三个条件

  ```css
  elem{
      /* 1. 先强制一行内显示文本 */
      white-space: nowrap;(默认normal自动换行)
      /* 2. 超出的步伐隐藏 */
      overflow: hidden;
      /* 3. 文字用省略号替代超出的部分 */
      text-overflow: ellipsis;
  }
  ```

* 多行文本溢出显示省略号

> 多行文本溢出显示省略号。有较大兼容性问题.适合于webKit浏览器或移动端(移动端大部分是webkit内核)

```css
elem {
    overflow: hidden;

    text-overflow: ellipsis;

    /* 弹性伸缩盒子模型显示 */
    display: -webkit-box;
    /* 限制在一个块元素显示的文本的行数 */
    -webkit-line-clamp: 2;
    /* 设置或检索伸缩对象的子元素的排列方式 */
    -webkit-box-orirnt: vertical;
}
```

> 更推荐让后台人员来做这个效果。因为后台人员可以设置显示多少个字，操作更简单。

## 布局技巧

### margin负值的运用

1. 让每个盒子margin往左侧移动-1px正好压住相邻盒子边框

2. 鼠标经过某个盒子的时候，提高当前盒子的层级即可（如果没有有定位,则加相对定位（保留位置） , 如果有定位，则加z-index ）

```css
ul li {
    position: relative;
    float: left;
    list-style: none;
    width: 150px;
    height: 200px;
    border: 1px solid red;
    margin-left: -1px;
}

/* ul li:hover {
1. 如果盒子没有定位，则鼠标经过添加相对定位即可
position: relative;
border: 1px solid blue;

} */
ul li:hover {
    /* 2.如果li都有定位，则利用 z-index提高层级 */
    z-index: 1;
    border: 1px solid blue;
}
```

```html
<body>
    <ul>
        <li>1</li>
        <li>2</li>
        <li>3</li>
        <li>4</li>
        <li>5</li>
    </ul>
</body>
```

### 文字围绕浮动元素的妙用

* float

```css
* {
    margin: 0;
    padding: 0;
}
.box {
    width: 300px;
    height: 70px;
    background-color: pink;
    margin: 0 auto;
    padding: 5px;
}
.pic {
    float: left;
    width: 120px;
    height: 60px;
    margin-right: 5px;
}
.pic img {
    width: 100%;
}
```

```html
<body>
    <div class="box">
        <div class="pic">
            <img src="images/img.png" alt="">
        </div>
        <p>【集锦】热身赛-巴西0-1秘鲁 内马尔替补两人血染赛场</p>
    </div>
</body>
```

### 行内块的巧妙运用

* 父元素使用行内块，可以使里面的所有元素居中对齐

```css
* {
    margin: 0;
    padding: 0;
}
.box {
    text-align: center;
}
.box a {
    display: inline-block;
    width: 36px;
    height: 36px;
    background-color: #f7f7f7;
    border: 1px solid #ccc;
    text-align: center;
    line-height: 36px;
    text-decoration: none;
    color: #333;
    font-size: 14px;
}
.box .prev,
.box .next {
    width: 85px;
}
.box .current,
.box .elp {
    background-color: #fff;
    border: none;
}
.box input {
    height: 36px;
    width: 45px;
    border: 1px solid #ccc;
    outline: none;
}
.box button {
    width: 60px;
    height: 36px;
    background-color: #f7f7f7;
    border: 1px solid #ccc;

}
```

```html
<body>
    <div class="box">
        <a href="#" class="prev">&lt;&lt;上一页</a>
        <a href="#" class="current">2</a>
        <a href="#">3</a>
        <a href="#">4</a>
        <a href="#">5</a>
        <a href="#">6</a>
        <a href="#" class="elp">...</a>
        <a href="#" class="next">&gt;&gt;下一页</a>
        到第 
        <input type="text">
        页
        <button>确定</button>
    </div>
</body>
```

### CSS三角强化的巧妙运用

```css
.box1 {
    width: 0;
    height: 0;
    /* 把上边框宽度调大 */
    /* border-top: 100px solid transparent;
    border-right: 50px solid skyblue; */
    /* 左边和下边的边框宽度设置为0 */
    /* border-bottom: 0 solid blue;
    border-left: 0 solid green; */
    /* 1.只保留右边的边框有颜色 */
    border-color: transparent red transparent transparent;
    /* 2. 样式都是solid */
    border-style: solid;
    /* 3. 上边框宽度要大， 右边框 宽度稍小， 其余的边框该为 0 */
    border-width: 100px 50px 0 0 ;

}
.price {
    width: 160px;
    height: 24px;
    line-height: 24px;
    border: 1px solid red;
    margin: 0 auto;
}
.miaosha {
    position: relative;
    float: left;
    width: 90px;
    height: 100%;
    background-color:red;
    text-align: center;
    color: #fff;
    font-weight: 700;
    margin-right: 8px;

}
.miaosha i {
    position: absolute;
    right: 0;
    top: 0;
    width: 0;
    height: 0;
    border-color: transparent #fff transparent transparent;
    border-style: solid;
    border-width: 24px 10px 0 0;
}
.origin {
    font-size: 12px;
    color: gray;
    text-decoration: line-through;
}
```

```html
<div class="box1"></div>
<div class="price">
    <span class="miaosha">
        ¥1650
        <i></i>
    </span>
    <span class="origin">¥5650</span>
</div>
```

## CSS初始化

> 不同浏览器对有些标签的默认值是不同的，为了消除不同浏览器对HTML文本呈现的差异。照顾刘览器的兼
> 容，我们需要对CSS初始化

```css
/* 把我们所有标签的内外边距清零 */
* {
    margin: 0;
    padding: 0;
}
/* em 和 i 斜体的文字不倾斜 */
em,
i {
    font-style: normal;
}
/* 去掉li 的小圆点 */
li {
    list-style: none;
}

img {
    /* border 0 照顾低版本浏览器 如果 图片外面包含了链接会有边框的问题 */
    border: 0;
    /* 取消图片底侧有空白缝隙的问题 */
    vertical-align: middle;
}

button {
    /* 当我们鼠标经过button 按钮的时候，鼠标变成小手 */
    cursor: pointer;
}

a {
    color: #666;
    text-decoration: none;
}

a:hover {
    color: #c81623;
}

button,
input {
    /* "\5B8B\4F53" 就是宋体的意思 这样浏览器兼容性比较好 */
    font-family: Microsoft YaHei, Heiti SC, tahoma, arial, Hiragino Sans GB, "\5B8B\4F53", sans-serif;
}

body {
    /* CSS3 抗锯齿形 让文字显示的更加清晰 */
    -webkit-font-smoothing: antialiased;
    background-color: #fff;
    font: 12px/1.5 Microsoft YaHei, Heiti SC, tahoma, arial, Hiragino Sans GB, "\5B8B\4F53", sans-serif;
    color: #666;
}

.hide,
.none {
    display: none;
}
/* 清除浮动 */
.clearfix:after {
    visibility: hidden;
    clear: both;
    display: block;
    content: ".";
    height: 0
}

.clearfix {
    *zoom: 1
}
```

