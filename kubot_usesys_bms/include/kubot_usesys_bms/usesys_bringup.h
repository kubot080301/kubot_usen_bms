#ifndef KUBOT_USESYS_BRINGUP_H_
#define KUBPT_USESYS_BRINGUP_H_

#include <ros/ros.h>
#include <serial/serial.h>
#include <RawJ1939.h>

#include <cmath>
#include <cstdint>

#pragma once

using namespace std;

class USESYS_bringup
{
   // 建立IPC透過USB UART與BMS通訊
private:
   serial::Serial USESYS_Serial;
   USESYS_bringup::RawJ1939_msg BMS_DATA;
   int Address;

   std::string port;
   int32_t baudrate;
   bool need_update_bms_data;
   double last_bms_data_time;

public:
   USESYS_bringup(std::string port) {
      this->init_usesys(port);
      this->Address = 0;
   }

   void init_usesys(std::string port); // 初始化通訊
   void request_usesys(unsigned char req); // 訪問訊息
   void read_usesys(std::vector<unsigned char>* return_buffer, int byte_size); // 解析回傳訊息
   void update_usesys(std::vector<unsigned char>* Response); // 更新至rostopic msgs

   // 建立ROS topic
private:

   ros::NodeHandle nh;
   ros::Publisher raw_bms_data_pub;


};

void Error_Handler(string error_result) {
   ROS_ERROR_STREAM(error_result);
}



#endif /* KUBOT_USESYS_BRINGUP_H_ */