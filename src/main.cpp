#include "sensesp/signalk/signalk_value_listener.h"
#include "sensesp_app_builder.h"

using namespace sensesp;

#define LGFX_USE_V1
#include <LovyanGFX.hpp>

// SETUP LGFX PARAMETERS FOR WT32-SC01-PLUS
class LGFX : public lgfx::LGFX_Device
{

  lgfx::Panel_ST7796 _panel_instance;
  lgfx::Bus_Parallel8 _bus_instance;
  lgfx::Light_PWM _light_instance;
  lgfx::Touch_FT5x06 _touch_instance; // FT5206, FT5306, FT5406, FT6206, FT6236, FT6336, FT6436

public:
  LGFX(void)
  {
    {
      auto cfg = _bus_instance.config();

      cfg.freq_write = 20000000;
      cfg.pin_wr = 47; // pin number connecting WR
      cfg.pin_rd = -1; // pin number connecting RD
      cfg.pin_rs = 0;  // Pin number connecting RS(D/C)
      cfg.pin_d0 = 9;  // pin number connecting D0
      cfg.pin_d1 = 46; // pin number connecting D1
      cfg.pin_d2 = 3;  // pin number connecting D2
      cfg.pin_d3 = 8;  // pin number connecting D3
      cfg.pin_d4 = 18; // pin number connecting D4
      cfg.pin_d5 = 17; // pin number connecting D5
      cfg.pin_d6 = 16; // pin number connecting D6
      cfg.pin_d7 = 15; // pin number connecting D7
      // cfg.i2s_port = I2S_NUM_0; // (I2S_NUM_0 or I2S_NUM_1)

      _bus_instance.config(cfg);              // Apply the settings to the bus.
      _panel_instance.setBus(&_bus_instance); // Sets the bus to the panel.
    }

    {                                      // Set display panel control.
      auto cfg = _panel_instance.config(); // Get the structure for display panel settings.

      cfg.pin_cs = -1;   // Pin number to which CS is connected (-1 = disable)
      cfg.pin_rst = 4;   // pin number where RST is connected (-1 = disable)
      cfg.pin_busy = -1; // pin number to which BUSY is connected (-1 = disable)

      // * The following setting values ​​are set to general default values ​​for each panel, and the pin number (-1 = disable) to which BUSY is connected, so please try commenting out any unknown items.

      cfg.memory_width = 320;  // Maximum width supported by driver IC
      cfg.memory_height = 480; // Maximum height supported by driver IC
      cfg.panel_width = 320;   // actual displayable width
      cfg.panel_height = 480;  // actual displayable height
      cfg.offset_x = 0;        // Panel offset in X direction
      cfg.offset_y = 0;        // Panel offset in Y direction
      cfg.offset_rotation = 0; // was 2
      cfg.dummy_read_pixel = 8;
      cfg.dummy_read_bits = 1;
      cfg.readable = true; // was false
      cfg.invert = true;
      cfg.rgb_order = false;
      cfg.dlen_16bit = false;
      cfg.bus_shared = true; // was false something to do with SD?

      _panel_instance.config(cfg);
    }

    {                                      // Set backlight control. (delete if not necessary)
      auto cfg = _light_instance.config(); // Get the structure for backlight configuration.

      cfg.pin_bl = 45;     // pin number to which the backlight is connected
      cfg.invert = false;  // true to invert backlight brightness
      cfg.freq = 44100;    // backlight PWM frequency
      cfg.pwm_channel = 0; // PWM channel number to use (7??)

      _light_instance.config(cfg);
      _panel_instance.setLight(&_light_instance); // Sets the backlight to the panel.
    }

    //*
    { // Configure settings for touch screen control. (delete if not necessary)
      auto cfg = _touch_instance.config();

      cfg.x_min = 0;          // Minimum X value (raw value) obtained from the touchscreen
      cfg.x_max = 319;        // Maximum X value (raw value) obtained from the touchscreen//319
      cfg.y_min = 0;          // Minimum Y value obtained from touchscreen (raw value)
      cfg.y_max = 479;        // Maximum Y value (raw value) obtained from the touchscreen//479
      cfg.pin_int = 7;        // pin number to which INT is connected
      cfg.bus_shared = false; // set true if you are using the same bus as the screen
      cfg.offset_rotation = 1;

      // For I2C connection
      cfg.i2c_port = 0;    // Select I2C to use (0 or 1)
      cfg.i2c_addr = 0x38; // I2C device address number
      cfg.pin_sda = 6;     // pin number where SDA is connected
      cfg.pin_scl = 5;     // pin number to which SCL is connected
      cfg.freq = 400000;   // set I2C clock

      _touch_instance.config(cfg);
      _panel_instance.setTouch(&_touch_instance); // Set the touchscreen to the panel.
    }
    //*/
    setPanel(&_panel_instance); // Sets the panel to use.
  }
};

