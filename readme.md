To build the project executables:

1. Create a build directory ("mkdir build")
2. navigate to build ("cd build")
3. run command "cmake .." (make sure paths in cmakelist.txt are consistent with local library path before doing this step)
4. compile by running "make"
5. run selected executable:
    - compute node: ./compute_node <port> <load_probability>
    - coordinator: ./coordinator <port> <scheduling_policy>
    - client: ./client <coordinator_ip> <coordinator_port> <dir_path> <rounds> <epochs>

* Be sure to set up compute nodes and coordinator before starting a job with client
