// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.1
// LVGL version: 8.3.11
// Project name: wind_instruments

#ifndef _WIND_INSTRUMENTS_UI_H
#define _WIND_INSTRUMENTS_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined __has_include
#if __has_include("lvgl.h")
#include "lvgl.h"
#elif __has_include("lvgl/lvgl.h")
#include "lvgl/lvgl.h"
#else
#include "lvgl.h"
#endif
#else
#include "lvgl.h"
#endif

#include "ui_helpers.h"
#include "ui_events.h"

// SCREEN: ui_ScreenMain
void ui_ScreenMain_screen_init(void);
extern lv_obj_t * ui_ScreenMain;
extern lv_obj_t * ui_MainContainerWind;
extern lv_obj_t * ui_PanelNavigation;
extern lv_obj_t * ui_LabelWindScreen;
void ui_event_Button3(lv_event_t * e);
extern lv_obj_t * ui_Button3;
extern lv_obj_t * ui_PanelWindGauge;
extern lv_obj_t * ui_LabelAppWindSpd;
extern lv_obj_t * ui_ImageArrowTrue;
extern lv_obj_t * ui_ImageArrowApp;
extern lv_obj_t * ui_ContainerTWS;
extern lv_obj_t * ui_Label1TWS;
extern lv_obj_t * ui_Panel1;
extern lv_obj_t * ui_LabelTWSValue;
extern lv_obj_t * ui_Label2;
extern lv_obj_t * ui_ContainerTWD;
extern lv_obj_t * ui_LabelTWD;
extern lv_obj_t * ui_Panel4;
extern lv_obj_t * ui_LabelTWDValue;
extern lv_obj_t * ui_Label4;
extern lv_obj_t * ui_ContainerAWA;
extern lv_obj_t * ui_LabelAWA;
extern lv_obj_t * ui_Panel3;
extern lv_obj_t * ui_LabelAWAValue;
extern lv_obj_t * ui_Label3;
extern lv_obj_t * ui_ContainerTWA;
extern lv_obj_t * ui_Label1TWA;
extern lv_obj_t * ui_Panel2;
extern lv_obj_t * ui_LabelTWAValue;
extern lv_obj_t * ui_Label1;
extern lv_obj_t * ui_MainContainerCompass;
extern lv_obj_t * ui_PanelNavigation2;
extern lv_obj_t * ui_LabelWindScreen2;
void ui_event_Button5(lv_event_t * e);
extern lv_obj_t * ui_Button5;
void ui_event_Button1(lv_event_t * e);
extern lv_obj_t * ui_Button1;
extern lv_obj_t * ui_ImageCompassBack;
extern lv_obj_t * ui_ImageRedGreen;
extern lv_obj_t * ui_ImageCompassCenter;
extern lv_obj_t * ui_LabelCompasHeading;
extern lv_obj_t * ui_Label9;
extern lv_obj_t * ui_Label10;
extern lv_obj_t * ui_LabelCompGPSSpeed;
extern lv_obj_t * ui_LabelCompDepth;
extern lv_obj_t * ui_MainContainerTridata;
extern lv_obj_t * ui_PanelNavigation3;
extern lv_obj_t * ui_LabelWindScreen3;
void ui_event_Button7(lv_event_t * e);
extern lv_obj_t * ui_Button7;
void ui_event_Button4(lv_event_t * e);
extern lv_obj_t * ui_Button4;
extern lv_obj_t * ui_Container2;
extern lv_obj_t * ui_ContainerDirection;
extern lv_obj_t * ui_Panel5;
extern lv_obj_t * ui_Label5;
extern lv_obj_t * ui_Panel6;
extern lv_obj_t * ui_LabelDirectionValue;
extern lv_obj_t * ui_Container3;
extern lv_obj_t * ui_Label6;
extern lv_obj_t * ui_ContainerDepth;
extern lv_obj_t * ui_Panel8;
extern lv_obj_t * ui_Label7;
extern lv_obj_t * ui_LabelDepthValue;
extern lv_obj_t * ui_ContainerSpeed;
extern lv_obj_t * ui_Panel9;
extern lv_obj_t * ui_Label8;
extern lv_obj_t * ui_LabelSpeedValue;
extern lv_obj_t * ui_MainContainerStatus;
extern lv_obj_t * ui_PanelNavigation4;
extern lv_obj_t * ui_LabelWindScreen4;
void ui_event_Button9(lv_event_t * e);
extern lv_obj_t * ui_Button9;
extern lv_obj_t * ui_Container4;
extern lv_obj_t * ui_Label11;
extern lv_obj_t * ui_Label12;
void ui_event_DropdownDefaultScreen(lv_event_t * e);
extern lv_obj_t * ui_DropdownDefaultScreen;
extern lv_obj_t * ui_Label16;
extern lv_obj_t * ui_LabelDeviceName;
extern lv_obj_t * ui_LabelIP;
extern lv_obj_t * ui_Label17;
extern lv_obj_t * ui_LabelSKAddress;
extern lv_obj_t * ui_Label18;
extern lv_obj_t * ui_LabelSKStatus;
extern lv_obj_t * ui_MainContainerSplash;
extern lv_obj_t * ui_Image1;
extern lv_obj_t * ui_Spinner1;
void ui_event_ButtonResetSettings(lv_event_t * e);
extern lv_obj_t * ui_ButtonResetSettings;
extern lv_obj_t * ui_Label20;
extern lv_obj_t * ui_LabelNeedToConfigure;
extern lv_obj_t * ui_LabelStartWiFiTxt;
extern lv_obj_t * ui_LabelStartSignalKTxt;
extern lv_obj_t * ui_LabelStartWiFiStatus;
extern lv_obj_t * ui_LabelStartSignalK;
extern lv_obj_t * ui_LabelStartSignalKStatus;
extern lv_obj_t * ui____initial_actions0;


LV_IMG_DECLARE(ui_img_1551684850);    // assets/arrow-circle-right.png
LV_IMG_DECLARE(ui_img_scale_back_png);    // assets/scale_back.png
LV_IMG_DECLARE(ui_img_arrow_true_png);    // assets/arrow_true.png
LV_IMG_DECLARE(ui_img_arrow_app_png);    // assets/arrow_app.png
LV_IMG_DECLARE(ui_img_674587949);    // assets/arrow-circle-left.png
LV_IMG_DECLARE(ui_img_827446305);    // assets/compass-back.png
LV_IMG_DECLARE(ui_img_1213530082);    // assets/compass-redgreen-op.png
LV_IMG_DECLARE(ui_img_1486399645);    // assets/compass-center.png
LV_IMG_DECLARE(ui_img_signalkinstrumentslogo_png);    // assets/SignalKinstrumentsLogo.png



LV_FONT_DECLARE(ui_font_condensed60);
LV_FONT_DECLARE(ui_font_freeman160);
LV_FONT_DECLARE(ui_font_freeman60);



void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
