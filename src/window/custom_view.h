#ifndef CUSTOM_VIEW_H
#define CUSTOM_VIEW_H

#include "includes/libs_file.h"
#include "scene/playground.h"

class CustomView : public QGraphicsView {
    public:
        CustomView (QGraphicsScene* scene, PlayGround* playground, QWidget* window);
        ~CustomView ();

    protected:
        // Override resize event to resize PlayGround rect representing the border
        void resizeEvent (QResizeEvent *event) override;

    private:
        PlayGround* mp_playground;
};

#endif // CUSTOM_VIEW_H
