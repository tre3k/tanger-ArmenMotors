/*----- PROTECTED REGION ID(ArmenMotors.cpp) ENABLED START -----*/
//=============================================================================
//
// file :        ArmenMotors.cpp
//
// description : C++ source for the ArmenMotors class and its commands.
//               The class is derived from Device. It represents the
//               CORBA servant object which will be accessed from the
//               network. All commands which can be executed on the
//               ArmenMotors are implemented in this file.
//
// project :     
//
// This file is part of Tango device class.
// 
// Tango is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Tango is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Tango.  If not, see <http://www.gnu.org/licenses/>.
// 
//
//
//=============================================================================
//                This file is generated by POGO
//        (Program Obviously used to Generate tango Object)
//=============================================================================


#include <ArmenMotors.h>
#include <ArmenMotorsClass.h>

/*----- PROTECTED REGION END -----*/	//	ArmenMotors.cpp

/**
 *  ArmenMotors class description:
 *    
 */

//================================================================
//  The following table gives the correspondence
//  between command and method names.
//
//  Command name  |  Method name
//================================================================
//  State         |  Inherited (no method)
//  Status        |  Inherited (no method)
//  PowerOn       |  power_on
//  MotionLeft    |  motion_left
//  MotionRight   |  motion_right
//  Stop          |  stop
//================================================================

//================================================================
//  Attributes managed is:
//================================================================
//================================================================

