# Mobile Robot Car

## Description

The Mobile Robot Car is a versatile project designed to demonstrate various functionalities of a robotic system. It is built using common electronic components and can perform tasks such as wall following, obstacle avoidance, and free movement. The project entails programming a robot car equipped with ultrasonic sensors for obstacle detection, a servo motor for navigation, and Bluetooth communication for remote control. The robot is capable of various movements including forward, backward, left, and right turns, as well as entering obstacle avoidance or wall-following modes.  
I use the Bluetooth Electronics app for controlling the robot car.

## Modes of Operation

- Forward (F): Move the robot forward.  
- Backward (B): Move the robot backward.  
- Left (L): Turn the robot left.  
- Right (R): Turn the robot right.  
- Stop (S): Stop the robot (red).  
- Avoidance Mode (A): Implement obstacle avoidance mode (green).  
- Wall Following Mode (W): Follow a wall based on sensor feedback (blue).  
- Turn Robot ON (ON): Activate the robot.  
- Turn Robot OFF (OFF): Deactivate the robot.

![2fd481b9-887e-4f28-8530-e496e2ad3cac](https://github.com/palpatinedude/Delfi---Small-Robot/assets/117318107/59d41e22-7f2c-4cca-81d9-e8a77e3253e6)

## Components

- Arduino Microcontroller  
- 2 x Ultrasonic Sensors (HC-SR04)  
- Servo Motor  
- Bluetooth Module (HC-05)  
- Motor Driver (L293D)  
- 2 x DC Geared Motors  
- Castor Wheel  
- 2 x Wheels  
- Tupper Box (Chassis)  
- 4 x AA batteries  

## Hardware Architecture

![system](https://github.com/palpatinedude/Delfi---Small-Robot/assets/117318107/3f96b5bd-3b04-4764-ba1b-b04220e868c4)

## System Architecture

![wholesystemdiagram](https://github.com/palpatinedude/Delfi---Small-Robot/assets/117318107/b5ab3269-bc6a-4af0-ad63-ab4d2f3a762d)

---

## Wall Following Mode

In Wall Following Mode, the robot utilizes its ultrasonic sensors to navigate along a wall while maintaining a certain distance from it. This mode is useful when the robot needs to traverse along a wall or boundary, such as exploring a room or following a corridor. The main objective is to keep the robot parallel to the wall, ensuring a consistent distance is maintained throughout the journey.

### Operation

- Initialization: Ultrasonic sensors measure distances to the wall and obstacles in front.  
- Distance Measurement: Sensors continuously measure distance to the wall on the side.  
- Adjustment: The robot adjusts its movement to remain parallel to the wall based on sensor data.  
- Obstacle Detection: The robot detects obstacles in its path while following the wall.  
- Obstacle Avoidance: If an obstacle is detected, the robot temporarily deviates from the wall to navigate around it, then resumes wall following.

### Implementation

- Sensor Feedback: Uses ultrasonic sensor data to determine distance from the wall.  
- Motor Control: Adjusts motor speed and direction to maintain desired distance.  
- Servo Motor: May scan the environment periodically to detect obstacles and adjust orientation.

---

## Avoid Obstacles Mode

The Avoid Obstacles Mode enables the robot to autonomously detect and navigate around obstacles, ensuring safe operation in dynamic environments.

### Operation

- Obstacle Detection: Ultrasonic sensors detect obstacles nearby.  
- Collision Avoidance: The robot avoids collision by moving toward the direction with the maximum distance.  
- Maneuvering: May stop, reverse, turn, or move laterally to avoid obstacles.  
- Resuming Operation: After avoiding obstacles, continues intended movement.

### Implementation

- Distance Measurement: Ultrasonic sensors measure distance to obstacles in front.  
- Decision Making: Control algorithm selects actions based on maximum distance available.  
- Dynamic Navigation: Adjusts path in real-time for safe navigation.

---

## Photos

![404160182_219714681195749_3811149012263920410_n](https://github.com/palpatinedude/Delfi---Small-Robot/assets/117318107/2b3df04a-5a43-415b-8a9d-c0c6f8675aee)




