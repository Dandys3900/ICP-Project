#include "custom_view.h"

CustomView::CustomView (QGraphicsScene* scene, PlayGround* playground, QWidget* widget)
    : QGraphicsView      (scene, widget),
      mp_playground (playground),
      mp_widget          (widget)
{
    construct_menu_bar();
}

CustomView::~CustomView() {
}

void CustomView::resizeEvent (QResizeEvent *event) {
    // Override resize event to resize PlayGround rect representing the border
    if (mp_playground) {
        QRectF new_rect = this->mapToScene(this->viewport()->rect()).boundingRect();
        mp_playground->setRect(new_rect);
    }
}

void CustomView::construct_menu_bar () {
    // Create the menu bar
    QMenuBar* menu_bar = new QMenuBar(mp_widget);

    // Add "File" menu option
    QMenu *menu_file = menu_bar->addMenu("&File");

    // Add actions to the "File" menu option
    QAction *load_action = menu_file->addAction("&Load");
    QAction *save_action = menu_file->addAction("&Save");

    // Connect actions to slots
    QObject::connect(load_action, &QAction::triggered, this, &CustomView::load_config);
    QObject::connect(save_action, &QAction::triggered, this, &CustomView::store_config);

}

void CustomView::load_config () {
    mp_playground->load_config();
}

void CustomView::store_config () {
    mp_playground->store_config();
}