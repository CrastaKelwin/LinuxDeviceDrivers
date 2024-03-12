//#define	__KERNEL__
//#define	  MODULE  

#include <linux/module.h>	// for init_module() 
#include <linux/fs.h>		// for register_chrdev()
#include <linux/sched.h>	// for interruptible_sleep_on() 
#include <linux/uaccess.h>	// for get_user(), put_user()
#include <linux/sched/signal.h>

#define RINGSIZE 3

static char modname[] = "stash";
static int my_major = 40;

// driver's data-structures
static volatile int head, tail;
static unsigned char ring[ RINGSIZE ];
DECLARE_WAIT_QUEUE_HEAD( rdq );
DECLARE_WAIT_QUEUE_HEAD( wrq );

// function prototypes
static ssize_t
my_write( struct file *file, const char *buf, size_t len, loff_t *pos ),
my_read( struct file *file, char *buf, size_t len, loff_t *pos );


static struct file_operations 
my_fops =	{
		owner:		THIS_MODULE,
		write:		my_write,
		read:		my_read,
		};


void cleanup_module( void )
{
	printk( "<1>Removing \'%s\' module\n", modname );
	unregister_chrdev( my_major, modname );
}


int init_module( void )
{
	printk( "<1>\nInstalling \'%s\' module ", modname );
	printk( "(major=%d) \n", my_major );
	return	register_chrdev( my_major, modname, &my_fops );
}


static ssize_t
my_write( struct file *file, const char *buf, size_t count, loff_t *pos )
{
	int	next = ( 1 + tail ) % RINGSIZE;

	// sleep if necessary until the ringbuffer has room for new data 
	while ( next == head )	// the ringbuffer is aready full 
		{
		wait_event_interruptible( wrq, 1 );
		if ( signal_pending( current ) ) return -ERESTARTSYS;
		}

	// insert a new byte of data into our ringbuffer
	
	if ( get_user( ring[ tail ], buf ) ) return -EFAULT; 
	//sleep_on_timeout(&wrq,5000);
	tail = next;

	// and awaken any sleeping readers 
	wake_up_interruptible( &rdq );
	return	1;
}


static ssize_t
my_read( struct file *file, char *buf, size_t count, loff_t *pos )
{
	int	next = ( 1 + head ) % RINGSIZE;

	// sleep if necessary until the ringbuffer has some data in it
	while ( head == tail ) 	// the ringbuffer is presently empty
		{
		  wait_event_interruptible( rdq, 1 );
		if ( signal_pending( current ) ) return -ERESTARTSYS;
		}

	// remove a byte of data from our ringbuffer
	if ( put_user( ring[ head ], buf ) ) return -EFAULT;
	head = next;

	// and awaken any sleeping writers
	wake_up_interruptible( &wrq );
	return	1;
}

MODULE_LICENSE("GPL");
