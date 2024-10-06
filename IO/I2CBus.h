#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <iostream>

int file;
int adapter_nr = 1; /* probably dynamically determined */
char filename[20];

int i2csetup()
{
	snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);
	file = open(filename, O_RDWR);

	if (file < 0)
	{
		/* ERROR HANDLING; you can check errno to see what went wrong */
		//std::cout << "file error" << std::endl;
		_exit(1);
	}

	int addr = 0x08; /* The I2C address */

	if (ioctl(file, I2C_SLAVE, addr) < 0)
	{
		/* ERROR HANDLING; you can check errno to see what went wrong */
		//std::cout << "i2c ioctl error" << std::endl;
		_exit(1);
	}

	return 0;
}

void send_midi_i2c(uint mtype, uint channel, uint note, uint velo)
{
	if (i2csetup() != 0)
	{
		return;
	}
	//__u8 reg = 0x08; /* Device register to access */
	//__s32 res;
	char buf[4];

	buf[0] = mtype;
	buf[1] = channel;
	buf[2] = note;
	buf[3] = velo;

	std::cout << "Sending data " << std::to_string(buf[0]) << "," << std::to_string(buf[1]) << "," << std::to_string(buf[2]) << "," << std::to_string(buf[3]) << std::endl;

	if (write(file, buf, 4) != 4)
	{
		/* ERROR HANDLING: i2c transaction failed */
		//std::cout << "Error writing to i2c" << std::endl;
	}
}
