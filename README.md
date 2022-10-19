# RSImage-Shadow-Detection
### `【武汉大学遥感学院】遥感原理与方法实习 | 基于HSV和C1C2C3彩色空间的阴影检测`
[ShadowDetetcion.cpp](./ShadowDetetcion.cpp)**核心代码**

## HSV色彩空间
在HSV彩色空间中（色相/饱和度/明度（Hue/Saturation/Value）），遥感影像阴影区域与非阴影区域相比有以下3 个特点：
- 阴影区域具有更大的色调值;
- 阴影区域的散射光线主要来自波长更短的蓝紫色光，因此具有高饱和度值;
- 阴影区域太阳光线被阻挡，导致低亮度值.
