#include "utilsprocess.h"

QPoint utilsProcess::resolution;
double utilsProcess::sDist;
double utilsProcess::sWidth;

/**
  *   @brief  Constructor por defecto
  *   @return void
  */
utilsProcess::utilsProcess(){}

/**
  *   @brief  Conversión de grados a píxeles (Usando todos los parámetros)
  *
  *   @param  deg entrada en grados a convertir
  *   @param  sceenDistance distancia del sujeto a la pantalla [cm]
  *   @param  pxDensity relación entre el ancho del monitor y su resolución [px/cm]
  *   @return double con el valor resultante de la conversión
  */
double utilsProcess::deg2px(double deg, double screenDistance, double pxDensity){
    return pxDensity*screenDistance*qTan(deg*M_PI/180);
}

/**
  *   @brief  Conversión de píxeles a grados (Usando todos los parámetros)
  *
  *   @param  px entrada en píxeles a convertir
  *   @param  sceenDistance distancia del sujeto a la pantalla [cm]
  *   @param  pxDensity relación entre el ancho del monitor y su resolución [px/cm]
  *   @return double con el valor resultante de la conversión
  */
double utilsProcess::px2deg(double px, double screenDistance, double pxDensity){
    return qAtan(px/(pxDensity*screenDistance))*180/M_PI;
}

/**
  *   @brief  Conversión de grados a píxeles (Usando los parámetros estáticos)
  *
  *   @param  deg entrada en grados a convertir
  *   @return double con el valor resultante de la conversión
  */
double utilsProcess::deg2px(double deg){
//    qDebug() << "Variables:\nDistance:" << sDist << "\nWidth:" << sWidth << "\nResolution:" << resolution;
    return (sDist*resolution.x()*qTan(deg*M_PI/180))/(float)sWidth;
}

/**
  *   @brief  Conversión de grados a píxeles (Usando los parámetros estáticos)
  *
  *   @param  px entrada en píxeles a convertir
  *   @return double con el valor resultante de la conversión
  */
double utilsProcess::px2deg(double px){
//    qDebug() << "Variables:\nDistance:" << sDist << "\nWidth:" << sWidth << "\nResolution:" << resolution;
    return qAtan((px*sWidth)/(float)(sDist*resolution.x()))*180/M_PI;
}


/**
  *   @brief  Conversión de longitud en cm a grados (Usando los parámetros estáticos)
  *   @details
  *   Se convierte una longitud en la pantalla (en cm) a los grados correspondientes en la mirada del paciente
  *
  *   @param  px entrada en cm a convertir
  *   @return double con el valor resultante de la conversión
  */
double utilsProcess::length2deg(double length)
{
    return qAtan(length/sDist)*180/M_PI;
}

bool utilsProcess::checkPosPointsCalibration(QVector<QPointF> m_pointsStimuli, QVector<QPointF> stimulusVector)
{
    bool leftPoint = false, rightPoint = false, middleHPoint = false, upPoint = false, downPoint = false, middleVPoint = false;

    if (stimulusVector.length() != 9){
        qDebug() << Q_FUNC_INFO << "El vector de estímulos no tiene 9 posiciones, error";
        return false;
    }

    for (int i = 0; i < m_pointsStimuli.length(); i++)
    {
        if (m_pointsStimuli[i].x() == stimulusVector.at(0).x()) //estímulo arriba izq
            leftPoint = true;
        else if (m_pointsStimuli[i].x() == stimulusVector.at(1).x()) //estímulo arriba medio
            middleHPoint = true;
        else if (m_pointsStimuli[i].x() == stimulusVector.at(2).x()) //estímulo arriba derecha
            rightPoint = true;

        if (m_pointsStimuli[i].y() == stimulusVector.at(0).y()) //estímulo arriba izq
            upPoint = true;
        else if (m_pointsStimuli[i].y() == stimulusVector.at(3).y()) //estímulo medio derecha
            middleVPoint = true;
        else if (m_pointsStimuli[i].y() == stimulusVector.at(6).y()) //estímulo abajo derecha
            downPoint = true;
    }
    return (leftPoint && middleHPoint && rightPoint && upPoint && middleVPoint && downPoint);
}
