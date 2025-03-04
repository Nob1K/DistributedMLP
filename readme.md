To build the project executables:

1. Create a build directory ("mkdir build")
2. navigate to build ("cd build")
3. run command "cmake .." (make sure paths in cmakelist.txt are consistent with local library path before doing this step)
4. compile by running "make"
5. run selected executable:
    - compute node: ./compute_node &lt;port&gt; <load_probability>
    - coordinator: ./coordinator &lt;port&gt; <scheduling_policy>
    - client: ./client <coordinator_ip> <coordinator_port> <dir_path> &lt;rounds&gt; &lt;epochs&gt;

* Be sure to set up compute nodes and coordinator before starting a job with client
* compute_client is used to test compute node functionalities and is not used in system
