#ifndef CUSTOM_VIEW_H
#define CUSTOM_VIEW_H

#include "includes/libs_file.h"
#include "scene/playground.h"

class CustomView : public QGraphicsScene {
    public:
        CustomView () {}
        ~CustomView () {}

    protected:
        // Override resize event to resize PlayGround rect representing the border
        void resizeEvent (QResizeEvent *event) {
            // PlayGround rect is added to the scene as the first one
            if (this->items().size() > 0) {
                QGraphicsRectItem *rectItem = dynamic_cast<PlayGround*>(this->items().at(0));
                if (rectItem) {
                    rectItem->rect().setSize(event->size());
                }
            }
        }
};

#endif // CUSTOM_VIEW_H
