#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define MPU6050_ID	0x68
#define MPU6050_ACC_X_H 0x3B
#define MPU6050_ACC_X_L 0x3C
#define MPU6050_ACC_Y_H 0x3D
#define MPU6050_ACC_Y_L 0x3E
#define MPU6050_ACC_Z_H 0x3F
#define MPU6050_ACC_Z_L 0x40
#define MPU6050_TMP_H 0x41
#define MPU6050_TMP_L 0x42
#define MPU6050_GYRO_X_H 0x43
#define MPU6050_GYRO_X_L 0x44
#define MPU6050_GYRO_Y_H 0x45
#define MPU6050_GYRO_Y_L 0x46
#define MPU6050_GYRO_Z_H 0x47
#define MPU6050_GYRO_Z_L 0x48
#define MPU_PWR_MGMT 0x6B

int main(void)
{
  int fd;
  int acc_x,acc_y,acc_z, gyro_x,gyro_y,gyro_z,tmp;
  printf("MPU6050 test\n");

  wiringPiSetup();  
  if((fd=wiringPiI2CSetup(MPU6050_ID))<0)
  {
    printf("can't find i2c!!\n");        
    return fd;
  }
  wiringPiI2CWriteReg8(fd,MPU_PWR_MGMT ,0);
  while(1){
    acc_x = wiringPiI2CReadReg8(fd,MPU6050_ACC_X_H)<<8; 
    acc_x |= wiringPiI2CReadReg8(fd,MPU6050_ACC_X_L);
    acc_y = wiringPiI2CReadReg8(fd,MPU6050_ACC_Y_H)<<8;
    acc_y |= wiringPiI2CReadReg8(fd,MPU6050_ACC_Y_L);
    acc_z = wiringPiI2CReadReg8(fd,MPU6050_ACC_Z_H)<<8;
    acc_z |= wiringPiI2CReadReg8(fd,MPU6050_ACC_Z_L);
    printf("acc_x=%d  acc_y=%d  acc_z=%d\n",acc_x,acc_y,acc_z);
    tmp = wiringPiI2CReadReg8(fd,MPU6050_TMP_H)<<8;
    tmp |= wiringPiI2CReadReg8(fd,MPU6050_TMP_L);
    printf("tmp=%d\n",tmp);
    gyro_x = wiringPiI2CReadReg8(fd,MPU6050_GYRO_X_H)<<8;
    gyro_x |= wiringPiI2CReadReg8(fd,MPU6050_GYRO_X_L);
    gyro_y = wiringPiI2CReadReg8(fd,MPU6050_GYRO_Y_H)<<8;
    gyro_y |= wiringPiI2CReadReg8(fd,MPU6050_GYRO_Y_L);
    gyro_z = wiringPiI2CReadReg8(fd,MPU6050_GYRO_Z_H)<<8;
    gyro_z |=  wiringPiI2CReadReg8(fd,MPU6050_GYRO_Z_L);
    printf("gyro_x=%d  gyro_y=%d  gyro_z=%d\n",gyro_x,gyro_y,gyro_z);
    delay(100);
    }        
  return 0;
}
