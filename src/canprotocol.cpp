
#include <arduino.h>
#include "canproc.h"
//#include "controller.h"

#include <ESP32CAN.h>
#include <CAN_config.h>

CAN_device_t CAN_cfg; // CAN Config

//BldcMotorCanData_ BldcMotorCanData;
//extern controller motorController;


void canInit()
{
  CAN_cfg.speed = CAN_SPEED_250KBPS;
  CAN_cfg.tx_pin_id = (gpio_num_t)CAN_TX;
  CAN_cfg.rx_pin_id = (gpio_num_t)CAN_RX;
  CAN_cfg.rx_queue = xQueueCreate(rx_queue_size, sizeof(CAN_frame_t));
  // Init CAN Module
  ESP32Can.CANInit();
};

void canproc(void *parameter)
{
  // put your main code here, to run repeatedly:
  CAN_frame_t rx_frame;

  while(true)
    {
      unsigned long currentMillis = millis();

      // Receive next CAN frame from queue
      if (xQueueReceive(CAN_cfg.rx_queue, &rx_frame, 3 * portTICK_PERIOD_MS) == pdTRUE)
      {
        if (rx_frame.FIR.B.FF == CAN_frame_std) { printf("Sframe");}
        else
        {
          printf("Eframe");
        }

        if (rx_frame.FIR.B.RTR == CAN_RTR)
        {
          printf(" RTR from 0x%08X, DLC %d\r\n", rx_frame.MsgID, rx_frame.FIR.B.DLC);
        }
        else
        {
          printf(" 0x%08X, DLC %d, Data ", rx_frame.MsgID, rx_frame.FIR.B.DLC);
          for (int i = 0; i < rx_frame.FIR.B.DLC; i++)
          {
            printf("0x%02X ", rx_frame.data.u8[i]);
          }
          /*
          if (rx_frame.MsgID == 0x0CF11E05)
          {
            BldcMotorCanData.rpm = rx_frame.data.u8[0] + (rx_frame.data.u8[1] << 8);
            BldcMotorCanData.A = rx_frame.data.u8[2] + (rx_frame.data.u8[3] << 8);
            BldcMotorCanData.V = rx_frame.data.u8[4] + (rx_frame.data.u8[5] << 8);
            BldcMotorCanData.errorCode= rx_frame.data.u8[6]+ + (rx_frame.data.u8[7] << 8);
            printf("rpm:%d %dA %dV", BldcMotorCanData.rpm, BldcMotorCanData.A, BldcMotorCanData.V);
          }
          if (rx_frame.MsgID == 0x0CF11F05)
          {
            BldcMotorCanData.throttle = rx_frame.data.u8[0];
            BldcMotorCanData.ctrlTemp = rx_frame.data.u8[1];
            BldcMotorCanData.motorTemp = rx_frame.data.u8[2];
            
            printf("throttle:%d ctrl:%dC mot:%dC", BldcMotorCanData.throttle, BldcMotorCanData.ctrlTemp, BldcMotorCanData.motorTemp );
          }
          printf("\n");
          */
        }
      }
    }
}

void sendCanStaus()
{
    CAN_frame_t tx_frame;
    tx_frame.FIR.B.FF = CAN_frame_std;
    tx_frame.MsgID = 0x666;
    tx_frame.FIR.B.DLC = 8;
    tx_frame.data.u8[0] = 0; //motorController.mode;
    tx_frame.data.u8[1] = 0; //motorController.throt;
    tx_frame.data.u8[2] = 0; //motorController.rpmSetP;
    tx_frame.data.u8[3] = 0x03;
    tx_frame.data.u8[4] = 0x04;
    tx_frame.data.u8[5] = 0x05;
    tx_frame.data.u8[6] = 0x06;
    tx_frame.data.u8[7] = 0x07;
    ESP32Can.CANWriteFrame(&tx_frame);
  }