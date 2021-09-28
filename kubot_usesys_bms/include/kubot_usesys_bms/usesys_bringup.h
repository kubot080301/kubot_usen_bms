#ifndef KUBOT_USESYS_BRINGUP_H_
#define KUBPT_USESYS_BRINGUP_H_

#include <ros/ros.h>
#include <serial/serial.h>
#include <RawJ1939.h>

#pragma once

using namespace std;

class USESYS_bringup
{
   // 建立IPC透過USB UART與BMS通訊
private:
   serial::Serial USESYS_Serial;
   USESYS_bringup::RawJ1939_msg BMS_DATA;
   int Address;

   bool need_update_bms_data;
   double last_bms_data_time;

public:
   USESYS_bringup(std::string comport) {
      this->init_usesys(comport);
      this->Address = 0;
   }

   void init_usesys(std::string comport);
   void usesys_callback(unsigned char request);
   void read_usesys(std::vector<unsigned char>* return_buffer, int byte_size);
   void update_usesys(std::vector<unsigned char>* Response);

   // 建立ROS topic
private:

   ros::NodeHandle nh;
   ros::Publisher raw_bms_data_pub;


};


void Error_Handler(string error_result) {
   ROS_ERROR_STREAM(error_result);
}



#endif /* KUBOT_USESYS_BRINGUP_H_ */