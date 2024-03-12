#include "custom_view.h"

CustomView::CustomView (QGraphicsScene* scene, PlayGround* playground, QWidget* window)
    : QGraphicsView  (scene, window),
      mp_playground  (playground)
{
}

CustomView::~CustomView() {
}

void CustomView::resizeEvent (QResizeEvent* event /*not used*/) {
    // Override resize event to resize PlayGround rect representing the border
    if (mp_playground) {
        QRectF new_rect = this->mapToScene(this->viewport()->rect()).boundingRect();
        mp_playground->setRect(new_rect);
    }
}
