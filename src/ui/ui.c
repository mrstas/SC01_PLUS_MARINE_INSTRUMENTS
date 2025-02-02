// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.1
// LVGL version: 8.3.11
// Project name: wind_instruments

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////


// SCREEN: ui_ScreenMain
void ui_ScreenMain_screen_init(void);
lv_obj_t * ui_ScreenMain;
lv_obj_t * ui_MainContainerWind;
lv_obj_t * ui_PanelNavigation;
lv_obj_t * ui_LabelWindScreen;
void ui_event_Button3(lv_event_t * e);
lv_obj_t * ui_Button3;
lv_obj_t * ui_PanelWindGauge;
lv_obj_t * ui_LabelAppWindSpd;
lv_obj_t * ui_ImageArrowTrue;
lv_obj_t * ui_ImageArrowApp;
lv_obj_t * ui_ContainerTWS;
lv_obj_t * ui_Label1TWS;
lv_obj_t * ui_Panel1;
lv_obj_t * ui_LabelTWSValue;
lv_obj_t * ui_Label2;
lv_obj_t * ui_ContainerTWD;
lv_obj_t * ui_LabelTWD;
lv_obj_t * ui_Panel4;
lv_obj_t * ui_LabelTWDValue;
lv_obj_t * ui_Label4;
lv_obj_t * ui_ContainerAWA;
lv_obj_t * ui_LabelAWA;
lv_obj_t * ui_Panel3;
lv_obj_t * ui_LabelAWAValue;
lv_obj_t * ui_Label3;
lv_obj_t * ui_ContainerTWA;
lv_obj_t * ui_Label1TWA;
lv_obj_t * ui_Panel2;
lv_obj_t * ui_LabelTWAValue;
lv_obj_t * ui_Label1;
lv_obj_t * ui_MainContainerCompass;
lv_obj_t * ui_PanelNavigation2;
lv_obj_t * ui_LabelWindScreen2;
void ui_event_Button5(lv_event_t * e);
lv_obj_t * ui_Button5;
void ui_event_Button1(lv_event_t * e);
lv_obj_t * ui_Button1;
lv_obj_t * ui_ImageCompassBack;
lv_obj_t * ui_ImageRedGreen;
lv_obj_t * ui_ImageCompassCenter;
lv_obj_t * ui_LabelCompasHeading;
lv_obj_t * ui_Label9;
lv_obj_t * ui_Label10;
lv_obj_t * ui_LabelCompGPSSpeed;
lv_obj_t * ui_LabelCompDepth;
lv_obj_t * ui_MainContainerTridata;
lv_obj_t * ui_PanelNavigation3;
lv_obj_t * ui_LabelWindScreen3;
void ui_event_Button7(lv_event_t * e);
lv_obj_t * ui_Button7;
void ui_event_Button4(lv_event_t * e);
lv_obj_t * ui_Button4;
lv_obj_t * ui_Container2;
lv_obj_t * ui_ContainerDirection;
lv_obj_t * ui_Panel5;
lv_obj_t * ui_Label5;
lv_obj_t * ui_Panel6;
lv_obj_t * ui_LabelDirectionValue;
lv_obj_t * ui_Container3;
lv_obj_t * ui_Label6;
lv_obj_t * ui_ContainerDepth;
lv_obj_t * ui_Panel8;
lv_obj_t * ui_Label7;
lv_obj_t * ui_LabelDepthValue;
lv_obj_t * ui_ContainerSpeed;
lv_obj_t * ui_Panel9;
lv_obj_t * ui_Label8;
lv_obj_t * ui_LabelSpeedValue;
lv_obj_t * ui_MainContainerStatus;
lv_obj_t * ui_PanelNavigation4;
lv_obj_t * ui_LabelWindScreen4;
void ui_event_Button9(lv_event_t * e);
lv_obj_t * ui_Button9;
lv_obj_t * ui_Container4;
lv_obj_t * ui_Label11;
lv_obj_t * ui_Label12;
void ui_event_DropdownDefaultScreen(lv_event_t * e);
lv_obj_t * ui_DropdownDefaultScreen;
lv_obj_t * ui_Label16;
lv_obj_t * ui_LabelDeviceName;
lv_obj_t * ui_LabelIP;
lv_obj_t * ui_Label17;
lv_obj_t * ui_LabelSKAddress;
lv_obj_t * ui_Label18;
lv_obj_t * ui_LabelSKStatus;
lv_obj_t * ui_MainContainerSplash;
lv_obj_t * ui_Image1;
lv_obj_t * ui_Spinner1;
void ui_event_ButtonResetSettings(lv_event_t * e);
lv_obj_t * ui_ButtonResetSettings;
lv_obj_t * ui_Label20;
lv_obj_t * ui_LabelNeedToConfigure;
lv_obj_t * ui_LabelStartWiFiTxt;
lv_obj_t * ui_LabelStartSignalKTxt;
lv_obj_t * ui_LabelStartWiFiStatus;
lv_obj_t * ui_LabelStartSignalK;
lv_obj_t * ui_LabelStartSignalKStatus;
lv_obj_t * ui____initial_actions0;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_Button3(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_MainContainerCompass, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_MainContainerWind, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}
void ui_event_Button5(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_MainContainerWind, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_MainContainerCompass, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}
void ui_event_Button1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_MainContainerTridata, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_MainContainerCompass, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}
void ui_event_Button7(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_MainContainerCompass, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_MainContainerTridata, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}
void ui_event_Button4(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_MainContainerStatus, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_MainContainerTridata, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}
void ui_event_Button9(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_MainContainerTridata, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_MainContainerStatus, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}
void ui_event_DropdownDefaultScreen(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED) {
        updateDefaultStartupScreen(e);
    }
}
void ui_event_ButtonResetSettings(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        resetSettings(e);
    }
}

///////////////////// SCREENS ////////////////////

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_ScreenMain_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_ScreenMain);
}
