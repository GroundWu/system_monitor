#ifndef CHART_H
#define CHART_H
#include <QtCharts/QChart>
#include "system_resouce_usage.h"
#include <QtCore/QTimer>

QT_CHARTS_BEGIN_NAMESPACE
class QSplineSeries;
class QValueAxis;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

//![1]
class Chart: public QChart
{
    Q_OBJECT
public:
    Chart(sys_usage *su, QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
    void set_sys_usage(sys_usage* su);
    void set_metrics_type(int i);
    float set_m_y();
    virtual ~Chart();
    void handleTimeout(qreal value);

private:
    QSplineSeries *m_series;
    QStringList m_titles;
    QValueAxis *m_axis;
    qreal m_step;
    sys_usage *su;
    int metric_type;
    qreal m_x;
    qreal m_y;
};

#endif // CHART_H
