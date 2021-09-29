#include "usesys_bringup.h"


int main(int argc, char** argv)
{
   ros::init(argc, argv, "usesys_bms_node");
   ros::Rate loop_rate(100);
   pn.param<std::string>("port", port, "/dev/ttyUSB0");
   pn.param<int32_t>("baudrate", baudrate, 38400);
   ROS_INFO("[KUBOT]port:%s baudrate:%d", port.c_str(), baudrate);

   USESYS_bringup::init_usesys(port);

   while (ros::ok())
   {
      

      ros::spinOnce();
      loop_rate.sleep();
   }

   return 0;
}

void USESYS_bringup::init_usesys(std::string comport)
{
   try
   {
      USESYS_Serial.setPort(port);
      USESYS_Serial.setBaudrate(baudrate);
      USESYS_Serial.setParity(serial::parity_even);
      serial::Timeout Lto = serial::Timeout::simpleTimeout(0);
      USESYS_Serial.setTimeout(Lto);
      USESYS_Serial.open();

   }
   catch (serial::IOException& e)
   {
      Error_Handler("Unable to open USESYS BMS!");
   }
}

void USESYS_bringup::request_usesys(unsigned char req)
{
   req += this->Address;

   vector<unsigned char> req_vector;
   req_vector.clear();
   req_vector.push_back(req);
   USESYS_Serial.write(req_vector);
   /*
   req_vector.clear();
   req_vector.push_back(255 - req);
   USESYS_Serial.write(req_vector);
   */
}

void USESYS_bringup::read_usesys(std::vector<unsigned char>* return_buffer, int byte_size)
{
   // 清除緩衝區
   return_buffer->clear();

   need_update_bms_data = false;

   while (return_buffer->size() < byte_size)
   {
      if (this->USESYS_Serial.available() > 0)
      {
         unsigned char Receive_buffer = 0xFF;
         this->USESYS_Serial.read(&Receive_buffer, 1);
         return_buffer->push_back(Receive_buffer);
      }
   }



}