#include <lvgl.h>
#include "ui/ui.h" // this is the ui generated with lvgl / squareline editor

LGFX tft;

#define screenWidth 480
#define screenHeight 320

// lv debugging can be set in lv_conf.h
#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char *buf)
{
  // debugD("%s", buf);
  Serial.printf(buf);
  Serial.flush();
}
#endif

// create buffer for display
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * 10];

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);
  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.writePixels((lgfx::rgb565_t *)&color_p->full, w * h);
  tft.endWrite();
  lv_disp_flush_ready(disp);
}

/*Read the touchpad*/
void my_touch_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
  uint16_t touchX, touchY;
  bool touched = tft.getTouch(&touchX, &touchY);
  if (!touched)
  {
    data->state = LV_INDEV_STATE_REL;
  }
  else
  {
    data->state = LV_INDEV_STATE_PR;
    //  data->point.x = touchX;
    //  data->point.y = touchY;
    data->point.x = map(touchX, 0, 319, 0, 479); // after rotation need to fix range???
    data->point.y = map(touchY, 0, 479, 0, 319);

#if DEBUG_TOUCH != 0
    Serial.print("Data x ");
    Serial.print(data->point.x);
    Serial.print("    y ");
    Serial.println(data->point.y);
#endif
  }
}

ReactESP app;

//************************************************************************************
//  SETUP AND LOOP
//************************************************************************************

// following vrs are fo storing current values, logic is to prevent refreshing displayed
// values if new value is the same as currently displayed
// storing in global var as reading from UI will return char[] which is not helpfull as we rounding
// and converting each text to desired resolution

float varWindScr_EnvironmentWindSpeedTrue = 0;
float varWindScr_EnvironmentWindDirectionTrue = 0;
float varWindScr_EnvironmentWindSpeedApparent = 0;
float varWindScr_EnvironmentWindAngleApparent = 0;
float varWindScr_EnvironmentWindAngleTrueGround = 0;

float varTridataScr_NavigationSpeedThroughWater = 0;
float varTridataScr_EnvironmentDepthBelowTransducer = 0;
float varTridataScr_NavigationCourseOverGroundMagnetic = 0;

float varCompassScr_NavigationSpeedOverGround = 0;
float varCompassScr_EnvironmentDepthBelowTransducer = 0;
float varCompassScr_NavigationCourseOverGroundMagnetic = 0;

// for Wind screen arrow animation
int currentTrueWindAngle = 0;
int targetTrueWindAngle = 0;

int currentAppWindAngle = 0;
int targetAppWindAngle = 0;

int currentCompassAngle = 0;
int targetCompassAngle = 0;

