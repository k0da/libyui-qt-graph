/*---------------------------------------------------------------------\
|								       |
|		       __   __	  ____ _____ ____		       |
|		       \ \ / /_ _/ ___|_   _|___ \		       |
|			\ V / _` \___ \ | |   __) |		       |
|			 | | (_| |___) || |  / __/		       |
|			 |_|\__,_|____/ |_| |_____|		       |
|								       |
|				core system			       |
|						   (c) SuSE Linux GmbH |
\----------------------------------------------------------------------/

  File:		QY2Graph.h

  Author:	Arvin Schnell <aschnell@suse.de>

/-*/


#ifndef QY2Graph_h
#define QY2Graph_h

#include <gvc.h>
#include <string>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPathItem>
#include <QSignalMapper>
#include <QPicture>


/**
 * The QY2Graph widget shows a graph layouted by graphviz in a
 * QGraphicsView/QGraphicsScene.
 */
class QY2Graph : public QGraphicsView
{
    Q_OBJECT

public:

    QY2Graph(QWidget* parent, const std::string& filename, const std::string& layoutAlgorithm);

    QY2Graph(QWidget* parent, graph_t* graph);

    virtual ~QY2Graph();

    virtual void renderGraph(const std::string& filename, const std::string& layoutAlgorithm);
    virtual void renderGraph(graph_t* graph);

    void clearGraph();

signals:

    void nodeDoubleClickEvent(const QString& name);

protected:

    void keyPressEvent(QKeyEvent* event);
    void wheelEvent(QWheelEvent* event);
    void scaleView(qreal scaleFactor);

private:

    void init();

    QGraphicsScene* scene;
    QSignalMapper* signalMapper;

    QRectF rect;

    QPointF gToQ(const point& p, bool upside_down = true) const;
    QPointF gToQ(const pointf& p, bool upside_down = true) const;

    QString aggetToQString(void* obj, const char* name, const QString& fallback) const;
    QColor aggetToQColor(void* obj, const char* name, const QColor& fallback) const;
    Qt::PenStyle aggetToQPenStyle(void* obj, const char* name, const Qt::PenStyle fallback) const;

    QPainterPath makeShape(node_t* node) const;
    QPolygonF makeShapeHelper(node_t* node) const;

    QPainterPath makeBezier(const bezier& bezier) const;

    void drawLabel(const textlabel_t* textlabel, QPainter* painter) const;

    void drawArrow(const QLineF& line, const QColor& color, QPainter* painter) const;

};


class QY2Node : public QObject, public QGraphicsPathItem
{
    Q_OBJECT

public:

    QY2Node(const QPainterPath& path, const QPicture& picture);

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

signals:

    void doubleClickEvent();

protected:

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:

    QPicture picture;

};


class QY2Edge : public QGraphicsPathItem
{

public:

    QY2Edge(const QPainterPath& path, const QPicture& picture);

    QRectF boundingRect() const;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

private:

    QPicture picture;

};


#endif // QY2Graph_h
