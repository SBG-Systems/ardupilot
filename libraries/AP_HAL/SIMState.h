#pragma once

#include <SITL/SITL.h>

#if AP_SIM_ENABLED

#include <AP_HAL/AP_HAL.h>

#include <SITL/SITL_Input.h>
#include <SITL/SIM_SoloGimbal.h>
#include <SITL/SIM_ADSB.h>
#include <SITL/SIM_Vicon.h>
#include <SITL/SIM_RF_Benewake_TF02.h>
#include <SITL/SIM_RF_Benewake_TF03.h>
#include <SITL/SIM_RF_Benewake_TFmini.h>
#include <SITL/SIM_RF_NoopLoop.h>
#include <SITL/SIM_RF_TeraRanger_Serial.h>
#include <SITL/SIM_RF_LightWareSerial.h>
#include <SITL/SIM_RF_LightWareSerialBinary.h>
#include <SITL/SIM_RF_Lanbao.h>
#include <SITL/SIM_RF_BLping.h>
#include <SITL/SIM_RF_LeddarOne.h>
#include <SITL/SIM_RF_RDS02UF.h>
#include <SITL/SIM_RF_USD1_v0.h>
#include <SITL/SIM_RF_USD1_v1.h>
#include <SITL/SIM_RF_MaxsonarSerialLV.h>
#include <SITL/SIM_RF_Wasp.h>
#include <SITL/SIM_RF_NMEA.h>
#include <SITL/SIM_RF_MAVLink.h>
#include <SITL/SIM_RF_GYUS42v2.h>
#include <SITL/SIM_VectorNav.h>
#include <SITL/SIM_MicroStrain.h>
#include <SITL/SIM_InertialLabs.h>
#include <SITL/SIM_AIS.h>
#include <SITL/SIM_GPS.h>

#include <SITL/SIM_EFI_Hirth.h>

#include <SITL/SIM_Frsky_D.h>
#include <SITL/SIM_CRSF.h>
#include <SITL/SIM_PS_RPLidarA2.h>
#include <SITL/SIM_PS_TeraRangerTower.h>
#include <SITL/SIM_PS_LightWare_SF45B.h>

#include <SITL/SIM_RichenPower.h>
#include <SITL/SIM_Loweheiser.h>
#include <SITL/SIM_FETtecOneWireESC.h>
#include <AP_HAL/utility/Socket_native.h>

#include <AP_HAL/AP_HAL_Namespace.h>

class AP_HAL::SIMState {
public:

    // simulated airspeed, sonar and battery monitor
    uint16_t sonar_pin_value;    // pin 0
    uint16_t airspeed_pin_value[2]; // pin 1
    uint16_t voltage_pin_value;  // pin 13
    uint16_t current_pin_value;  // pin 12
    uint16_t voltage2_pin_value;  // pin 15
    uint16_t current2_pin_value;  // pin 14

    void update();

#if AP_SIM_GPS_ENABLED
    void set_gps0(SITL::GPS *_gps) { gps[0] = _gps; }
#endif

    uint16_t pwm_output[32];  // was SITL_NUM_CHANNELS

private:
    void _set_param_default(const char *parm);
    void _sitl_setup(const char *home_str);
    void _setup_timer(void);
    void _setup_adc(void);

    void set_height_agl(void);
    void _set_signal_handlers(void) const;

    void _update_airspeed(float airspeed);
    void _simulator_servos(struct sitl_input &input);
    void _fdm_input_step(void);
    void fdm_input_local(void);

    void wait_clock(uint64_t wait_time_usec);

    uint16_t pwm_input[16];  // was SITL_RC_INPUT_CHANNELS

    // internal state
    // enum vehicle_type _vehicle;
    uint8_t _instance;
    uint16_t _base_port;
    pid_t _parent_pid;
    uint32_t _update_count;

    SITL::SIM *_sitl;
    uint16_t _rcin_port;
    uint16_t _fg_view_port;
    uint16_t _irlock_port;
    float _current;

    bool _use_rtscts;
    bool _use_fg_view;
    
    const char *_fg_address;

    // internal SITL model
    SITL::Aircraft *sitl_model;

#if AP_SIM_SOLOGIMBAL_ENABLED
    // simulated gimbal
    bool enable_gimbal;
    SITL::SoloGimbal *gimbal;
#endif

#if AP_SIM_ADSB_ENABLED
    // simulated ADSb
    SITL::ADSB *adsb;
#endif  // AP_SIM_ADSB_ENABLED

