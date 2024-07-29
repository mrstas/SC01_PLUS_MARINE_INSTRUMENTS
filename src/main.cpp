#include "sensesp/signalk/signalk_value_listener.h"
#include "sensesp_app_builder.h"
#include <Preferences.h>

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <esp_wifi.h>

#include <nvs_flash.h>

#include <SC01Plus.h>
#include <utils.h>

using namespace sensesp;

ReactESP app;

Preferences preferences;

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

String ipAddress = "";
String ssid = "";
String password = "";

String hostname = "instruments-";
String portalPassword = "password123";

void setup()
{

#ifndef SERIAL_DEBUG_DISABLED
  SetupSerialDebug(115200);
#endif

  preferences.begin("instruments", false);
  // preferences.clear();
  // preferences.remove(key);
  // preferences.end();

  // Create a builder object
  SensESPAppBuilder builder;

  String macAddress = WiFi.macAddress();
  macAddress.replace(":", ""); // remove separator from MAC
  hostname += macAddress;      // add MAC address to hostname in case we have multiple devices

  // Create the global SensESPApp() object.
  sensesp_app = builder.set_hostname(hostname)
                    ->set_wifi_manager_password(portalPassword.c_str()) // captive/configuration portal password
                    // ->set_wifi("WiFiAPname", "APpassword") // we can hardcode WIFI connection here so no need to configure via captive portal
                    //->set_sk_server("10.0.0.77", 3000) //we can hardcode SignalK address so no need to configure via UI/mDNS
                    ->get_app();

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

  init_display();

  // start custom UI
  debugD("init dispay");
  ui_init();

  debugD("show splash");
  _ui_flag_modify(ui_MainContainerSplash, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
  // let's hide all labels but leave spinner and button
  _ui_flag_modify(ui_LabelNeedToConfigure, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
  _ui_flag_modify(ui_LabelStartSignalK, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
  _ui_flag_modify(ui_LabelStartWiFiTxt, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
  _ui_flag_modify(ui_LabelStartSignalKTxt, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
  _ui_flag_modify(ui_LabelStartWiFiStatus, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
  _ui_flag_modify(ui_LabelStartSignalKStatus, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
  // let's spin flash screen for 2 seconds and give a chance to press Facory reset button, before starting esp app
  for (size_t i = 0; i < 2000; i++)
  {
    lv_timer_handler();
    delay(1);
  }

  // hide button and spinner
  debugD("hide button and spinner");
  _ui_flag_modify(ui_ButtonResetSettings, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
  _ui_flag_modify(ui_Spinner1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);

  debugD("displaying captive portal connection instruction");
  _ui_flag_modify(ui_LabelNeedToConfigure, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
  lv_label_set_text(ui_LabelNeedToConfigure, String(String("Connect to WiFi AP \n`Configure ") + String(hostname) + String("`\n use password: ") + String(portalPassword) + String("\nand set WiFi connection")).c_str());

  refreshScreen();

  debugD("starting sensesp_app");
  // after this point UI will "stuck" till sensesp_app gets connected to WiFi and SignalK server
  sensesp_app->start();
  debugD("sensesp_app started");

  // wait in splash screen
  _ui_flag_modify(ui_LabelNeedToConfigure, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
  _ui_flag_modify(ui_Spinner1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
  _ui_flag_modify(ui_LabelStartSignalK, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
  _ui_flag_modify(ui_LabelStartWiFiTxt, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
  _ui_flag_modify(ui_LabelStartSignalKTxt, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
  _ui_flag_modify(ui_LabelStartWiFiStatus, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
  _ui_flag_modify(ui_LabelStartSignalKStatus, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);

  //  WAIT FOR WIFI CONNECTION
  while (WiFi.status() != WL_CONNECTED)
  {
    // spinner animation
    lv_timer_handler();
  }
  ipAddress = WiFi.localIP().toString();
  debugD("Connected to WiFi. IP address: %s", ipAddress.c_str());

  String WiFiStatus = "Connected, IP: " + ipAddress;
  lv_label_set_text(ui_LabelStartWiFiStatus, WiFiStatus.c_str()); // IP on splash screen

  lv_timer_handler();

  // wait for SK servere connection here
  // need either connect to device web interface and set SK Server IP and port
  // or wait for mDNS service to find SK server in the network
  // mDNS service checkbox should be enabled in SKServer "Server->Settings"
  String skStatus;
  String skAddress;
  auto wsclient = sensesp_app->get_ws_client();
  while (!wsclient->is_connected())
  {
    skAddress = wsclient->get_server_address() + ":" + String(wsclient->get_server_port());
    skStatus = wsclient->get_connection_status().c_str();
    lv_label_set_text(ui_LabelStartSignalK, skAddress.c_str());
    lv_label_set_text(ui_LabelStartSignalKStatus, skStatus.c_str());
    lv_timer_handler();
  }

  // update labels on status screen
  lv_label_set_text(ui_LabelIP, WiFiStatus.c_str());       // IP
  lv_label_set_text(ui_LabelDeviceName, hostname.c_str()); // device name
  lv_label_set_text(ui_LabelSKAddress, skAddress.c_str()); // SK Server address
  lv_label_set_text(ui_LabelSKStatus, skStatus.c_str());   // SK Server connection status

  // update screen
  lv_timer_handler();

  // hide splash
  debugD("hide splash");
  _ui_flag_modify(ui_MainContainerSplash, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
  // read settings and show default working screen
  // you can set preffered default screen in status page
  // if you have multiple screens each can boot into different default page
  int selectedScreen = preferences.getInt("startupDisplay", 0);
  debugD("startup display is: %d", selectedScreen);
  switch (selectedScreen)
  {
  case 0:
    _ui_flag_modify(ui_MainContainerWind, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    break;
  case 1:
    _ui_flag_modify(ui_MainContainerCompass, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    break;
  case 2:
    _ui_flag_modify(ui_MainContainerTridata, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    break;
  default:
    _ui_flag_modify(ui_MainContainerWind, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    break;
  }
  lv_dropdown_set_selected(ui_DropdownDefaultScreen, selectedScreen);
  // do render
  lv_timer_handler();
}

// main loop
void loop()
{
  // refresh screen
  lv_timer_handler();

  // do sensesp stuff
  app.tick();

  // attempt to animate arrows by moving 1 degree at a time instead of jumping to target position
  // TODO: fix full circle transition when value crosses 0, f.e. when it changes from 5 to 355
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

// save default screen selection in nvram
void updateDefaultStartupScreen(lv_event_t *e)
{
  debugD("dropdown changed event");
  lv_obj_t *dropdown = lv_event_get_target(e);
  int i = lv_dropdown_get_selected(dropdown);
  preferences.putInt("startupDisplay", i);
  debugD("dropdown changed to %d", i);
}

void resetSettings(lv_event_t *e)
{
  debugD("erasing nvs parameters...");
  nvs_flash_erase(); // erase the NVS partition and...
  nvs_flash_init();
  debugD("erasing all SPIFFS files...");
  listDirAndDelete(SPIFFS, "/", 0);
  ESP.restart();
}
