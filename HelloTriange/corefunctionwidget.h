#ifndef COREFUNCTIONWIDGET_H
#define COREFUNCTIONWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QVector>
#include <QTimer>
#include "camera.h"
#include <QKeyEvent>
#include <QPoint>
#include <QWheelEvent>

class CoreFunctionWidget:public QOpenGLWidget
        , protected /*QOpenGLExtraFunctions*/QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit CoreFunctionWidget(QWidget *parent = nullptr);
       ~CoreFunctionWidget();
protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void keyReleaseEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;


private:
    QOpenGLShaderProgram shaderProgram;

    QTimer* m_pTimer = nullptr;
    float m_uniformValue = 0.0f;
    camera *pCamera;

    bool CtrlOn;
    bool MouseLeftOn;
    bool MouseRightOn;
    QPoint mouseFirstPlace;
    QPoint mouseSecondPlace;
};

#endif // COREFUNCTIONWIDGET_H
