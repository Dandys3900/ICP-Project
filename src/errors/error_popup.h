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
        Error_PopUp (QWidget* window);
        ~Error_PopUp ();

        static void show_err (QString err_msg);
        static void clean_up ();

    private:
        QLabel*      mp_err_txt_label;
        QWidget*     mp_main_window;
        QTimer*      mp_popup_timer;
        QVBoxLayout* mp_layout;

        static Error_PopUp* instance;
};

#endif // ERRPOPUP_H
