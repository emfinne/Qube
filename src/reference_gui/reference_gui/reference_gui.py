#!/usr/bin/env python3

import sys
import threading

import rclpy
from rclpy.node import Node
from std_msgs.msg import Float64

from python_qt_binding.QtCore import Qt
from python_qt_binding.QtWidgets import (
    QApplication,
    QWidget,
    QVBoxLayout,
    QHBoxLayout,
    QLabel,
    QSlider,
    QDoubleSpinBox,
)


class ReferenceNode(Node):
    def __init__(self):
        super().__init__('reference_gui')
        self.publisher_ = self.create_publisher(Float64, '/reference', 10)

        self.current_value = 0.0

        # 50 Hz
        self.timer = self.create_timer(0.02, self.timer_callback)

    def timer_callback(self):
        msg = Float64()
        msg.data = self.current_value
        self.publisher_.publish(msg)

    def set_value(self, value: float):
        self.current_value = value


class ReferenceGUI(QWidget):
    def __init__(self, ros_node):
        super().__init__()
        self.ros_node = ros_node
        self.scale = 1

        self.setWindowTitle("Reference GUI")
        self.resize(500, 100)

        main_layout = QVBoxLayout()
        row = QHBoxLayout()

        self.label = QLabel("reference")
        self.slider = QSlider(Qt.Horizontal)
        self.spinbox = QDoubleSpinBox()

        self.slider.setRange(-1000, 1000)
        self.spinbox.setRange(-1000.0, 1000.0)
        self.spinbox.setDecimals(0)
        self.spinbox.setSingleStep(1.0)

        row.addWidget(self.label)
        row.addWidget(self.slider)
        row.addWidget(self.spinbox)

        main_layout.addLayout(row)
        self.setLayout(main_layout)

        self.slider.valueChanged.connect(self.on_slider_changed)
        self.spinbox.valueChanged.connect(self.on_spinbox_changed)

        self.spinbox.setValue(0.0)

    def on_slider_changed(self, value):
        real_value = value / self.scale

        self.spinbox.blockSignals(True)
        self.spinbox.setValue(real_value)
        self.spinbox.blockSignals(False)

        self.ros_node.set_value(real_value)

    def on_spinbox_changed(self, value):
        int_value = int(value * self.scale)

        self.slider.blockSignals(True)
        self.slider.setValue(int_value)
        self.slider.blockSignals(False)

        self.ros_node.set_value(value)


def main(args=None):
    rclpy.init(args=args)
    ros_node = ReferenceNode()

    ros_thread = threading.Thread(target=rclpy.spin, args=(ros_node,), daemon=True)
    ros_thread.start()

    app = QApplication(sys.argv)
    gui = ReferenceGUI(ros_node)
    gui.show()
    app.exec_()

    ros_node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()