void setup()
{

  // Create a builder object
  SensESPAppBuilder builder;

  // Create the global SensESPApp() object.
  sensesp_app = builder.set_hostname("sensesp-listener-heading")
                    //->enable_ota("thisisfine")
                    ->get_app();

#ifndef SERIAL_DEBUG_DISABLED
  SetupSerialDebug(115200);
#endif

  // apparent wind speed (m/s)
  auto wind_speedApparent = new SKValueListener<float>("environment.wind.speedApparent");
  wind_speedApparent->connect_to(new LambdaConsumer<float>([](float input)
                                                           {
    debugD("wind.speedApparent: %f", input);
    if (!lv_obj_has_flag(ui_MainContainerWind, LV_OBJ_FLAG_HIDDEN)) //update only if current container is not hidden (e.g. container is visible)
    {
      if (input != varWindScr_EnvironmentWindSpeedApparent) // update only if displayed value is different from new input
      {
        char displayValueBuffer[10];
        sprintf(displayValueBuffer, "%0.1f", input * 1.944);
        debugD("setting ui_LabelAppWindSpd to %s", displayValueBuffer);
        lv_label_set_text(ui_LabelAppWindSpd, displayValueBuffer);
        varWindScr_EnvironmentWindSpeedApparent = input; // assign new input to variable for checking in next input update
      }
    } }));

  // apparent wind angle (rad)
  auto wind_angleApparent = new SKValueListener<float>("environment.wind.angleApparent");
  wind_angleApparent->connect_to(new LambdaConsumer<float>([](float input)
                                                           {
    debugD("environment.wind.angleApparent: %f", input);
    if (!lv_obj_has_flag(ui_MainContainerWind, LV_OBJ_FLAG_HIDDEN))
    {
      if (input != varWindScr_EnvironmentWindAngleApparent)
      {
        char displayValueBuffer[10];
        targetAppWindAngle = int(trunc(input * 180 / PI)); 
        sprintf(displayValueBuffer, "%d", targetAppWindAngle);
        debugD("setting ui_LabelAWAValue to %s", displayValueBuffer);
        lv_label_set_text(ui_LabelAWAValue, displayValueBuffer);
        varWindScr_EnvironmentWindAngleApparent = input;
      }
    } }));

  // true wind angle varWind_angleTrueGround (rad)
  auto wind_angleTrueGround = new SKValueListener<float>("environment.wind.angleTrueGround");
  wind_angleTrueGround->connect_to(new LambdaConsumer<float>([](float input)
                                                             {
    debugD("environment.wind.angleTrueGround: %f", input);
    if (!lv_obj_has_flag(ui_MainContainerWind, LV_OBJ_FLAG_HIDDEN))
    {
      if (input != varWindScr_EnvironmentWindAngleTrueGround)
      {
        char displayValueBuffer[10];
        targetTrueWindAngle = int(trunc(input * 180 / PI));
        sprintf(displayValueBuffer, "%d", targetTrueWindAngle);
        debugD("setting ui_LabelTWAValue to %s", displayValueBuffer);
        lv_label_set_text(ui_LabelTWAValue, displayValueBuffer);       
        varWindScr_EnvironmentWindAngleTrueGround = input;
      }
    } }));

  // true wind direction varWind_directionTrue in rad
  auto wind_directionTrue = new SKValueListener<float>("environment.wind.directionTrue");
  wind_directionTrue->connect_to(new LambdaConsumer<float>([](float input)
                                                           {
    debugD("environment.wind.directionTrue: %f", input);
    if (!lv_obj_has_flag(ui_MainContainerWind, LV_OBJ_FLAG_HIDDEN))
    {
      if (input != varWindScr_EnvironmentWindDirectionTrue)
      {
        char displayValueBuffer[10];
        int trueWindDirectionVal = int(trunc(input * 1800 / PI));
        sprintf(displayValueBuffer, "%d", trueWindDirectionVal / 10);
        debugD("setting ui_LabelTWDValue to %s", displayValueBuffer);
        lv_label_set_text(ui_LabelTWDValue, displayValueBuffer);
        varWindScr_EnvironmentWindDirectionTrue = input;
      }
    } }));

  // true wind speed varWind_speedTrue in m/s
  auto wind_speedTrue = new SKValueListener<float>("environment.wind.speedTrue");
  wind_speedTrue->connect_to(new LambdaConsumer<float>([](float input)
                                                       {
    debugD("environment.wind.speedTrue: %f", input);
    if (!lv_obj_has_flag(ui_MainContainerWind, LV_OBJ_FLAG_HIDDEN))
    {
      if (input != varWindScr_EnvironmentWindSpeedTrue)
      {
        char displayValueBuffer[10];
        sprintf(displayValueBuffer, "%0.1f", input * 1.944);
        debugD("setting ui_LabelTWSValue to %s", displayValueBuffer);
        lv_label_set_text(ui_LabelTWSValue, displayValueBuffer);
        varWindScr_EnvironmentWindSpeedTrue = input;
      }
    } }));

  // depth below transducer (m)
  auto depth_belowTransducer = new SKValueListener<float>("environment.depth.belowTransducer");
  depth_belowTransducer->connect_to(new LambdaConsumer<float>([](float input)
                                                              {
    debugD("environment.depth.belowTransducer: %f", input);
    if (!lv_obj_has_flag(ui_MainContainerCompass, LV_OBJ_FLAG_HIDDEN))
    {
      if (input!=varCompassScr_EnvironmentDepthBelowTransducer)
      {
        char displayValueBuffer[10];
        sprintf(displayValueBuffer, "%0.1f", input);
        lv_label_set_text(ui_LabelCompDepth, displayValueBuffer);
        varCompassScr_EnvironmentDepthBelowTransducer = input;
      }      
    }

    if (!lv_obj_has_flag(ui_MainContainerTridata, LV_OBJ_FLAG_HIDDEN))
    {
      if (input!=varTridataScr_EnvironmentDepthBelowTransducer)
      {
        char displayValueBuffer[10];
        sprintf(displayValueBuffer, "%0.1f", input);
        lv_label_set_text(ui_LabelDepthValue, displayValueBuffer);
        varTridataScr_EnvironmentDepthBelowTransducer = input;
      }      
    } }));

  // speed through water -- from lag sensor varSpeedThroughWater in m/s
  auto speedThroughWater = new SKValueListener<float>("navigation.speedThroughWater");
  speedThroughWater->connect_to(new LambdaConsumer<float>([](float input)
                                                          {
    debugD("navigation.speedThroughWater: %f", input);
    if (!lv_obj_has_flag(ui_MainContainerTridata, LV_OBJ_FLAG_HIDDEN))
    {
      if (input != varTridataScr_NavigationSpeedThroughWater)
      {
        char displayValueBuffer[10];
        sprintf(displayValueBuffer, "%0.1f", input * 1.944);
        lv_label_set_text(ui_LabelSpeedValue, displayValueBuffer);
        varTridataScr_NavigationSpeedThroughWater = input;
      }
    } }));

  // GPS speed over ground varSpeedOverGround in m/s
  auto speedOverGround = new SKValueListener<float>("navigation.speedOverGround");
  speedOverGround->connect_to(new LambdaConsumer<float>([](float input)
                                                        {
    debugD("navigation.speedOverGround: %f", input);
    if (!lv_obj_has_flag(ui_MainContainerCompass, LV_OBJ_FLAG_HIDDEN))
    {
      if (input != varCompassScr_NavigationSpeedOverGround)
      {
        char displayValueBuffer[10];
        sprintf(displayValueBuffer, "%0.1f", input * 1.944);
        lv_label_set_text(ui_LabelCompGPSSpeed, displayValueBuffer);
        varCompassScr_NavigationSpeedOverGround = input;
      }
    } }));

  // magnetic direction and compas dial rotation in rad
  auto courseOverGroundMagnetic = new SKValueListener<float>("navigation.courseOverGroundMagnetic");
  courseOverGroundMagnetic->connect_to(new LambdaConsumer<float>([](float input)
                                                                 {
    debugD("navigation.courseOverGroundMagnetic: %f", input);

    if (!lv_obj_has_flag(ui_MainContainerCompass, LV_OBJ_FLAG_HIDDEN))
    {
      if (input != varCompassScr_NavigationCourseOverGroundMagnetic)
      {
        char displayValueBuffer[10];
        targetCompassAngle = int(trunc(input * 180 / PI));
        sprintf(displayValueBuffer, "%3d", targetCompassAngle);
        lv_label_set_text(ui_LabelCompasHeading, displayValueBuffer);
        varCompassScr_NavigationCourseOverGroundMagnetic = input;
      }
    }

    if (!lv_obj_has_flag(ui_MainContainerTridata, LV_OBJ_FLAG_HIDDEN))
    {
      if (input != varTridataScr_NavigationCourseOverGroundMagnetic)
      {
        char displayValueBuffer[10];
        int course = int(trunc(input * 180 / PI));
        sprintf(displayValueBuffer, "%3d", course);
        lv_label_set_text(ui_LabelDirectionValue, displayValueBuffer);
        varTridataScr_NavigationCourseOverGroundMagnetic = input;
      }
        } }));

  // // print out free heap
  // app.onRepeat(2000, []() {
  //   debugD("Free heap: %d", ESP.getFreeHeap());
  //   debugD("Connected to WiFi. IP address: %s", WiFi.localIP().toString().c_str());

  // });

  tft.begin();
  tft.setRotation(0); // 1/3 rotation
  tft.setBrightness(255);

  lv_init();

#if LV_USE_LOG != 0
  lv_log_register_print_cb(my_print); /* register print function for debugging */
#endif

  lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * 10);

  /*Initialize the display*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  // set rotation
  // disp_drv.sw_rotate = 1; // 2/3 rotation
  disp_drv.rotated = LV_DISP_ROT_90; // 3/3 rotation
  lv_disp_drv_register(&disp_drv);

  /*Initialize the input device driver*/
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touch_read;
  lv_indev_drv_register(&indev_drv);

  // start the UI
  ui_init();

  sensesp_app->start();

  _ui_flag_modify(ui_MainContainerWind, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
}

