# hexcopter_autonomy
Code base for Autonomous behaviors of the Hexcopters. 

Currently, this package supports the following behaviors - 1. Follow the leader behavior between two hexcopters.

Fly in simple patterns - square, triangle, etc.
Basic velocity control of the hexcopters.
To run any of these behaviors - 1. Clone the repository git clone https://github.com/tanmayshankar/hexcopter_autonomy

Build the package. cd hexcopter_autonomy then make clean && make .
Once the required set up is ready, run the behavior. rosrun hexcopter_autonomy follow_auto
