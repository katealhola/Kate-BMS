#ifdef JBD_BMS
#pragma once
#include <Arduino.h>

#define ANT_BUF_LEN 160

namespace jbd_bms {

    #define  LOG_TEXT_SENSOR

class JbdBms  {
 public:
  void loop() ;
  void dump_config() ;
  void update() ;
  void setup() ;
  float get_setup_priority() const ;

  unsigned char buffer[BUF_LEN];

 protected:

  

  struct Cell {
    float cell_voltage_sensor_;
  } cells_[32];

  struct Temperature {
    float temperature_sensor_;
  } temperatures_[6];

  uint8_t cells ;
  float min_cell_voltage;
  float max_cell_voltage;
  float average_cell_voltage ;
  float total_voltage;
  float current;
  float power;
  uint8_t min_voltage_cell;
  uint8_t max_voltage_cell;

  uint8_t operation_status;
  uint8_t mosfet_status;
  uint8_t charging_binary;
  uint8_t charging_switch;
  uint8_t discharging_binary;
  uint8_t discharging_switch;
  // @TODO:
  //
  // Cycle life
  // Production date
  // Balance status bitmask (32 Bits)
  // Protection status bitmask (16 Bits)
  // Version

  std::string device_model_{""};
  std::vector<uint8_t> rx_buffer_;
  uint32_t last_byte_{0};
  uint16_t rx_timeout_{150};
  uint8_t no_response_count_{0};
  uint8_t mosfet_status_{255};
  bool enable_fake_traffic_;

  void on_jbd_bms_data_(const uint8_t &function, const std::vector<uint8_t> &data);
  void on_cell_info_data_(const std::vector<uint8_t> &data);
  void on_hardware_info_data_(const std::vector<uint8_t> &data);
  void on_hardware_version_data_(const std::vector<uint8_t> &data);
  bool parse_jbd_bms_byte_(uint8_t byte);
  void publish_state_(binary_sensor::BinarySensor *binary_sensor, const bool &state);
  void publish_state_(sensor::Sensor *sensor, float value);
  void publish_state_(switch_::Switch *obj, const bool &state);
  void publish_state_(text_sensor::TextSensor *text_sensor, const std::string &state);
  void publish_device_unavailable_();
  void reset_online_status_tracker_();
  void track_online_status_();
  void send_command_(uint8_t action, uint8_t function);
  std::string error_bits_to_string_(uint16_t bitmask);

  uint16_t chksum_(const uint8_t data[], const uint16_t len) {
    uint16_t checksum = 0x00;
    for (uint16_t i = 0; i < len; i++) {
      checksum = checksum - data[i];
    }
    return checksum;
  }
};

}  // namespace jbd_bms
#endif