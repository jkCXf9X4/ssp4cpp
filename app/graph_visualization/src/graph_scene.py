# graph_scene.py
# Handles graph visualization and information propagation animation

from PyQt5.QtWidgets import QGraphicsScene, QGraphicsEllipseItem, QGraphicsTextItem, QGraphicsLineItem, QGraphicsRectItem
from PyQt5.QtCore import QTimer, QPointF, Qt
import networkx as nx
import pydot

class InformationMarker:
    def __init__(self, scene, node, node_item, node_delay, path=None, color=Qt.red):
        self.scene = scene
        self.node = node
        self.node_item = node_item
        self.node_delay = node_delay
        self.node_elapsed = 0.0
        self.progress = 0.0
        self.path = path or [node]
        self.state = 'at_node'
        self.periodic_ready = False
        self.edge_dot = None
        self.edge_delay = None
        self.edge_elapsed = 0.0
        self.from_node = None
        self.to_node = None
        x, y, w, h = self._get_rect()
        self.item = QGraphicsEllipseItem(x, y, w, h)
        self.item.setBrush(color)
        self.item.setZValue(2)
        self.scene.addItem(self.item)

    def _get_rect(self):
        rect = self.node_item.rect()
        x = rect.left()
        y = rect.center().y() - 5
        return x-5, y, 10, 10

    def update_at_node(self, dt):
        self.node_elapsed += dt
        rect = self.node_item.rect()
        progress = min(self.node_elapsed / self.node_delay, 1.0) if self.node_delay > 0 else 1.0
        x = rect.left() + (rect.width() - 10) * progress
        y = rect.center().y() - 5
        self.item.setRect(x, y, 10, 10)
        self.progress = progress

    def ready_to_pass(self, is_sensor, is_periodic_model):
        if is_sensor:
            return self.node_elapsed >= self.node_delay
        elif is_periodic_model:
            return self.node_elapsed >= self.node_delay and self.periodic_ready
        else:
            return self.node_elapsed >= self.node_delay

    def start_edge(self, from_node, to_node, edge_delay, pos, color=Qt.blue):
        self.state = 'on_edge'
        self.from_node = from_node
        self.to_node = to_node
        self.edge_delay = edge_delay
        self.edge_elapsed = 0.0
        self.progress = 0.0
        self.item.setBrush(color)
        self.path = self.path + [to_node]
        self._update_edge_position(pos)

    def update_on_edge(self, dt, pos):
        self.edge_elapsed += dt
        if self.edge_delay > 0:
            self.progress = min(self.edge_elapsed / self.edge_delay, 1.0)
        else:
            self.progress = 1.0
        self._update_edge_position(pos)

    def _update_edge_position(self, pos):
        p1 = QPointF(*pos[self.from_node])
        p2 = QPointF(*pos[self.to_node])
        x = p1.x() + (p2.x() - p1.x()) * self.progress
        y = p1.y() + (p2.y() - p1.y()) * self.progress
        self.item.setRect(x-7, y-7, 14, 14)
        # Draw a small dot on the edge to show propagation
        if self.edge_dot:
            self.scene.removeItem(self.edge_dot)
        self.edge_dot = QGraphicsEllipseItem(x-4, y-4, 8, 8)
        self.edge_dot.setBrush(Qt.green)
        self.edge_dot.setZValue(2)
        self.scene.addItem(self.edge_dot)

    def arrive_at_node(self, node, node_item, node_delay):
        self.state = 'at_node'
        self.node = node
        self.node_item = node_item
        self.node_delay = node_delay
        self.node_elapsed = 0.0
        if self.edge_dot:
            self.scene.removeItem(self.edge_dot)
            self.edge_dot = None
        self.from_node = None
        self.to_node = None
        self.edge_delay = None
        self.edge_elapsed = 0.0
        self.item.setRect(*self._get_rect())

    def remove(self):
        self.scene.removeItem(self.item)
        if self.edge_dot:
            self.scene.removeItem(self.edge_dot)
            self.edge_dot = None

