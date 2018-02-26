Multi-Version Timestamp Interval Locking (MVTIL)
================================================

MVTIL is a distributed concurrency control protocol based on multiversion timestamp locking (MVTL). Here, we implement and compare it with alternative protocols, such as 2PL and MVTO+.

Compilation
-----------
The required libraries are 

  * Boost
  * Apache Thrift
  * Intel TBB (https://github.com/01org/tbb)

You can install the dependencies of MVTIL by running script `make_dependencies.sh`


Build & Test
------------
To build the system

	make -j

To test the system


Configuration
-------------
The system configuration can be changed in `common/config.h` file. Here we list the meaning of some important parameters.


	S_THREAD_CNT		:	Number of threads running simultaneously in this server
	PORT			:	Server port
	DEFAULT_TIMEOUT		:	Timeout for one operation
	MIN_NUM_RETRIES		:	Minimum retry number of one read operation
	C_THREAD_CNT		:	Number of concurrent transactions in this client
	MAX_RESTART		:	Maximum restart number of one transaction
	KEY_SPACE		:	Size of key space size
	TEST_TYPE		:	Type of the tested transaction. Five types of transactions are supported (Read-Only, Read-Intensive, Write-Intensive, Short, Mix)
	CLIENT_ID		:	Client Id
	TEST_DURATION_MS	:	Test Duration

For each protocol, there are some separate configurations.

MVTIL: 

	MVTL_POLICY		:	MVTIL-early (LOCK_FIRST_INTERVAL) and MVTIL-late (LOCK_LAST_INTERVAL) are supported.
	INTERVAL_DURATION	:	Initial interval length




EC2 Deployment
--------------
Step 1. Launch EC2 instances and install SSM Agent(**https://docs.aws.amazon.com/systems-manager/latest/userguide/sysman-install-startup-linux.html**)

Step 2. Use EC2 run command(**https://docs.aws.amazon.com/systems-manager/latest/userguide/rc-console.html**) to download system code and run `ec2_deploy.sh` on each instance. 

Step 3. Run evaluation scripts.






