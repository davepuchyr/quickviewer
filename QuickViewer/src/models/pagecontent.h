#ifndef PAGECONTENT_H
#define PAGECONTENT_H

#include <QtCore>
#include <QtWidgets>

#include "filevolume.h"

/**
 * @brief PageContent
 * contains the informations of a Page
 */
class PageContent : public QObject
{
    Q_OBJECT
public:
    QGraphicsScene *Scene;
    ImageContent Ic;
    /**
     * @brief GrItem
     * Page image is used as a QGraphicsItem. it will be registed to the scene
     */
    QGraphicsItem* GrItem;
    /**
     * @brief Resized
     * Store the image changed to the specified size (newsize)
     */
    QPixmap ResizedPage;
    QFutureWatcher<QImage> generateWatcher;
    /**
     * @brief Rotate: rotation as digrees
     */
    int Rotate;
    enum Fitting {
        FitCenter,
        FitLeft,
        FitRight
    };
    PageContent(QObject* parent=nullptr);
    PageContent(QObject* parent, QGraphicsScene *s, ImageContent ic);
    PageContent(const PageContent& rhs);
    PageContent& operator=(const PageContent& rhs);

    QPoint Offset(int rotateOffset=0);
    QSize CurrentSize(int rotateOffset=0);

    /**
     * @brief setPageLayout set each image on the page
     * @param viewport: the image must be inscribed in the viewport area
     */
    QRect setPageLayoutFitting(QRect viewport, Fitting fitting, int rotateOffset=0);
    QRect setPageLayoutManual(QRect viewport, Fitting fitting, qreal scale, int rotateOffset=0);

    void applyResize(qreal scale, int rotateOffset, QPoint pos, QSize newsize);
    void initializePage();
signals:
    void resizeFinished();
public slots:
    void on_resizeFinished_trigger();

private:
    int m_resizeGeneratingState;
};

#endif // PAGECONTENT_H