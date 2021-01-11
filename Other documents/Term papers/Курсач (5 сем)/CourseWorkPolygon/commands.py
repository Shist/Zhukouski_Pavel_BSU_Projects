import math
import multiprocessing
from concurrent.futures import ThreadPoolExecutor
from pulseapi import RobotPulse, position, pose

robot = RobotPulse("http://192.168.1.52:8081")
pool = ThreadPoolExecutor(2)
def circle():
    def wrap():
        while True:
            pose_target = pose([0, -90, 90, -90, -90, 0])
            position_targets = [
                position([-0.37, -0.12, 0.35], [math.pi, 0, 0]),
                position([-0.42, -0.12, 0.35], [math.pi, 0, 0]),
                position([-0.42, -0.17, 0.35], [math.pi, 0, 0]),
                position([-0.37, -0.17, 0.35], [math.pi, 0, 0]),
            ]

            robot.set_pose(pose_target, 90)
            robot.run_positions(position_targets, 90)
            robot.await_stop(1)
    pool.submit(wrap)

def stop():
    pool.submit(robot.stop)

def activate():
    pool.submit(robot.recover)

def home():
    def wrap():
        robot.set_pose(pose([0, -90, 0, -90, -90, 0]), 100)
        robot.await_stop()
    pool.submit(wrap)

ref = {
    "stop": stop,
    "activate": activate,
    "circle": circle,
    "home": home,
}
