**Required Software**

1.  Atollic TrueStudio 9.3.0 ([https://atollic.com/truestudio/](https://atollic.com/truestudio/))
    
2.  STM32CubeMX 5.1.0 ([https://www.st.com/en/development-tools/stm32cubemx.html](https://www.st.com/en/development-tools/stm32cubemx.html))

**Steps to run communication between ROS and MCU**
    
1.  Clone this repository and build firmware.
    
2.  Start docker
    
3.  Separate console window to 4 parts.
    
4.  Run ***roscore***
    
5.  Run ***rosrun rosserial_python serial_node.py /dev/ttyACM0 _baud:=115200*** if used STLink UART
    
6.  Run ***rosrun rosserial_python serial_node.py /dev/ttyUSB0 _baud:=115200*** if used external USB to UART converter (connected to pins PF6 and PF7 of MCU)
    
7.  Run ***rostopic echo chatter***
    
8.  Run ***rostopic pub led std_msgs/UInt16   0***    (0 - to disable LD3, 1 - to enable) LD3 (LD3 is red)
    
9.  If everything is made correct, you will see "*data: "hello world!*" " messages in the terminal and you will be able to controll LD3 from console
