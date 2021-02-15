#include "corefunctionwidget.h"

#include <QDebug>
#include <QFile>

static GLuint VBO, VAO, EBO,texture1, texture2;;

CoreFunctionWidget::CoreFunctionWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    m_pTimer = new QTimer(this);
    m_pTimer->setInterval(200);

    connect(m_pTimer, &QTimer::timeout, this, [=]{
        m_uniformValue = 0.03f;

        if (m_uniformValue > 1.5f) {
            m_uniformValue = -1.5f;
        }

        //update();//要求刷新窗口 会调用paintGL()
    });

    m_pTimer->start();

    pCamera = new camera(this,QVector3D(0,0,10));

    CtrlOn = false;
}

CoreFunctionWidget::~CoreFunctionWidget()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
void CoreFunctionWidget::initializeGL(){
    this->initializeOpenGLFunctions();

    bool success = shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/triangle.vert");
    if (!success) {
        qDebug() << "shaderProgram addShaderFromSourceFile failed!" << shaderProgram.log();
        return;
    }

    success = shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/triangle.frag");
    if (!success) {
        qDebug() << "shaderProgram addShaderFromSourceFile failed!" << shaderProgram.log();
        return;
    }

    success = shaderProgram.link();
    if(!success) {
        qDebug() << "shaderProgram link failed!" << shaderProgram.log();
    }

    //VAO，VBO数据部分
    float vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
    };

     QVector<float> vecVertices;
     // 1
     vecVertices.push_back(-1.0);
     vecVertices.push_back(1.0);
     vecVertices.push_back(0.0);
     vecVertices.push_back(0.5);
     vecVertices.push_back(0.5);
     vecVertices.push_back(0.5);
     //top 1 Texture
     vecVertices.push_back(0.0);
     vecVertices.push_back(0.0);

     // bottom 2
     vecVertices.push_back(1);
     vecVertices.push_back(1);
     vecVertices.push_back(0.0);
     vecVertices.push_back(0.5);
     vecVertices.push_back(0.5);
     vecVertices.push_back(0.5);
     // bottom 2 texture
     vecVertices.push_back(1.0);
     vecVertices.push_back(0.0);

     // top 3
     vecVertices.push_back(1);
     vecVertices.push_back(-1);
     vecVertices.push_back(0);
     vecVertices.push_back(0.5);
     vecVertices.push_back(0.5);
     vecVertices.push_back(0.5);
     //top 3 texture
     vecVertices.push_back(1.0);
     vecVertices.push_back(1.0);

     // bottom 4
     vecVertices.push_back(-1.0);
     vecVertices.push_back(-1.0);
     vecVertices.push_back(0.0);
     vecVertices.push_back(0.5);
     vecVertices.push_back(0.5);
     vecVertices.push_back(0.5);
     // bottom 4 texture
     vecVertices.push_back(0.0);
     vecVertices.push_back(1.0);

//     // 5
//     vecVertices.push_back(-1.0);
//     vecVertices.push_back(-1.0);
//     vecVertices.push_back(-1.0);
//     vecVertices.push_back(0.5);
//     vecVertices.push_back(0.5);
//     vecVertices.push_back(0.5);
//     //top 1 Texture
//     vecVertices.push_back(0.0);
//     vecVertices.push_back(1.0);

//     // 6
//     vecVertices.push_back(1.0);
//     vecVertices.push_back(-1.0);
//     vecVertices.push_back(-1.0);
//     vecVertices.push_back(0.5);
//     vecVertices.push_back(0.5);
//     vecVertices.push_back(0.5);
//     //top 1 Texture
//     vecVertices.push_back(1.0);
//     vecVertices.push_back(1.0);

//     // 7
//     vecVertices.push_back(1.0);
//     vecVertices.push_back(-1.0);
//     vecVertices.push_back(1.0);
//     vecVertices.push_back(0.5);
//     vecVertices.push_back(0.5);
//     vecVertices.push_back(0.5);
//     //top 1 Texture
//     vecVertices.push_back(1.0);
//     vecVertices.push_back(0.0);

//     // 8
//     vecVertices.push_back(-1.0);
//     vecVertices.push_back(-1.0);
//     vecVertices.push_back(1.0);
//     vecVertices.push_back(0.5);
//     vecVertices.push_back(0.5);
//     vecVertices.push_back(0.5);
//     //top 1 Texture
//     vecVertices.push_back(0.0);
//     vecVertices.push_back(0.0);


    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    QVector<int> vecIndices;
    // first
    vecIndices.push_back(0);
    vecIndices.push_back(1);
    vecIndices.push_back(3);
    // second
    vecIndices.push_back(1);
    vecIndices.push_back(2);
    vecIndices.push_back(3);

//    vecIndices.push_back(1);
//    vecIndices.push_back(4);
//    vecIndices.push_back(8);

//    vecIndices.push_back(8);
//    vecIndices.push_back(5);
//    vecIndices.push_back(1);

//    vecIndices.push_back(1);
//    vecIndices.push_back(5);
//    vecIndices.push_back(6);

//    vecIndices.push_back(6);
//    vecIndices.push_back(2);
//    vecIndices.push_back(1);

//    vecIndices.push_back(4);
//    vecIndices.push_back(3);
//    vecIndices.push_back(7);

//    vecIndices.push_back(7);
//    vecIndices.push_back(8);
//    vecIndices.push_back(4);

//    vecIndices.push_back(8);
//    vecIndices.push_back(6);
//    vecIndices.push_back(7);

//    vecIndices.push_back(8);
//    vecIndices.push_back(5);
//    vecIndices.push_back(6);

//    vecIndices.push_back(2);
//    vecIndices.push_back(6);
//    vecIndices.push_back(7);

