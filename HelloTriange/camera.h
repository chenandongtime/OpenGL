#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include<QMatrix4x4>
#include<QVector3D>
#include<QVector4D>
#include<math.h>

class camera : public QObject
{
    Q_OBJECT
public:
    camera(QObject *parent ,QVector3D camPosition);
//定义属性
private:
    QVector3D position; //相机位置
    QVector3D target; //目标位置
    QVector3D worldUp; //世界坐标系 上向量（0，0，1）

    QMatrix4x4 view; //相机坐标系变换矩阵
    QMatrix4x4 worldM; //世界坐标系变换矩阵

    float sensitivity; //相机灵敏度
public:
    //函数说明:获取视图矩阵
    //函数返回: 视图矩阵
    QMatrix4x4 getView();

    //函数说明：对相机位置做旋转变化，利用arcBall原理,改变相机的位置
    //参数说明:float xOffset: 水平方向的偏移，大小为根据屏幕宽度归一化的数值
    // float yOffset:竖直方向的偏移:大小为根据屏幕高度归一化的数值
    void rotateCamera(float xOffset,float yOffset);

    //函数说明：获取世界坐标系绕任意经过原点的轴的旋转任意角度的变换矩阵
    //参数说明：QVector3D:Axis 经过世界原点的轴的方向
    // float:theta 旋转角度
    // 返回值: QMatrix4x4 wolrdRotate 世界坐标系旋转矩阵
    QMatrix4x4 getWorldRotateM(QVector3D axis,float theta);

    //放大缩小 ：就是拉近或者送远的相机的距离,也就是改变相机的位置
    // 参数说明： scalef 拉近或者送远的倍数
    void scale(float scalef);

    //平移变换 : 修改世界坐标系变换矩阵，使物体在世界坐标系中的位置发生变化从而改变视图中物体位置
    //参数说明 : xOffset 屏幕上x的偏移 yOffset屏幕上y的偏移
    void translateWorldM(float xOffset,float yOffset);

    //获取世界模型
    QMatrix4x4 getWorldM();

signals:

};

#endif // CAMERA_H
