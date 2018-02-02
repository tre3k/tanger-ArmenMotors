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
//  TestPing      |  test_ping
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
	
	close(comPort);
	device_state = Tango::CLOSE;
	
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


	if(comPort==0 && number_of_motor==0){
		comPort = initComPort();
		cout << "Com port has been init!\n";
	}

	device_state = Tango::INIT;

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
	Tango::DevBoolean argout;
	DEBUG_STREAM << "ArmenMotors::PowerOn()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(ArmenMotors::power_on) ENABLED START -----*/
	
	char *buff=new char[8];

	if(argin){
		sprintf(buff,"081Z0000"); //enable on
		writeread(comPort,buff,8);
		device_state = Tango::ON;
		argout = true;
	}else{
		sprintf(buff,"081Z1000"); //disable (enable off)
		writeread(comPort,buff,8);
		device_state = Tango::OFF;
	}
	
	delete [] buff;

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
	
	char *buff = new char[9];
	sprintf(buff,"081A0123"); //test
	writeread(comPort,buff,8,2);
	cout << buff << "\n";

	sprintf(buff,"081M0000"); //set direction right
	writeread(comPort,buff,8);
	setFreq();
	sprintf(buff,"081T4000"); //enable freq
	writeread(comPort,buff,8);
	sprintf(buff,"081B0000"); //start
	writeread(comPort,buff,8);

	sprintf(buff,"081A0123"); //test
	writeread(comPort,buff,8,2);
	cout << buff << "\n";

	delete [] buff;

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

	char *buff = new char[9];
	sprintf(buff,"081A0123"); //test
	writeread(comPort,buff,8,2);
	cout << buff << "\n";

	sprintf(buff,"081M1000"); //set direction right
	writeread(comPort,buff,8);
	setFreq();
	sprintf(buff,"081T4000"); //enable freq
	writeread(comPort,buff,8);
	sprintf(buff,"081B0000"); //start
	writeread(comPort,buff,8);

	sprintf(buff,"081A0123"); //test
	writeread(comPort,buff,8,2);
	cout << buff << "\n";

	delete [] buff;
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

	/* Test command */
	char *buff = new char[9];
	sprintf(buff,"081A0123"); //test
	writeread(comPort,buff,8,2);
	cout << buff << "\n";

	/* command stop! */
	sprintf(buff,"081P0000"); //STOP!
	writeread(comPort,buff,8);

	device_state = Tango::ON;
	delete [] buff;
	
	/*----- PROTECTED REGION END -----*/	//	ArmenMotors::stop
}
//--------------------------------------------------------
/**
 *	Command TestPing related method
 *	Description: send command xxxA0012 and controller must be recived ``OK``
 *
 *	@returns 
 */
//--------------------------------------------------------
Tango::DevString ArmenMotors::test_ping()
{
	Tango::DevString argout;
	DEBUG_STREAM << "ArmenMotors::TestPing()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(ArmenMotors::test_ping) ENABLED START -----*/
	


	/*----- PROTECTED REGION END -----*/	//	ArmenMotors::test_ping
	return argout;
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

int ArmenMotors::initComPort(void){
	int port = open(rs232port.c_str(), O_RDWR| O_NOCTTY );
	struct termios tty;
	struct termios tty_old;
	memset (&tty, 0, sizeof(tty));

	/* Error Handling */
	if(tcgetattr(port, &tty )!= 0){
		cout << "Error get attribute port\n";
	}

	/* Save old tty parameters */
	tty_old = tty;

	/* Set Baud Rate */
	cfsetospeed (&tty, (speed_t) PORT_BAUDRATE);
	cfsetispeed (&tty, (speed_t) PORT_BAUDRATE);

	tty.c_cflag     &=  ~PARENB;            // Make 8n1
	tty.c_cflag     &=  ~CSTOPB;
	tty.c_cflag     &=  ~CSIZE;
	tty.c_cflag     |=  CS8;

	tty.c_cflag     &=  ~CRTSCTS;           // no flow control
	tty.c_cc[VMIN]   =  1;                  // read doesn't block
	tty.c_cc[VTIME]  =  5;                  // 0.5 seconds read timeout
	tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

	cfmakeraw(&tty);

	tcflush(port, TCIFLUSH);
	if (tcsetattr(port,TCSANOW,&tty)!=0) {
		cout << "Error set attribute\n";
	}

	return port;
}

int ArmenMotors::writeread(int dev,char *buff,int size_write,int size_read){
	int spot=0;

	for(int i=0;i<size_write;i++){
		if(write(dev,&buff[i],1)==0) break;
	}

	for(int i=0;i<size_write;i++) buff[i] = 0x00;

	for(int i=0;i<size_read;i++){
		spot += read(dev,&buff[i],1);
	}
	  return 0;
}

void ArmenMotors::setFreq(){
	char low,hight;
	low = (char)((speed_of_motor>>8) & 0xff);
	hight = (char)(speed_of_motor & 0xff);
	char *buff = new char [8];

	cout << "Set freq " << speed_of_motor << " Hz\n";
	sprintf(buff,"081L%c%c01",hight,low);
	cout << buff << "\n";
	writeread(comPort,buff,8);

	delete [] buff;
}

/*----- PROTECTED REGION END -----*/	//	ArmenMotors::namespace_ending
} //	namespace
