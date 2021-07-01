import math
import multiprocessing
from concurrent.futures import ThreadPoolExecutor
from pulseapi import RobotPulse, position, pose

robot = RobotPulse("http://192.168.2.4:8081")
pool = ThreadPoolExecutor(2)

def activate():
    pool.submit(robot.recover)

def stop():
    pool.submit(robot.stop)

def home():
    def wrap():
        robot.set_pose(pose([0, -90, 0, -90, -90, 0]), 100)
        robot.await_stop()
    pool.submit(wrap)

def square():
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

def line():
    def wrap():
        while True:
            pose_target = pose([0, -90, 90, -90, -90, 0])
            position_targets = [
                position([-0.3, -0.1, 0.35], [math.pi, 0, 0]),
                position([-0.3, -0.3, 0.35], [math.pi, 0, 0]),
                position([-0.3, -0.5, 0.35], [math.pi, 0, 0]),
                position([-0.3, -0.7, 0.35], [math.pi, 0, 0]),
            ]

            robot.set_pose(pose_target, 90)
            robot.run_positions(position_targets, 90)
            robot.await_stop(1)
    pool.submit(wrap)

def rectangular():
    def wrap():
        while True:
            pose_target = pose([0, -90, 90, -90, -90, 0])
            position_targets = [
                position([-0.5, -0.1, 0.6], [math.pi, 0, 0]),
                position([-0.3, -0.3, 0.7], [math.pi, 0, 0]),
                position([-0.7, -0.2, 0.4], [math.pi, 0, 0]),
                position([-0.3, -0.4, 0.5], [math.pi, 0, 0]),
            ]

            robot.set_pose(pose_target, 90)
            robot.run_positions(position_targets, 90)
            robot.await_stop(1)
    pool.submit(wrap)

def dance():
    def wrap():
        while True:
            pose_target = pose([0, -90, 90, -90, -90, 0])
            position_targets = [
                position([-0.8, -0.3, 0.4], [math.pi, 0, 0]),
                position([-0.2, -0.6, 0.6], [math.pi, 0, 0]),
                position([-0.9, -0.1, 0.4], [math.pi, 0, 0]),
                position([-0.1, -0.5, 0.6], [math.pi, 0, 0]),
            ]

            robot.set_pose(pose_target, 90)
            robot.run_positions(position_targets, 90)
            robot.await_stop(1)
    pool.submit(wrap)

def move():
    def wrap():
        while True:
            pose_target = pose([0, -70, 60, -80, -80, 0])
            position_targets = [
                position([-0.8, -0.5, 0.8], [math.pi, 0, 0]),
                position([-0.7, -0.4, 0.7], [math.pi, 0, 0]),
                position([-0.6, -0.3, 0.6], [math.pi, 0, 0]),
                position([-0.5, -0.2, 0.5], [math.pi, 0, 0]),
            ]

            robot.set_pose(pose_target, 90)
            robot.run_positions(position_targets, 90)
            robot.await_stop(1)
    pool.submit(wrap)

def slow():
    def wrap():
        while True:
            pose_target = pose([0, -20, 30, -10, -20, 10])
            position_targets = [
                position([-0.5, -0.3, 0.5], [math.pi, 0, 0]),
                position([-0.5, -0.3, 0.5], [math.pi, 0, 0]),
                position([-0.4, -0.4, 0.6], [math.pi, 0, 0]),
                position([-0.4, -0.4, 0.6], [math.pi, 0, 0]),
            ]

            robot.set_pose(pose_target, 90)
            robot.run_positions(position_targets, 90)
            robot.await_stop(1)
    pool.submit(wrap)

def fast():
    def wrap():
        while True:
            pose_target = pose([0, -45, 45, -45, -45, 0])
            position_targets = [
                position([-0.9, -0.3, 0.4], [math.pi, 0, 0]),
                position([-0.2, -0.7, 0.7], [math.pi, 0, 0]),
                position([-0.3, -0.1, 0.4], [math.pi, 0, 0]),
                position([-0.7, -0.4, 0.9], [math.pi, 0, 0]),
            ]

            robot.set_pose(pose_target, 90)
            robot.run_positions(position_targets, 90)
            robot.await_stop(1)
    pool.submit(wrap)

ref = {
    "activate": activate,
    "stop": stop,
    "home": home,
    "square": square,
    "line": line,
    "rectangular": rectangular,
    "dance": dance,
    "move": move,
    "slow": slow,
    "fast": fast
}
