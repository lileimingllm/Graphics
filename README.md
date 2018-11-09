<此版本有bug,后续更新地址为：/>https://github.com/lileimingllm/Graphics.git 
# 简介

1. 目的

- 开始是为了写着玩,到了后来,感觉这东西用着也不错,就往下写了这么一个小项目

2. 功能

- 基于BaseClasss类重写的类,然后调用REGISTERGCLASS宏就可也将对象注册到程序中,在图形化编程界面就能看到具体的生成类图形,整个工程支持的消息机制还仅仅只是信号和槽,事件也可以封装成信号的槽的形式,其他的留有扩展,暂时没有实现

3. 后续

- 会继续更新, 同时也希望更多的朋友一起完善

4. 附图 

按普通流程执行函数
![image](http://upload-images.jianshu.io/upload_images/2429262-1a818af29480baf7.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
 
 执行效果为打印"Hello Graphics" 
 ![image](http://upload-images.jianshu.io/upload_images/2429262-efab697a262a8446.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240) 
 加上信号 构成无限循环的函数: 
![image](http://upload-images.jianshu.io/upload_images/2429262-ca6e94dbffd46b48.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240) 
 无限打印"Hello Graphics": 
 ![image](https://upload-images.jianshu.io/upload_images/9964879-9bec58aa84d7da6a.PNG?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
 还可以创建其它的节点                                                              
 ![image](https://upload-images.jianshu.io/upload_images/9964879-7b75e16d751f1812.PNG?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
