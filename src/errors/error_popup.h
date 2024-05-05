/** ICP Project 2023/2024
 * @file error_popup.h
 * @author Tomáš Daniel (xdanie14)
 * @brief Header file for Error_PopUp class.
 */

#ifndef ERRPOPUP_H
#define ERRPOPUP_H

#include "includes/libs_file.h"

class Error_PopUp : public QWidget {
    public:
        /**
         * @brief Constructor.
         * @param window Parent.
         */
        Error_PopUp (QWidget* window);
        /**
         * @brief Destructor.
         */
        ~Error_PopUp ();
        /**
         * @brief Constructs error widget with given message.
         * @param err_msg Error message to be displayed.
         */
        static void show_err (QString err_msg);
        /**
         * @brief Deallocates static instance of this class.
         */
        static void clean_up ();

    private:
        QLabel*      err_txt_label; // Error label inside of widget
        QWidget*     main_window;
        QTimer*      popup_timer;
        QVBoxLayout* layout;

        static Error_PopUp* instance;
};

#endif // ERRPOPUP_H