//    vecIndices.push_back(7);
//    vecIndices.push_back(3);
//    vecIndices.push_back(2);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(&vecVertices[0])*vecVertices.size(), &vecVertices[0], GL_STATIC_DRAW);  //顶点数据复制到缓冲

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(&vecIndices[0])*vecIndices.size(), &vecIndices[0], GL_STATIC_DRAW);

    //一笑函数连接上面的顶点数组，和后面顶点着色器
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);//解析顶点坐标
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));//解析顶点颜色
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6*sizeof(GLfloat)));//解析顶点纹理坐标
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);//取消VBO的绑定, glVertexAttribPointer已经把顶点属性关联到顶点缓冲对象了
    glBindVertexArray(0);   //取消VAO绑定

    // texture 1
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    QImage img4 = QImage(":/container.jpeg").convertToFormat(QImage::Format_RGB888);
    QImage img1 = img4.mirrored(false,true);
    if (!img1.isNull()) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img1.width(), img1.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, img1.bits());
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    // texture 2
    // ---------
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    QImage img3 = QImage(":/awesomeface.png").convertToFormat(QImage::Format_RGBA8888).mirrored(true, true);
    QImage img2 = img3.mirrored(false,true);
    if (!img2.isNull()) {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img2.width(), img2.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img2.bits());
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    shaderProgram.bind();   // don't forget to activate/use the shader before setting uniforms!
    glUniform1i(shaderProgram.uniformLocation("texture1"), 0); //默认纹理采样区域
    glUniform1i(shaderProgram.uniformLocation("texture2"), 1); //手动设置纹理采样区域


    //投影矩阵
    QMatrix4x4 projection;
    projection.perspective(45.0f, 1.0f * width() / height(), 0.1f, 100.0f);
    //projection.ortho(-10,10,-10,10,-10,10);
    shaderProgram.setUniformValue("projection",projection);

    shaderProgram.release();

//    remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

//    You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
//    VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    //glBindVertexArray(0);   //取消VAO绑定

    //线框模式，QOpenGLExtraFunctions没这函数, 3_3_Core有
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void CoreFunctionWidget::resizeGL(int w, int h){
    glViewport(0, 0, w, h);
}

void CoreFunctionWidget::paintGL(){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram.bind();
    //int xOffsetLocation = shaderProgram.uniformLocation("xOffset");
    //glUniform1f(xOffsetLocation, m_uniformValue);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    //修改世界坐标投影矩阵
    QMatrix4x4 model = pCamera->getWorldM();
    shaderProgram.setUniformValue("model",model);

    //修改view矩阵
    QMatrix4x4 view; //产生一个4*4的单位矩阵
    //pCamera->rotateCamera(0.0,0.0);
    view = pCamera->getView();
    shaderProgram.setUniformValue("view",view);

    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
//    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    shaderProgram.release();
}

void CoreFunctionWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Control)
    {
        this->CtrlOn = true;
    }
}

void CoreFunctionWidget::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Control)
    {
        this->CtrlOn = false;
    }
}

void CoreFunctionWidget::mousePressEvent(QMouseEvent *event)
{
    if(this->CtrlOn == true)
    {
        if(event->button() == Qt::LeftButton)
        {
            mouseFirstPlace = event->pos();
            this->MouseLeftOn = true;
        }
        else if(event->button() == Qt::RightButton)
        {
            mouseFirstPlace = event->pos();
            this->MouseRightOn = true;
        }
    }
    else
    {
        this->MouseLeftOn = true;
    }
}

void CoreFunctionWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        this->MouseLeftOn = false;
    }
    if(event->button() == Qt::RightButton)
    {
        this->MouseRightOn = false;
    }
}

void CoreFunctionWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(this->CtrlOn == true)
    {
        if(this->MouseLeftOn == true)
        {
            this->mouseSecondPlace = event->pos();
            QPoint DisPoint = this->mouseSecondPlace - this->mouseFirstPlace;
            if(DisPoint.manhattanLength() > 50) //当鼠标移动了一定的距离后
            {
                this->mouseFirstPlace = event->pos(); //更新起点位置
                int MatDis = this->height();
                if(this->width() > this->height())
                    MatDis = this->width();
                float xOffset = -(float) DisPoint.x() / MatDis;
                float yOffset = (float) DisPoint.y() / MatDis;
                qDebug()<< "xOffset" << xOffset;
                qDebug()<< "yOffset" << yOffset;
                pCamera->rotateCamera(xOffset,yOffset);
                update();           //要求刷新窗口 会调用paintGL()
            }
        }
        else if(this->MouseRightOn == true) //平移模型
        {
            this->mouseSecondPlace = event->pos();
            QPoint DisPoint = this->mouseSecondPlace - this->mouseFirstPlace;
            if(DisPoint.manhattanLength() > 30) //当鼠标移动了一定的距离后
            {
                this->mouseFirstPlace = event->pos(); //更新起点位置
                float xOffset = (float) DisPoint.x() / this->width();
                float yOffset = -(float) DisPoint.y() / this->height();
                qDebug()<< "xOffset" << xOffset;
                qDebug()<< "yOffset" << yOffset;
                pCamera->translateWorldM(xOffset,yOffset);
                update();           //要求刷新窗口 会调用paintGL()
            }
         }
    }
}

void CoreFunctionWidget::wheelEvent(QWheelEvent *event)
{
    if(this->CtrlOn == true)
    {
        float rotatef = event->angleDelta().y() / 30.0f;
        if(rotatef < 0)  //缩小
            rotatef = 1 / abs(rotatef);
        else  // 放大
            rotatef =1.0 + 1 / abs(rotatef);
        pCamera->scale(rotatef);
        update();
    }
}
