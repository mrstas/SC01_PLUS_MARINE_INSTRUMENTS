SET(SOURCES screens/ui_ScreenMain.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.c
    images/ui_img_674587949.c
    images/ui_img_1551684850.c
    images/ui_img_scale_back_png.c
    images/ui_img_arrow_true_png.c
    images/ui_img_arrow_app_png.c
    images/ui_img_827446305.c
    images/ui_img_1213530082.c
    images/ui_img_1486399645.c
    fonts/ui_font_condensed60.c
    fonts/ui_font_freeman160.c
    fonts/ui_font_freeman60.c)

add_library(ui ${SOURCES})
