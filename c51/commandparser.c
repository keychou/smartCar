#include "commandparser.h"
#include "moto.h"
#include "pwm.h"
#include "serial.h"
#include "rgbled.h"
#include "servo.h"

//#define UP 0x57     // W
//#define DOWN 0x53   // S
//#define LEFT 0x41   // A
//#define RIGHT 0x44  // D
//#define STOP 0x50   // P




void commandparser(unsigned char cmd)
{
   send_string_by_uart1("cmd = ");
   send_data_by_uart1(cmd);
   send_string_by_uart1("\r\n");

   switch (cmd)
   {
       case 'W':
	      send_string_by_uart1("car UP\r\n");
		  moto_side1(0, 2000);
          moto_side2(0, 2000);
	      break;
	   case 'S':
	      send_string_by_uart1("car DOWN\r\n");
		  moto_side1(1, 2000);
          moto_side2(1, 2000);
	      break;
	   case 'A':
	      send_string_by_uart1("car LEFT\r\n");
	      moto_side1(1, 2000);
		  moto_side2(0, 2000);
	      break;
       case 'D':
	      send_string_by_uart1("car RIGHT\r\n");
	      moto_side1(0, 2000);
		  moto_side2(1, 2000);
	      break;
	   case 'P':
	      send_string_by_uart1("car STOP\r\n");
	      moto_side1(0, 0);
          moto_side2(0, 0);
   		  break;

	   case 'U':
	      send_string_by_uart1("car acc\r\n");
          set_speed_up(0);
   		  break;

	   case 'N':
	      send_string_by_uart1("car dec\r\n");
	      set_speed_down(0);
   		  break;

	   case 'H':
	      send_string_by_uart1("servo h increase\r\n");
	      servo_h_increase();
   		  break;

	   case 'J':
	      send_string_by_uart1("servo h decrease\r\n");
	      servo_h_decrease();
   		  break;

	   case 'V':
	      send_string_by_uart1("servo v increase\r\n");
	      servo_v_increase();
   		  break;
	   
	   case 'B':
	      send_string_by_uart1("servo v decrease\r\n");
	      servo_v_decrease();
   		  break;

	   // led control
	   case '0':
	      send_string_by_uart1("turn on led off\r\n");
	      led_none();
   		  break;
	   case '1':
	      send_string_by_uart1("turn on led white\r\n");
	      led_white();
   		  break;
	   case '2':
	      send_string_by_uart1("turn on led red\r\n");
	      led_red();
   		  break;
	   case '3':
	      send_string_by_uart1("turn on led green\r\n");
	      led_green();
   		  break;
	   case '4':
	      send_string_by_uart1("turn on led blue\r\n");
	      led_blue();
   		  break;
	   case '5':
	      send_string_by_uart1("turn on led red green\r\n");
	      led_red_green();
   		  break;
	   case '6':
	      send_string_by_uart1("turn on led red blue\r\n");
	      led_red_blue();
   		  break;
	   case '7':
	      send_string_by_uart1("turn on led green blue\r\n");
	      led_green_blue();
   		  break;
	   case '8':
	      send_string_by_uart1("turn on led flowing water light\r\n");
	      flowing_water_light();
   		  break;
	   default:
	      send_string_by_uart1("cmd not found\r\n");
	      break;
   }
}



