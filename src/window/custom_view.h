/** ICP Project 2023/2024
 * @file custom_view.h
 * @author Tomáš Daniel (xdanie14)
 * @brief Header file for CustomView class.
 */

#ifndef CUSTOM_VIEW_H
#define CUSTOM_VIEW_H

#include "includes/libs_file.h"
#include "scene/playground.h"

class CustomView : public QGraphicsView {
    public:
        /**
         * @brief Constructor.
         * @param scene Constructed scene.
         * @param playground Scene objects and event management.
         * @param window Program window widget.
         */
        CustomView (QGraphicsScene* scene, PlayGround* playground, QWidget* window);
        /**
         * @brief Destructor.
         */
        ~CustomView ();

    protected:
        /**
         * @brief Overrides resize event handling to resize playground border rect.
         * @param event Generated resize event.
         */
        void resizeEvent (QResizeEvent* event) override;

    private:
        PlayGround* playground;
};

#endif // CUSTOM_VIEW_H
