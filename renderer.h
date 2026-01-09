void DrawLine(Vec2i start, Vec2i end, int color)
{
    int d_x = end.X - start.X;
    int d_y = end.Y - start.Y;
    if (Math.Abs(d_y) < Math.Abs(d_x)) {
        if (d_x < 0) {
            (start, end) = (end, start);
            d_x = end.X - start.X;
        }
        d_y = Math.Abs(end.Y - start.Y);
        int err = 0;
        int delta_err = 2 * d_y;
        int step = end.Y > start.Y ? 1 : -1;
        int row = start.Y * target.Width;
        int row_step = step * target.Width;
        for (int x = start.X; x <= end.X; x++) {
            target.Data[row + x] = color;
            err += delta_err;
            if (err >= d_x) {
                row += row_step;
                err -= d_x * 2;
            }
        }
    }
    else {
        if (d_y < 0) {
            (start, end) = (end, start);
            d_y = end.Y - start.Y;
        }
        d_x = Math.Abs(end.X - start.X);
        int err = 0;
        int delta_err = 2 * d_x;
        int x = start.X;
        int step = end.X > start.X ? 1 : -1;
        int row = start.Y * target.Width;
        for (int y = start.Y; y <= end.Y; y++) {
            target.Data[row + x] = color;
            err += delta_err;
            if (err >= d_y) {
                x += step;
                err -= d_y * 2;
            }
            row += target.Width;
        }
    }
}
