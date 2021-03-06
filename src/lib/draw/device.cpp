#include "device.h"

Device::Device()
{
    QPixmap brushPix;
    brushPix.load(":/res/texture/machine.jpg");
    m_Brush.setTexture(brushPix);
    m_Kind = "Device";

}

Device::~Device(){

}

void Device::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setPen(m_pen);
    painter->setBrush(m_Brush);
    painter->drawRect(*(m_Rect));
    qDebug("device paint");
}

QPainterPath Device::shape() const{
    QPainterPath path;
    path.addRect(*(m_Rect));
    return path;
}

QRectF Device::boundingRect() const{
    return m_Rect->adjusted(-margin,-margin,margin,margin);
}

QRect Device::getBoundary(){

}

bool Device::contains(int x, int y){

}

void Device::setSelected(bool val){

}

bool Device::isSelected(){

}

QPen Device::getPen(){
    return m_pen;
}

void Device::setPen(QColor color, int width){
    m_pen.setColor(color);
    m_pen.setWidth(width);
}

QBrush Device::getBrush(){
    return m_Brush;
}

void Device::setBrush(){

}

QPoint Device::getDevicePositionTL(){
    return m_DevicePositionTL;
}

void Device::setDevicePositionTL(QPoint value){
    m_DevicePositionTL = value;
}

QPoint Device::getDevicePositionBR(){
    return m_DevicePositionBR;
}

void Device::setDevicePositionBR(QPoint value){
    m_DevicePositionBR = value;
}


int Device::getWidth(){
    return m_DeviceWidth;
}

void Device::setWidth(int value){
    m_DeviceWidth = value;
}

int Device::getHeight(){
    return m_DeviceHeight;
}

void Device::setHeight(int value){
    m_DeviceHeight = value;
}

QString Device::getDeviceName(){
    return m_DeviceName;
}

void Device::setDeviceName(QString string){
    m_DeviceName = string;
}
