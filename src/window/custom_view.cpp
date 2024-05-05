/** ICP Project 2023/2024
 * @file custom_view.cpp
 * @author Tomáš Daniel (xdanie14)
 * @brief Handling scene resizing and adjusts PlayGround's rectangle properties.
 */

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
        mp_playground->resize_playground(new_rect);
    }
}
