/*
 * The information in this file is
 * Copyright(c) 2007 Ball Aerospace & Technologies Corporation
 * and is subject to the terms and conditions of the
 * GNU Lesser General Public License Version 2.1
 * The license text is available from   
 * http://www.gnu.org/licenses/lgpl.html
 */

#ifndef TIMELINEWIDGET_H__
#define TIMELINEWIDGET_H__

#include "AnimationController.h"
#include "AnimationToolBar.h"
#include "AttachmentPtr.h"
#include <QtGui/QDialog>
#include <QtGui/QWidget>
#include <qwt_abstract_scale.h>

class Animation;
class AnimationController;
class QDateTimeEdit;
class QwtScaleDraw;

class TimelineWidget : public QWidget, public QwtAbstractScale
{
   Q_OBJECT

public:
   TimelineWidget(QWidget *pParent = NULL);
   virtual ~TimelineWidget();

   void controllerChanged(Subject &subject, const std::string &signal, const boost::any &v);
   void currentFrameChanged(Subject &subject, const std::string &signal, const boost::any &v);

   void setRange(double vmin, double vmax, bool lg=false);

   virtual QSize sizeHint() const;
   virtual QSize minimumSizeHint() const;

   void setScaleDraw(QwtScaleDraw *pScaleDraw);
   const QwtScaleDraw *scaleDraw() const;

protected:
   void draw(QPainter *pPainter, const QRect &update_rect);
   void layout(bool update_geometry=true);
   virtual void paintEvent(QPaintEvent *pEvent);
   virtual void resizeEvent(QResizeEvent *pEvent);
   virtual void contextMenuEvent(QContextMenuEvent *pEvent);
   QwtScaleDraw *scaleDraw();

private slots:
   void rescaleController();

private:
   int transform(double value) const;
   void setAnimationController(AnimationController *pController);

   class PrivateData;
   PrivateData *pD;
  
   AttachmentPtr<AnimationToolBar> mpToolbar;
   AttachmentPtr<AnimationController> mpControllerAttachments;
};

class RescaleDialog : public QDialog
{
   Q_OBJECT

public:
   RescaleDialog(AnimationController *pController, QWidget *pParent = NULL);
   virtual ~RescaleDialog();

private slots:
   void acceptValues();

private:
   AnimationController *mpController;
   QDateTimeEdit *mpStart;
   QDateTimeEdit *mpStop;
};

#endif