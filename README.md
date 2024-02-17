Description

The Mobile Robot Car is a versatile project designed to demonstrate various functionalities of a robotic system. It is built using common electronic components and can perform tasks such as wall following, obstacle avoidance, and free movement.

Modes of Operation:

    Forward (F): Move the robot forward.
    Backward (B): Move the robot backward.
    Left (L): Turn the robot left.
    Right (R): Turn the robot right.
    Stop (S): Stop the robot.
    Avoidance Mode (A): Implement obstacle avoidance mode.
    Wall Following Mode (W): Follow a wall based on sensor feedback.
    Turn Robot ON (X): Activate the robot.
    Turn Robot OFF (x): Deactivate the robot.
    
    ![platform](https://github.com/palpatinedude/Delfi---Small-Robot/assets/117318107/d6995aa2-a036-4a74-a390-ac7acd6c49b7)

Components:

    Arduino Microcontroller
    2 x Ultrasonic Sensors (HC-SR04)
    Servo Motor
    Bluetooth Module (HC-05)
    Motor Driver (L293D) 
    2 x DC Geared Motors
    Castor Wheel
    2 x Wheels
    Tupper Box (Chassis)

    

Wall Following Mode:

In the Wall Following Mode, the robot utilizes its ultrasonic sensors to navigate along a wall while maintaining a certain distance from it. This mode is particularly useful for scenarios where the robot needs to traverse along a wall or boundary, such as exploring a room or following a corridor. The main objective of wall following is to keep the robot parallel to the wall, ensuring a consistent distance is maintained throughout the journey.
Operation

    Initialization: The robot's ultrasonic sensors are used to measure distances to the wall and obstacles in front of it.
    Distance Measurement: The sensors continuously measure the distance between the robot and the wall on its side.
    Adjustment: Based on the measured distance, the robot adjusts its movement to ensure it remains parallel to the wall.
    Obstacle Detection: While following the wall, the robot also detects obstacles in its path using the sensors.
    Obstacle Avoidance: If an obstacle is detected, the robot may temporarily deviate from the wall to navigate around the obstruction before resuming wall following.

Implementation

    Sensor Feedback: The robot receives feedback from its ultrasonic sensors to determine its distance from the wall.
    Motor Control: Based on the feedback, the robot adjusts the speed and direction of its motors to maintain the desired distance from the wall.
    Servo Motor: The servo motor may be used to periodically scan the environment for obstacles and adjust the robot's orientation accordingly.

Avoid Obstacles Mode:

The Avoid Obstacles Mode enables the robot to autonomously detect and navigate around obstacles in its path. This mode is crucial for ensuring the robot can operate safely in dynamic environments where obstacles may appear unexpectedly.
Operation

    Obstacle Detection: The robot uses its ultrasonic sensors to detect obstacles within its vicinity.
    Collision Avoidance: Upon detecting an obstacle, the robot  avoid colliding with it and moves to the direction with the maximun distance.
    Maneuvering: The robot may execute maneuvers such as stopping, reversing, turning, or moving laterally to navigate around the obstacle.
    Resuming Operation: After successfully avoiding the obstacle, the robot continues its intended operation, whether it's moving towards a specific destination.

Implementation

    Distance Measurement: Ultrasonic sensors are used to measure the distance to obstacles in front of the robot.
    Decision Making: The robot's control algorithm determines the appropriate action to take based on the proximity and size of the detected obstacle.
    Dynamic Navigation: The robot dynamically adjusts its path to avoid obstacles in real-time, ensuring safe and efficient navigation.





