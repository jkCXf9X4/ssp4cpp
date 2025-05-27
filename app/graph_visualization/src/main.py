# main.py
# Entry point for the graph visualization application

import sys
from PyQt5.QtWidgets import QApplication
from graph_window import GraphWindow


def main():
    app = QApplication(sys.argv)
    window = GraphWindow()
    window.show()
    sys.exit(app.exec_())


if __name__ == "__main__":
    main()
