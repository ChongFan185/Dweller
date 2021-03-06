#include "lib\ui\dwellercanvas.h"

DwellerCanvas::DwellerCanvas(QGraphicsScene *m_scene)
{
    scene = m_scene;
    m_translateButton = Qt::LeftButton;
//    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
//    scene->setSceneRect(-100,-100,1000,1000);
//    setSceneRect(0,0,1000,1000);
    setScene(scene);
    setCacheMode(QGraphicsView::CacheNone);

    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setDragMode(QGraphicsView::NoDrag);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
//    scale(qreal(1), qreal(1));
//    setMinimumSize(400, 400);

}

//bool DwellerCanvas::event(QEvent *event){
//    m_ActiveTool->handleEvent(event);
//}


//void DwellerCanvas::itemMoved(){
////    if(!timerId)
////        timerId=startTimer(1000/25);
//}

//void DwellerCanvas::timerEvent(QTimerEvent *event)
//{
////    Q_UNUSED(event);

//}

void DwellerCanvas::keyPressEvent(QKeyEvent *event){
    m_ActiveTool->handleEvent(event);
    QGraphicsView::keyPressEvent(event);
}

void DwellerCanvas::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}

void DwellerCanvas::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 1 || factor > 10)
        return;

    scale(scaleFactor, scaleFactor);
    m_scale *= scaleFactor;
}

void DwellerCanvas::drawBackground(QPainter *painter, const QRectF &rect){
    //QRectF sceneRect = this->sceneRect();
    int i;
    QPen pen;
    pen.setColor(QColor(173,202,232,120));
    pen.setStyle(Qt::DotLine);

    painter->setPen(pen);
    for(i=0;i<(200);i++){
        painter->drawLine(-1000,-1000+CANVAS_RATIO*i,1000,-1000+CANVAS_RATIO*i);
        painter->drawLine(-1000+CANVAS_RATIO*i,-1000,-1000+CANVAS_RATIO*i,1000);
    }
}

void DwellerCanvas::mouseMoveEvent(QMouseEvent *event){

    if(m_bMouseTranslate){
        QPointF mouseDelta = mapToScene(event->pos())-mapToScene(m_lastMousePos);
        translate(mouseDelta);
    }
    m_lastMousePos = event->pos();
    m_ActiveTool->m_MapTranslate = mapFromScene(QPoint(0,0));
    m_ActiveTool->handleEvent(event);
    QGraphicsView::mouseMoveEvent(event);
}

void DwellerCanvas::mousePressEvent(QMouseEvent *event){

    if ((event->button() == m_translateButton) && (m_ActiveTool->m_EnableViewChange)) {
        //qDebug("press1");
        QPointF point = mapToScene(event->pos());
        if (scene->itemAt(point, transform()) == NULL)  {
            qDebug("press2");
            m_bMouseTranslate = true;
            m_lastMousePos = event->pos();
            if(m_ActiveTool->m_EnableViewChange){
                setDragMode(QGraphicsView::ScrollHandDrag);
            }else{
                setDragMode(QGraphicsView::NoDrag);
            }
        }
    }
    m_ActiveTool->m_MapTranslate = mapFromScene(QPoint(0,0));
    m_ActiveTool->handleEvent(event);
    QGraphicsView::mousePressEvent(event);
}

void DwellerCanvas::mouseReleaseEvent(QMouseEvent *event){

    if (event->button() == m_translateButton){
        m_bMouseTranslate = false;
//        if(!(m_ActiveTool->m_EnableViewChange)){
        setDragMode(QGraphicsView::NoDrag);

    }
    m_ActiveTool->m_MapTranslate = mapFromScene(QPoint(0,0));
    m_ActiveTool->handleEvent(event);
    QGraphicsView::mouseReleaseEvent(event);
}

void DwellerCanvas::translate(QPointF delta){
    // 根据当前 zoom 缩放平移数
    delta *= m_scale;
    delta *= m_translateSpeed;

    // view 根据鼠标下的点作为锚点来定位 scene
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    QPoint newCenter(this->width() / 2 - delta.x(),  this->height() / 2 - delta.y());
    centerOn(mapToScene(newCenter));

    // scene 在 view 的中心点作为锚点
    setTransformationAnchor(QGraphicsView::AnchorViewCenter);
}

void DwellerCanvas::setTranslateSpeed(qreal speed)
{
     //建议速度范围
    Q_ASSERT_X(speed >= 0.0 && speed <= 2.0,
               "InteractiveView::setTranslateSpeed", "Speed should be in range [0.0, 2.0].");
    m_translateSpeed = speed;
}

qreal DwellerCanvas::translateSpeed() const
{
    return m_translateSpeed;
}

// 缩放的增量
void DwellerCanvas::setZoomDelta(qreal delta)
{
    // 建议增量范围
    Q_ASSERT_X(delta >= 0.0 && delta <= 1.0,
               "InteractiveView::setZoomDelta", "Delta should be in range [0.0, 1.0].");
    m_zoomDelta = delta;
}

qreal DwellerCanvas::zoomDelta() const
{
    return m_zoomDelta;
}
