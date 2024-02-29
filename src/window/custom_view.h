#ifndef CUSTOM_VIEW_H
#define CUSTOM_VIEW_H

#include "includes/libs_file.h"
#include "scene/playground.h"

class CustomView : public QGraphicsView {
    Q_OBJECT

    public:
        CustomView (QGraphicsScene* scene, PlayGround* playground, QWidget* widget);
        ~CustomView ();

    protected:
        // Override resize event to resize PlayGround rect representing the border
        void resizeEvent (QResizeEvent *event) override;

    private:
        PlayGround* mp_playground;
        QWidget* mp_widget;

        void construct_menu_bar ();

    private slots:
        // Methods for handling menu buttons presses
        void load_config ();
        void store_config ();
};

#endif // CUSTOM_VIEW_H
