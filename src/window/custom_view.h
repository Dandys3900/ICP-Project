#ifndef CUSTOM_VIEW_H
#define CUSTOM_VIEW_H

#include "includes/libs_file.h"
#include "scene/playground.h"

class CustomView : public QGraphicsView {
    public:
        CustomView (QGraphicsScene* scene, QGraphicsRectItem* playground)
            : QGraphicsView      (scene),
              mp_playground_rect (playground)
        {
        }

        ~CustomView () {
        }

    protected:
        // Override resize event to resize PlayGround rect representing the border
        void resizeEvent (QResizeEvent *event) {
            if (mp_playground_rect) {
                QRectF new_rect = this->mapToScene(this->viewport()->rect()).boundingRect();
                mp_playground_rect->setRect(new_rect);
            }
        }

    private:
        QGraphicsRectItem* mp_playground_rect;
};

#endif // CUSTOM_VIEW_H
