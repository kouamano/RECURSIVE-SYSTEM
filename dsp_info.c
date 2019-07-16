/*
 * dsp_info.c
 * Example program to display sound device capabilities.
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/soundcard.h>

/* some functions require a more recent version of the sound driver */
#if SOUND_VERSION >= 301

/* utility function for displaying boolean status */
static char *yes_no(int condition)
{
  if (condition) return "yes"; else return "no";
}

/* utility function for displaying format */
static void print_format(int formatBits, int format, int deffmt, char *name)
{
  if (formatBits & format) {   /* is this format supported? */
    printf("  %s", name);
    if (deffmt == format)      /* is it the default format? */
      printf(" (default)\n");
    else 
      printf("\n");
  }
}
#endif /* SOUND_VERSION > 301 */

/*
 * Set sound device parameters to given values. Return -1 if
 * values not valid. Sampling rate is returned.
 */
static int set_dsp_params(int fd, int channels, int bits, int *rate) {
  int status, val = channels;

  status = ioctl(fd, SOUND_PCM_WRITE_CHANNELS, &val);
  if (status == -1)
    perror("SOUND_PCM_WRITE_CHANNELS ioctl failed");
  if (val != channels) /* not valid, so return */
    return -1;
  val = bits;
  status = ioctl(fd, SOUND_PCM_WRITE_BITS, &val);
  if (status == -1)
    perror("SOUND_PCM_WRITE_BITS ioctl failed");
  if (val != bits)
    return -1;
  status = ioctl(fd, SOUND_PCM_WRITE_RATE, rate);
  if (status == -1)
    perror("SOUND_PCM_WRITE_RATE ioctl failed");
  return 0;
}

int main(int argc, char *argv[])
{
  int rate;
  int channels;            /* number of channels */
  int bits;                /* sample size */
  int blocksize;           /* block size */
  int min_rate, max_rate;  /* min and max sampling rates */
  char *device;            /* name of device to report on */
  int fd;                  /* file descriptor for device */
  int status;              /* return value from ioctl */
#if SOUND_VERSION >= 301
  int formats;             /* data formats */
  int caps;                /* capabilities */
  int deffmt;              /* default format */
#endif

  /* get device name from command line or use default */  
  if (argc == 2)
    device = argv[1];
  else
    device = "/dev/dsp";

  /* try to open device */
  fd = open(device, O_RDWR);
  if (fd == -1) {
    fprintf(stderr, "%s: unable to open `%s', ", argv[0], device);
    perror("");
    return 1;
  }
  
  status = ioctl(fd, SOUND_PCM_READ_RATE, &rate);
  if (status ==  -1)
    perror("SOUND_PCM_READ_RATE ioctl failed");
  status = ioctl(fd, SOUND_PCM_READ_CHANNELS, &channels);
  if (status ==  -1)
    perror("SOUND_PCM_READ_CHANNELS ioctl failed");
  status = ioctl(fd, SOUND_PCM_READ_BITS, &bits);
  if (status ==  -1)
    perror("SOUND_PCM_READ_BITS ioctl failed");
  status = ioctl(fd, SNDCTL_DSP_GETBLKSIZE, &blocksize);
  if (status ==  -1)
    perror("SNFCTL_DSP_GETBLKSIZE ioctl failed");
  
  printf(
	 "Information on %s:\n\n"
	 "Defaults:\n"
	 "  sampling rate: %d Hz\n"
	 "  channels: %d\n"
	 "  sample size: %d bits\n"
	 "  block size: %d bytes\n",
	 device, rate, channels, bits, blocksize
	 );

#if SOUND_VERSION >= 301
  printf("\nSupported Formats:\n");
  deffmt = AFMT_QUERY;
  status = ioctl(fd, SOUND_PCM_SETFMT, &deffmt);
  if (status ==  -1)
    perror("SOUND_PCM_SETFMT ioctl failed");
  status = ioctl(fd, SOUND_PCM_GETFMTS, &formats);
  if (status ==  -1)
    perror("SOUND_PCM_GETFMTS ioctl failed");
  print_format(formats, AFMT_MU_LAW, deffmt, "mu-law");
  print_format(formats, AFMT_A_LAW, deffmt, "A-law");
  print_format(formats, AFMT_IMA_ADPCM, deffmt, "IMA ADPCM");
  print_format(formats, AFMT_U8, deffmt, "unsigned 8-bit");
  print_format(formats, AFMT_S8, deffmt, "signed 8-bit");
  print_format(formats, AFMT_S16_LE, deffmt, "signed 16-bit little-endian");
  print_format(formats, AFMT_S16_BE, deffmt, "signed 16-bit big-endian");
  print_format(formats, AFMT_U16_LE, deffmt, "unsigned 16-bit little-endian");
  print_format(formats, AFMT_U16_BE, deffmt, "unsigned 16-bit big-endian");
  print_format(formats, AFMT_MPEG, deffmt, "MPEG-2");
  
  printf("\nCapabilities:\n");
  status = ioctl(fd, SNDCTL_DSP_GETCAPS, &caps);
  if (status ==  -1)
    perror("SNDCTL_DSP_GETCAPS ioctl failed");
  printf(
	 "  revision: %d\n"
	 "  full duplex: %s\n"
	 "  real-time: %s\n"
	 "  batch: %s\n"
	 "  coprocessor: %s\n" 
	 "  trigger: %s\n"
	 "  mmap: %s\n",
	 caps & DSP_CAP_REVISION,
	 yes_no(caps & DSP_CAP_DUPLEX),
	 yes_no(caps & DSP_CAP_REALTIME),
	 yes_no(caps & DSP_CAP_BATCH),
	 yes_no(caps & DSP_CAP_COPROC),
	 yes_no(caps & DSP_CAP_TRIGGER),
	 yes_no(caps & DSP_CAP_MMAP));

#endif /* SOUND_VERSION >= 301 */
  
  /* display table heading */
  printf(
	 "\nModes and Limits:\n"
	 "Device    Sample    Minimum   Maximum\n"
	 "Channels  Size      Rate      Rate\n"
	 "--------  --------  --------  --------\n"
	 );
  
  /* do mono and stereo */  
  for (channels = 1; channels <= 2 ; channels++) {
    /* do 8 and 16 bits */
    for (bits = 8; bits <= 16 ; bits += 8) {
      /* To find the minimum and maximum sampling rates we rely on
	 the fact that the kernel sound driver will round them to
	 the closest legal value. */
      min_rate = 1;
      if (set_dsp_params(fd, channels, bits, &min_rate) == -1)
	continue;
      max_rate = 100000;
      if (set_dsp_params(fd, channels, bits, &max_rate) == -1)
	continue;
      /* display the results */
      printf("%8d  %8d  %8d  %8d\n", channels, bits, min_rate, max_rate);
    }
  }
  close(fd);
  return 0;
}
