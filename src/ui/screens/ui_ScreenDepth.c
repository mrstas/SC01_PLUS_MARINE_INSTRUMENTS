// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: wind_instruments

#include "../ui.h"

void ui_ScreenDepth_screen_init(void)
{
    ui_ScreenDepth = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenDepth, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_ContainerTridata = lv_obj_create(ui_ScreenDepth);
    lv_obj_remove_style_all(ui_ContainerTridata);
    lv_obj_set_width(ui_ContainerTridata, lv_pct(100));
    lv_obj_set_height(ui_ContainerTridata, lv_pct(100));
    lv_obj_set_align(ui_ContainerTridata, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_ContainerTridata, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Container1 = lv_obj_create(ui_ContainerTridata);
    lv_obj_remove_style_all(ui_Container1);
    lv_obj_set_height(ui_Container1, 50);
    lv_obj_set_width(ui_Container1, lv_pct(100));
    lv_obj_set_align(ui_Container1, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_Container1, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Container1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Container1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PanelCompassNavigation2 = lv_obj_create(ui_Container1);
    lv_obj_set_height(ui_PanelCompassNavigation2, 50);
    lv_obj_set_width(ui_PanelCompassNavigation2, lv_pct(100));
    lv_obj_set_align(ui_PanelCompassNavigation2, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_PanelCompassNavigation2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_PanelCompassNavigation2, lv_color_hex(0xD8D8D8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PanelCompassNavigation2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_PanelCompassNavigation2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelWindScreen3 = lv_label_create(ui_PanelCompassNavigation2);
    lv_obj_set_width(ui_LabelWindScreen3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelWindScreen3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelWindScreen3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelWindScreen3, "Tridata");
    lv_obj_set_style_text_color(ui_LabelWindScreen3, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelWindScreen3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelWindScreen3, &lv_font_montserrat_36, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Button6 = lv_btn_create(ui_PanelCompassNavigation2);
    lv_obj_set_width(ui_Button6, 50);
    lv_obj_set_height(ui_Button6, 50);
    lv_obj_set_align(ui_Button6, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(ui_Button6, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Button6, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Button6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Button6, lv_color_hex(0xD8D8D8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Button6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Button6, &ui_img_674587949, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Button7 = lv_btn_create(ui_PanelCompassNavigation2);
    lv_obj_set_width(ui_Button7, 50);
    lv_obj_set_height(ui_Button7, 50);
    lv_obj_set_align(ui_Button7, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_Button7, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Button7, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Button7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Button7, lv_color_hex(0xD8D8D8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Button7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Button7, &ui_img_1551684850, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ContainerTridataValues = lv_obj_create(ui_ContainerTridata);
    lv_obj_remove_style_all(ui_ContainerTridataValues);
    lv_obj_set_height(ui_ContainerTridataValues, 430);
    lv_obj_set_width(ui_ContainerTridataValues, lv_pct(100));
    lv_obj_set_x(ui_ContainerTridataValues, 0);
    lv_obj_set_y(ui_ContainerTridataValues, 50);
    lv_obj_set_align(ui_ContainerTridataValues, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_ContainerTridataValues, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ContainerTridataValues, lv_color_hex(0xD8D8D8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ContainerTridataValues, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ContainerDirection = lv_obj_create(ui_ContainerTridataValues);
    lv_obj_remove_style_all(ui_ContainerDirection);
    lv_obj_set_width(ui_ContainerDirection, lv_pct(100));
    lv_obj_set_height(ui_ContainerDirection, lv_pct(50));
    lv_obj_set_align(ui_ContainerDirection, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_ContainerDirection, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_border_color(ui_ContainerDirection, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_ContainerDirection, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_ContainerDirection, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel5 = lv_obj_create(ui_ContainerDirection);
    lv_obj_set_width(ui_Panel5, lv_pct(100));
    lv_obj_set_height(ui_Panel5, lv_pct(23));
    lv_obj_set_align(ui_Panel5, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_Panel5, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel5, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel5, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label5 = lv_label_create(ui_Panel5);
    lv_obj_set_width(ui_Label5, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label5, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label5, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label5, "Heading (°M)");
    lv_obj_set_style_text_font(ui_Label5, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel6 = lv_obj_create(ui_ContainerDirection);
    lv_obj_set_width(ui_Panel6, lv_pct(100));
    lv_obj_set_height(ui_Panel6, lv_pct(77));
    lv_obj_set_align(ui_Panel6, LV_ALIGN_BOTTOM_MID);
    lv_obj_clear_flag(ui_Panel6, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelDirectionValue = lv_label_create(ui_Panel6);
    lv_obj_set_width(ui_LabelDirectionValue, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelDirectionValue, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelDirectionValue, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelDirectionValue, "000");
    lv_obj_set_style_text_align(ui_LabelDirectionValue, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelDirectionValue, &ui_font_freeman160, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Container3 = lv_obj_create(ui_ContainerTridataValues);
    lv_obj_remove_style_all(ui_Container3);
    lv_obj_set_width(ui_Container3, lv_pct(100));
    lv_obj_set_height(ui_Container3, lv_pct(10));
    lv_obj_set_x(ui_Container3, 0);
    lv_obj_set_y(ui_Container3, 20);
    lv_obj_set_align(ui_Container3, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Container3, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label6 = lv_label_create(ui_Container3);
    lv_obj_set_width(ui_Label6, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label6, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label6, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label6, "Sensors");
    lv_obj_set_style_text_font(ui_Label6, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ContainerDepth = lv_obj_create(ui_ContainerTridataValues);
    lv_obj_remove_style_all(ui_ContainerDepth);
    lv_obj_set_width(ui_ContainerDepth, lv_pct(50));
    lv_obj_set_height(ui_ContainerDepth, lv_pct(40));
    lv_obj_set_align(ui_ContainerDepth, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_clear_flag(ui_ContainerDepth, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_border_color(ui_ContainerDepth, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_ContainerDepth, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_ContainerDepth, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel8 = lv_obj_create(ui_ContainerDepth);
    lv_obj_set_width(ui_Panel8, lv_pct(100));
    lv_obj_set_height(ui_Panel8, lv_pct(23));
    lv_obj_set_align(ui_Panel8, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_Panel8, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel8, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel8, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel8, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label7 = lv_label_create(ui_Panel8);
    lv_obj_set_width(ui_Label7, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label7, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label7, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label7, "Depth (m)");
    lv_obj_set_style_text_font(ui_Label7, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelDepthValue = lv_label_create(ui_ContainerDepth);
    lv_obj_set_width(ui_LabelDepthValue, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelDepthValue, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelDepthValue, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelDepthValue, "00.00");
    lv_obj_set_style_text_align(ui_LabelDepthValue, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelDepthValue, &ui_font_freeman60, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ContainerSpeed = lv_obj_create(ui_ContainerTridataValues);
    lv_obj_remove_style_all(ui_ContainerSpeed);
    lv_obj_set_width(ui_ContainerSpeed, lv_pct(50));
    lv_obj_set_height(ui_ContainerSpeed, lv_pct(40));
    lv_obj_set_align(ui_ContainerSpeed, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_clear_flag(ui_ContainerSpeed, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_border_color(ui_ContainerSpeed, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_ContainerSpeed, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_ContainerSpeed, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel9 = lv_obj_create(ui_ContainerSpeed);
    lv_obj_set_width(ui_Panel9, lv_pct(100));
    lv_obj_set_height(ui_Panel9, lv_pct(23));
    lv_obj_set_align(ui_Panel9, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_Panel9, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel9, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel9, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel9, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label8 = lv_label_create(ui_Panel9);
    lv_obj_set_width(ui_Label8, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label8, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label8, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label8, "Speed (kt)");
    lv_obj_set_style_text_font(ui_Label8, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelSpeedValue = lv_label_create(ui_ContainerSpeed);
    lv_obj_set_width(ui_LabelSpeedValue, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelSpeedValue, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelSpeedValue, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelSpeedValue, "00.0");
    lv_obj_set_style_text_align(ui_LabelSpeedValue, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelSpeedValue, &ui_font_freeman60, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_Button6, ui_event_Button6, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Button7, ui_event_Button7, LV_EVENT_ALL, NULL);

}