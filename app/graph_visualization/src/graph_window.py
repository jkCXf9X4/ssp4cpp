# graph_window.py
# Main window for the graph visualization application

from PyQt5.QtWidgets import QMainWindow, QWidget, QVBoxLayout, QHBoxLayout, QPushButton, QSlider, QLabel, QGraphicsView, QGraphicsScene
from PyQt5.QtCore import Qt
from graph_scene import GraphScene

class GraphWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Graph Information Propagation Visualization")
        self.resize(1000, 700)
        self._init_ui()

    def _init_ui(self):
        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        layout = QVBoxLayout(central_widget)

        # Graphics view for the graph
        self.scene = GraphScene()
        self.view = QGraphicsView(self.scene)
        layout.addWidget(self.view)

        # Controls
        controls = QHBoxLayout()
        self.start_btn = QPushButton("Start")
        self.pause_btn = QPushButton("Pause")
        self.stop_btn = QPushButton("Stop")
        self.speed_slider = QSlider(Qt.Horizontal)
        self.speed_slider.setMinimum(1)   # 0.1ms
        self.speed_slider.setMaximum(100) # 10ms
        self.speed_slider.setValue(10)    # 1.0ms default
        self.speed_label = QLabel("Interval: 1.0 ms")

        controls.addWidget(self.start_btn)
        controls.addWidget(self.pause_btn)
        controls.addWidget(self.stop_btn)
        controls.addWidget(self.speed_label)
        controls.addWidget(self.speed_slider)
        layout.addLayout(controls)

        self.speed_slider.valueChanged.connect(self._on_speed_change)
        self.start_btn.clicked.connect(self.scene.start_propagation)
        self.pause_btn.clicked.connect(self.scene.pause_propagation)
        self.stop_btn.clicked.connect(self.scene.stop_propagation)

        # Set initial interval
        self._on_speed_change(self.speed_slider.value())

    def _on_speed_change(self, value):
        interval_ms = value / 10.0  # 1 = 0.1ms, 100 = 10ms
        self.speed_label.setText(f"Interval: {interval_ms:.1f} ms")
        self.scene.set_update_interval(interval_ms / 1000.0)  # seconds