namespace ArmenMotors_ns
{
/*----- PROTECTED REGION ID(ArmenMotors::namespace_starting) ENABLED START -----*/

//	static initializations

/*----- PROTECTED REGION END -----*/	//	ArmenMotors::namespace_starting

//--------------------------------------------------------
/**
 *	Method      : ArmenMotors::ArmenMotors()
 *	Description : Constructors for a Tango device
 *                implementing the classArmenMotors
 */
//--------------------------------------------------------
ArmenMotors::ArmenMotors(Tango::DeviceClass *cl, string &s)
 : TANGO_BASE_CLASS(cl, s.c_str())
{
	/*----- PROTECTED REGION ID(ArmenMotors::constructor_1) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	ArmenMotors::constructor_1
}
//--------------------------------------------------------
ArmenMotors::ArmenMotors(Tango::DeviceClass *cl, const char *s)
 : TANGO_BASE_CLASS(cl, s)
{
	/*----- PROTECTED REGION ID(ArmenMotors::constructor_2) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	ArmenMotors::constructor_2
}
//--------------------------------------------------------
ArmenMotors::ArmenMotors(Tango::DeviceClass *cl, const char *s, const char *d)
 : TANGO_BASE_CLASS(cl, s, d)
{
	/*----- PROTECTED REGION ID(ArmenMotors::constructor_3) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	ArmenMotors::constructor_3
}

//--------------------------------------------------------
/**
 *	Method      : ArmenMotors::delete_device()
 *	Description : will be called at device destruction or at init command
 */
//--------------------------------------------------------
void ArmenMotors::delete_device()
{
	DEBUG_STREAM << "ArmenMotors::delete_device() " << device_name << endl;
	/*----- PROTECTED REGION ID(ArmenMotors::delete_device) ENABLED START -----*/
	
	closeComPort();
	
	/*----- PROTECTED REGION END -----*/	//	ArmenMotors::delete_device
}

//--------------------------------------------------------
/**
 *	Method      : ArmenMotors::init_device()
 *	Description : will be called at device initialization.
 */
//--------------------------------------------------------
void ArmenMotors::init_device()
{
	DEBUG_STREAM << "ArmenMotors::init_device() create device " << device_name << endl;
	/*----- PROTECTED REGION ID(ArmenMotors::init_device_before) ENABLED START -----*/
	
	//	Initialization before get_device_property() call
	
	/*----- PROTECTED REGION END -----*/	//	ArmenMotors::init_device_before
	

	//	Get the device properties from database
	get_device_property();
	
	/*----- PROTECTED REGION ID(ArmenMotors::init_device) ENABLED START -----*/
	
	//	Initialize device

	cout << "Init: num of motor: " << number_of_motor << ", address: " << address <<
			", freq: " << speed_of_motor << "Hz\n";


	if(comPort==0) if(!openComPort()) cout << "Error open port " << rs232port << "!\n";
	if(comPort<1){
		device_status = "Error open port: " + rs232port + "\n";
		device_state = Tango::FAULT;
		return;
	}
	device_state = Tango::OPEN;

	devName = new char [3];
	strcpy(devName,"\x00\x00\x00");

	sendCommand(devName,(char *)"A0012");  //This test command, controller must be recived "OK"
	rcvBuff = new char [2];
	recvData(rcvBuff,2);
	cout << rcvBuff << "\n";

	/*----- PROTECTED REGION END -----*/	//	ArmenMotors::init_device
}

//--------------------------------------------------------
/**
 *	Method      : ArmenMotors::get_device_property()
 *	Description : Read database to initialize property data members.
 */
//--------------------------------------------------------
void ArmenMotors::get_device_property()
{
	/*----- PROTECTED REGION ID(ArmenMotors::get_device_property_before) ENABLED START -----*/
	
	//	Initialize property data members
	
	/*----- PROTECTED REGION END -----*/	//	ArmenMotors::get_device_property_before


	//	Read device properties from database.
	Tango::DbData	dev_prop;
	dev_prop.push_back(Tango::DbDatum("number_of_motor"));
	dev_prop.push_back(Tango::DbDatum("speed_of_motor"));
	dev_prop.push_back(Tango::DbDatum("address"));
	dev_prop.push_back(Tango::DbDatum("rs232port"));

	//	is there at least one property to be read ?
	if (dev_prop.size()>0)
	{
		//	Call database and extract values
		if (Tango::Util::instance()->_UseDb==true)
			get_db_device()->get_property(dev_prop);
	
		//	get instance on ArmenMotorsClass to get class property
		Tango::DbDatum	def_prop, cl_prop;
		ArmenMotorsClass	*ds_class =
			(static_cast<ArmenMotorsClass *>(get_device_class()));
		int	i = -1;

		//	Try to initialize number_of_motor from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  number_of_motor;
		else {
			//	Try to initialize number_of_motor from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  number_of_motor;
		}
		//	And try to extract number_of_motor value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  number_of_motor;

		//	Try to initialize speed_of_motor from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  speed_of_motor;
		else {
			//	Try to initialize speed_of_motor from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  speed_of_motor;
		}
		//	And try to extract speed_of_motor value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  speed_of_motor;

		//	Try to initialize address from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  address;
		else {
			//	Try to initialize address from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  address;
		}
		//	And try to extract address value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  address;

		//	Try to initialize rs232port from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  rs232port;
		else {
			//	Try to initialize rs232port from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  rs232port;
		}
		//	And try to extract rs232port value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  rs232port;

	}

	/*----- PROTECTED REGION ID(ArmenMotors::get_device_property_after) ENABLED START -----*/
	
	//	Check device property data members init
	
	/*----- PROTECTED REGION END -----*/	//	ArmenMotors::get_device_property_after
}

//--------------------------------------------------------
/**
 *	Method      : ArmenMotors::always_executed_hook()
 *	Description : method always executed before any command is executed
 */
//--------------------------------------------------------
void ArmenMotors::always_executed_hook()
{
	DEBUG_STREAM << "ArmenMotors::always_executed_hook()  " << device_name << endl;
	/*----- PROTECTED REGION ID(ArmenMotors::always_executed_hook) ENABLED START -----*/
	
	//	code always executed before all requests
	
	/*----- PROTECTED REGION END -----*/	//	ArmenMotors::always_executed_hook
}

//--------------------------------------------------------
/**
 *	Method      : ArmenMotors::read_attr_hardware()
 *	Description : Hardware acquisition for attributes
 */
//--------------------------------------------------------
void ArmenMotors::read_attr_hardware(TANGO_UNUSED(vector<long> &attr_list))
{
	DEBUG_STREAM << "ArmenMotors::read_attr_hardware(vector<long> &attr_list) entering... " << endl;
	/*----- PROTECTED REGION ID(ArmenMotors::read_attr_hardware) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	ArmenMotors::read_attr_hardware
}


//--------------------------------------------------------
/**
 *	Method      : ArmenMotors::add_dynamic_attributes()
 *	Description : Create the dynamic attributes if any
 *                for specified device.
 */
//--------------------------------------------------------
void ArmenMotors::add_dynamic_attributes()
{
	/*----- PROTECTED REGION ID(ArmenMotors::add_dynamic_attributes) ENABLED START -----*/
	
	//	Add your own code to create and add dynamic attributes if any
	
	/*----- PROTECTED REGION END -----*/	//	ArmenMotors::add_dynamic_attributes
}

//--------------------------------------------------------
/**
 *	Command PowerOn related method
 *	Description: This command power on/off motor
 *
 *	@param argin false
 *	@returns 
 */
//--------------------------------------------------------
Tango::DevBoolean ArmenMotors::power_on(Tango::DevBoolean argin)
{
	Tango::DevBoolean argout = false;
	DEBUG_STREAM << "ArmenMotors::PowerOn()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(ArmenMotors::power_on) ENABLED START -----*/
	
	if(argin){
		device_state = Tango::ON;
		argout = true;
	}else{
		device_state = Tango::OFF;
	}
	
	/*----- PROTECTED REGION END -----*/	//	ArmenMotors::power_on
	return argout;
}
//--------------------------------------------------------
/**
 *	Command MotionLeft related method
 *	Description: 
 *
 */
//--------------------------------------------------------
void ArmenMotors::motion_left()
{
	DEBUG_STREAM << "ArmenMotors::MotionLeft()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(ArmenMotors::motion_left) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	ArmenMotors::motion_left
}
//--------------------------------------------------------
/**
 *	Command MotionRight related method
 *	Description: 
 *
 */
//--------------------------------------------------------
void ArmenMotors::motion_right()
{
	DEBUG_STREAM << "ArmenMotors::MotionRight()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(ArmenMotors::motion_right) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	ArmenMotors::motion_right
}
//--------------------------------------------------------
/**
 *	Command Stop related method
 *	Description: 
 *
 */
//--------------------------------------------------------
void ArmenMotors::stop()
{
	DEBUG_STREAM << "ArmenMotors::Stop()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(ArmenMotors::stop) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	ArmenMotors::stop
}
//--------------------------------------------------------
/**
 *	Method      : ArmenMotors::add_dynamic_commands()
 *	Description : Create the dynamic commands if any
 *                for specified device.
 */
//--------------------------------------------------------
void ArmenMotors::add_dynamic_commands()
{
	/*----- PROTECTED REGION ID(ArmenMotors::add_dynamic_commands) ENABLED START -----*/
	
	//	Add your own code to create and add dynamic commands if any
	
	/*----- PROTECTED REGION END -----*/	//	ArmenMotors::add_dynamic_commands
}

/*----- PROTECTED REGION ID(ArmenMotors::namespace_ending) ENABLED START -----*/

bool ArmenMotors::openComPort(){

	comPort = open(rs232port.c_str(),O_RDWR | O_NOCTTY);
	if(comPort < 1) return false;
	struct termios port_cfg;
	tcgetattr(comPort,&port_cfg);
	cfmakeraw(&port_cfg);
	cfsetospeed(&port_cfg,PORT_BAUDRATE);
	cfsetispeed(&port_cfg,PORT_BAUDRATE);
	if(tcsetattr(comPort,TCSANOW,&port_cfg) < 0) return false;

	return true;
}

void ArmenMotors::closeComPort(){
	device_state = Tango::CLOSE;
	close(comPort);
	return;
}

void ArmenMotors::sendCommand(char *devicename, char *command){
	char buffer[8];
	for(int i=0;i<3;i++) buffer[i] = devicename[i];
	for(int i=0;i<5;i++) buffer[i+3] = command[i];
	write(comPort,buffer,8);
	return;
}

int ArmenMotors::recvData(char *buffer,int bytes){
	int rcvBytes = read(comPort,buffer,bytes);
	return rcvBytes;
}

/*----- PROTECTED REGION END -----*/	//	ArmenMotors::namespace_ending
} //	namespace
