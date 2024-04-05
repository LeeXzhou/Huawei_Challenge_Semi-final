import tkinter as tk

mp=[("#80ff80",".","land"),
    ("#00aa00",">","landway"),
    ("#8080ff","*","sea"),
    ("#0000ff","~","seaway"),
    ("#000000","#","obstacle"),
    ("#ff0000","R","buyrobot"),
    ("#000080","S","buyship"),
    ("#808080","B","berth"),
    ("#404040","K","kaoboqu"),
    ("#80ffff","C","normalcross"),
    ("#00ffff","c","supercross"),
    ("#ff00ff","T","tradepoint")]

class GridPainter:
    def __init__(self, master):
        self.master = master
        self.master.title("Grid Painter")
        self.selected_color = "#80ff80"  # 默认选择land
        
        self.start_x = None
        self.start_y = None
        
        self.canvas_scale = 1.0  # 初始化缩放比例为1.0

        self.create_widgets()
        self.create_grid()

        # # 绑定鼠标滚轮事件
        # self.canvas.bind("<MouseWheel>", self.on_mousewheel)
        # self.canvas.bind("<Button-4>", self.on_mousewheel)  # 鼠标滚轮向上
        # self.canvas.bind("<Button-5>", self.on_mousewheel)  # 鼠标滚轮向下

        # 绑定鼠标事件
        self.canvas.bind("<Button-1>", self.on_mouse_click)
        self.canvas.bind("<B1-Motion>", self.on_mouse_drag)
        self.canvas.bind("<ButtonRelease-1>", self.on_mouse_release)

    def create_widgets(self):
        self.canvas = tk.Canvas(self.master, width=1000, height=1000)
        self.canvas.pack()
        
        
            
        self.color_frame = tk.Frame(self.master)
        self.color_frame.pack(side=tk.BOTTOM, pady=10)
        for code,char,name in mp:
            button = tk.Button(self.color_frame, text=name, command=lambda c=code: self.select_color(c))
            button.pack(side=tk.LEFT, padx=10)

        # self.draw_button = tk.Button(self.color_frame, text="Draw Mode", command=self.toggle_draw_mode)
        # self.draw_button.pack(side=tk.LEFT, padx=10)

        self.save_button = tk.Button(self.color_frame, text="Save Map", command=self.save_map)
        self.save_button.pack(side=tk.LEFT, padx=10)

    def create_grid(self):
        self.grid = [[None for _ in range(200)] for _ in range(200)]

        cell_size = 5
        for i in range(200):
            for j in range(200):
                x1, y1 = j * cell_size, i * cell_size
                x2, y2 = x1 + cell_size, y1 + cell_size
                cell = self.canvas.create_rectangle(x1, y1, x2, y2, fill="#80ff80", outline="black")
                self.grid[i][j] = cell

    def select_color(self, color):
        self.selected_color = color

    def paint_cell(self, i, j):
        cell = self.grid[i][j]
        self.canvas.itemconfig(cell, fill=self.selected_color)

    def on_mousewheel(self, event):
        scale_factor = 0.9 if event.delta < 0 else 1.1  # 根据滚轮滚动方向选择缩放比例
        self.canvas_scale *= scale_factor  # 更新缩放比例

        # 使用缩放比例重新调整画布大小
        new_width = int(self.canvas.winfo_width() * scale_factor)
        new_height = int(self.canvas.winfo_height() * scale_factor)
        self.canvas.config(width=new_width, height=new_height)

        # 对画布上的所有对象进行缩放
        self.canvas.scale("all", 0, 0, scale_factor, scale_factor)

    def on_mouse_click(self, event):
        self.start_x = event.x
        self.start_y = event.y

    def on_mouse_drag(self, event):
        if self.start_x is not None and self.start_y is not None:
            x1, y1 = self.start_x, self.start_y
            x2, y2 = event.x, event.y
            self.canvas.delete("draw_rectangle")  # 删除之前的矩形
            self.canvas.create_rectangle(x1, y1, x2, y2, outline="black", tags="draw_rectangle")

    def on_mouse_release(self, event):
        if  self.start_x is not None and self.start_y is not None:
            x1, y1 = self.start_x, self.start_y
            x2, y2 = event.x, event.y
            self.canvas.delete("draw_rectangle")  # 删除绘制的矩形

            # 将矩形区域内的单元格染色
            for i in range(max(0,min(y1, y2) // 5), min(200,max(y1, y2) // 5 + 1)):
                for j in range(max(0,min(x1, x2) // 5),min(200, max(x1, x2) // 5 + 1)):
                    self.paint_cell(i, j)

            # 清除绘制模式的起始坐标
            self.start_x = None
            self.start_y = None

    def toggle_draw_mode(self):
        self.draw_mode = not self.draw_mode

    def save_map(self):
        with open("map.txt", "w") as f:
            for row in self.grid:
                for cell in row:
                    color = self.canvas.itemcget(cell, "fill")
                    for cc,char,name in mp:
                        if color==cc:
                            f.write(char)
                f.write("\n")

def main():
    root = tk.Tk()
    app = GridPainter(root)
    root.mainloop()

if __name__ == "__main__":
    main()
