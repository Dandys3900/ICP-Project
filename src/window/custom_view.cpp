#include "custom_view.h"

CustomView::CustomView (QGraphicsScene* scene, PlayGround* playground, QWidget* window)
    : QGraphicsView  (scene, window),
      mp_playground  (playground),
      mp_main_window (window),
      mp_menu_bar    (nullptr)
{
    construct_menu_bar();
}

CustomView::~CustomView() {
}

QMenuBar* CustomView::get_menu_bar () {
    return mp_menu_bar;
}

void CustomView::resizeEvent (QResizeEvent* event /*not used*/) {
    // Override resize event to resize PlayGround rect representing the border
    if (mp_playground) {
        QRectF new_rect = this->mapToScene(this->viewport()->rect()).boundingRect();
        mp_playground->setRect(new_rect);
    }
}

void CustomView::construct_menu_bar () {
    // Create the menu bar
    mp_menu_bar = new QMenuBar(mp_main_window);

    // Add "File" menu option
    QMenu *menu_file = mp_menu_bar->addMenu("&File");

    // Add actions to the "File" menu option
    QAction *load_action = menu_file->addAction("&Load");
    QAction *save_action = menu_file->addAction("&Save");

    // Connect actions with corresponding PlayGround methods
    QObject::connect(load_action, &QAction::triggered, this, &CustomView::load_config);
    QObject::connect(save_action, &QAction::triggered, this, &CustomView::store_config);
}

void CustomView::load_config () {
    mp_playground->load_config();
}

void CustomView::store_config () {
    mp_playground->store_config();
}