void loop()
{
  lv_timer_handler();
  app.tick();

  // attempt to animate arrows by moving 1 degree at a time instead of jumping to target position
  if (!lv_obj_has_flag(ui_MainContainerWind, LV_OBJ_FLAG_HIDDEN))
  {
    if (currentTrueWindAngle != targetTrueWindAngle)
    {
      if (currentTrueWindAngle > targetTrueWindAngle)
        currentTrueWindAngle--;
      else if (currentTrueWindAngle < targetTrueWindAngle)
        currentTrueWindAngle++;
      debugD("setting set_angle ui_ImageArrowTrue to %d, target is %d", currentTrueWindAngle * 10, targetTrueWindAngle * 10);
      lv_img_set_angle(ui_ImageArrowTrue, currentTrueWindAngle * 10); // we have 0-360, but UI needs 0-3600
    }

    if (currentAppWindAngle != targetAppWindAngle)
    {
      if (currentAppWindAngle > targetAppWindAngle)
        currentAppWindAngle--;
      else if (currentAppWindAngle < targetAppWindAngle)
        currentAppWindAngle++;
      debugD("setting set_angle ui_ImageArrowApp to %d, target is %d", currentAppWindAngle * 10, targetAppWindAngle * 10);
      lv_img_set_angle(ui_ImageArrowApp, currentAppWindAngle * 10);
    }
  }

  if (!lv_obj_has_flag(ui_MainContainerCompass, LV_OBJ_FLAG_HIDDEN))
  {
    if (currentCompassAngle != targetCompassAngle)
    {
      if (currentCompassAngle > targetCompassAngle)
        currentCompassAngle--;
      else if (currentCompassAngle < targetCompassAngle)
        currentCompassAngle++;
      debugD("setting set_angle ui_ImageCompassBack to %d, target is %d", -currentCompassAngle * 10, -targetCompassAngle * 10);
      lv_img_set_angle(ui_ImageCompassBack, -currentCompassAngle * 10);
    }
  }
}