class GraphScene(QGraphicsScene):
    def __init__(self):
        super().__init__()
        self.graph = self._load_graph()
        self.node_items = {}
        self.edge_items = {}
        self.markers = []
        self.update_interval = 0.001  # default 1ms
        self.timer = QTimer()
        self.timer.timeout.connect(self._update_propagation)
        self._draw_graph()
        self.running = False

    def set_update_interval(self, interval):
        self.update_interval = interval
        if self.timer.isActive():
            self.timer.stop()
            self.timer.start(int(self.update_interval * 1000))

    def _load_graph(self):
        import os
        dot_path = os.path.abspath(os.path.join(os.path.dirname(__file__), '../graph.dot'))
        graphs = pydot.graph_from_dot_file(dot_path)
        pydot_graph = graphs[0]
        G = nx.DiGraph()
        # Add nodes
        for node in pydot_graph.get_nodes():
            name = node.get_name().strip('"')
            if name == '' or name == 'node':
                continue
            G.add_node(name, **node.get_attributes())
        # Add edges
        for edge in pydot_graph.get_edges():
            src = edge.get_source().strip('"')
            dst = edge.get_destination().strip('"')
            G.add_edge(src, dst, **edge.get_attributes())
        return G

    def _draw_graph(self):
        self.clear()
        pos = nx.nx_pydot.graphviz_layout(self.graph, prog="dot")
        self.pos = pos  # Save for later use
        # Draw edges
        for u, v, data in self.graph.edges(data=True):
            p1 = QPointF(*pos[u])
            p2 = QPointF(*pos[v])
            edge = QGraphicsLineItem(p1.x(), p1.y(), p2.x(), p2.y())
            edge.setZValue(-1)
            self.addItem(edge)
            self.edge_items[(u, v)] = edge
        # Draw nodes as rectangles
        for n, data in self.graph.nodes(data=True):
            x, y = pos[n]
            node = QGraphicsRectItem(x-35, y-20, 70, 40)
            node.setBrush(Qt.white)
            node.setZValue(1)
            self.addItem(node)
            # Place the label above the rectangle
            label = QGraphicsTextItem(n)
            label_rect = label.boundingRect()
            label_x = x - label_rect.width() / 2
            label_y = y - 20 - label_rect.height() - 4  # 4px gap above box
            label.setPos(label_x, label_y)
            self.addItem(label)
            self.node_items[n] = node
        # Set the scene rect to fit all items
        self.setSceneRect(self.itemsBoundingRect())

    def _get_node_delay(self, node):
        # Try to extract 'd' from label, fallback to 0.0
        label = self.graph.nodes[node].get('label', '')
        if 'd =' in label:
            try:
                d_str = label.split('d =')[1].split('|')[0].split('}')[0].strip()
                return float(d_str)
            except Exception:
                return 0.0
        return 0.0

    def _get_edge_delay(self, u, v):
        label = self.graph.edges[u, v].get('label', '')
        if 'd =' in label:
            try:
                d_str = label.split('d =')[1].split('|')[0].split('}')[0].split()[0].strip().replace('"', '')
                return float(d_str)
            except Exception as e:
                print(f"Edge delay parse error for {u}->{v}: {label} ({e})")
                return 0.0
        return 0.0

    def _get_node_frequency(self, node):
        # Try to extract 'f' from label, fallback to None
        label = self.graph.nodes[node].get('label', '')
        if 'f =' in label:
            try:
                f_str = label.split('f =')[1].split('|')[0].split('}')[0].strip()
                return float(f_str)
            except Exception:
                return None
        return None

    def _is_sensor(self, node):
        # Sensors are nodes with in-degree 0 and have frequency
        return self.graph.in_degree(node) == 0 and self._get_node_frequency(node) is not None

    def _is_periodic_model(self, node):
        # Models with a frequency defined (not just sensors)
        return self._get_node_frequency(node) is not None

    def start_propagation(self):
        if not self.running:
            self.running = True
            self.model_timers = {}
            self.sensor_timers = {}
            # Set up timers for each sensor node with frequency
            for n in self.graph.nodes:
                if self._is_sensor(n):
                    freq = self._get_node_frequency(n)
                    if freq and freq > 0:
                        interval_ms = int(1000 / freq)
                        timer = QTimer()
                        timer.timeout.connect(lambda n=n: self._spawn_marker(n))
                        timer.start(interval_ms)
                        self.sensor_timers[n] = timer
            # Set up timers for each non-sensor node with frequency (periodic models)
            for n in self.graph.nodes:
                if self._is_periodic_model(n) and not self._is_sensor(n):
                    freq = self._get_node_frequency(n)
                    if freq and freq > 0:
                        interval_ms = int(1000 / freq)
                        timer = QTimer()
                        timer.timeout.connect(lambda n=n: self._schedule_periodic_pass(n))
                        timer.start(interval_ms)
                        self.model_timers[n] = timer
            self.timer.start(int(self.update_interval * 1000))

    def pause_propagation(self):
        self.timer.stop()
        self.running = False

    def stop_propagation(self):
        self.timer.stop()
        self.running = False
        for marker in self.markers:
            marker.remove()
        self.markers.clear()
        # Stop all model timers
        if hasattr(self, 'model_timers'):
            for t in self.model_timers.values():
                t.stop()
            self.model_timers.clear()
        # Stop all sensor timers
        if hasattr(self, 'sensor_timers'):
            for t in self.sensor_timers.values():
                t.stop()
            self.sensor_timers.clear()

    def set_speed(self, value):
        self.speed = value

    def _spawn_marker(self, node=None):
        # If node is None, spawn for all sensors
        if node is None:
            for n in self.graph.nodes:
                if self._is_sensor(n):
                    self._spawn_marker(n)
            return
        node_item = self.node_items[node]
        node_delay = self._get_node_delay(node)
        marker = InformationMarker(self, node, node_item, node_delay)
        self.markers.append(marker)

    def _schedule_periodic_pass(self, node):
        for marker in self.markers:
            if marker.state == 'at_node' and marker.node == node and not marker.periodic_ready:
                marker.periodic_ready = True

    def _update_propagation(self):
        dt = self.update_interval
        new_markers = []
        for marker in list(self.markers):
            if marker.state == 'at_node':
                marker.update_at_node(dt)
                is_sensor = self._is_sensor(marker.node)
                is_periodic = self._is_periodic_model(marker.node)
                ready = marker.ready_to_pass(is_sensor, is_periodic)
                if ready:
                    out_edges = list(self.graph.successors(marker.node))
                    if not out_edges:
                        # Remove marker if at end node
                        marker.remove()
                        self.markers.remove(marker)
                        continue
                    for succ in out_edges:
                        edge_delay = self._get_edge_delay(marker.node, succ)
                        print(f"Spawning edge marker: {marker.node} -> {succ}, edge_delay={edge_delay}")
                        new_marker = InformationMarker(self, marker.node, marker.node_item, marker.node_delay, path=marker.path, color=Qt.blue)
                        new_marker.start_edge(marker.node, succ, edge_delay, self.pos)
                        new_markers.append(new_marker)
                    marker.remove()
                    self.markers.remove(marker)
                if marker.periodic_ready and ready:
                    marker.periodic_ready = False
            elif marker.state == 'on_edge':
                marker.update_on_edge(dt, self.pos)
                if marker.progress >= 1.0:
                    to_node = marker.to_node
                    node_item = self.node_items[to_node]
                    node_delay = self._get_node_delay(to_node)
                    marker.arrive_at_node(to_node, node_item, node_delay)
        self.markers.extend(new_markers)