    // simulated vicon system:
#if AP_SIM_VICON_ENABLED
    SITL::Vicon *vicon;
#endif  // AP_SIM_VICON_ENABLED

    // simulated Benewake tf02 rangefinder:
    SITL::RF_Benewake_TF02 *benewake_tf02;
    // simulated Benewake tf03 rangefinder:
    SITL::RF_Benewake_TF03 *benewake_tf03;
    // simulated Benewake tfmini rangefinder:
    SITL::RF_Benewake_TFmini *benewake_tfmini;
    //simulated NoopLoop TOFSense rangefinder:
    SITL::RF_Nooploop *nooploop;
    // simulated TeraRangerSerial rangefinder:
    SITL::RF_TeraRanger_Serial *teraranger_serial;

    // simulated LightWareSerial rangefinder - legacy protocol::
    SITL::RF_LightWareSerial *lightwareserial;
    // simulated LightWareSerial rangefinder - binary protocol:
    SITL::RF_LightWareSerialBinary *lightwareserial_binary;
    // simulated Lanbao rangefinder:
    SITL::RF_Lanbao *lanbao;
    // simulated BLping rangefinder:
    SITL::RF_BLping *blping;
    // simulated LeddarOne rangefinder:
    SITL::RF_LeddarOne *leddarone;
    // simulated RDS02UF rangefinder:
    SITL::RF_RDS02UF *rds02uf;
    // simulated USD1 v0 rangefinder:
    SITL::RF_USD1_v0 *USD1_v0;
    // simulated USD1 v1 rangefinder:
    SITL::RF_USD1_v1 *USD1_v1;
    // simulated MaxsonarSerialLV rangefinder:
    SITL::RF_MaxsonarSerialLV *maxsonarseriallv;
    // simulated Wasp rangefinder:
    SITL::RF_Wasp *wasp;
    // simulated NMEA rangefinder:
    SITL::RF_NMEA *nmea;
    // simulated MAVLink rangefinder:
    SITL::RF_MAVLink *rf_mavlink;
    // simulated GYUS42v2 rangefinder:
    SITL::RF_GYUS42v2 *gyus42v2;

    // simulated Frsky devices
    SITL::Frsky_D *frsky_d;
    // SITL::Frsky_SPort *frsky_sport;
    // SITL::Frsky_SPortPassthrough *frsky_sportpassthrough;

#if AP_SIM_PS_RPLIDARA2_ENABLED
    // simulated RPLidarA2:
    SITL::PS_RPLidarA2 *rplidara2;
#endif

    // simulated FETtec OneWire ESCs:
    SITL::FETtecOneWireESC *fetteconewireesc;

#if AP_SIM_PS_LIGHTWARE_SF45B_ENABLED
    // simulated SF45B proximity sensor:
    SITL::PS_LightWare_SF45B *sf45b;
#endif

#if AP_SIM_PS_TERARANGERTOWER_ENABLED
    SITL::PS_TeraRangerTower *terarangertower;
#endif

#if AP_SIM_CRSF_ENABLED
    // simulated CRSF devices
    SITL::CRSF *crsf;
#endif

    // simulated VectorNav system:
    SITL::VectorNav *vectornav;

    // simulated MicroStrain Series 5 system
    SITL::MicroStrain5 *microstrain5;

    // simulated MicroStrain Series 7 system
    SITL::MicroStrain7 *microstrain7;

    // simulated InertialLabs INS-U
    SITL::InertialLabs *inertiallabs;

#if AP_SIM_JSON_MASTER_ENABLED
    // Ride along instances via JSON SITL backend
    SITL::JSON_Master ride_along;
#endif  // AP_SIM_JSON_MASTER_ENABLED

#if AP_SIM_AIS_ENABLED
    // simulated AIS stream
    SITL::AIS *ais;
#endif

    // simulated EFI MegaSquirt device:
    SITL::EFI_MegaSquirt *efi_ms;

    // simulated EFI Hirth device:
    SITL::EFI_Hirth *efi_hirth;

#if CONFIG_HAL_BOARD == HAL_BOARD_SITL
    // output socket for flightgear viewing
    SocketAPM_native fg_socket{true};
#endif

    const char *defaults_path = HAL_PARAM_DEFAULTS_PATH;

    const char *_home_str;

    uint32_t wind_start_delay_micros;

#if AP_SIM_GPS_ENABLED
    // simulated GPS devices
    SITL::GPS *gps[2];  // constrained by # of parameter sets
#endif
};

#endif // AP_SIM_ENABLED
